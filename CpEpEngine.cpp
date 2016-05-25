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

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

#define FAIL(msg) error(msg)

STDMETHODIMP CpEpEngine::verbose_logging(VARIANT_BOOL enable)
{
    verbose_mode = enable != VARIANT_FALSE;
    return S_OK;
}

STDMETHODIMP CpEpEngine::passive_mode(VARIANT_BOOL enable)
{
    ::config_passive_mode(get_session(), enable != VARIANT_FALSE);
    return S_OK;
}

STDMETHODIMP CpEpEngine::unencrypted_subject(VARIANT_BOOL enable)
{
    ::config_unencrypted_subject(get_session(), enable != VARIANT_FALSE);
    return S_OK;
}

STDMETHODIMP CpEpEngine::log(BSTR title, BSTR entity, BSTR description, BSTR comment)
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


STDMETHODIMP CpEpEngine::decrypt(BSTR ctext, BSTR * ptext, LPSAFEARRAY * key_list, pEp_STATUS * status)
{
    assert(ctext);
    assert(ptext);
    assert(key_list);
    assert(status);

    if (ctext == NULL || ptext == NULL || key_list == NULL || status == NULL) {
        if (ptext)
            *ptext = NULL;
        if (key_list)
            *key_list = NULL;
        if (status)
            *status = pEp_UNENCRYPTED;
        return E_INVALIDARG;
    }

    string _ctext = utf8_string(ctext);

    char *_ptext = NULL;
    size_t _psize = 0;
    ::stringlist_t *_keylist = NULL;
    PEP_STATUS _status;

    _status = ::decrypt_and_verify(get_session(), _ctext.c_str(), _ctext.size(), &_ptext, &_psize, &_keylist);
    assert(_status != PEP_OUT_OF_MEMORY);
    if (_status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    *status = (pEp_STATUS) _status;
    if (_ptext == NULL) {
        if (_keylist) {
            string msg;
            if (_keylist->value[0] != 0) {
                msg = _keylist->value;
            }
            else {
                for (::stringlist_t *s = _keylist->next; s != NULL; s = s->next) {
                    if (s->value) {
                        msg += s->value;
                        msg += ";";
                    }
                }
            }
            ::free_stringlist(_keylist);

            return FAIL(utf16_bstr(msg));
        }
        else
            return FAIL(L"cannot decrypt");
    }

    *ptext = utf16_bstr(_ptext);
    pEp_free(_ptext);

    if (_keylist && _keylist->value)
        *key_list = string_array(_keylist);
    else
        *key_list = NULL;
    ::free_stringlist(_keylist);

    return S_OK;
}

STDMETHODIMP CpEpEngine::decrypt_b(BSTR ctext, LPSAFEARRAY * ptext, LPSAFEARRAY * key_list, pEp_STATUS * status)
{
    assert(ctext);
    assert(ptext);
    assert(key_list);
    assert(status);

    if (ctext == NULL || ptext == NULL || key_list == NULL || status == NULL) {
        if (ptext)
            *ptext = NULL;
        if (key_list)
            *key_list = NULL;
        if (status)
            *status = pEp_UNENCRYPTED;
        return E_INVALIDARG;
    }

    // Welcome to Windoze string hell!

    char *_ctext = NULL;
    _bstr_t bstr_ctext(ctext, true);
    int w_csize = bstr_ctext.length() + 1;
    int _csize = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, (wchar_t *) bstr_ctext, w_csize, NULL, 0, NULL, NULL);
    if (_csize) {
        _ctext = new char[_csize];
        WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, (wchar_t *) bstr_ctext, w_csize, _ctext, _csize, NULL, NULL);
    }

    char *_ptext = NULL;
    size_t _psize = 0;
    ::stringlist_t *_keylist = NULL;
    PEP_STATUS _status;

    _status = ::decrypt_and_verify(get_session(), _ctext, _csize, &_ptext, &_psize, &_keylist);
    assert(_status != PEP_OUT_OF_MEMORY);
    delete[] _ctext;
    if (_status == PEP_OUT_OF_MEMORY) {
        ::free_stringlist(_keylist);
        return E_OUTOFMEMORY;
    }
    *status = (pEp_STATUS) _status;

    if (_ptext == NULL) {
        ::free_stringlist(_keylist);
        return FAIL(L"decrypt_and_verify");
    }

    CComSafeArray<BYTE> sa_ptext;

    HRESULT _result = sa_ptext.Create(_psize, 0);
    assert(_result == S_OK);
    if (_result == E_OUTOFMEMORY) {
        pEp_free(_ptext);
        ::free_stringlist(_keylist);
        return E_OUTOFMEMORY;
    }
    else if (_result != S_OK) {
        pEp_free(_ptext);
        ::free_stringlist(_keylist);
        return FAIL(L"CComSafeArray<BYTE>::Create");
    }

    memcpy(sa_ptext.m_psa->pvData, _ptext, _psize);
    *ptext = sa_ptext.Detach();
    ::pEp_free(_ptext);

    if (_keylist && _keylist->value)
        *key_list = string_array(_keylist);
    else
        *key_list = NULL;
    ::free_stringlist(_keylist);

    return S_OK;
}

STDMETHODIMP CpEpEngine::verify(BSTR text, BSTR signature, LPSAFEARRAY * key_list, pEp_STATUS * verify_status)
{
    assert(text);
    assert(signature);
    assert(key_list);

    if (text == NULL || signature == NULL || key_list == NULL)
        return E_INVALIDARG;

    string _text = utf8_string(text);
    string _signature = utf8_string(signature);

    ::stringlist_t *_keylist = NULL;
    PEP_STATUS _status;
    _status = ::verify_text(get_session(), _text.c_str(), _text.size(), _signature.c_str(), _signature.size(), &_keylist);
    assert(_status != PEP_OUT_OF_MEMORY);
    if (_status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;
    if (_status == PEP_DECRYPT_WRONG_FORMAT || _status == PEP_UNKNOWN_ERROR)
        return FAIL(L"verify_text");

    *verify_status = (pEp_STATUS) _status;

    if (_keylist && _keylist->value)
        *key_list = string_array(_keylist);
    else
        *key_list = NULL;
    ::free_stringlist(_keylist);

    return S_OK;
}

STDMETHODIMP CpEpEngine::encrypt(SAFEARRAY * key_list, BSTR ptext, BSTR * ctext, pEp_STATUS * status)
{
    assert(key_list);
    assert(ptext);
    assert(ctext);
    assert(status);

    if (ctext == NULL || ptext == NULL || key_list == NULL || status == NULL) {
        if (ctext)
            *ctext = NULL;
        if (status)
            *status = pEp_UNKNOWN_ERROR;
        return E_INVALIDARG;
    }

    HRESULT result = S_OK;

    ::stringlist_t *_keylist = new_stringlist(key_list);
    string _ptext = utf8_string(ptext);

    char *_ctext = NULL;
    size_t _csize = 0;
    PEP_STATUS _status;

    _status = ::encrypt_and_sign(get_session(), _keylist, _ptext.c_str(), _ptext.size(), &_ctext, &_csize);

    assert(_status != PEP_OUT_OF_MEMORY);
    ::free_stringlist(_keylist);
    if (_status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;
    *status = (pEp_STATUS) _status;

    if (_ctext == NULL)
        return FAIL(L"encrypt_and_sign");

    *ctext = utf16_bstr(_ctext);
    pEp_free(_ctext);

    return S_OK;
}

STDMETHODIMP CpEpEngine::encrypt_b(SAFEARRAY * key_list, SAFEARRAY * ptext, BSTR * ctext, pEp_STATUS * status)
{
    assert(key_list);
    assert(ptext);
    assert(ctext);
    assert(status);

    if (ctext == NULL || ptext == NULL || key_list == NULL || status == NULL) {
        if (ctext)
            *ctext = NULL;
        if (status)
            *status = pEp_UNKNOWN_ERROR;
        return E_INVALIDARG;
    }

    HRESULT result = S_OK;

    ::stringlist_t *_keylist = new_stringlist(key_list);

    char *_ctext = NULL;
    size_t _csize = 0;
    ::PEP_STATUS _status;

    _status = ::encrypt_and_sign(get_session(), _keylist, (const char *) ptext->pvData, ptext->rgsabound[0].cElements, &_ctext, &_csize);
    assert(_status != PEP_OUT_OF_MEMORY);
    ::free_stringlist(_keylist);
    if (_status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;
    *status = (pEp_STATUS) _status;

    if (_ctext == NULL)
        return FAIL(L"encrypt_and_sign");

    *status = (pEp_STATUS) _status;
    wchar_t *w_ctext = NULL;
    int w_csize = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, _ctext, _csize, NULL, 0);
    if (w_csize) {
        w_ctext = new wchar_t[w_csize + 1];
        MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, _ctext, _csize, w_ctext, w_csize);
        w_ctext[w_csize] = 0; // this is for debugging; Visual Studio will crash without that if you're unlucky
    }
    *ctext = ::SysAllocStringLen(w_ctext, w_csize);
    assert(ctext);
    delete[] w_ctext;
    pEp_free(_ctext);
    if (ctext == NULL)
        return E_OUTOFMEMORY;

    return S_OK;
}

STDMETHODIMP CpEpEngine::trustword(LONG value, BSTR lang, BSTR * word)
{
    assert(value >= 0 && value <= 65535);
    assert(word);

    HRESULT result = S_OK;

    uint16_t _value = 0;
    if (value < 0 || value > 65535)
        result = E_INVALIDARG;
    else
        _value = (uint16_t) value;

    string _lang = "en";
    if (lang) {
        _lang = utf8_string(lang);
        if (_lang.length() != 2)
            result = E_INVALIDARG;
    }

    if (word == NULL)
        result = E_INVALIDARG;

    if (result != S_OK)
        return result;

    char *_word = NULL;
    size_t _wsize = 0;

    PEP_STATUS status = ::trustword(get_session(), _value, _lang.c_str(), &_word, &_wsize);
    assert(status != PEP_OUT_OF_MEMORY);
    if (status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    if (_word == NULL) {
        *word = NULL;
        return FAIL(L"trustword");
    }
    else {
        *word = utf16_bstr(_word);
        pEp_free(_word);
        return S_OK;
    }
}

STDMETHODIMP CpEpEngine::trustwords(BSTR fpr, BSTR lang, LONG max_words, BSTR * words)
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
        return FAIL(L"trustwords");
    }
    else {
        *words = utf16_bstr(_words);
        pEp_free(_words);
        return S_OK;
    }
}

STDMETHODIMP CpEpEngine::get_crashdump_log(LONG maxlines, BSTR * log)
{
    assert(maxlines >= 0);
    assert(log);

    if (!(maxlines >= 0 && log))
        return E_INVALIDARG;

    char *_log;
    PEP_STATUS status = ::get_crashdump_log(get_session(), (int) maxlines, &_log);
    assert(status == PEP_STATUS_OK);
    if (status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;
    if (status != PEP_STATUS_OK || _log == NULL)
        return FAIL(L"get_crashdump_log");

    *log = utf16_bstr(_log);
    pEp_free(_log);
    return S_OK;
}

STDMETHODIMP CpEpEngine::get_languagelist(BSTR * languages)
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
        return FAIL(L"get_languagelist");

    *languages = utf16_bstr(_languages);
    pEp_free(_languages);
    return S_OK;
}

STDMETHODIMP CpEpEngine::get_phrase(BSTR lang, LONG phrase_id, BSTR * phrase)
{
    assert(lang && phrase_id >= 0 && phrase);

    if (!(lang && phrase_id >= 0 && phrase))
        return E_INVALIDARG;

    string _lang = utf8_string(lang);
    assert(_lang.length() == 2);
    if (_lang.length() != 2)
        return E_INVALIDARG;

    char *_phrase;
    PEP_STATUS status = ::get_phrase(get_session(), _lang.c_str(), (int) phrase_id, &_phrase);
    assert(status == PEP_STATUS_OK);
    if (status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;
    if (status != PEP_STATUS_OK || _phrase == NULL)
        return FAIL(L"get_phrase");

    *phrase = utf16_bstr(_phrase);
    pEp_free(_phrase);
    return S_OK;
}

STDMETHODIMP CpEpEngine::get_identity(BSTR address, BSTR user_id, pEp_identity_s * ident)
{
    assert(address);
    assert(user_id);
    assert(ident);

    if (address == NULL)
        return E_INVALIDARG;
    if (user_id == NULL)
        return E_INVALIDARG;
    if (ident == NULL)
        return E_INVALIDARG;

    string _address = utf8_string(address);
    string _user_id = utf8_string(user_id);

    ::pEp_identity *_ident = NULL;
    PEP_STATUS status = ::get_identity(get_session(), _address.c_str(), _user_id.c_str(), &_ident);
    assert(status != PEP_OUT_OF_MEMORY);
    if (status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    if (_ident == NULL) {
        return FAIL(L"get_identity");
    }

    copy_identity(ident, _ident);
    ::free_identity(_ident);

    return S_OK;
}

STDMETHODIMP CpEpEngine::set_identity(pEp_identity_s * ident)
{
    assert(ident);
    assert(ident->address);
    assert(ident->fpr);
    assert(ident->username);
    assert(ident->user_id);

    if (ident == NULL || ident->address == NULL || ident->fpr == NULL
        || ident->username == NULL || ident->user_id == NULL)
        return E_INVALIDARG;

    ::pEp_identity *_ident = new_identity(ident);
    ::PEP_STATUS status = ::set_identity(get_session(), _ident);
    ::free_identity(_ident);

    if (status != ::PEP_STATUS_OK)
        return FAIL(L"set_identity");
    else
        return S_OK;
}

STDMETHODIMP CpEpEngine::generate_keypair(pEp_identity_s * ident, BSTR * fpr)
{
    assert(ident);
    assert(ident->address);
    assert(ident->username);
    assert(fpr);

    if (ident == NULL || ident->address == NULL || ident->username == NULL || fpr == NULL)
        return E_INVALIDARG;

    ::pEp_identity *_ident = new_identity(ident);
    ::pEp_free(_ident->fpr);
    _ident->fpr = NULL;

    ::PEP_STATUS status = ::generate_keypair(get_session(), _ident);
    assert(status != ::PEP_OUT_OF_MEMORY);
    if (status == ::PEP_OUT_OF_MEMORY) {
        ::free_identity(_ident);
        return E_OUTOFMEMORY;
    }

    if (_ident->fpr)
        *fpr = utf16_bstr(_ident->fpr);

    ::free_identity(_ident);

    if (status != ::PEP_STATUS_OK)
        return FAIL(L"generate_keypair");

    return S_OK;
}

STDMETHODIMP CpEpEngine::delete_keypair(BSTR fpr)
{
    assert(fpr);

    if (fpr == NULL)
        return E_INVALIDARG;

    string _fpr = utf8_string(fpr);

    ::PEP_STATUS status = ::delete_keypair(get_session(), _fpr.c_str());
    assert(status != PEP_OUT_OF_MEMORY);
    if (status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    if (status != ::PEP_STATUS_OK)
        return FAIL(L"delete_keypair");
    else
        return S_OK;
}

STDMETHODIMP CpEpEngine::import_key(BSTR key_data)
{
    assert(key_data);

    if (key_data == NULL)
        return E_INVALIDARG;

    string _key_data = utf8_string(key_data);

    PEP_STATUS status = ::import_key(get_session(), _key_data.c_str(), _key_data.length());
    assert(status != PEP_OUT_OF_MEMORY);
    if (status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    if (status != pEp_STATUS_OK)
        return FAIL(L"import_key");
    else
        return S_OK;
}

STDMETHODIMP CpEpEngine::import_key_b(SAFEARRAY * key_data)
{
    assert(key_data);

    if (key_data == NULL)
        return E_INVALIDARG;

    ::PEP_STATUS status = ::import_key(get_session(), (const char *) key_data->pvData, key_data->rgsabound[0].cElements);
    assert(status != ::PEP_OUT_OF_MEMORY);
    if (status == ::PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    if (status != ::PEP_STATUS_OK)
        return FAIL(L"import_key");
    else
        return S_OK;
}

STDMETHODIMP CpEpEngine::export_key(BSTR fpr, BSTR * key_data)
{
    assert(fpr);
    assert(key_data);

    if (fpr == NULL || key_data == NULL)
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
    *key_data = b_key_data.Detach();

    return S_OK;
}

STDMETHODIMP CpEpEngine::recv_key(BSTR pattern)
{
    assert(pattern);

    if (pattern == NULL)
        return E_INVALIDARG;

    string _pattern = utf8_string(pattern);

    PEP_STATUS status = ::recv_key(get_session(), _pattern.c_str());
    assert(status != PEP_OUT_OF_MEMORY);
    if (status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    if (status != ::PEP_STATUS_OK)
        return FAIL(L"recv_key");
    else
        return S_OK;
}

STDMETHODIMP CpEpEngine::find_keys(BSTR pattern, LPSAFEARRAY * key_list)
{
    assert(pattern);
    assert(key_list);

    if (pattern == NULL || key_list == NULL)
        return E_INVALIDARG;

    string _pattern = utf8_string(pattern);
    ::stringlist_t *_keylist = NULL;

    PEP_STATUS status = ::find_keys(get_session(), _pattern.c_str(), &_keylist);
    assert(status != PEP_OUT_OF_MEMORY);
    if (status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    if (status != ::PEP_STATUS_OK)
        return FAIL(L"find_keys");

    if (_keylist && _keylist->value) {
        *key_list = string_array(_keylist);
    }
    else {
        ::free_stringlist(_keylist);
        return FAIL(L"find_keys: no keys found");
    }

    ::free_stringlist(_keylist);
    return S_OK;
}

STDMETHODIMP CpEpEngine::send_key(BSTR pattern)
{
    assert(pattern);

    if (pattern == NULL)
        return E_INVALIDARG;

    string _pattern = utf8_string(pattern);

    ::PEP_STATUS status = ::send_key(get_session(), _pattern.c_str());

    if (status != ::PEP_STATUS_OK)
        return FAIL(L"send_key");
    else
        return S_OK;
}

STDMETHODIMP CpEpEngine::start_keyserver_lookup()
{
    if (identity_queue.load())
        return S_OK;

    identity_queue.store(new identity_queue_t());
    keymanagement_thread = new thread(::do_keymanagement, retrieve_next_identity, (void *) identity_queue.load());
    
    return S_OK;
}

STDMETHODIMP CpEpEngine::stop_keyserver_lookup()
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

STDMETHODIMP CpEpEngine::examine_identity(pEp_identity_s * ident)
{
    assert(ident);
    if (ident == NULL)
        return E_INVALIDARG;

    if (identity_queue.load() == NULL) {
        try {
            identity_queue.load()->push_back(ident);
        }
        catch (bad_alloc) {
            return E_OUTOFMEMORY;
        }
    }

    return S_OK;
}

STDMETHODIMP CpEpEngine::myself(struct pEp_identity_s *ident, struct pEp_identity_s *result)
{
    assert(ident);
    assert(result);

    if (ident == NULL || result == NULL)
        return E_INVALIDARG;

    ::pEp_identity *_ident = new_identity(ident);
    assert(_ident);
    if (_ident == NULL)
        return E_OUTOFMEMORY;

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

STDMETHODIMP CpEpEngine::update_identity(struct pEp_identity_s *ident, struct pEp_identity_s *result)
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
            return FAIL(L"update_identity");
    }
}

STDMETHODIMP CpEpEngine::key_compromized(struct pEp_identity_s *ident)
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

    PEP_STATUS status = ::key_compromized(get_session(), _ident);
    free_identity(_ident);

    if (status == PEP_OUT_OF_MEMORY)
        return E_OUTOFMEMORY;

    if (status == PEP_KEY_NOT_FOUND)
        return FAIL(L"key not found");

    if (status != ::PEP_STATUS_OK)
        return FAIL(L"cannot revoke compromized key");

    return S_OK;
}

STDMETHODIMP CpEpEngine::key_reset_trust(struct pEp_identity_s *ident)
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

    CpEpEngine *me = (CpEpEngine *) management;

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
    identity_queue_t *iq = (identity_queue_t *) management;

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

PEP_STATUS CpEpEngine::messageToSend(void * obj, const message *msg)
{
    assert(msg);
    if (msg == NULL)
        return PEP_ILLEGAL_VALUE;

    text_message _msg;
    memset(&_msg, 0, sizeof(text_message));

    text_message_from_C(&_msg, msg);
    CpEpEngine *me = (CpEpEngine *) obj;
    HRESULT r = me->Fire_MessageToSend(&_msg);
    assert(r == S_OK);
    clear_text_message(&_msg);
    if (r == E_OUTOFMEMORY)
        return PEP_OUT_OF_MEMORY;
    if (r != S_OK)
        return PEP_UNKNOWN_ERROR;

    return PEP_STATUS_OK;
}

PEP_STATUS CpEpEngine::showHandshake(void * obj, const pEp_identity *self, const pEp_identity *partner)
{
    assert(self && partner);
    if (!(self && partner))
        return PEP_ILLEGAL_VALUE;

    pEp_identity_s _self;
    copy_identity(&_self, self);
    pEp_identity_s _partner;
    copy_identity(&_partner, partner);
    CpEpEngine *me = (CpEpEngine *) obj;
    sync_handshake_result_s _result;
    HRESULT r = me->Fire_ShowHandshake(&_self, &_partner, &_result);
    assert(r == S_OK);
    clear_identity_s(_self);
    clear_identity_s(_partner);
    if (r == E_OUTOFMEMORY)
        return PEP_OUT_OF_MEMORY;
    if (r != S_OK)
        return PEP_UNKNOWN_ERROR;

    PEP_STATUS status = deliverHandshakeResult(me->get_session(), (sync_handshake_result) (int) _result);
    return status;
}

STDMETHODIMP CpEpEngine::blacklist_add(BSTR fpr)
{
    assert(fpr);

    string _fpr = utf8_string(fpr);
    PEP_STATUS status = ::blacklist_add(get_session(), _fpr.c_str());
    assert(status == PEP_STATUS_OK);
    if (status != PEP_STATUS_OK)
        return FAIL(L"blacklist_add failed in pEp engine");

    return S_OK;
}

STDMETHODIMP CpEpEngine::blacklist_delete(BSTR fpr)
{
    assert(fpr);

    string _fpr = utf8_string(fpr);
    PEP_STATUS status = ::blacklist_delete(get_session(), _fpr.c_str());
    assert(status == PEP_STATUS_OK);
    if (status != PEP_STATUS_OK)
        return FAIL(L"blacklist_delete failed in pEp engine");

    return S_OK;
}

STDMETHODIMP CpEpEngine::blacklist_is_listed(BSTR fpr, VARIANT_BOOL *listed)
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

STDMETHODIMP CpEpEngine::blacklist_retrieve(SAFEARRAY **blacklist)
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

STDMETHODIMP CpEpEngine::encrypt_message(text_message * src, text_message * dst, SAFEARRAY * extra)
{
    assert(src);
    assert(dst);

    ::message *_src = text_message_to_C(src);
    ::message *msg_dst;
    ::stringlist_t *_extra = new_stringlist(extra);

    PEP_STATUS status = ::encrypt_message(get_session(), _src, _extra, &msg_dst, PEP_enc_pieces);
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

STDMETHODIMP CpEpEngine::decrypt_message(text_message * src, text_message * dst, SAFEARRAY ** keylist, pEp_color *rating)
{
    assert(src);
    assert(dst);
    assert(keylist);
    assert(rating);

    *keylist = NULL;
    *rating = pEp_rating_undefined;

    ::message *_src = text_message_to_C(src);
    ::message *msg_dst = NULL;
    ::stringlist_t *_keylist;
    ::PEP_color _rating;

    PEP_STATUS status = ::decrypt_message(get_session(), _src, &msg_dst, &_keylist, &_rating);

    if (msg_dst)
        text_message_from_C(dst, msg_dst);

    ::free_message(_src);
    ::free_message(msg_dst);

    if (_keylist) {
        *keylist = string_array(_keylist);
        free_stringlist(_keylist);
    }

    *rating = (pEp_color) _rating;

    return S_OK;
}

STDMETHODIMP CpEpEngine::outgoing_message_color(text_message *msg, pEp_color * pVal)
{
    assert(msg);
    assert(pVal);

    ::message *_msg = text_message_to_C(msg);

    PEP_color _color;
    PEP_STATUS status = ::outgoing_message_color(get_session(), _msg, &_color);
    if (status != PEP_STATUS_OK)
        return FAIL(L"cannot get message color");

    *pVal = (pEp_color) _color;
    return S_OK;
}

STDMETHODIMP CpEpEngine::identity_color(struct pEp_identity_s *ident, pEp_color * pVal)
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

    PEP_color _color;
    PEP_STATUS status = ::identity_color(get_session(), _ident, &_color);
    free_identity(_ident);
    if (status != PEP_STATUS_OK)
        return FAIL(L"cannot get message color");

    *pVal = (pEp_color) _color;
    return S_OK;
}

STDMETHODIMP CpEpEngine::trust_personal_key(struct pEp_identity_s *ident, struct pEp_identity_s *result)
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
        ss << "trust_personal_key called with ";
        ss << utf8_string(ident->address);
        ss << L": ";
        ss << ident->comm_type;
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
        return FAIL(L"failure while executing trust_personal_key()");

    return S_OK;
}
