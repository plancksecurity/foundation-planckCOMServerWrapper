// TextMessage.h : Declaration of the CTextMessage

#pragma once
#include "resource.h"       // main symbols


#include "pEpCOMServerAdapter_i.h"
#include "_ITextMessageEvents_CP.h"

#include "pEp_identity_cpp.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;
using namespace std;

// CTextMessage

class ATL_NO_VTABLE CTextMessage :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTextMessage, &CLSID_TextMessage>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CTextMessage>,
	public CProxy_ITextMessageEvents<CTextMessage>,
	public ITextMessage
{
private:
    ::message *msg;

public:
	CTextMessage()
	{
        msg = (::message *) calloc(1, sizeof(::message));
        assert(msg);
        if (msg == NULL)
            throw bad_alloc();
	}

    CTextMessage(const CTextMessage& second)
    {
        msg = ::message_dup(second.msg);
        assert(msg);
        if (msg == NULL)
            throw bad_alloc();
    }

    CTextMessage(const ::message *second)
    {
        assert(second);
        msg = ::message_dup(second);
        assert(msg);
        if (msg == NULL)
            throw bad_alloc();
    }

    virtual ~CTextMessage()
    {
        ::free_message(msg);
    }

DECLARE_REGISTRY_RESOURCEID(IDR_TEXTMESSAGE)


BEGIN_COM_MAP(CTextMessage)
	COM_INTERFACE_ENTRY(ITextMessage)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CTextMessage)
	CONNECTION_POINT_ENTRY(__uuidof(_ITextMessageEvents))
END_CONNECTION_POINT_MAP()
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



    STDMETHOD(get_from)(pEp_identity_s* pVal);
    STDMETHOD(put_from)(pEp_identity_s* newVal);
};

OBJECT_ENTRY_AUTO(__uuidof(TextMessage), CTextMessage)
