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

// The second argument is optional, and currently supports PEP_STATUS.
#define FAIL(msg, ...) error(msg, __VA_ARGS__)

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

    if (!(fpr && keyData))
        return E_INVALIDARG;

    string _fpr = utf8_string(fpr);
    char *_key_data = NULL;
    size_t _size = 0;

    ::PEP_STATUS status = ::export_key(get_session(), _fpr.c_str(), &_key_data, &_size);
    assert(status != ::PEP_OUT_OF_MEMORY);
    if (status == ::PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    if (status != ::PEP_STATUS_OK)
        return FAIL(L"export_key", status);

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
		return FAIL(L"log_event", _status);
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
		return FAIL(L"TrustWords: _words == NULL", status);
	}
	else {
		*words = utf16_bstr(_words);
		pEp_free(_words);
		return S_OK;
	}
}

STDMETHODIMP CpEpEngine::GetTrustWords(struct pEpIdentity *id1, struct pEpIdentity *id2, BSTR lang, VARIANT_BOOL full, BSTR *words)
{
    assert(id1);
    assert(id2);
    assert(words);

    if (!(id1 && id2 && words))
    {
        return E_INVALIDARG;
    }

    HRESULT result = S_OK;

    pEp_identity* _id1 = NULL;
    pEp_identity* _id2 = NULL;
    string _lang;
    *words = NULL;

    try {
        _id1 = new_identity(id1);
        _id2 = new_identity(id2);

        if (!lang) {
            _lang = utf8_string(lang);
            if (_lang.length() == 0) {
                _lang = "en";
            } else if (_lang.length() != 2) {
                result = E_INVALIDARG;
            }
        } else {
            _lang = "en";
        }
    } catch (bad_alloc&) {
        result = E_OUTOFMEMORY;
    } catch (exception& ex) {
        result = FAIL(ex.what());
    }

    char* _words;
    size_t _size;
    if (result = S_OK) {
        auto status = ::get_trustwords(get_session(), _id1, _id2, _lang.c_str(), &_words, &_size, full != 0 /* convert variant bool to C bool */);

        if (status == PEP_OUT_OF_MEMORY) {
            result = E_OUTOFMEMORY;
        }
        else if (status == PEP_TRUSTWORD_NOT_FOUND) {
            result = FAIL(L"GetTrustWords: Trustword not found", status);
        }
        else if (!words) {
            result = FAIL(L"GetTrustWords: _words == NULL", status);
        }
        else {
            *words = utf16_bstr(_words);
            pEp_free(_words);
        }
    }

    free_identity(_id1);
    free_identity(_id2);

    return result;
}


STDMETHODIMP CpEpEngine::GetCrashdumpLog(LONG maxlines, BSTR * log)
{
	// COM-18: Currently, long == int on windows, so the check
	// for INT_MAX is not strictly necessary. However, the code
	// might get copy-pasted to other adapters in the future,
	// so safety first...
	assert(maxlines >= 0 && maxlines <= INT_MAX);
	assert(log);

	if (!(maxlines >= 0 && maxlines <= INT_MAX && log))
		return E_INVALIDARG;

	char *_log;
	PEP_STATUS status = ::get_crashdump_log(get_session(), (int)maxlines, &_log);
	assert(status == PEP_STATUS_OK);
	if (status == PEP_OUT_OF_MEMORY)
		return E_OUTOFMEMORY;
	if (status != PEP_STATUS_OK)
		return FAIL(L"GetCrashdumpLog", status);
    if (_log == NULL)
        return FAIL(L"GetCrashdumpLog: _log == NULL");

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
		return FAIL(L"GetEngineVersion: _engine_version == NULL");

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
    if (status != PEP_STATUS_OK)
        return FAIL(L"GetLanguageList", status);
	if (_languages == NULL)
		return FAIL(L"GetLanguageList: _languages == NULL");

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

	if (!(ident && result))
		return E_INVALIDARG;

	::pEp_identity *_ident = 0;
	
	try {
		_ident = new_identity(ident);
		assert(_ident);
		if (_ident == NULL)
			return E_OUTOFMEMORY;
	}
	catch (bad_alloc&) {
		return E_OUTOFMEMORY;
	}
	catch (exception& ex) {
		return FAIL(ex.what());;
	}


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
			return FAIL(L"myself", status);
	}
}

STDMETHODIMP CpEpEngine::UpdateIdentity(struct pEpIdentity *ident, struct pEpIdentity *result)
{
	assert(ident);
	assert(result);

	if (!(ident && result))
		return E_INVALIDARG;

	::pEp_identity *_ident;
	try {
		_ident = new_identity(ident);
	}
	catch (bad_alloc&) {
		return E_OUTOFMEMORY;
	}
	catch (exception& ex) {
		return FAIL(ex.what());
	}

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
			return FAIL(L"UpdateIdentity", status);
	}
}

STDMETHODIMP CpEpEngine::KeyMistrusted(struct pEpIdentity *ident)
{
	::pEp_identity *_ident;

	assert(ident);
	if (!ident)
		return E_INVALIDARG;

	try {
		_ident = new_identity(ident);
	}
	catch (bad_alloc&) {
		return E_OUTOFMEMORY;
	}
	catch (exception& ex) {
		return FAIL(ex.what());;
	}

	PEP_STATUS status = ::key_mistrusted(get_session(), _ident);
	free_identity(_ident);

	if (status == PEP_OUT_OF_MEMORY)
		return E_OUTOFMEMORY;

	if (status == PEP_KEY_NOT_FOUND)
		return FAIL(L"key not found");

	if (status != ::PEP_STATUS_OK)
		return FAIL(L"cannot revoke compromized key", status);

	return S_OK;
}

STDMETHODIMP CpEpEngine::KeyResetTrust(struct pEpIdentity *ident)
{
	::pEp_identity *_ident;

	assert(ident); 
	
	if (!ident)
		return E_INVALIDARG;

	try {
		_ident = new_identity(ident);
	}
	catch (bad_alloc&) {
		return E_OUTOFMEMORY;
	}
	catch (exception& ex) {
		return FAIL(ex.what());;
	}

	PEP_STATUS status = ::key_reset_trust(get_session(), _ident);
	free_identity(_ident);

	if (status == PEP_OUT_OF_MEMORY)
		return E_OUTOFMEMORY;

	if (status == PEP_KEY_NOT_FOUND)
		return FAIL(L"key not found");

	if (status != ::PEP_STATUS_OK)
		return FAIL(L"cannot reset trust", status);

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
	if (!management)
		return NULL;

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
	assert(obj);
	if (!(msg && obj))
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
	if (!fpr)
		return E_INVALIDARG;

	string _fpr = utf8_string(fpr);
	PEP_STATUS status = ::blacklist_add(get_session(), _fpr.c_str());
	assert(status == PEP_STATUS_OK);
	if (status != PEP_STATUS_OK)
		return FAIL(L"blacklist_add failed in pEp engine", status);

	return S_OK;
}

STDMETHODIMP CpEpEngine::BlacklistDelete(BSTR fpr)
{
	assert(fpr);
	if (!fpr)
		return E_INVALIDARG;

	string _fpr = utf8_string(fpr);
	PEP_STATUS status = ::blacklist_delete(get_session(), _fpr.c_str());
	assert(status == PEP_STATUS_OK);
	if (status != PEP_STATUS_OK)
		return FAIL(L"blacklist_delete failed in pEp engine", status);

	return S_OK;
}

STDMETHODIMP CpEpEngine::BlacklistIsListed(BSTR fpr, VARIANT_BOOL *listed)
{
	assert(fpr);
	assert(listed);

	if (!(fpr && listed))
		return E_INVALIDARG;

	string _fpr = utf8_string(fpr);
	bool result;
	PEP_STATUS status = ::blacklist_is_listed(get_session(), _fpr.c_str(), &result);
	assert(status == PEP_STATUS_OK);
	if (status != PEP_STATUS_OK)
		return FAIL(L"blacklist_is_listed failed in pEp engine", status);

	*listed = result ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CpEpEngine::BlacklistRetrieve(SAFEARRAY **blacklist)
{
	assert(blacklist);

	if (!blacklist)
		return E_INVALIDARG;

	::stringlist_t *_blacklist = NULL;
	PEP_STATUS status = ::blacklist_retrieve(get_session(), &_blacklist);
	assert(status == PEP_STATUS_OK);
	if (status != PEP_STATUS_OK)
		return FAIL(L"blacklist_retrieve failed in pEp engine", status);
	assert(_blacklist);

	*blacklist = string_array(_blacklist);
	::free_stringlist(_blacklist);
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

HRESULT CpEpEngine::error(_bstr_t msg, PEP_STATUS status)
{
    std::stringstream stream;
    stream << msg;
    stream << ": ";
    stream << std::hex << status;
    
    error(stream.str().c_str());

    if (status == ::PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    return E_FAIL;
}

STDMETHODIMP CpEpEngine::EncryptMessage(TextMessage * src, TextMessage * dst, SAFEARRAY * extra, pEpEncryptFlags flags)
{
	assert(src);
	assert(dst);

	if (!(src && dst))
		return E_INVALIDARG;

	::message *_src = text_message_to_C(src);

	// COM-19: Initialize msg_dst to NULL, or we end up calling
	// free_message() below with a pointer to random garbage in
	// case of an error in encrypt_message().
	::message *msg_dst = NULL;
	::stringlist_t *_extra = new_stringlist(extra); // can cope with NULL

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
	assert(flags);
	assert(rating);

	if (!(src && dst && keylist && flags && rating))
		return E_INVALIDARG;

	*keylist = NULL;
	*rating = pEpRatingUndefined;

	::message *_src = text_message_to_C(src);
	::message *msg_dst = NULL;
	::stringlist_t *_keylist = NULL;
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

	if (!(msg  && pVal))
		return E_INVALIDARG;

	::message *_msg = text_message_to_C(msg);

	PEP_rating _rating;
	PEP_STATUS status = ::outgoing_message_rating(get_session(), _msg, &_rating);
	if (status != PEP_STATUS_OK)
		return FAIL(L"cannot get message rating", status);

	*pVal = (pEpRating)_rating;
	return S_OK;
}

STDMETHODIMP CpEpEngine::IdentityRating(struct pEpIdentity *ident, pEpRating * pVal)
{
	::pEp_identity *_ident;

	assert(ident);
	assert(pVal);

	if (!(ident  && pVal))
		return E_INVALIDARG;

	try {
		_ident = new_identity(ident);
	}
	catch (bad_alloc&) {
		return E_OUTOFMEMORY;
	}
	catch (exception& ex) {
		return FAIL(ex.what());;
	}

	PEP_rating _rating;
	PEP_STATUS status = ::identity_rating(get_session(), _ident, &_rating);
	free_identity(_ident);

	if (status != PEP_STATUS_OK)
		return FAIL(L"cannot get message color", status);

	*pVal = (pEpRating)_rating;
	return S_OK;
}

STDMETHODIMP CpEpEngine::ColorFromRating(pEpRating rating, pEpColor * pVal)
{
	assert(pVal);

	if (!pVal)
		return E_INVALIDARG;

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

	if (!ident || !result)
		return E_INVALIDARG;

	try {
		_ident = new_identity(ident);
	}
	catch (bad_alloc&) {
		return E_OUTOFMEMORY;
	}
	catch (exception& ex) {
		return FAIL(ex.what());;
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
		return FAIL(L"failure while executing TrustPersonalKey()", status);

	return S_OK;
}

// keysync api

void CpEpEngine::start_keysync()
{
	// acquire the lock
	std::unique_lock<std::mutex> lock(keysync_mutex);

	// Assert if we're not already running.
    assert(!this->keysync_thread);

	// Ensure we are not aborting the new thread due to a
	// left over flag.
	keysync_abort_requested = false;

	// Init our keysync session
	PEP_STATUS status = ::init(&keysync_session);
	::register_sync_callbacks(keysync_session, (void*)this, messageToSend, showHandshake, inject_sync_msg, retrieve_next_sync_msg);
	assert(status == PEP_STATUS_OK);

    attach_sync_session(get_session(), keysync_session);

    // We need to marshal the callbacks to the keysync thread
    LPSTREAM marshaled_callbacks;

    auto result = CoMarshalInterThreadInterfaceInStream(IID_IpEpEngineCallbacks, client_callbacks, &marshaled_callbacks);
    assert(result == S_OK);

	// Star the keysync thread
	keysync_thread = new thread(do_keysync_in_thread, this, marshaled_callbacks);
}

void CpEpEngine::do_keysync_in_thread(CpEpEngine* self, LPSTREAM marshaled_callbacks) 
{
    assert(self);
	assert(marshaled_callbacks);

    // We need to initialize COM here for successfull delivery of the callbacks.
    // As we don't create any COM instances in our thread, the COMINIT value is
    // currently irrelevant, so we go with the safest value.
    auto res = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    assert(res == S_OK);

    LPVOID vp;

    res = CoGetInterfaceAndReleaseStream(marshaled_callbacks, IID_IpEpEngineCallbacks, &vp);
    assert(SUCCEEDED(res));

    self->client_callbacks_on_sync_thread = static_cast<IpEpEngineCallbacks*>(vp);

    ::do_sync_protocol(self->keysync_session, self);

    self->client_callbacks_on_sync_thread->Release();

    self->client_callbacks_on_sync_thread = NULL;

    CoUninitialize();
}

void CpEpEngine::stop_keysync()
{
	// acquire the lock
	std::unique_lock<std::mutex> lock(keysync_mutex);

    // Do nothing if keysync is not running.
    if (!keysync_thread)
        return;

    assert(!keysync_abort_requested);
	// signal that we're gonna abort
	keysync_abort_requested = true;

	// Notify the keysync thread
	keysync_condition.notify_all();

	// Wait for the other thread to finish and clean up
	while (keysync_abort_requested)
		keysync_condition.wait(lock);

	// collect the child thread for the thread to end
	keysync_thread->join();

	// clean up
	delete keysync_thread;
	keysync_thread = NULL;

    ::detach_sync_session(get_session());
	::unregister_sync_callbacks(keysync_session);
	release(keysync_session);
    keysync_session = NULL;
}

int CpEpEngine::inject_sync_msg(void * msg, void * management)
{
	assert(msg);
	assert(management);
	// check argument
	if (!msg)
		return E_INVALIDARG;
	if (!management)
		return ERROR_INVALID_HANDLE;

	CpEpEngine* me = (CpEpEngine*)management;

	// acquire the lock
	std::unique_lock<std::mutex> lock(me->keysync_mutex);

	// check whether we're in a valid state running:
	if (!me->keysync_thread)
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
	if (!management)
		return NULL;

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
	me->keysync_abort_requested = false;

	// We signal the main thread that we got his signal
	// so it can gain the mutex again and call join() on us.
	me->keysync_condition.notify_all();

	// and tell the pep engine we're done.
	return NULL;
}


// Event callbacks

STDMETHODIMP CpEpEngine::RegisterCallbacks(IpEpEngineCallbacks* new_callbacks)
{
    // check for valid parameter
    if (!new_callbacks)
        return E_INVALIDARG;

    // don't allow double registration.
    if (this->client_callbacks)
        return E_ILLEGAL_STATE_CHANGE;

    this->client_callbacks = new_callbacks;
    new_callbacks->AddRef();

	start_keysync();

	return S_OK;
}

STDMETHODIMP CpEpEngine::UnregisterCallbacks()
{
    // don't allow double deregistration.
    // S_FALSE still is no error (as double deregistration is not fatal).
    if (!this->client_callbacks)
        return S_FALSE;

    stop_keysync();

    this->client_callbacks->Release();

    this->client_callbacks = NULL;

    return S_OK;
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
		return FAIL(L"OpenPGP_list_keyinfo", status);

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
	assert(msg);
    assert(this->client_callbacks_on_sync_thread);

	if (!msg)
		return E_INVALIDARG;

	if (!this->client_callbacks_on_sync_thread)
		return E_ILLEGAL_METHOD_CALL;

    auto result = this->client_callbacks_on_sync_thread->MessageToSend(msg);

	return result;
}

HRESULT CpEpEngine::Fire_ShowHandshake(pEpIdentity * self, pEpIdentity * partner, SyncHandshakeResult * result)
{
	assert(self);
	assert(partner);
	assert(result);
    assert(this->client_callbacks_on_sync_thread);

	if (!(self && partner && result))
		return E_INVALIDARG;
	if (!this->client_callbacks_on_sync_thread)
		return E_ILLEGAL_METHOD_CALL;
    	
	auto res = this->client_callbacks_on_sync_thread->ShowHandshake(self, partner, result);
		
	return res;	
}
