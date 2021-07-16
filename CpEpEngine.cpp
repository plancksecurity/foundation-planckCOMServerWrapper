// CpEpEngine.cpp : Implementation of CpEpEngine

#include "stdafx.h"
#include "CpEpEngine.h"
#include "GateKeeper.h"
#include "LocalJSONAdapter.h"
#include "../libpEpAdapter/src/group_manager_api.h"

using namespace std;
using namespace pEp::utility;

// CpEpEngine

CpEpEngine::callback_container CpEpEngine::sync_callbacks;

// the init_mutex protects our initialization and destruction
// against a running keysync thread, and it ensures that the
// keysync thread actually has finished before we're destructed.

std::mutex CpEpEngine::init_mutex;
atomic< int > CpEpEngine::count = 0;

extern LocalJSONAdapter* ljs;

STDMETHODIMP CpEpEngine::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const IID* const arr[] =
    {
        &IID_IpEpEngine,
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
    ::config_passive_mode(session(), enable != VARIANT_FALSE);
    return S_OK;
}

STDMETHODIMP CpEpEngine::UnencryptedSubject(VARIANT_BOOL enable)
{
    ::config_unencrypted_subject(session(), enable != VARIANT_FALSE);
    return S_OK;
}

STDMETHODIMP CpEpEngine::ConfigCipherSuite(pEpCipherSuite cipherSuite)
{
    PEP_STATUS status = ::config_cipher_suite(session(), (PEP_CIPHER_SUITE)cipherSuite);

    if (status)
        return FAIL(L"config_cipher_suite", status);

    return S_OK;
}

STDMETHODIMP CpEpEngine::ImportKey(BSTR keyData, LPSAFEARRAY * privateKeys)
{
    return ImportKeyWithFprReturn(keyData, privateKeys, NULL);
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

    PEP_STATUS status = passphrase_cache.api(::export_key, session(), _fpr.c_str(), &_key_data, &_size);
    assert(status != ::PEP_OUT_OF_MEMORY);
    if (status == ::PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    if (status != PEP_STATUS_OK)
        return FAIL(L"export_key", status);

    _bstr_t b_key_data(utf16_string(_key_data).c_str());
    pEp_free(_key_data);
    *keyData = b_key_data.Detach();

    return S_OK;
}

STDMETHODIMP CpEpEngine::ExportSecretKey(BSTR fpr, BSTR* keyData)
{
    assert(fpr);
    assert(keyData);

    if (!(fpr && keyData))
        return E_INVALIDARG;

    string _fpr = utf8_string(fpr);
    char* _key_data = NULL;
    size_t _size = 0;

    PEP_STATUS status = passphrase_cache.api(::export_secret_key, session(), _fpr.c_str(), &_key_data, &_size);
    assert(status != ::PEP_OUT_OF_MEMORY);
    if (status == ::PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    if (status != PEP_STATUS_OK)
        return FAIL(L"export_secret_key", status);

    _bstr_t b_key_data(utf16_string(_key_data).c_str());
    pEp_free(_key_data);
    *keyData = b_key_data.Detach();

    return S_OK;
}

STDMETHODIMP CpEpEngine::LeaveDeviceGroup()
{
    PEP_STATUS status = passphrase_cache.api(::leave_device_group, session());

    if (status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    if (status != PEP_STATUS_OK)
        return FAIL(L"cannot leave device group", status);

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

    PEP_STATUS _status = ::log_event(session(), _title.c_str(), _entity.c_str(), _description.c_str(), _comment.c_str());
    assert(_status == PEP_STATUS_OK);
    if (_status != PEP_STATUS_OK)
        return FAIL(L"log_event", _status);
    else
        return S_OK;
}

STDMETHODIMP CpEpEngine::Trustwords(BSTR fpr, BSTR lang, LONG max_words, BSTR * words)
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

    PEP_STATUS status = ::trustwords(session(), _fpr.c_str(), _lang.c_str(), &_words, &_wsize, max_words);
    assert(status != PEP_OUT_OF_MEMORY);
    if (status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    if (_words == NULL) {
        *words = NULL;
        return FAIL(L"Trustwords: _words == NULL", status);
    }
    else {
        *words = utf16_bstr(_words);
        pEp_free(_words);
        return S_OK;
    }
}

STDMETHODIMP CpEpEngine::GetTrustwordsForFprs(BSTR fpr1, BSTR fpr2, BSTR lang, VARIANT_BOOL full, BSTR *words)
{
    assert(fpr1);
    assert(fpr2);
    assert(words);

    if (!(fpr1 && fpr2 && words))
    {
        return E_INVALIDARG;
    }

    HRESULT result = S_OK;
    string _fpr1;
    string _fpr2;
    string _lang;
    *words = NULL;

    try {

        _fpr1 = utf8_string(fpr1);
        _fpr2 = utf8_string(fpr2);

        if (lang) {
            _lang = utf8_string(lang);
            if (_lang.length() == 0) {
                _lang = "en";
            }
            else if (_lang.length() != 2) {
                result = E_INVALIDARG;
            }
        }
        else {
            _lang = "en";
        }
    }
    catch (bad_alloc&) {
        result = E_OUTOFMEMORY;
    }
    catch (exception& ex) {
        result = FAIL(ex.what());
    }

    char* _words;
    size_t _size;
    if (result == S_OK) {
        auto status = ::get_trustwords_for_fprs(session(), _fpr1.c_str(), _fpr2.c_str(), _lang.c_str(), &_words, &_size, full != 0 /* convert variant bool to C bool */);

        if (status == PEP_OUT_OF_MEMORY) {
            result = E_OUTOFMEMORY;
        }
        else if (status == PEP_TRUSTWORD_NOT_FOUND) {
            result = FAIL(L"GetTrustwords: Trustword not found", status);
        }
        else if (!words) {
            result = FAIL(L"GetTrustwords: _words == NULL", status);
        }
        else {
            *words = utf16_bstr(_words);
            pEp_free(_words);
        }
    }

    return result;
}

STDMETHODIMP CpEpEngine::GetTrustwords(struct pEpIdentity *id1, struct pEpIdentity *id2, BSTR lang, VARIANT_BOOL full, BSTR *words)
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

        if (lang) {
            _lang = utf8_string(lang);
            if (_lang.length() == 0) {
                _lang = "en";
            }
            else if (_lang.length() != 2) {
                result = E_INVALIDARG;
            }
        }
        else {
            _lang = "en";
        }
    }
    catch (bad_alloc&) {
        result = E_OUTOFMEMORY;
    }
    catch (exception& ex) {
        result = FAIL(ex.what());
    }

    char* _words;
    size_t _size;
    if (result == S_OK) {
        auto status = ::get_trustwords(session(), _id1, _id2, _lang.c_str(), &_words, &_size, full != 0 /* convert variant bool to C bool */);

        if (status == PEP_OUT_OF_MEMORY) {
            result = E_OUTOFMEMORY;
        }
        else if (status == PEP_TRUSTWORD_NOT_FOUND) {
            result = FAIL(L"GetTrustwords: Trustword not found", status);
        }
        else if (!words) {
            result = FAIL(L"GetTrustwords: _words == NULL", status);
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

STDMETHODIMP CpEpEngine::GetMessageTrustwords(
    /* [in] */ struct TextMessage *msg,
    /* [in] */ struct pEpIdentity *receivedBy,
    /* [in] */ SAFEARRAY *keylist,
    /* [defaultvalue][in] */ BSTR lang,
    /* [defaultvalue][in] */ VARIANT_BOOL full,
    /* [retval][out] */ BSTR *words) {
    assert(msg);
    assert(receivedBy);
    assert(words);

    if (!(msg && receivedBy && words))
    {
        return E_INVALIDARG;
    }

    HRESULT result = S_OK;

    pEp_identity * _received_by = NULL;
    ::message * _msg = NULL;
    ::stringlist_t *_keylist = NULL;
    string _lang;
    *words = NULL;

    try {
        _received_by = new_identity(receivedBy);
        _msg = text_message_to_C(msg);

        if (keylist) {
            _keylist = new_stringlist(keylist);
        }

        if (lang) {
            _lang = utf8_string(lang);
            if (_lang.length() == 0) {
                _lang = "en";
            }
            else if (_lang.length() != 2) {
                result = E_INVALIDARG;
            }
        }
        else {
            _lang = "en";
        }
    }
    catch (bad_alloc&) {
        result = E_OUTOFMEMORY;
    }
    catch (exception& ex) {
        result = FAIL(ex.what());
    }

    char* _words = NULL;
    if (result == S_OK) {
        auto status = passphrase_cache.api(::get_message_trustwords,
            session(),
            _msg,
            _keylist,
            _received_by,
            _lang.c_str(),
            &_words,
            full != 0 /* convert variant bool to C bool */);

        if (status == PEP_OUT_OF_MEMORY) {
            result = E_OUTOFMEMORY;
        }
        else if (status == PEP_TRUSTWORD_NOT_FOUND) {
            result = FAIL(L"GetTrustwords: Trustword not found", status);
        }
        else if (!words) {
            result = FAIL(L"GetTrustwords: _words == NULL", status);
        }
        else {
            *words = utf16_bstr(_words);
        }
    }

    ::pEp_free(_words);
    ::free_message(_msg);
    ::free_stringlist(_keylist);
    ::free_identity(_received_by);

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
    PEP_STATUS status = ::get_crashdump_log(session(), (int)maxlines, &_log);
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
    PEP_STATUS status = ::get_languagelist(session(), &_languages);
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

STDMETHODIMP CpEpEngine::SetIdentityFlags(struct pEpIdentity *identity, pEpIdentityFlags flags)
{
    assert(identity);
    if (!identity)
        return E_INVALIDARG;

    ::pEp_identity *_ident = nullptr;

    try {
        _ident = new_identity(identity);
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

    PEP_STATUS status = passphrase_cache.api(::set_identity_flags, session(), _ident, (identity_flags_t)flags);
    ::free_identity(_ident);
    if (status != PEP_STATUS_OK)
        return FAIL(_T("SetIdentityFlags"), status);

    return S_OK;
}

STDMETHODIMP CpEpEngine::UnsetIdentityFlags(struct pEpIdentity *identity, pEpIdentityFlags flags)
{
    assert(identity);
    if (!identity)
        return E_INVALIDARG;

    ::pEp_identity *_ident = nullptr;

    try {
        _ident = new_identity(identity);
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

    PEP_STATUS status = passphrase_cache.api(::unset_identity_flags, session(), _ident, (identity_flags_t)flags);
    ::free_identity(_ident);
    if (status != PEP_STATUS_OK)
        return FAIL(_T("UnsetIdentityFlags"), status);

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

STDMETHODIMP CpEpEngine::MIMEDecodeMessage(BSTR mimeText, TextMessage *msg)
{
    assert(mimeText);

    if (!mimeText)
        return E_INVALIDARG;

    string _mimeText = utf8_string(mimeText);
    size_t size = SysStringLen(mimeText);
    ::message *_msg = NULL;

    PEP_STATUS status = mime_decode_message(_mimeText.c_str(), size, &_msg, nullptr);
    assert(status != ::PEP_OUT_OF_MEMORY);
    if (status == ::PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    if (status != PEP_STATUS_OK)
        return FAIL(L"mime_decode_message", status);

    if (_msg)
        text_message_from_C(msg, _msg);

    free_message(_msg);

    return status;
}


STDMETHODIMP CpEpEngine::MIMEEncodeMessage(TextMessage *msg, VARIANT_BOOL omitFields, BSTR *mimeText)
{
    assert(msg);

    if (!msg)
        return E_INVALIDARG;

    ::message *_msg = NULL;
    try {
        _msg = text_message_to_C(msg);
    }
    catch (bad_alloc&) {
        return E_OUTOFMEMORY;
    }
    catch (exception& ex) {
        return FAIL(ex.what());
    }

    char *_mimeText;

    PEP_STATUS status = mime_encode_message(_msg, omitFields != 0, &_mimeText, false);
    free_message(_msg);

    assert(status != ::PEP_OUT_OF_MEMORY);
    if (status == ::PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    if (status != PEP_STATUS_OK)
        return FAIL(L"mime_encode_message", status);

    *mimeText = utf16_bstr(_mimeText);
    pEp_free(_mimeText);

    return status;
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

    PEP_STATUS status;
    if (passphrase_for_new_keys != "")
        status = ::config_passphrase_for_new_keys(session(), true, passphrase_for_new_keys.c_str());
    else
        status = ::config_passphrase_for_new_keys(session(), false, passphrase_for_new_keys.c_str());
    status = passphrase_cache.api(::myself, session(), _ident);

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

    PEP_STATUS status = passphrase_cache.api(::update_identity, session(), _ident);

    if (status == PEP_STATUS_OK) {
        copy_identity(result, _ident);
        ::free_identity(_ident);
        return S_OK;
    }
    else if (status == PEP_GET_KEY_FAILED || status == PEP_KEY_NOT_FOUND || status == PEP_KEY_UNSUITABLE) {
        if (_ident->fpr) {
            pEp_free(_ident->fpr);
            _ident->fpr = NULL;
        }
        copy_identity(result, _ident);
        result->Fpr = NULL;
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

    PEP_STATUS status = passphrase_cache.api(::key_mistrusted, session(), _ident);
    free_identity(_ident);

    if (status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    if (status == PEP_GET_KEY_FAILED || status == PEP_KEY_NOT_FOUND || status == PEP_KEY_UNSUITABLE)
        return FAIL(L"key not found");

    if (status != PEP_STATUS_OK)
        return FAIL(L"cannot revoke compromised key", status);

    return S_OK;
}

STDMETHODIMP CpEpEngine::IspEpUser(/* [in] */ struct pEpIdentity *ident, /* [retval][out] */ VARIANT_BOOL *ispEp)
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

    bool is_pep = FALSE;
    PEP_STATUS status = passphrase_cache.api(::is_pEp_user, session(), _ident, &is_pep);

    *ispEp = is_pep;

    if (status == PEP_CANNOT_FIND_PERSON)
        return FAIL(L"Cannot find identity!", status);

    if (status == PEP_ILLEGAL_VALUE)
        return E_INVALIDARG;

    if (status != PEP_STATUS_OK)
        return FAIL(L"Engine is_pEp_user returned error", status);

    return S_OK;
}

STDMETHODIMP CpEpEngine::KeyResetIdentity(struct pEpIdentity ident, BSTR fpr)
{
    ::pEp_identity *_ident;

    try {
        _ident = new_identity(&ident);
    }
    catch (bad_alloc&) {
        return E_OUTOFMEMORY;
    }
    catch (exception& ex) {
        return FAIL(ex.what());;
    }

    string _fpr = utf8_string(fpr);

    PEP_STATUS status = passphrase_cache.api(::key_reset_identity, session(), _ident, _fpr.c_str());

    free_identity(_ident);

    if (status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    if (status == PEP_GET_KEY_FAILED || status == PEP_KEY_NOT_FOUND || status == PEP_KEY_UNSUITABLE)
        return FAIL(L"key not found");

    if (status != PEP_STATUS_OK)
        return FAIL(L"cannot reset identity", status);

    return S_OK;
}

STDMETHODIMP CpEpEngine::KeyResetUser(BSTR userId, BSTR fpr)
{
    string _userId = utf8_string(userId);
    string _fpr = utf8_string(fpr);

    PEP_STATUS status = passphrase_cache.api(::key_reset_user, session(), _userId.c_str(), _fpr.c_str());

    if (status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    if (status == PEP_GET_KEY_FAILED || status == PEP_KEY_NOT_FOUND || status == PEP_KEY_UNSUITABLE)
        return FAIL(L"key not found");

    if (status != PEP_STATUS_OK)
        return FAIL(L"cannot reset user", status);

    return S_OK;
}

STDMETHODIMP CpEpEngine::KeyResetAllOwnKeys()
{
    PEP_STATUS status = passphrase_cache.api(::key_reset_all_own_keys, session());

    if (status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    if (status != PEP_STATUS_OK)
        return FAIL(L"cannot reset all own keys", status);

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

    PEP_STATUS status = passphrase_cache.api(::key_reset_trust, session(), _ident);
    free_identity(_ident);

    if (status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    if (status == PEP_GET_KEY_FAILED || status == PEP_KEY_NOT_FOUND || status == PEP_KEY_UNSUITABLE)
        return FAIL(L"key not found");

    if (status != PEP_STATUS_OK)
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

static IpEpEngineCallbacks * _unmarshaled_consumer(CpEpEngine::callback_container::Container::iterator p)
{
    if (!p->cdata && p->pdata && p->pdata->marshaled) {
        HRESULT r = CoGetInterfaceAndReleaseStream(p->pdata->marshaled, IID_IpEpEngineCallbacks, (LPVOID*)&p->cdata);
        if (!SUCCEEDED(r))
            throw runtime_error("_unmarshaled_consumer(): CoGetInterfaceAndReleaseStream() failed");
        p->pdata->marshaled = nullptr;
    }
    else if (p->cdata && !p->pdata) {
        p->cdata->Release();
        p->cdata = nullptr;
    }

    return p->cdata;
}

PEP_STATUS CpEpEngine::messageToSend(message *msg)
{
    bool in_sync = on_sync_thread();

    for (auto p = sync_callbacks.begin(); p != sync_callbacks.end(); ++p) {
        IpEpEngineCallbacks *cb = in_sync ? _unmarshaled_consumer(p) : p->pdata->unmarshaled;

        if (cb) {
            TextMessage _msg;
            memset(&_msg, 0, sizeof(TextMessage));

            text_message_from_C(&_msg, msg);
            HRESULT r = cb->MessageToSend(&_msg);
            assert(r == S_OK);
            clear_text_message(&_msg);
            if (r == E_OUTOFMEMORY)
                return PEP_OUT_OF_MEMORY;
            if (r != S_OK)
                return PEP_UNKNOWN_ERROR;
        }
    }

    if (ljs)
        ljs->messageToSend(msg);

    sync_callbacks.compact();

    return PEP_STATUS_OK;
}

PEP_STATUS CpEpEngine::notifyHandshake(::pEp_identity *self, ::pEp_identity *partner, ::sync_handshake_signal signal)
{
    assert(signal);
    if (!signal)
        return PEP_ILLEGAL_VALUE;

    bool in_sync = on_sync_thread();

    // fire all of them
    for (auto p = sync_callbacks.begin(); p != sync_callbacks.end(); ++p) {
        IpEpEngineCallbacks *cb = in_sync ? _unmarshaled_consumer(p) : p->pdata->unmarshaled;

        if (cb) {
            pEpIdentity _self;
            copy_identity(&_self, self);
            pEpIdentity _partner;
            copy_identity(&_partner, partner);

            SyncHandshakeSignal _signal = (SyncHandshakeSignal)signal;
            HRESULT r = cb->NotifyHandshake(&_self, &_partner, _signal);
            assert(r == S_OK);
            clear_identity_s(_self);
            clear_identity_s(_partner);
            if (r == E_OUTOFMEMORY)
                return PEP_OUT_OF_MEMORY;
        }
    }

    sync_callbacks.compact();

    return PEP_STATUS_OK;
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
    stream << pEp_status_to_string(status);
    stream << std::hex << " (" << status << ")";

    error(stream.str().c_str());

    if (status == ::PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    return MAKE_HRESULT(1, FACILITY_ITF, (0xFFFF & status));
}

STDMETHODIMP CpEpEngine::EncryptMessage(TextMessage * src, TextMessage * dst, SAFEARRAY * extra, pEpEncryptFlags flags, pEpEncFormat encFormat)
{
    assert(src);
    assert(dst);

    if (!(src && dst))
        return E_INVALIDARG;

    ::message *_src = NULL;
    try {
        _src = text_message_to_C(src);
    }
    catch (bad_alloc&) {
        return E_OUTOFMEMORY;
    }
    catch (exception& ex) {
        return FAIL(ex.what());
    }

    _PEP_enc_format _encFormat = (_PEP_enc_format)encFormat;

    // COM-19: Initialize msg_dst to NULL, or we end up calling
    // free_message() below with a pointer to random garbage in
    // case of an error in encrypt_message().
    ::message *msg_dst = NULL;
    ::stringlist_t *_extra = new_stringlist(extra); // can cope with NULL

    // _PEP_enc_format used to be intentionally hardcoded to PEP_enc_PEP:
    // Since COM-74, this has been changed to an explicit parameter, to allow the engine to attach
    // the keys and headers to outgoing, unencrypted messages.
    PEP_encrypt_flags_t engineFlags = (PEP_encrypt_flags_t)flags;
    PEP_STATUS status = passphrase_cache.api(::encrypt_message, session(), _src, _extra, &msg_dst, _encFormat, engineFlags);
    ::free_stringlist(_extra);

    if (status == PEP_STATUS_OK)
        text_message_from_C(dst, msg_dst);
    else
        text_message_from_C(dst, _src);

    ::free_message(msg_dst);
    ::free_message(_src);

    if (status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    // COM-41: Enhanced PEP status handling
    if ((status != PEP_STATUS_OK) && (status < PEP_UNENCRYPTED || status >= PEP_TRUSTWORD_NOT_FOUND))
        return FAIL("Failure to encrypt message", status);

    // Statii like PEP_UNENCRYPTED due to no private key
    // should not be a catastrophic failure here. Using S_FALSE
    // still allows clients to differentiate with S_OK,
    // although this does not work out of the box with
    // the standard .NET mapping of COM.
    if (status != PEP_STATUS_OK)
        return S_FALSE;

    return S_OK;
}

STDMETHODIMP CpEpEngine::EncryptMessageAndAddPrivKey(TextMessage * src, TextMessage * dst, BSTR to_fpr, pEpEncryptFlags flags, pEpEncFormat encFormat)
{
    assert(src);
    assert(dst);
    assert(to_fpr);

    if (!(src && dst))
        return E_INVALIDARG;

    ::message *_src = NULL;
    try {
        _src = text_message_to_C(src);
    }
    catch (bad_alloc&) {
        return E_OUTOFMEMORY;
    }
    catch (exception& ex) {
        return FAIL(ex.what());
    }

    _PEP_enc_format _encFormat = (_PEP_enc_format)encFormat;

    // COM-19: Initialize msg_dst to NULL, or we end up calling
    // free_message() below with a pointer to random garbage in
    // case of an error in encrypt_message().
    ::message *msg_dst = NULL;

    string _to_fpr = utf8_string(to_fpr);
    // _PEP_enc_format used to be intentionally hardcoded to PEP_enc_PEP:
    // Since COM-74, this has been changed to an explicit parameter, to allow the engine to attach
    // the keys and headers to outgoing, unencrypted messages.
    PEP_encrypt_flags_t engineFlags = (PEP_encrypt_flags_t)flags;
    PEP_STATUS status = passphrase_cache.api(::encrypt_message_and_add_priv_key, session(), _src, &msg_dst, _to_fpr.c_str(), _encFormat, engineFlags);

    if (status == PEP_STATUS_OK)
        text_message_from_C(dst, msg_dst);
    else
        text_message_from_C(dst, _src);

    ::free_message(msg_dst);
    ::free_message(_src);

    if (status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    // COM-41: Enhanced PEP status handling
    if ((status != PEP_STATUS_OK) && (status < PEP_UNENCRYPTED || status >= PEP_TRUSTWORD_NOT_FOUND))
        return FAIL("Failure to encrypt message", status);

    // Statii like PEP_UNENCRYPTED due to no private key
    // should not be a catastrophic failure here. Using S_FALSE
    // still allows clients to differentiate with S_OK,
    // although this does not work out of the box with
    // the standard .NET mapping of COM.
    if (status != PEP_STATUS_OK)
        return S_FALSE;

    return S_OK;
}

STDMETHODIMP CpEpEngine::EncryptMessageForSelf(pEpIdentity * targetId, TextMessage * src,
    /* [in] */ SAFEARRAY *extra, TextMessage * dst, pEpEncryptFlags flags)
{
    assert(targetId);
    assert(src);
    assert(dst);

    if (!(targetId && src && dst))
        return E_INVALIDARG;

    PEP_encrypt_flags_t engineFlags = (PEP_encrypt_flags_t)flags;

    ::pEp_identity *_target_id = new_identity(targetId);

    ::message *_src = NULL;
    try {
        _src = text_message_to_C(src);
    }
    catch (bad_alloc&) {
        return E_OUTOFMEMORY;
    }
    catch (exception& ex) {
        return FAIL(ex.what());
    }

    ::stringlist_t* _extra = NULL;
    HRESULT result = S_OK;
    ::message *msg_dst = NULL;
    PEP_STATUS status = PEP_STATUS_OK;

    try {
        if (extra) {
            _extra = new_stringlist(extra);
        }

        // COM-19: Initialize msg_dst to NULL, or we end up calling
        // free_message() below with a pointer to random garbage in
        // case of an error in encrypt_message_for_self().
        status = passphrase_cache.api(::encrypt_message_for_self, session(), _target_id, _src, _extra, &msg_dst, PEP_enc_PEP, engineFlags);

        if (status == PEP_STATUS_OK)
            text_message_from_C(dst, msg_dst);
        else
            text_message_from_C(dst, _src);
    }
    catch (bad_alloc&) {
        result = E_OUTOFMEMORY;
    }
    catch (exception& ex) {
        result = FAIL(ex.what());
    }

    ::free_message(msg_dst);
    ::free_message(_src);
    ::free_identity(_target_id);
    ::free_stringlist(_extra);

    if (status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    // Different to encrypt_message, this should never fail (we ought to always
    // have a private key for ourself).#
    if (status != PEP_STATUS_OK)
        return FAIL("Failure to encrypt message", status);

    return result;
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

    *rating = pEpRatingUndefined;

    ::message *_src = NULL;
    try {
        _src = text_message_to_C(src);
    }
    catch (bad_alloc&) {
        return E_OUTOFMEMORY;
    }
    catch (exception& ex) {
        return FAIL(ex.what());
    }
    ::message *msg_dst = NULL;
    ::stringlist_t *_keylist = new_stringlist(*keylist);
    ::PEP_rating _rating;

    PEP_decrypt_flags_t engineflags = (PEP_decrypt_flags_t)*flags;
    PEP_STATUS status = passphrase_cache.api(::decrypt_message, session(), _src, &msg_dst, &_keylist, &_rating, &engineflags);

    *flags = (pEpDecryptFlags)engineflags;

    if (_src)
        text_message_from_C(src, _src);

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

STDMETHODIMP CpEpEngine::ReEvaluateMessageRating(TextMessage * msg, SAFEARRAY * x_KeyList, pEpRating x_EncStatus, pEpRating *rating)
{
    assert(msg);
    assert(x_EncStatus != PEP_rating_undefined);
    assert(rating);

    if (!(msg && x_EncStatus != PEP_rating_undefined && rating))
        return E_INVALIDARG;

    *rating = pEpRatingUndefined;

    ::message *_msg = NULL;
    try {
        _msg = text_message_to_C(msg);
    }
    catch (bad_alloc&) {
        return E_OUTOFMEMORY;
    }
    catch (exception& ex) {
        return FAIL(ex.what());
    }

    ::stringlist_t *_keylist = new_stringlist(x_KeyList);
    ::PEP_rating _rating = PEP_rating_undefined;

    PEP_STATUS status = passphrase_cache.api(::re_evaluate_message_rating, session(), _msg, _keylist, (PEP_rating)x_EncStatus, &_rating);

    if (_msg)
        text_message_from_C(msg, _msg);

    ::free_stringlist(_keylist);
    ::free_message(_msg);

    *rating = (pEpRating)_rating;

    return S_OK;
}

STDMETHODIMP CpEpEngine::OutgoingMessageRating(TextMessage *msg, pEpRating * pVal)
{
    assert(msg);
    assert(pVal);

    if (!(msg  && pVal))
        return E_INVALIDARG;

    ::message *_msg = NULL;
    try {
        _msg = text_message_to_C(msg);
    }
    catch (bad_alloc&) {
        return E_OUTOFMEMORY;
    }
    catch (exception& ex) {
        return FAIL(ex.what());
    }

    PEP_rating _rating;
    PEP_STATUS status = passphrase_cache.api(::outgoing_message_rating, session(), _msg, &_rating);
    if (status != PEP_STATUS_OK)
        return FAIL(L"cannot get message rating", status);

    *pVal = (pEpRating)_rating;
    return S_OK;
}

STDMETHODIMP CpEpEngine::OutgoingMessageRatingPreview(TextMessage *msg, pEpRating * pVal)
{
    assert(msg);
    assert(pVal);

    if (!(msg  && pVal))
        return E_INVALIDARG;

    ::message *_msg = NULL;
    try {
        _msg = text_message_to_C(msg);
    }
    catch (bad_alloc&) {
        return E_OUTOFMEMORY;
    }
    catch (exception& ex) {
        return FAIL(ex.what());
    }

    PEP_rating _rating;
    PEP_STATUS status = ::outgoing_message_rating_preview(session(), _msg, &_rating);
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
    PEP_STATUS status = passphrase_cache.api(::identity_rating, session(), _ident, &_rating);
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

STDMETHODIMP CpEpEngine::OwnIdentitiesRetrieve(LPSAFEARRAY* ownIdentities)
{
    assert(ownIdentities);
    if (!ownIdentities)
        return E_INVALIDARG;

    *ownIdentities = nullptr;

    ::identity_list *il = nullptr;
    PEP_STATUS status = passphrase_cache.api(::own_identities_retrieve, session(), &il);
    if (status == PEP_OUT_OF_MEMORY) {
        return E_OUTOFMEMORY;
    }
    else if (status != PEP_STATUS_OK)
    {
        return FAIL(_T("OwnIdentitiesRetrieve"), status);
    }

    SAFEARRAY * _own_identities = nullptr;
    try {
        _own_identities = array_from_C<pEpIdentity, identity_list>(il);
    }
    catch (exception& ex)
    {
        ::free_identity_list(il);
        try {
            dynamic_cast<bad_alloc&>(ex);
        }
        catch (bad_cast&)
        {
            return FAIL(ex.what());
        }
        return E_OUTOFMEMORY;
    }
    free_identity_list(il);

    *ownIdentities = _own_identities;
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

    PEP_STATUS status = passphrase_cache.api(::trust_personal_key, session(), _ident);

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

// Force an update check now
STDMETHODIMP CpEpEngine::UpdateNow(BSTR productCode, VARIANT_BOOL *didUpdate)
{
    BOOL result = FALSE;

    try
    {
        _bstr_t pc(productCode);
        wstring _pc = pc;

        auto products = pEp::GateKeeper::gatekeeper()->registered_products();
        for (auto p = products.begin(); p != products.end(); ++p) {
            if (_pc == p->first) {
                result = pEp::GateKeeper::gatekeeper()->update_product(*p);
                break;
            }
        }
    }
    catch (bad_alloc&) {
        return E_OUTOFMEMORY;
    }
    catch (exception& ex) {
        return FAIL(ex.what());;
    }

    *didUpdate = result;
    return S_OK;
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

    // provide callbacks to sync
    LPSTREAM marshaled_callbacks = nullptr;
    auto result = CoMarshalInterThreadInterfaceInStream(IID_IpEpEngineCallbacks, client_callbacks, &marshaled_callbacks);
    assert(SUCCEEDED(result));
    assert(marshaled_callbacks);
    sync_callbacks.insert(new MarshaledCallbacks({ this->client_callbacks, marshaled_callbacks }));

    return S_OK;
}

STDMETHODIMP CpEpEngine::UnregisterCallbacks()
{
    // don't allow double deregistration.
    // S_FALSE still is no error (as double deregistration is not fatal).
    if (!this->client_callbacks)
        return S_FALSE;

    for (auto p = sync_callbacks.begin(); p != sync_callbacks.end(); ++p) {
        if (p->pdata && p->pdata->unmarshaled == this->client_callbacks) {
            if (p->pdata->marshaled)
                p->pdata->marshaled->Release();
            if (p->pdata->unmarshaled)
                p->pdata->unmarshaled->Release();
            delete p->pdata;
            p->pdata = nullptr;
            break;
        }
    }

    this->client_callbacks->Release();
    this->client_callbacks = nullptr;

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

    PEP_STATUS status = passphrase_cache.api(::OpenPGP_list_keyinfo, session(), _pattern.c_str(), &_keyinfo_list);
    assert(status != PEP_OUT_OF_MEMORY);
    if (status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    if (status != PEP_STATUS_OK)
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

STDMETHODIMP CpEpEngine::SetOwnKey(pEpIdentity * ident, BSTR fpr, struct pEpIdentity *result)
{
    assert(ident);
    assert(result);
    assert(fpr);

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

    string _fpr = utf8_string(fpr);
    PEP_STATUS status = passphrase_cache.api(::set_own_key, session(), _ident, _fpr.c_str());

    if (status == PEP_STATUS_OK) {
        copy_identity(result, _ident);
        ::free_identity(_ident);
        return S_OK;
    }
    else {
        ::free_identity(_ident);
        if (status == PEP_OUT_OF_MEMORY)
            return E_OUTOFMEMORY;
        else
            return FAIL(L"SetOwnKey", status);
    }

    return S_OK;
}

STDMETHODIMP CpEpEngine::TrustOwnKey(pEpIdentity * ident)
{
    assert(ident);

    if (!ident)
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

    PEP_STATUS status = passphrase_cache.api(::trust_own_key, session(), _ident);

    ::free_identity(_ident);

    if (status == PEP_STATUS_OK)
        return S_OK;
    else if (status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;
    else
        return FAIL(L"TrustOwnKey", status);
}

STDMETHODIMP CpEpEngine::Startup()
{
    try
    {
        // this must be unblocked, because it's not possible to have two API calls in parallel
        // start_sync() may send notifyHandshake() to ask for a passphrase; when this happens
        // the client needs to call ConfigPassphrase() while the startup process is being executed
        // so we need to return from Startup() immediately to make this possible

        pEp::Adapter::start_sync();
    }
    catch (bad_alloc&) {
        return E_OUTOFMEMORY;
    }
    catch (exception& ex) {
        return FAIL(ex.what());
    }

    return S_OK;
}

STDMETHODIMP CpEpEngine::GetKeyRating(BSTR fpr, pEpComType *commType)
{
    assert(fpr);

    if (!fpr)
        return E_INVALIDARG;

    string _fpr = utf8_string(fpr);

    PEP_comm_type _commType;
    PEP_STATUS status = passphrase_cache.api(::get_key_rating, session(), _fpr.c_str(), &_commType);
    if (status != PEP_STATUS_OK)
        return FAIL(L"cannot get key rating", status);

    *commType = (pEpComType)_commType;

    return S_OK;
}

STDMETHODIMP CpEpEngine::GetKeyRatingForUser(BSTR userId, BSTR fpr, pEpRating *rating)
{
    assert(userId);
    assert(fpr);

    if (!(userId && fpr))
        return E_INVALIDARG;

    string user_id = utf8_string(userId);
    string _fpr = utf8_string(fpr);

    PEP_rating _rating;
    PEP_STATUS status = passphrase_cache.api(::get_key_rating_for_user, session(), user_id.c_str(), _fpr.c_str(), &_rating);
    if (status != PEP_STATUS_OK)
        return FAIL(L"cannot get key rating for user", status);

    *rating = (pEpRating)_rating;

    return S_OK;
}

STDMETHODIMP CpEpEngine::DeliverHandshakeResult(enum SyncHandshakeResult result, SAFEARRAY *identities_sharing)
{
    sync_handshake_result _result = (sync_handshake_result)result;
    identity_list *_identities_sharing = NULL;
    if (identities_sharing)
    {
        try {
            _identities_sharing = identities(identities_sharing);
        }
        catch (bad_alloc&) {
            return E_OUTOFMEMORY;
        }
    }

    PEP_STATUS status = ::deliverHandshakeResult(session(), _result, _identities_sharing);
    free_identity_list(_identities_sharing);
    switch (status) {
    case PEP_STATUS_OK:
        break;
    case PEP_OUT_OF_MEMORY:
        return E_OUTOFMEMORY;
    default:
        return FAIL(L"deliverHandshakeResult is reporting an error", status);
    }

    return S_OK;
}

STDMETHODIMP CpEpEngine::PERToXERSyncMessage(TextMessage *msg, BSTR * xer)
{
    assert(msg);

    if (!msg)
        return E_INVALIDARG;

    ::message *_msg = NULL;
    try {
        _msg = text_message_to_C(msg);
    }
    catch (bad_alloc&) {
        return E_OUTOFMEMORY;
    }
    catch (exception& ex) {
        return FAIL(ex.what());
    }

    char* text;
    char* val = _msg->attachments->value;

    PEP_STATUS status = ::PER_to_XER_Sync_msg(val, strlen(val), &text);
    free_message(_msg);

    if (status != PEP_STATUS_OK)
        return FAIL(L"cannot get XER", status);

    *xer = utf16_bstr(text);
    pEp_free(text);

    return S_OK;
}

STDMETHODIMP CpEpEngine::DisableIdentityForSync(struct pEpIdentity * ident)
{
    assert(ident);

    if (!ident)
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

    PEP_STATUS status = passphrase_cache.api(::disable_identity_for_sync, session(), _ident);

    ::free_identity(_ident);

    if (status == PEP_STATUS_OK)
        return S_OK;
    else if (status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;
    else
        return FAIL(L"DisableIdentityForSync", status);
}

STDMETHODIMP CpEpEngine::EnableIdentityForSync(struct pEpIdentity * ident)
{
    assert(ident);

    if (!ident)
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

    PEP_STATUS status = passphrase_cache.api(::enable_identity_for_sync, session(), _ident);

    ::free_identity(_ident);

    if (status == PEP_STATUS_OK)
        return S_OK;
    else if (status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;
    else
        return FAIL(L"EnableIdentityForSync", status);
}

STDMETHODIMP CpEpEngine::PerMachineDirectory(BSTR * directory)
{
    assert(directory);

    if (!directory)
        return E_INVALIDARG;

    const char *_directory = ::per_machine_directory();

    if (_directory == NULL)
        return FAIL(L"PerMachineDirectory: _directory is NULL");

    *directory = utf16_bstr(_directory);

    return S_OK;
}

STDMETHODIMP CpEpEngine::PerUserDirectory(BSTR * directory)
{
    assert(directory);

    if (!directory)
        return E_INVALIDARG;

    const char *_directory = ::per_user_directory();

    if (_directory == NULL)
        return FAIL(L"PerUserDirectory: _directory is NULL");

    *directory = utf16_bstr(_directory);

    return S_OK;
}

STDMETHODIMP CpEpEngine::RatingFromCommType(pEpComType commType, pEpRating * rating)
{
    PEP_comm_type _comm_type = (PEP_comm_type)commType;
    PEP_rating _rating = ::rating_from_comm_type(_comm_type);

    *rating = (pEpRating)_rating;

    return S_OK;
}

STDMETHODIMP CpEpEngine::GetIsSyncRunning(VARIANT_BOOL *running)
{
    *running = pEp::Adapter::is_sync_running();
    return S_OK;
}

STDMETHODIMP CpEpEngine::ShutDownSync()
{
    pEp::Adapter::stop_sync();
    return S_OK;
}

STDMETHODIMP CpEpEngine::ConfigPassphrase(BSTR passphrase)
{
    string _passphrase = "";

    if (passphrase)
        _passphrase = utf8_string(passphrase);

    PEP_STATUS status = ::config_passphrase(session(), passphrase_cache.add(_passphrase));

    if (status == PEP_STATUS_OK)
        return S_OK;
    else if (status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;
    else
        return FAIL(L"ConfigPassphrase", status);
}

STDMETHODIMP CpEpEngine::ConfigPassphraseForNewKeys(VARIANT_BOOL enable, BSTR passphrase)
{
    string _passphrase = "";
    
    if (passphrase)
        _passphrase = utf8_string(passphrase);

    passphrase_for_new_keys = _passphrase;
    PEP_STATUS status = ::config_passphrase_for_new_keys(session(), enable, passphrase_cache.add_stored(_passphrase));

    if (status == PEP_STATUS_OK)
        return S_OK;
    else if (status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;
    else
        return FAIL(L"ConfigPassphraseForNewKeys", status);
}

STDMETHODIMP CpEpEngine::ShowNotification(BSTR title, BSTR message) 
{
    pEp::GateKeeper::gatekeeper()->show_notification(title, message);
    return S_OK;
}

STDMETHODIMP CpEpEngine::DisableAllSyncChannels() 
{
    PEP_STATUS status = passphrase_cache.api(::disable_all_sync_channels, session());

    if (status == PEP_STATUS_OK)
        return S_OK;
    else if (status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;
    else
        return FAIL(L"DisableAllSyncChannels", status);
}

// Group Management methods

STDMETHODIMP CpEpEngine::GroupCreate(pEpIdentity* groupIdentity, pEpIdentity* manager, SAFEARRAY* memberlist)
{
    assert(groupIdentity);
    assert(manager);

    if (!groupIdentity || !manager)
        return E_INVALIDARG;

    try
    {
        IdentityPtr _group_identity(new_identity(groupIdentity), free_identity);
        if (!_group_identity)
            return E_OUTOFMEMORY;
        IdentityPtr _manager_identity(new_identity(manager), free_identity);
        if (!_manager_identity)
            return E_OUTOFMEMORY;
        IdentityListPtr _member_ident_list(identities(memberlist), free_identity_list);
        if (!_member_ident_list)
            return E_OUTOFMEMORY;
    
        const PEP_STATUS status = ::adapter_group_create(session(), _group_identity.get(), _manager_identity.get(), _member_ident_list.get());

        switch (status) {
        case PEP_STATUS_OK:
            break;
        case PEP_OUT_OF_MEMORY:
            return E_OUTOFMEMORY;
        default:
            return FAIL(L"group_create is reporting an error", status);
        }
    }
    catch (bad_alloc&) {
        return E_OUTOFMEMORY;
    }
    catch (const exception& ex) {
        return FAIL(ex.what());
    }

    return ERROR_SUCCESS;
}

template<typename FUNCTION>
STDMETHODIMP CpEpEngine::group_operation(pEpIdentity* param1, pEpIdentity* param2, FUNCTION f, const wchar_t* f_name )
{
    assert(param1);
    assert(param2);

    if (!param1 || !param2)
        return E_INVALIDARG;

    try
    {
        IdentityPtr _group_identity(new_identity(param1), free_identity);
        if (!_group_identity)
            return E_OUTOFMEMORY;
        IdentityPtr _as_member(new_identity(param2), free_identity);
        if (!_as_member)
            return E_OUTOFMEMORY;

        const PEP_STATUS status = f(session(), _group_identity.get(), _as_member.get());

        switch (status) {
        case PEP_STATUS_OK:
            break;
        case PEP_OUT_OF_MEMORY:
            return E_OUTOFMEMORY;
        default:
            {
                std::wstringstream ss;
                ss << f_name << " is reporting an error";
                return FAIL(ss.str().c_str(), status);
            }
        }
    }
    catch (bad_alloc&) {
        return E_OUTOFMEMORY;
    }
    catch (const exception& ex) {
        return FAIL(ex.what());
    }

    return ERROR_SUCCESS;
}

STDMETHODIMP CpEpEngine::GroupJoin(pEpIdentity* groupIdentity, pEpIdentity* asMember)
{
    return group_operation(groupIdentity, asMember, adapter_group_join, L"adapter_group_join");
}

STDMETHODIMP CpEpEngine::GroupDissolve(pEpIdentity* groupIdentity, pEpIdentity* manager)
{
    return group_operation(groupIdentity, manager, adapter_group_dissolve, L"adapter_group_dissolve");
}

STDMETHODIMP CpEpEngine::GroupInviteMember(pEpIdentity* groupIdentity, pEpIdentity* groupMember)
{
    return group_operation(groupIdentity, groupMember, adapter_group_invite_member, L"adapter_group_invite_member");
}

STDMETHODIMP CpEpEngine::GroupRemoveMember(pEpIdentity* groupIdentity, pEpIdentity* groupMember)
{
    return group_operation(groupIdentity, groupMember, adapter_group_remove_member, L"adapter_group_remove_member");
}

STDMETHODIMP CpEpEngine::GroupRating(pEpIdentity* groupIdentity, pEpIdentity* manager, pEpRating* rating)
{
    assert(groupIdentity);
    assert(manager);

    if (!groupIdentity || !manager || !rating)
        return E_INVALIDARG;

    try
    {
        IdentityPtr _group_identity(new_identity(groupIdentity), free_identity);
        if (!_group_identity)
            return E_OUTOFMEMORY;
        IdentityPtr _as_member(new_identity(manager), free_identity);
        if (!_as_member)
            return E_OUTOFMEMORY;
        PEP_rating _rating;

        const PEP_STATUS status = ::group_rating(session(), _group_identity.get(), _as_member.get(), &_rating);
        *rating = (pEpRating)_rating;

        switch (status) {
        case PEP_STATUS_OK:
            break;
        case PEP_OUT_OF_MEMORY:
            return E_OUTOFMEMORY;
        default:
            return FAIL(L"group_create is reporting an error", status);
        }
    }
    catch (bad_alloc&) {
        return E_OUTOFMEMORY;
    }
    catch (const exception& ex) {
        return FAIL(ex.what());
    }

    return ERROR_SUCCESS;
}

STDMETHODIMP CpEpEngine::GroupQueryGroups(pEpIdentity* groupIdentity, LPSAFEARRAY* groupList)
{
    if (!groupList)
        return E_INVALIDARG;

    ::identity_list* il = nullptr;
    PEP_STATUS status = ::adapter_group_query_groups(session(), &il);
    if (status == PEP_OUT_OF_MEMORY) {
        return E_OUTOFMEMORY;
    }
    else if (status != PEP_STATUS_OK)
    {
        return FAIL(_T("GroupQueryGroups"), status);
    }

    SAFEARRAY* _group_list = nullptr;
    try {
        _group_list = array_from_C<pEpIdentity, identity_list>(il);
    }
    catch (exception& ex)
    {
        ::free_identity_list(il);
        try {
            dynamic_cast<bad_alloc&>(ex);
        }
        catch (bad_cast&)
        {
            return FAIL(ex.what());
        }
        return E_OUTOFMEMORY;
    }
    free_identity_list(il);

    *groupList = _group_list;
    return S_OK;
}

STDMETHODIMP CpEpEngine::GroupQueryManager(pEpIdentity* groupIdentity, pEpIdentity* manager)
{
    IdentityPtr _group_identity(new_identity(groupIdentity), free_identity);
    if (!_group_identity)
        return E_OUTOFMEMORY;

    ::pEp_identity* _ident;
    PEP_STATUS const status = ::adapter_group_query_manager(session(), _group_identity.get(), &_ident);
    if (status == PEP_OUT_OF_MEMORY) {
        return E_OUTOFMEMORY;
    }
    else if (status != PEP_STATUS_OK)
    {
        return FAIL(_T("GroupQueryManager"), status);
    }

    copy_identity(manager, _ident);
    ::free_identity(_ident);
    return S_OK;

}

STDMETHODIMP CpEpEngine::GroupQueryMembers(pEpIdentity* groupIdentity, LPSAFEARRAY* members)
{
    if (!members)
        return E_INVALIDARG;

    IdentityPtr _group_identity(new_identity(groupIdentity), free_identity);
    if (!_group_identity)
        return E_OUTOFMEMORY;

    ::identity_list* il = nullptr;
    PEP_STATUS const status = adapter_group_query_members(session(), _group_identity.get(), &il);

    if (status == PEP_OUT_OF_MEMORY) {
        return E_OUTOFMEMORY;
    }
    else if (status != PEP_STATUS_OK)
    {
        return FAIL(_T("GroupQueryMembers"), status);
    }

    SAFEARRAY* _members_list = nullptr;
    try {
        _members_list = array_from_C<pEpIdentity, identity_list>(il);
    }
    catch (exception& ex)
    {
        ::free_identity_list(il);
        try {
            dynamic_cast<bad_alloc&>(ex);
        }
        catch (bad_cast&)
        {
            return FAIL(ex.what());
        }
        return E_OUTOFMEMORY;
    }

    free_identity_list(il);
    *members = _members_list;
    return S_OK;
}

STDMETHODIMP CpEpEngine::SetIdentity(struct pEpIdentity* identity) {
    
    assert(identity);
    if (!identity)
        return E_INVALIDARG;

    ::pEp_identity* _ident = nullptr;

    try {
        _ident = new_identity(identity);
        assert(_ident);
        if (_ident == NULL)
            return E_OUTOFMEMORY;
    }
    catch (bad_alloc&) {
        return E_OUTOFMEMORY;
    }
    catch (exception& ex) {
        return FAIL(ex.what());
    }

    PEP_STATUS status = passphrase_cache.api(::set_identity, session(), (const ::pEp_identity*)_ident);
    ::free_identity(_ident);
    if (status != PEP_STATUS_OK)
        return FAIL(_T("SetIdentity"), status);

    return S_OK;
}

STDMETHODIMP CpEpEngine::SetCommPartnerKey(pEpIdentity* identity, BSTR fpr) {
    
    assert(identity);
    assert(fpr);
    if (!(identity && fpr))
        return E_INVALIDARG;

    ::pEp_identity* _ident = nullptr;

    try {
        _ident = new_identity(identity);
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

    string _fpr = utf8_string(fpr);

    PEP_STATUS status = passphrase_cache.api(::set_comm_partner_key, session(), _ident, _fpr.c_str());
    ::free_identity(_ident);
    if (status != PEP_STATUS_OK)
        return FAIL(_T("SetCommPartnerKey"), status);

    return S_OK;
}

STDMETHODIMP CpEpEngine::ImportKeyWithFprReturn(BSTR keyData, LPSAFEARRAY* privateKeys, LPSAFEARRAY* importedKeys)
{
    assert(keyData);

    if (!keyData)
        return E_INVALIDARG;

    string key_data = utf8_string(keyData);
    size_t size = SysStringLen(keyData);
    ::identity_list* private_keys = nullptr;
    ::stringlist_t* imported_keys = nullptr;
    if (importedKeys) {
        imported_keys = new_stringlist(*importedKeys);
    }

    PEP_STATUS status = passphrase_cache.api(::import_key_with_fpr_return, session(), key_data.c_str(), size, &private_keys, &imported_keys, (uint64_t*)nullptr);
    assert(status != ::PEP_OUT_OF_MEMORY);
    if (status == ::PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    if ((status != PEP_STATUS_OK) && (status != PEP_KEY_IMPORTED))
        return FAIL(L"ImportKeyWithFprReturn", status);

    SAFEARRAY* _privateKeys = nullptr;
    try {
        _privateKeys = array_from_C<pEpIdentity, identity_list>(private_keys);
    }
    catch (exception& ex)
    {
        ::free_identity_list(private_keys);
        try {
            dynamic_cast<bad_alloc&>(ex);
        }
        catch (bad_cast&)
        {
            return FAIL(ex.what());
        }
        return E_OUTOFMEMORY;
    }
    free_identity_list(private_keys);
    *privateKeys = _privateKeys;

    if (imported_keys) {
        if (importedKeys) {
            *importedKeys = string_array(imported_keys);
        }
        free_stringlist(imported_keys);
    }

    return status;
}