// TextMessage.cpp : Implementation of CTextMessage

#include "stdafx.h"
#include "TextMessage.h"

using namespace pEp::utility;

// CTextMessage

STDMETHODIMP CTextMessage::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* const arr[] = 
	{
		&IID_ITextMessage
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CTextMessage::get_from(pEp_identity_s* pVal)
{
    assert(pVal);

    try {
        copy_identity(pVal, msg->from);
    }
    catch (bad_alloc&) {
        return E_OUTOFMEMORY;
    }
    catch (exception&) {
        return E_FAIL;
    }

    return S_OK;
}


STDMETHODIMP CTextMessage::put_from(pEp_identity_s* newVal)
{
    assert(newVal);

    ::pEp_identity *_from;
    
    try {
        _from = new_identity(newVal);
    }
    catch (bad_alloc&) {
        return E_OUTOFMEMORY;
    }
    catch (exception&)
    {
        return E_FAIL;
    }

    ::free_identity(msg->from);
    msg->from = _from;
    return S_OK;
}

STDMETHODIMP CTextMessage::get_to(LPSAFEARRAY * pVal)
{
    assert(pVal);

    int len = identity_list_length(msg->to);

    LPSAFEARRAY sa = newSafeArray<pEp_identity_s>(len);
    if (sa == NULL)
        return E_OUTOFMEMORY;

    pEp_identity_s *cs = accessData<pEp_identity_s>(sa);    

    identity_list *il = msg->to;
    LONG i;
    for (i = 0, il = msg->to; il && il->ident; il = il->next, i++) {
        try {
            copy_identity(&cs[i], il->ident);
        }
        catch (bad_alloc&) {
            SafeArrayUnaccessData(sa);
            SafeArrayDestroy(sa);
            return E_OUTOFMEMORY;
        }
        catch (exception&) {
            SafeArrayUnaccessData(sa);
            SafeArrayDestroy(sa);
            return E_FAIL;
        }
    }

    SafeArrayUnaccessData(sa);

    *pVal = sa;
    return S_OK;
}

STDMETHODIMP CTextMessage::put_to(SAFEARRAY * newVal)
{
    assert(newVal);

    if (newVal == NULL)
        return E_INVALIDARG;

    identity_list *il = new_identity_list(NULL);
    if (il == NULL)
        return E_OUTOFMEMORY;

    pEp_identity_s *cs;
    HRESULT hr = SafeArrayAccessData(newVal, (void **) &cs);
    assert(SUCCEEDED(hr) && cs);
    if (cs == NULL) {
        free_identity_list(il);
        return E_FAIL;
    }

    identity_list *_il;
    LONG lbound, ubound;
    LONG i;
    SafeArrayGetLBound(newVal, 1, &lbound);
    SafeArrayGetUBound(newVal, 1, &ubound);

    for (i = 0, _il = il; i < ubound - lbound + 1; i++) {
        pEp_identity * ident;
        try {
            ident = new_identity(&cs[i]);
        }
        catch (bad_alloc&) {
            SafeArrayUnaccessData(newVal);
            free_identity_list(il);
            return E_OUTOFMEMORY;
        }
        catch (exception&) {
            SafeArrayUnaccessData(newVal);
            free_identity_list(il);
            return E_FAIL;
        }
        _il = identity_list_add(_il, ident);
        if (_il == NULL) {
            SafeArrayUnaccessData(newVal);
            free_identity_list(il);
            return E_OUTOFMEMORY;
        }
    }

    SafeArrayUnaccessData(newVal);
    
    free_identity_list(msg->to);
    msg->to = il;

    return S_OK;
}

STDMETHODIMP CTextMessage::get_recv_by(pEp_identity_s* pVal)
{
    assert(pVal);

    try {
        copy_identity(pVal, msg->recv_by);
    }
    catch (bad_alloc&) {
        return E_OUTOFMEMORY;
    }
    catch (exception&) {
        return E_FAIL;
    }

    return S_OK;
}


STDMETHODIMP CTextMessage::put_recv_by(pEp_identity_s* newVal)
{
    assert(newVal);

    ::pEp_identity *_recv_by;

    try {
        _recv_by = new_identity(newVal);
    }
    catch (bad_alloc&) {
        return E_OUTOFMEMORY;
    }
    catch (exception&) {
        return E_FAIL;
    }

    ::free_identity(msg->recv_by);
    msg->recv_by = _recv_by;
    return S_OK;
}

STDMETHODIMP CTextMessage::get_cc(LPSAFEARRAY * pVal)
{
    assert(pVal);

    int len = identity_list_length(msg->cc);

    LPSAFEARRAY sa = newSafeArray<pEp_identity_s>(len);
    if (sa == NULL)
        return E_OUTOFMEMORY;

    pEp_identity_s *cs = accessData<pEp_identity_s>(sa);

    identity_list *il = msg->cc;
    LONG i;
    for (i = 0, il = msg->cc; il && il->ident; il = il->next, i++) {
        try {
            copy_identity(&cs[i], il->ident);
        }
        catch (bad_alloc&) {
            SafeArrayUnaccessData(sa);
            SafeArrayDestroy(sa);
            return E_OUTOFMEMORY;
        }
        catch (exception&) {
            SafeArrayUnaccessData(sa);
            SafeArrayDestroy(sa);
            return E_FAIL;
        }
    }

    SafeArrayUnaccessData(sa);

    *pVal = sa;
    return S_OK;
}

STDMETHODIMP CTextMessage::put_cc(SAFEARRAY * newVal)
{
    assert(newVal);

    if (newVal == NULL)
        return E_INVALIDARG;

    identity_list *il = new_identity_list(NULL);
    if (il == NULL)
        return E_OUTOFMEMORY;

    pEp_identity_s *cs;
    HRESULT hr = SafeArrayAccessData(newVal, (void **) &cs);
    assert(SUCCEEDED(hr) && cs);
    if (cs == NULL) {
        free_identity_list(il);
        return E_FAIL;
    }

    identity_list *_il;
    LONG lbound, ubound;
    LONG i;
    SafeArrayGetLBound(newVal, 1, &lbound);
    SafeArrayGetUBound(newVal, 1, &ubound);

    for (i = 0, _il = il; i < ubound - lbound + 1; i++) {
        pEp_identity * ident;
        try {
            ident = new_identity(&cs[i]);
        }
        catch (bad_alloc&) {
            SafeArrayUnaccessData(newVal);
            free_identity_list(il);
            return E_OUTOFMEMORY;
        }
        catch (exception&) {
            SafeArrayUnaccessData(newVal);
            free_identity_list(il);
            return E_FAIL;
        }
        _il = identity_list_add(_il, ident);
        if (_il == NULL) {
            SafeArrayUnaccessData(newVal);
            free_identity_list(il);
            return E_OUTOFMEMORY;
        }
    }

    SafeArrayUnaccessData(newVal);

    free_identity_list(msg->cc);
    msg->cc = il;

    return S_OK;
}

STDMETHODIMP CTextMessage::get_bcc(LPSAFEARRAY * pVal)
{
    assert(pVal);

    int len = identity_list_length(msg->bcc);

    LPSAFEARRAY sa = newSafeArray<pEp_identity_s>(len);
    if (sa == NULL)
        return E_OUTOFMEMORY;

    pEp_identity_s *cs = accessData<pEp_identity_s>(sa);

    identity_list *il = msg->bcc;
    LONG i;
    for (i = 0, il = msg->bcc; il && il->ident; il = il->next, i++) {
        try {
            copy_identity(&cs[i], il->ident);
        }
        catch (bad_alloc&) {
            SafeArrayUnaccessData(sa);
            SafeArrayDestroy(sa);
            return E_OUTOFMEMORY;
        }
        catch (exception&) {
            SafeArrayUnaccessData(sa);
            SafeArrayDestroy(sa);
            return E_FAIL;
        }
    }

    SafeArrayUnaccessData(sa);

    *pVal = sa;
    return S_OK;
}

STDMETHODIMP CTextMessage::put_bcc(SAFEARRAY * newVal)
{
    assert(newVal);

    if (newVal == NULL)
        return E_INVALIDARG;

    identity_list *il = new_identity_list(NULL);
    if (il == NULL)
        return E_OUTOFMEMORY;

    pEp_identity_s *cs;
    HRESULT hr = SafeArrayAccessData(newVal, (void **) &cs);
    assert(SUCCEEDED(hr) && cs);
    if (cs == NULL) {
        free_identity_list(il);
        return E_FAIL;
    }

    identity_list *_il;
    LONG lbound, ubound;
    LONG i;
    SafeArrayGetLBound(newVal, 1, &lbound);
    SafeArrayGetUBound(newVal, 1, &ubound);

    for (i = 0, _il = il; i < ubound - lbound + 1; i++) {
        pEp_identity * ident;
        try {
            ident = new_identity(&cs[i]);
        }
        catch (bad_alloc&) {
            SafeArrayUnaccessData(newVal);
            free_identity_list(il);
            return E_OUTOFMEMORY;
        }
        catch (exception&) {
            SafeArrayUnaccessData(newVal);
            free_identity_list(il);
            return E_FAIL;
        }
        _il = identity_list_add(_il, ident);
        if (_il == NULL) {
            SafeArrayUnaccessData(newVal);
            free_identity_list(il);
            return E_OUTOFMEMORY;
        }
    }

    SafeArrayUnaccessData(newVal);

    free_identity_list(msg->bcc);
    msg->bcc = il;

    return S_OK;
}

STDMETHODIMP CTextMessage::get_reply_to(LPSAFEARRAY * pVal)
{
    assert(pVal);

    int len = identity_list_length(msg->reply_to);

    LPSAFEARRAY sa = newSafeArray<pEp_identity_s>(len);
    if (sa == NULL)
        return E_OUTOFMEMORY;

    pEp_identity_s *cs = accessData<pEp_identity_s>(sa);

    identity_list *il = msg->reply_to;
    LONG i;
    for (i = 0, il = msg->reply_to; il && il->ident; il = il->next, i++) {
        try {
            copy_identity(&cs[i], il->ident);
        }
        catch (bad_alloc&) {
            SafeArrayUnaccessData(sa);
            SafeArrayDestroy(sa);
            return E_OUTOFMEMORY;
        }
        catch (exception&) {
            SafeArrayUnaccessData(sa);
            SafeArrayDestroy(sa);
            return E_FAIL;
        }
    }

    SafeArrayUnaccessData(sa);

    *pVal = sa;
    return S_OK;
}

STDMETHODIMP CTextMessage::put_reply_to(SAFEARRAY * newVal)
{
    assert(newVal);

    if (newVal == NULL)
        return E_INVALIDARG;

    identity_list *il = new_identity_list(NULL);
    if (il == NULL)
        return E_OUTOFMEMORY;

    pEp_identity_s *cs;
    HRESULT hr = SafeArrayAccessData(newVal, (void **) &cs);
    assert(SUCCEEDED(hr) && cs);
    if (cs == NULL) {
        free_identity_list(il);
        return E_FAIL;
    }

    identity_list *_il;
    LONG lbound, ubound;
    LONG i;
    SafeArrayGetLBound(newVal, 1, &lbound);
    SafeArrayGetUBound(newVal, 1, &ubound);

    for (i = 0, _il = il; i < ubound - lbound + 1; i++) {
        pEp_identity * ident;
        try {
            ident = new_identity(&cs[i]);
        }
        catch (bad_alloc&) {
            SafeArrayUnaccessData(newVal);
            free_identity_list(il);
            return E_OUTOFMEMORY;
        }
        catch (exception&) {
            SafeArrayUnaccessData(newVal);
            free_identity_list(il);
            return E_FAIL;
        }
        _il = identity_list_add(_il, ident);
        if (_il == NULL) {
            SafeArrayUnaccessData(newVal);
            free_identity_list(il);
            return E_OUTOFMEMORY;
        }
    }

    SafeArrayUnaccessData(newVal);

    free_identity_list(msg->reply_to);
    msg->reply_to = il;

    return S_OK;
}

STDMETHODIMP CTextMessage::get_dir(pEp_msg_direction *pVal)
{
    assert(pVal);

    *pVal = (pEp_msg_direction) msg->dir;

    return S_OK;
}

STDMETHODIMP CTextMessage::put_dir(pEp_msg_direction newVal)
{
    msg->dir = (PEP_msg_direction) newVal;

    return S_OK;
}

STDMETHODIMP CTextMessage::get_id(BSTR * pVal)
{
    assert(pVal);

    _bstr_t val;

    if (msg->id) {
        try {
            val = utf16_bstr(msg->id);
        }
        catch (bad_alloc&) {
            return E_OUTOFMEMORY;
        }
        catch (exception&) {
            return E_FAIL;
        }
        *pVal = val.Detach();
    }

    return S_OK;
}

STDMETHODIMP CTextMessage::put_id(BSTR newVal)
{
    char *_val = NULL;
    string val;

    if (newVal) {
        try {
            val = utf8_string(newVal);
        }
        catch (bad_alloc&) {
            return E_OUTOFMEMORY;
        }
        catch (exception&) {
            return E_FAIL;
        }

        _val = _strdup(val.c_str());
        if (_val == NULL)
            return E_OUTOFMEMORY;
    }

    if (msg->id)
        free(msg->id);

    msg->id = _val;
    return S_OK;
}

STDMETHODIMP CTextMessage::get_shortmsg(BSTR * pVal)
{
    assert(pVal);

    _bstr_t val;

    if (msg->shortmsg) {
        try {
            val = utf16_bstr(msg->shortmsg);
        }
        catch (bad_alloc&) {
            return E_OUTOFMEMORY;
        }
        catch (exception&) {
            return E_FAIL;
        }
        *pVal = val.Detach();
    }

    return S_OK;
}

STDMETHODIMP CTextMessage::put_shortmsg(BSTR newVal)
{
    char *_val = NULL;

    if (newVal) {
        string val;

        try {
            val = utf8_string(newVal);
        }
        catch (bad_alloc&) {
            return E_OUTOFMEMORY;
        }
        catch (exception&) {
            return E_FAIL;
        }

        _val = _strdup(val.c_str());
        if (_val == NULL)
            return E_OUTOFMEMORY;
    }

    if (msg->shortmsg)
        free(msg->shortmsg);

    msg->shortmsg = _val;
    return S_OK;
}

STDMETHODIMP CTextMessage::get_longmsg(BSTR * pVal)
{
    assert(pVal);

    _bstr_t val;

    if (msg->longmsg) {
        try {
            val = utf16_bstr(msg->longmsg);
        }
        catch (bad_alloc&) {
            return E_OUTOFMEMORY;
        }
        catch (exception&) {
            return E_FAIL;
        }
        *pVal = val.Detach();
    }

    return S_OK;
}

STDMETHODIMP CTextMessage::put_longmsg(BSTR newVal)
{
    char * _val = NULL;

    if (newVal) {
        string val;

        try {
            val = utf8_string(newVal);
        }
        catch (bad_alloc&) {
            return E_OUTOFMEMORY;
        }
        catch (exception&) {
            return E_FAIL;
        }

        _val = _strdup(val.c_str());
        if (_val == NULL)
            return E_OUTOFMEMORY;
    }

    if (msg->longmsg)
        free(msg->longmsg);

    msg->longmsg = _val;
    return S_OK;
}

STDMETHODIMP CTextMessage::get_longmsg_formatted(BSTR * pVal)
{
    assert(pVal);

    _bstr_t val;

    if (msg->longmsg_formatted) {
        try {
            val = utf16_bstr(msg->longmsg_formatted);
        }
        catch (bad_alloc&) {
            return E_OUTOFMEMORY;
        }
        catch (exception&) {
            return E_FAIL;
        }
        *pVal = val.Detach();
    }

    return S_OK;
}

STDMETHODIMP CTextMessage::put_longmsg_formatted(BSTR newVal)
{
    char *_val = NULL;

    if (newVal) {
        string val;

        try {
            val = utf8_string(newVal);
        }
        catch (bad_alloc&) {
            return E_OUTOFMEMORY;
        }
        catch (exception&) {
            return E_FAIL;
        }

        _val = _strdup(val.c_str());
        if (_val == NULL)
            return E_OUTOFMEMORY;
    }

    if (msg->longmsg_formatted)
        free(msg->longmsg_formatted);

    msg->longmsg_formatted = _val;
    return S_OK;
}

STDMETHODIMP CTextMessage::add_attachment(SAFEARRAY * data, BSTR mime_type, BSTR filename)
{
    assert(data);
    if (data == NULL)
        return E_INVALIDARG;

    CComSafeArray<BYTE> sa_data(data);
    size_t len = sa_data.GetCount();

    char *_data = (char *) malloc(sa_data.GetCount() + 1);
    assert(_data);
    if (_data == NULL)
        return E_OUTOFMEMORY;

    memcpy(_data, sa_data.m_psa->pvData, len);
    _data[len] = 0;
    sa_data.Detach();

    string _mime_type;
    if (mime_type) {
        try {
            _mime_type = utf8_string(mime_type);
        }
        catch (bad_alloc&) {
            free(_data);
            return E_OUTOFMEMORY;
        }
        catch (exception&) {
            free(_data);
            return E_FAIL;
        }
    }

    string _filename;
    if (filename) {
        try {
            _filename = utf8_string(filename);
        }
        catch (bad_alloc&) {
            free(_data);
            return E_OUTOFMEMORY;
        }
        catch (exception&) {
            free(_data);
            return E_FAIL;
        }
    }

    bloblist_t *blob = bloblist_add(msg->attachments, _data, len, _mime_type.c_str(), _filename.c_str());
    if (blob == NULL) {
        free(_data);
        return E_OUTOFMEMORY;
    }

    if (msg->attachments == NULL)
        msg->attachments = blob;

    return S_OK;
}

STDMETHODIMP CTextMessage::has_attachments(boolean *result)
{
    assert(result);

    if (msg->attachments == NULL || msg->attachments->data == NULL) {
        m_next_attachment = NULL;
        *result = false;
        return S_OK;
    }

    m_next_attachment = msg->attachments;
    *result = true;

    return S_OK;
}

STDMETHODIMP CTextMessage::next_attachment(SAFEARRAY ** data, BSTR * mime_type, BSTR * filename, boolean *result)
{
    assert(data);
    assert(mime_type);
    assert(filename);
    assert(result);

    if (m_next_attachment == NULL)
        return E_ILLEGAL_METHOD_CALL;

    CComSafeArray<BYTE> sa;
    try {
        sa.Create(m_next_attachment->size);
    }
    catch (bad_alloc&) {
        return E_OUTOFMEMORY;
    }

    memcpy(sa.m_psa->pvData, m_next_attachment->data, m_next_attachment->size);

    _bstr_t _mime_type;
    if (m_next_attachment->mime_type) {
        try {
            _mime_type = utf16_bstr(m_next_attachment->mime_type);
        }
        catch (bad_alloc&) {
            return E_OUTOFMEMORY;
        }
        catch (exception&) {
            return E_FAIL;
        }
    }

    _bstr_t _filename;
    if (m_next_attachment->filename) {
        try {
            _filename = utf16_bstr(m_next_attachment->filename);
        }
        catch (bad_alloc&) {
            return E_OUTOFMEMORY;
        }
        catch (exception&) {
            return E_FAIL;
        }
    }

    *data = sa.Detach();
    *mime_type = _mime_type.Detach();
    *filename = _filename.Detach();

    m_next_attachment = m_next_attachment->next;
    *result = m_next_attachment != NULL;

    return S_OK;
}

STDMETHODIMP CTextMessage::get_sent(hyper * result)
{
    assert(result);

    if (msg->sent == NULL)
        return E_NOT_SET;

    *result = mktime(msg->sent);
    return S_OK;
}

STDMETHODIMP CTextMessage::put_sent(hyper val)
{
    ::timestamp * ts = new_timestamp(val);
    if (ts == NULL)
        return E_OUTOFMEMORY;

    if (msg->sent)
        free_timestamp(msg->sent);
    msg->sent = ts;

    return S_OK;
}

STDMETHODIMP CTextMessage::get_recv(hyper * result)
{
    assert(result);

    if (msg->recv == NULL)
        return E_NOT_SET;

    *result = mktime(msg->recv);
    return S_OK;
}

STDMETHODIMP CTextMessage::put_recv(hyper val)
{
    ::timestamp * ts = new_timestamp(val);
    if (ts == NULL)
        return E_OUTOFMEMORY;

    if (msg->recv)
        free_timestamp(msg->recv);
    msg->recv = ts;

    return S_OK;
}

STDMETHODIMP CTextMessage::get_references(SAFEARRAY ** pVal)
{
    assert(pVal);

    CComSafeArray<BSTR> sa;
    try {
        if (msg->references) {
            sa = string_array(msg->references);
        }
        else {
            sa.Create(0UL);
        }
    }
    catch (bad_alloc&) {
        return E_OUTOFMEMORY;
    }
    catch (exception&) {
        return E_FAIL;
    }
    
    *pVal = sa.Detach();
    return S_OK;
}

STDMETHODIMP CTextMessage::put_references(SAFEARRAY * newVal)
{
    assert(newVal);

    stringlist_t *sl;
    
    try {
        sl = new_stringlist(newVal);
    }
    catch (bad_alloc&) {
        return E_OUTOFMEMORY;
    }
    catch (exception&) {
        return E_FAIL;
    }

    if (msg->references)
        free_stringlist(msg->references);

    msg->references = sl;

    return S_OK;
}

STDMETHODIMP CTextMessage::get_keywords(SAFEARRAY ** pVal)
{
    assert(pVal);

    CComSafeArray<BSTR> sa;
    try {
        if (msg->keywords) {
            sa = string_array(msg->keywords);
        }
        else {
            sa.Create(0UL);
        }
    }
    catch (bad_alloc&) {
        return E_OUTOFMEMORY;
    }
    catch (exception&) {
        return E_FAIL;
    }

    *pVal = sa.Detach();
    return S_OK;
}

STDMETHODIMP CTextMessage::put_keywords(SAFEARRAY * newVal)
{
    assert(newVal);

    stringlist_t *sl;

    try {
        sl = new_stringlist(newVal);
    }
    catch (bad_alloc&) {
        return E_OUTOFMEMORY;
    }
    catch (exception&) {
        return E_FAIL;
    }

    if (msg->keywords)
        free_stringlist(msg->keywords);

    msg->keywords = sl;

    return S_OK;
}

STDMETHODIMP CTextMessage::get_comments(BSTR * pVal)
{
    assert(pVal);

    _bstr_t val;

    if (msg->comments) {
        try {
            val = utf16_bstr(msg->comments);
        }
        catch (bad_alloc&) {
            return E_OUTOFMEMORY;
        }
        catch (exception&) {
            return E_FAIL;
        }
        *pVal = val.Detach();
    }

    return S_OK;
}

STDMETHODIMP CTextMessage::put_comments(BSTR newVal)
{
    char * _val = NULL;

    if (newVal) {
        string val;

        try {
            val = utf8_string(newVal);
        }
        catch (bad_alloc&) {
            return E_OUTOFMEMORY;
        }
        catch (exception&) {
            return E_FAIL;
        }

        _val = _strdup(val.c_str());
        if (_val == NULL)
            return E_OUTOFMEMORY;
    }

    if (msg->comments)
        free(msg->comments);

    msg->comments = _val;
    return S_OK;
}

STDMETHODIMP CTextMessage::get_opt_fields(LPSAFEARRAY * pVal)
{
    assert(pVal);

    if (msg->opt_fields == NULL)
        return S_OK;

    int len = stringpair_list_length(msg->opt_fields);

    LPSAFEARRAY sa = newSafeArray<struct opt_field>(len);
    if (sa == NULL)
        return E_OUTOFMEMORY;

    struct opt_field *cs = accessData<struct opt_field>(sa);

    stringpair_list_t *il;
    LONG i;
    for (i = 0, il = msg->opt_fields; il && il->value; il = il->next, i++) {
        try {
            _bstr_t key = utf16_bstr(il->value->key);
            _bstr_t value = utf16_bstr(il->value->value);
            
            cs[i].name = key.Detach();
            cs[i].value = value.Detach();
        }
        catch (bad_alloc&) {
            SafeArrayUnaccessData(sa);
            SafeArrayDestroy(sa);
            return E_OUTOFMEMORY;
        }
        catch (exception&) {
            SafeArrayUnaccessData(sa);
            SafeArrayDestroy(sa);
            return E_FAIL;
        }
    }

    SafeArrayUnaccessData(sa);

    *pVal = sa;
    return S_OK;
}

STDMETHODIMP CTextMessage::put_opt_fields(SAFEARRAY * newVal)
{
    assert(newVal);

    if (newVal == NULL)
        return E_INVALIDARG;

    stringpair_list_t *il = new_stringpair_list(NULL);
    if (il == NULL)
        return E_OUTOFMEMORY;

    struct opt_field *cs;
    HRESULT hr = SafeArrayAccessData(newVal, (void **) &cs);
    assert(SUCCEEDED(hr) && cs);
    if (cs == NULL) {
        free_stringpair_list(il);
        return E_FAIL;
    }

    stringpair_list_t *_il;
    LONG lbound, ubound;
    LONG i;
    SafeArrayGetLBound(newVal, 1, &lbound);
    SafeArrayGetUBound(newVal, 1, &ubound);

    for (i = 0, _il = il; i < ubound - lbound + 1; i++) {
        stringpair_t * pair;
        try {
            pair = new_stringpair(utf8_string(cs[i].name).c_str(), utf8_string(cs[i].value).c_str());
        }
        catch (bad_alloc&) {
            SafeArrayUnaccessData(newVal);
            free_stringpair_list(il);
            return E_OUTOFMEMORY;
        }
        catch (exception&) {
            SafeArrayUnaccessData(newVal);
            free_stringpair_list(il);
            return E_FAIL;
        }
        _il = stringpair_list_add(_il, pair);
        if (_il == NULL) {
            SafeArrayUnaccessData(newVal);
            free_stringpair_list(il);
            return E_OUTOFMEMORY;
        }
    }

    SafeArrayUnaccessData(newVal);

    free_stringpair_list(msg->opt_fields);
    msg->opt_fields = il;

    return S_OK;
}
