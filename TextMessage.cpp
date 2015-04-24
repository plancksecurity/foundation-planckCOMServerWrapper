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
