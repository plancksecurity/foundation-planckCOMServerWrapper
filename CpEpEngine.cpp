// CpEpEngine.cpp : Implementation of CpEpEngine

#include "stdafx.h"
#include "CpEpEngine.h"

using namespace std;
using namespace pEp::utility;

// CpEpEngine

STDMETHODIMP CpEpEngine::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* const arr[] =
	{
		&IID_IpEpEngine
	};

	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i], riid))
			return S_OK;
	}
	return S_FALSE;
}

#define FAIL(msg) error(msg)

STDMETHODIMP CpEpEngine::VerboseLogging(VARIANT_BOOL enable)
{
	verbose_mode = enable != VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CpEpEngine::PassiveMode(VARIANT_BOOL enable)
{
	::config_passive_mode(get_session(), enable != VARIANT_FALSE);
	return S_OK;
}

STDMETHODIMP CpEpEngine::UnencryptedSubject(VARIANT_BOOL enable)
{
	::config_unencrypted_subject(get_session(), enable != VARIANT_FALSE);
	return S_OK;
}

STDMETHODIMP CpEpEngine::ExportKey(BSTR fpr, BSTR * keyData)
{
    assert(fpr);
    assert(keyData);

    if (fpr == NULL || keyData == NULL)
        return E_INVALIDARG;

    string _fpr = utf8_string(fpr);
    char *_key_data = NULL;
    size_t _size = 0;

    ::PEP_STATUS status = ::export_key(get_session(), _fpr.c_str(), &_key_data, &_size);
    assert(status != ::PEP_OUT_OF_MEMORY);
    if (status == ::PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    if (status != ::PEP_STATUS_OK)
        return FAIL(L"export_key");

    _bstr_t b_key_data(utf16_string(_key_data).c_str());
    pEp_free(_key_data);
    * keyData = b_key_data.Detach();

    return S_OK;
}

STDMETHODIMP CpEpEngine::Log(BSTR title, BSTR entity, BSTR description, BSTR comment)
{
	string _title;
	string _entity;
	string _description;
	string _comment;
	HRESULT result = S_OK;

	assert(title);
	if (title)
		_title = utf8_string(title);
	else
		result = E_INVALIDARG;

	assert(entity);
	if (entity)
		_entity = utf8_string(entity);
	else
		result = E_INVALIDARG;

	if (description)
		_description = utf8_string(description);

	if (comment)
		_comment = utf8_string(comment);

	if (result != S_OK)
		return result;

	PEP_STATUS _status = ::log_event(get_session(), _title.c_str(), _entity.c_str(), _description.c_str(), _comment.c_str());
	assert(_status == PEP_STATUS_OK);
	if (_status != PEP_STATUS_OK)
		return FAIL(L"log_event");
	else
		return S_OK;
}

STDMETHODIMP CpEpEngine::TrustWords(BSTR fpr, BSTR lang, LONG max_words, BSTR * words)
{
	assert(fpr);
	assert(max_words >= 0);
	assert(words);

	HRESULT result = S_OK;

	string _fpr;
	if (fpr)
		_fpr = utf8_string(fpr);
	else
		result = E_INVALIDARG;

	string _lang;
	if (lang) {
		_lang = utf8_string(lang);
		if (_lang.length()) {
			if (_lang.length() != 2)
				result = E_INVALIDARG;
		}
		else
			_lang = "en";
	}
	else
		_lang = "en";

	if (max_words < 0)
		result = E_INVALIDARG;

	if (words == NULL)
		result = E_INVALIDARG;

	if (result != S_OK)
		return result;

	char *_words = NULL;
	size_t _wsize = 0;

	PEP_STATUS status = ::trustwords(get_session(), _fpr.c_str(), _lang.c_str(), &_words, &_wsize, max_words);
	assert(status != PEP_OUT_OF_MEMORY);
	if (status == PEP_OUT_OF_MEMORY)
		return E_OUTOFMEMORY;

	if (_words == NULL) {
		*words = NULL;
		return FAIL(L"TrustWords");
	}
	else {
		*words = utf16_bstr(_words);
		pEp_free(_words);
		return S_OK;
	}
}

STDMETHODIMP CpEpEngine::GetCrashdumpLog(LONG maxlines, BSTR * log)
{
	assert(maxlines >= 0);
	assert(log);

	if (!(maxlines >= 0 && log))
		return E_INVALIDARG;

	char *_log;
	PEP_STATUS status = ::get_crashdump_log(get_session(), (int)maxlines, &_log);
	assert(status == PEP_STATUS_OK);
	if (status == PEP_OUT_OF_MEMORY)
		return E_OUTOFMEMORY;
	if (status != PEP_STATUS_OK || _log == NULL)
		return FAIL(L"GetCrashdumpLog");

	*log = utf16_bstr(_log);
	pEp_free(_log);
	return S_OK;
}

STDMETHODIMP CpEpEngine::GetEngineVersion(BSTR * engine_version)
{
	assert(engine_version);

	if (!engine_version)
		return E_INVALIDARG;

	const char *_engine_version = ::get_engine_version();

	if (_engine_version == NULL)
		return FAIL(L"GetEngineVersion");

	*engine_version = utf16_bstr(_engine_version);

	return S_OK;
}

STDMETHODIMP CpEpEngine::GetLanguageList(BSTR * languages)
{
	assert(languages);

	if (!languages)
		return E_INVALIDARG;

	char *_languages;
	PEP_STATUS status = ::get_languagelist(get_session(), &_languages);
	assert(status == PEP_STATUS_OK);
	if (status == PEP_OUT_OF_MEMORY)
		return E_OUTOFMEMORY;
	if (status != PEP_STATUS_OK || _languages == NULL)
		return FAIL(L"GetLanguageList");

	*languages = utf16_bstr(_languages);
	pEp_free(_languages);
	return S_OK;
}

STDMETHODIMP CpEpEngine::StartKeyserverLookup()
{
	if (identity_queue.load())
		return S_OK;

	identity_queue.store(new identity_queue_t());
	keymanagement_thread = new thread(::do_keymanagement, retrieve_next_identity, (void *)identity_queue.load());

	return S_OK;
}

STDMETHODIMP CpEpEngine::StopKeyserverLookup()
{
	if (identity_queue.load() == NULL)
		return S_OK;

	identity_queue_t *_iq = identity_queue.load();
	identity_queue.store(NULL);

	pEp_identity_cpp shutdown;
	_iq->push_front(shutdown);

	keymanagement_thread->join();
	delete keymanagement_thread;
	keymanagement_thread = NULL;

	delete _iq;

	return S_OK;
}

STDMETHODIMP CpEpEngine::Myself(struct pEpIdentity *ident, struct pEpIdentity *result)
{
	assert(ident);
	assert(result);

	if (ident == NULL || result == NULL)
		return E_INVALIDARG;

	::pEp_identity *_ident = new_identity(ident);
	assert(_ident);
	if (_ident == NULL)
		return E_OUTOFMEMORY;

	// DEBUG CODE - REMOVE BEFORE RELEASE!
	// SyncHandshakeResult handshakeResult;
	//
	// HRESULT res = Fire_ShowHandshake(ident, result, &handshakeResult);
	// 
	// HRESULT res2 = Fire_TestEvent(15, _bstr_t( "hallo"));

	PEP_STATUS status = ::myself(get_session(), _ident);

	if (status == PEP_STATUS_OK) {
		assert(_ident->fpr);
		copy_identity(result, _ident);
		::free_identity(_ident);
		return S_OK;
	}
	else {
		::free_identity(_ident);
		if (status == PEP_OUT_OF_MEMORY)
			return E_OUTOFMEMORY;
		else
			return FAIL(L"myself");
	}
}

STDMETHODIMP CpEpEngine::UpdateIdentity(struct pEpIdentity *ident, struct pEpIdentity *result)
{
	assert(ident);
	assert(result);

	if (ident == NULL || result == NULL)
		return E_INVALIDARG;

	::pEp_identity *_ident = new_identity(ident);
	assert(_ident);
	if (_ident == NULL)
		return E_OUTOFMEMORY;

	PEP_STATUS status = ::update_identity(get_session(), _ident);

	if (status == PEP_STATUS_OK) {
		assert(_ident->fpr);
		copy_identity(result, _ident);
		::free_identity(_ident);
		return S_OK;
	}
	else {
		::free_identity(_ident);
		if (status == PEP_OUT_OF_MEMORY)
			return E_OUTOFMEMORY;
		else
			return FAIL(L"UpdateIdentity");
	}
}

STDMETHODIMP CpEpEngine::KeyMistrusted(struct pEpIdentity *ident)
{
	::pEp_identity *_ident;

	assert(ident);

	try {
		_ident = new_identity(ident);
	}
	catch (bad_alloc&) {
		return E_OUTOFMEMORY;
	}
	catch (exception&) {
		return E_FAIL;
	}

	PEP_STATUS status = ::key_mistrusted(get_session(), _ident);
	free_identity(_ident);

	if (status == PEP_OUT_OF_MEMORY)
		return E_OUTOFMEMORY;

	if (status == PEP_KEY_NOT_FOUND)
		return FAIL(L"key not found");

	if (status != ::PEP_STATUS_OK)
		return FAIL(L"cannot revoke compromized key");

	return S_OK;
}

STDMETHODIMP CpEpEngine::KeyResetTrust(struct pEpIdentity *ident)
{
	::pEp_identity *_ident;

	assert(ident);

	try {
		_ident = new_identity(ident);
	}
	catch (bad_alloc&) {
		return E_OUTOFMEMORY;
	}
	catch (exception&) {
		return E_FAIL;
	}

	PEP_STATUS status = ::key_reset_trust(get_session(), _ident);
	free_identity(_ident);

	if (status == PEP_OUT_OF_MEMORY)
		return E_OUTOFMEMORY;

	if (status == PEP_KEY_NOT_FOUND)
		return FAIL(L"key not found");

	if (status != ::PEP_STATUS_OK)
		return FAIL(L"cannot reset trust");

	return S_OK;
}

int CpEpEngine::examine_identity(pEp_identity *ident, void *management)
{
	assert(ident);
	assert(management);
	if (!(ident && management))
		return -1;

	CpEpEngine *me = (CpEpEngine *)management;

	if (me->identity_queue.load() == NULL)
		return 0;

	try {
		me->identity_queue.load()->push_back(ident);
	}
	catch (exception&) {
		return -1;
	}

	return 0;
}

::pEp_identity * CpEpEngine::retrieve_next_identity(void *management)
{
	assert(management);
	identity_queue_t *iq = (identity_queue_t *)management;

	do /* poll queue */ {
		if (iq->size())
			break;
		::Sleep(100);
	} while (true);

	::pEp_identity *_ident;
	pEp_identity_cpp& ident = iq->front();

	if (ident.address.size() == 0)
		return NULL;

	_ident = ident.to_pEp_identity();
	iq->pop_front();

	return _ident;
}

PEP_STATUS CpEpEngine::messageToSend(void * obj, message *msg)
{
	assert(msg);
	if (msg == NULL)
		return PEP_ILLEGAL_VALUE;

	TextMessage _msg;
	memset(&_msg, 0, sizeof(TextMessage));

	text_message_from_C(&_msg, msg);
	CpEpEngine *me = (CpEpEngine *)obj;
	HRESULT r = me->Fire_MessageToSend(&_msg);
	assert(r == S_OK);
	clear_text_message(&_msg);
	if (r == E_OUTOFMEMORY)
		return PEP_OUT_OF_MEMORY;
	if (r != S_OK)
		return PEP_UNKNOWN_ERROR;

	return PEP_STATUS_OK;
}

PEP_STATUS CpEpEngine::showHandshake(void * obj, pEp_identity *self, pEp_identity *partner)
{
	assert(self && partner);
	if (!(self && partner))
		return PEP_ILLEGAL_VALUE;

	pEpIdentity _self;
	copy_identity(&_self, self);
	pEpIdentity _partner;
	copy_identity(&_partner, partner);
	CpEpEngine *me = (CpEpEngine *)obj;
	SyncHandshakeResult _result;
	HRESULT r = me->Fire_ShowHandshake(&_self, &_partner, &_result);
	assert(r == S_OK);
	clear_identity_s(_self);
	clear_identity_s(_partner);
	if (r == E_OUTOFMEMORY)
		return PEP_OUT_OF_MEMORY;
	if (r != S_OK)
		return PEP_UNKNOWN_ERROR;

	PEP_STATUS status = deliverHandshakeResult(me->get_session(), partner, (sync_handshake_result)(int)_result);
	return status;
}

STDMETHODIMP CpEpEngine::BlacklistAdd(BSTR fpr)
{
	assert(fpr);

	string _fpr = utf8_string(fpr);
	PEP_STATUS status = ::blacklist_add(get_session(), _fpr.c_str());
	assert(status == PEP_STATUS_OK);
	if (status != PEP_STATUS_OK)
		return FAIL(L"blacklist_add failed in pEp engine");

	return S_OK;
}

STDMETHODIMP CpEpEngine::BlacklistDelete(BSTR fpr)
{
	assert(fpr);

	string _fpr = utf8_string(fpr);
	PEP_STATUS status = ::blacklist_delete(get_session(), _fpr.c_str());
	assert(status == PEP_STATUS_OK);
	if (status != PEP_STATUS_OK)
		return FAIL(L"blacklist_delete failed in pEp engine");

	return S_OK;
}

STDMETHODIMP CpEpEngine::BlacklistIsListed(BSTR fpr, VARIANT_BOOL *listed)
{
	assert(fpr);
	assert(listed);

	string _fpr = utf8_string(fpr);
	bool result;
	PEP_STATUS status = ::blacklist_is_listed(get_session(), _fpr.c_str(), &result);
	assert(status == PEP_STATUS_OK);
	if (status != PEP_STATUS_OK)
		return FAIL(L"blacklist_is_listed failed in pEp engine");

	*listed = result ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CpEpEngine::BlacklistRetrieve(SAFEARRAY **blacklist)
{
	assert(blacklist);

	::stringlist_t *_blacklist = NULL;
	PEP_STATUS status = ::blacklist_retrieve(get_session(), &_blacklist);
	assert(status == PEP_STATUS_OK);
	if (status != PEP_STATUS_OK)
		return FAIL(L"blacklist_retrieve failed in pEp engine");
	assert(_blacklist);

	*blacklist = string_array(_blacklist);
	return S_OK;
}

HRESULT CpEpEngine::error(_bstr_t msg)
{
	_bstr_t helpFile = L"";
	_bstr_t source = L"pEp COM Adapter";

	ICreateErrorInfo *cei;
	if (SUCCEEDED(CreateErrorInfo(&cei))) {
		cei->SetDescription(msg);
		cei->SetGUID(__uuidof(IpEpEngine));
		cei->SetHelpContext(0);
		cei->SetHelpFile(helpFile);
		cei->SetSource(source);

		IErrorInfo *errinfo;
		if (SUCCEEDED(cei->QueryInterface(IID_IErrorInfo, (LPVOID FAR*) &errinfo))) {
			SetErrorInfo(0, errinfo);
			errinfo->Release();
		}
		cei->Release();
	}
	return E_FAIL;
}

STDMETHODIMP CpEpEngine::EncryptMessage(TextMessage * src, TextMessage * dst, SAFEARRAY * extra, pEpEncryptFlags flags)
{
	assert(src);
	assert(dst);

	::message *_src = text_message_to_C(src);
	::message *msg_dst;
	::stringlist_t *_extra = new_stringlist(extra);

	// _PEP_enc_format is intentionally hardcoded to PEP_enc_PEP:
	// 2016-10-02 14:10 < fdik> schabi: actually, all adapters now must use PEP_enc_PEP
	PEP_encrypt_flags_t engineFlags = (PEP_encrypt_flags_t) flags;
	PEP_STATUS status = ::encrypt_message(get_session(), _src, _extra, &msg_dst, PEP_enc_PEP, engineFlags);
	::free_stringlist(_extra);

	if (status == PEP_STATUS_OK)
		text_message_from_C(dst, msg_dst);
	else
		text_message_from_C(dst, _src);

	::free_message(msg_dst);
	::free_message(_src);

	if (status == PEP_OUT_OF_MEMORY)
		return E_OUTOFMEMORY;

	return S_OK;
}

STDMETHODIMP CpEpEngine::DecryptMessage(TextMessage * src, TextMessage * dst, SAFEARRAY ** keylist, pEpDecryptFlags *flags, pEpRating *rating)
{
	assert(src);
	assert(dst);
	assert(keylist);
	assert(rating);

	*keylist = NULL;
	*rating = pEpRatingUndefined;

	::message *_src = text_message_to_C(src);
	::message *msg_dst = NULL;
	::stringlist_t *_keylist;
	::PEP_rating _rating;

	PEP_decrypt_flags_t engineflags = 0;
	PEP_STATUS status = ::decrypt_message(get_session(), _src, &msg_dst, &_keylist, &_rating, &engineflags);

	*flags = (pEpDecryptFlags)engineflags;

	if (msg_dst)
		text_message_from_C(dst, msg_dst);

	::free_message(_src);
	::free_message(msg_dst);

	if (_keylist) {
		*keylist = string_array(_keylist);
		free_stringlist(_keylist);
	}

	*rating = (pEpRating)_rating;

	return S_OK;
}

STDMETHODIMP CpEpEngine::OutgoingMessageRating(TextMessage *msg, pEpRating * pVal)
{
	assert(msg);
	assert(pVal);

	::message *_msg = text_message_to_C(msg);

	PEP_rating _rating;
	PEP_STATUS status = ::outgoing_message_rating(get_session(), _msg, &_rating);
	if (status != PEP_STATUS_OK)
		return FAIL(L"cannot get message rating");

	*pVal = (pEpRating)_rating;
	return S_OK;
}

STDMETHODIMP CpEpEngine::IdentityRating(struct pEpIdentity *ident, pEpRating * pVal)
{
	::pEp_identity *_ident;

	assert(ident);
	assert(pVal);

	try {
		_ident = new_identity(ident);
	}
	catch (bad_alloc&) {
		return E_OUTOFMEMORY;
	}
	catch (exception&) {
		return E_FAIL;
	}

	PEP_rating _rating;
	PEP_STATUS status = ::identity_rating(get_session(), _ident, &_rating);
	free_identity(_ident);
	if (status != PEP_STATUS_OK)
		return FAIL(L"cannot get message color");

	*pVal = (pEpRating)_rating;
	return S_OK;
}

STDMETHODIMP CpEpEngine::ColorFromRating(pEpRating rating, pEpColor * pVal)
{
	assert(pVal);

	PEP_rating engineRating = (PEP_rating)rating;
	PEP_color _color = ::color_from_rating(engineRating);

	*pVal = (pEpColor)_color;

	return S_OK;
}

STDMETHODIMP CpEpEngine::TrustPersonalKey(struct pEpIdentity *ident, struct pEpIdentity *result)
{
	::pEp_identity *_ident;

	assert(ident);
	assert(result);

	try {
		_ident = new_identity(ident);
	}
	catch (bad_alloc&) {
		return E_OUTOFMEMORY;
	}
	catch (exception&) {
		return E_FAIL;
	}

	if (verbose_mode) {
		stringstream ss;
		ss << "TrustPersonalKey called with ";
		ss << utf8_string(ident->Address);
		ss << L": ";
		ss << ident->CommType;
		verbose(ss.str());
	}

	PEP_STATUS status = ::trust_personal_key(get_session(), _ident);

	if (verbose_mode) {
		stringstream ss;
		ss << "result ";
		ss << status;
		ss << " for ";
		ss << _ident->address;
		ss << L": ";
		ss << _ident->comm_type;
		verbose(ss.str());
	}

	if (status == PEP_STATUS_OK)
		copy_identity(result, _ident);

	free_identity(_ident);
	if (status == PEP_OUT_OF_MEMORY)
		return E_OUTOFMEMORY;
	else if (status != PEP_STATUS_OK)
		return FAIL(L"failure while executing TrustPersonalKey()");

	return S_OK;
}

// keysync api

void CpEpEngine::start_keysync()
{
	// acquire the lock
	std::unique_lock<std::mutex> lock(keysync_mutex);

	// Check if we're already running.
	if (keysync_thread_running) 
	{
		// If we have pending aborts, we need to wake up those threads
		// and cancel the pending abort.
		if (keysync_abort_requested) 
		{
			keysync_abort_requested = false;
			keysync_condition.notify_all();
		}
		return;
	}

	// Ensure we are not aborting the new thread due to a
	// left over flag.
	keysync_abort_requested = false;

	// Init our keysync session
	PEP_STATUS status = ::init(&keysync_session);
	::register_sync_callbacks(keysync_session, (void*)this, messageToSend, showHandshake, inject_sync_msg, retrieve_next_sync_msg);
	assert(status == PEP_STATUS_OK);

    attach_sync_session(get_session(), keysync_session);

	// Star the keysync thread
	keysync_thread = new thread(::do_sync_protocol, keysync_session, this);

	// flag to signal we're running
	keysync_thread_running = true;
}

void CpEpEngine::stop_keysync()
{
	// acquire the lock
	std::unique_lock<std::mutex> lock(keysync_mutex);

	// check whether we're not running, or there's a concurrent abort
	if (keysync_abort_requested || !keysync_thread_running)
		return;

	// signal that we're gonna abort
	keysync_abort_requested = true;

	// Notify the keysync thread
	keysync_condition.notify_all();

	// Wait for the other thread to finish and clean up
	while (keysync_thread_running && keysync_abort_requested)
		keysync_condition.wait(lock);

	if (!keysync_abort_requested)
		return; // someone called start_keysync() while we were trying to stop it...

    detach_sync_session(get_session());

	// wait for the thread to end
	keysync_thread->join();

	// clean up
	delete keysync_thread;
	keysync_thread = NULL;
	::unregister_sync_callbacks(keysync_session);
	release(keysync_session);
    keysync_session = NULL;
	keysync_abort_requested = false;
}

int CpEpEngine::inject_sync_msg(void * msg, void * management)
{
	// check argument
	if (!msg)
		return E_INVALIDARG;
	if (!management)
		return ERROR_INVALID_HANDLE;

	CpEpEngine* me = (CpEpEngine*)management;

	// acquire the lock
	std::unique_lock<std::mutex> lock(me->keysync_mutex);

	// check whether we're running:
	if (me->keysync_abort_requested || !me->keysync_thread_running)
		return E_ASYNC_OPERATION_NOT_STARTED;

	// queue the message
	me->keysync_queue.push(msg);

	// notify the receivers
	me->keysync_condition.notify_all();

    return S_OK;
}

void * CpEpEngine::retrieve_next_sync_msg(void * management)
{
	// sanity check
	assert(management);

	CpEpEngine* me = (CpEpEngine*)management;

	// acquire the lock
	std::unique_lock<std::mutex> lock(me->keysync_mutex);

	// as long as we're supposed to be active 
	// (we won't wait for the queue to empty currently...)
	while (!me->keysync_abort_requested)
	{
		// If the queue is empty, wait for a signal, and try again.
		if (me->keysync_queue.empty())
		{
			me->keysync_condition.wait(lock);
			continue;
		}

		// Pop the message and return it.
		void* msg = me->keysync_queue.front();
		assert(msg);

		me->keysync_queue.pop();

		return msg;
	}

	// we acknowledge that we're quitting...
	me->keysync_thread_running = false;

	// We signal the main thread that we got his signal
	// so it can gain the mutex again and call join() on us.
	me->keysync_condition.notify_all();

	// and tell the pep engine we're done.
	return NULL;
}


// Event callbacks

STDMETHODIMP CpEpEngine::RegisterCallbacks(IpEpEngineCallbacks* new_callbacks)
{
	callbacks cbs = get_callbacks();
	vector<IpEpEngineCallbacks*>& vec = cbs;

	vec.push_back(new_callbacks);
	new_callbacks->AddRef();
	start_keysync();

	return S_OK;
}

STDMETHODIMP CpEpEngine::UnregisterCallbacks(IpEpEngineCallbacks* obsolete_callbacks)
{
	callbacks cbs = get_callbacks();
	vector<IpEpEngineCallbacks*>& vec = cbs;

	auto position = std::find(vec.begin(), vec.end(), obsolete_callbacks);
	if (position != vec.end()) {
		vec.erase(position);
		obsolete_callbacks->Release();
		if (vec.empty())
			stop_keysync();

		return S_OK;
	}

	return S_FALSE;
}

STDMETHODIMP CpEpEngine::OpenPGPListKeyinfo(BSTR search_pattern, LPSAFEARRAY* keyinfo_list) {
	assert(keyinfo_list);

	if (keyinfo_list == NULL)
		return E_INVALIDARG;

	string _pattern = "";
	if (search_pattern)
		_pattern = utf8_string(search_pattern);
	::stringpair_list_t* _keyinfo_list = NULL;

	PEP_STATUS status = ::OpenPGP_list_keyinfo(get_session(), _pattern.c_str(), &_keyinfo_list);
	assert(status != PEP_OUT_OF_MEMORY);
	if (status == PEP_OUT_OF_MEMORY)
		return E_OUTOFMEMORY;

	if (status != ::PEP_STATUS_OK)
		return FAIL(L"OpenPGP_list_keyinfo");

	if (_keyinfo_list && _keyinfo_list->value) {
		::opt_field_array_from_C(_keyinfo_list, keyinfo_list);
	}
	else {
		::free_stringpair_list(_keyinfo_list);
		return FAIL(L"OpenPGP_list_keyinfo: no keys found");
	}

	::free_stringpair_list(_keyinfo_list);
	return S_OK;

}

HRESULT CpEpEngine::Fire_MessageToSend(TextMessage * msg)
{
	callbacks cbs = get_callbacks();
	vector<IpEpEngineCallbacks*>& vec = cbs;

	assert(msg);

	for (auto it = vec.begin(); it != vec.end(); ++it)
	{
		auto res = (*it)->MessageToSend(msg);
		if (res != S_OK)
			return res;
	}
	return S_OK;
}

HRESULT CpEpEngine::Fire_ShowHandshake(pEpIdentity * self, pEpIdentity * partner, SyncHandshakeResult * result)
{
	callbacks cbs = get_callbacks();
	vector<IpEpEngineCallbacks*>& vec = cbs;

	assert(self);
	assert(partner);
	assert(result);

	for (auto it = vec.begin(); it != vec.end(); ++it)
	{
		auto res = (*it)->ShowHandshake(self, partner, result);
		if (res != S_OK)
			return res;
	}
	return S_OK;
}
