// TextMessage.h : Declaration of the CTextMessage

#pragma once
#include "resource.h"       // main symbols


#include "pEpCOMServerAdapter_i.h"
#include "_ITextMessageEvents_CP.h"

#include "pEp_identity_helper.h"

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
    ::bloblist_t *m_next_attachment;
    mutex message_mutex;
    ::message *_msg;

protected:
    class Msg {
    private:
        CTextMessage *me;

    public:
        Msg(CTextMessage *myself)
        {
            me = myself;
            me->message_mutex.lock();
        }

        ~Msg()
        {
            me->message_mutex.unlock();
        }

        ::message * operator->()
        {
            return me->_msg;
        }

        operator ::message *()
        {
            return me->_msg;
        }
    };

public:
    Msg msg()
    {
        return Msg(this);
    }

    void msg(::message *new_msg)
    {
        lock_guard<mutex> lg(message_mutex);

        ::free_message(_msg);
        _msg = new_msg;
    }

    CTextMessage()
        : m_next_attachment(NULL)
	{
        _msg = (::message *) calloc(1, sizeof(::message));
        assert(_msg);
        if (_msg == NULL)
            throw bad_alloc();
	}

    // the violation of the rule of three is intended

    CTextMessage(const CTextMessage& second)
        : m_next_attachment(NULL)
    {
        _msg = (::message *) calloc(1, sizeof(::message));
        assert(_msg);
        if (_msg == NULL)
            throw bad_alloc();
    }

    virtual ~CTextMessage()
    {
        ::free_message(_msg);
    }

DECLARE_REGISTRY_RESOURCEID(IDR_TEXTMESSAGE)

DECLARE_NOT_AGGREGATABLE(CTextMessage)

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
    STDMETHOD(get_dir)(pEp_msg_direction * pVal);
    STDMETHOD(put_dir)(pEp_msg_direction newVal);

    STDMETHOD(get_id)(BSTR * pVal);
    STDMETHOD(put_id)(BSTR newVal);

    STDMETHOD(get_shortmsg)(BSTR * pVal);
    STDMETHOD(put_shortmsg)(BSTR newVal);

    STDMETHOD(get_longmsg)(BSTR * pVal);
    STDMETHOD(put_longmsg)(BSTR newVal);

    STDMETHOD(get_longmsg_formatted)(BSTR * pVal);
    STDMETHOD(put_longmsg_formatted)(BSTR newVal);

    STDMETHOD(add_attachment)(SAFEARRAY * data, BSTR mime_type, BSTR filename);
    STDMETHOD(has_attachments)(boolean *result);
    STDMETHOD(next_attachment)(SAFEARRAY ** data, BSTR * mime_type, BSTR * filename, boolean *result);

    STDMETHOD(get_sent)(hyper * result);
    STDMETHOD(put_sent)(hyper val);

    STDMETHOD(get_recv)(hyper * result);
    STDMETHOD(put_recv)(hyper val);

    STDMETHOD(get_from)(pEp_identity_s * pVal);
    STDMETHOD(put_from)(pEp_identity_s * newVal);

    STDMETHOD(get_to)(LPSAFEARRAY * pVal);
    STDMETHOD(put_to)(SAFEARRAY * newVal);

    STDMETHOD(get_recv_by)(pEp_identity_s * pVal);
    STDMETHOD(put_recv_by)(pEp_identity_s * newVal);

    STDMETHOD(get_cc)(LPSAFEARRAY * pVal);
    STDMETHOD(put_cc)(SAFEARRAY * newVal);

    STDMETHOD(get_bcc)(LPSAFEARRAY * pVal);
    STDMETHOD(put_bcc)(SAFEARRAY * newVal);

    STDMETHOD(get_reply_to)(LPSAFEARRAY * pVal);
    STDMETHOD(put_reply_to)(SAFEARRAY * newVal);

    STDMETHOD(get_references)(SAFEARRAY ** pVal);
    STDMETHOD(put_references)(SAFEARRAY * newVal);

    STDMETHOD(get_keywords)(SAFEARRAY ** pVal);
    STDMETHOD(put_keywords)(SAFEARRAY * newVal);

    STDMETHOD(get_comments)(BSTR * pVal);
    STDMETHOD(put_comments)(BSTR newVal);

    STDMETHOD(get_opt_fields)(LPSAFEARRAY * pVal);
    STDMETHOD(put_opt_fields)(SAFEARRAY * newVal);
};

OBJECT_ENTRY_AUTO(__uuidof(TextMessage), CTextMessage)
