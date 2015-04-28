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
    catch (bad_alloc& e) {
        return E_OUTOFMEMORY;
    }
    catch (exception& e) {
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
    catch (bad_alloc& e) {
        return E_OUTOFMEMORY;
    }
    catch (exception& e)
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
    ULONG i;
    for (i = 0, il = msg->to; il && il->ident; il = il->next, i++) {
        try {
            copy_identity(&cs[i], il->ident);
        }
        catch (bad_alloc& e) {
            SafeArrayUnaccessData(sa);
            SafeArrayDestroy(sa);
            return E_OUTOFMEMORY;
        }
        catch (exception& e) {
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
    LONG i, lbound, ubound;
    SafeArrayGetLBound(newVal, 1, &lbound);
    SafeArrayGetUBound(newVal, 1, &ubound);

    for (i = lbound, _il = il; i <= ubound; i++) {
        pEp_identity * ident;
        try {
            ident = new_identity(&cs[i]);
        }
        catch (bad_alloc& e) {
            SafeArrayUnaccessData(newVal);
            free_identity_list(il);
            return E_OUTOFMEMORY;
        }
        catch (exception& e) {
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
