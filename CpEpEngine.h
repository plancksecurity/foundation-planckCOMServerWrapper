// CpEpEngine.h : Declaration of the CpEpEngine

#pragma once
#include "resource.h"       // main symbols



#include "pEpComServerAdapter_i.h"
#include "_IpEpEngineEvents_CP.h"
#include "locked_queue.hh"
#include "utf8_helper.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;
using namespace utility;


// CpEpEngine

class ATL_NO_VTABLE CpEpEngine :
    public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CpEpEngine, &CLSID_pEpEngine>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CpEpEngine>,
	public CProxy_IpEpEngineEvents<CpEpEngine>,
	public IpEpEngine,
    public IMessageAPI_Outlook
{
public:
	CpEpEngine()
	{
        PEP_STATUS status = ::init(&m_session);
        assert(status == PEP_STATUS_OK);
        ::log_event(m_session, "Startup", "pEp COM Adapter", NULL, NULL);
        identity_queue = new identity_queue_t();
        keymanagement_thread = new thread(::do_keymanagement, retrieve_next_identity, (void *) identity_queue);
        keymanagement_thread->detach();
    }
    ~CpEpEngine()
    {
        pEp_identity_cpp shutdown;
        identity_queue->push_front(shutdown);
        ::log_event(m_session, "Shutdown", "pEp COM Adapter", NULL, NULL);
        ::release(m_session);
    }

DECLARE_REGISTRY_RESOURCEID(IDR_PEPENGINE)

DECLARE_NOT_AGGREGATABLE(CpEpEngine)

BEGIN_COM_MAP(CpEpEngine)
    COM_INTERFACE_ENTRY(IpEpEngine)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
    COM_INTERFACE_ENTRY(IConnectionPointContainer)
    COM_INTERFACE_ENTRY(IMessageAPI_Outlook)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CpEpEngine)
	CONNECTION_POINT_ENTRY(__uuidof(_IpEpEngineEvents))
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


protected:
    struct pEp_identity_cpp {
        std::string address;
        std::string fpr;
        std::string user_id;
        std::string username;
        pEp_comm_type comm_type;
        std::string lang;
        bool me;

        pEp_identity_cpp(
            std::string _address = std::string(),
            std::string _fpr = std::string(),
            std::string _user_id = std::string(),
            std::string _username = std::string(),
            pEp_comm_type _comm_type = pEp_ct_unknown,
            std::string _lang = std::string()
            ) : address(_address), fpr(_fpr), user_id(_user_id), username(_username), comm_type(_comm_type), lang(_lang), me(false)
        { }

        pEp_identity_cpp(const ::pEp_identity *_ident)
            : me(false)
        {
            if (_ident->address)
                address = _ident->address;
            if (_ident->fpr)
                fpr = _ident->fpr;
            if (_ident->user_id)
                user_id = _ident->user_id;
            if (_ident->username)
                username = _ident->username;
            comm_type = (pEp_comm_type) _ident->comm_type;
            lang = _ident->lang;
        }

        pEp_identity_cpp(const pEp_identity_s *_ident)
            : me(false)
        {
            if (_ident->address)
                address = utf8_string(_ident->address);
            if (_ident->fpr)
                fpr = utf8_string(_ident->fpr);
            if (_ident->user_id)
                user_id = utf8_string(_ident->user_id);
            if (_ident->username)
                username = utf8_string(_ident->username);
            comm_type = _ident->comm_type;
            if (_ident->lang)
                lang = utf8_string(_ident->lang);
        }
    };

    class session
    {
    private:
        CpEpEngine *me;

    public:
        session(CpEpEngine *myself)
        {
            me = myself;
            me->session_mutex.lock();
        }

        ~session()
        {
            me->session_mutex.unlock();
        }

        operator PEP_SESSION const () 
        {
            return me->m_session;
        }
    };

    session get_session()
    {
        return session(this);
    }

    static ::pEp_identity *new_identity(const pEp_identity_cpp&);

    typedef locked_queue<pEp_identity_cpp> identity_queue_t;
    static ::pEp_identity * retrieve_next_identity(void *management);
    HRESULT error(_bstr_t msg);

private:
    PEP_SESSION m_session;
    mutex session_mutex;
    identity_queue_t *identity_queue;
    thread *keymanagement_thread;

public:
    STDMETHOD(log)(BSTR title, BSTR entity, BSTR description, BSTR comment);
    STDMETHOD(decrypt)(BSTR ctext, BSTR * ptext, LPSAFEARRAY * key_list, pEp_STATUS * decrypt_status);
    STDMETHOD(decrypt_b)(BSTR ctext, LPSAFEARRAY * ptext, LPSAFEARRAY * key_list, pEp_STATUS * decrypt_status);
    STDMETHOD(encrypt)(SAFEARRAY * key_list, BSTR ptext, BSTR * ctext, pEp_STATUS * status);
    STDMETHOD(encrypt_b)(SAFEARRAY * key_list, SAFEARRAY * ptext, BSTR * ctext, pEp_STATUS * status);
    STDMETHOD(safeword)(LONG value, BSTR lang, BSTR * word);
    STDMETHOD(safewords)(BSTR fpr, BSTR lang, LONG max_words, BSTR * words);
    STDMETHOD(get_identity)(BSTR address, pEp_identity_s * ident);
    STDMETHOD(set_identity)(pEp_identity_s * ident);
    STDMETHOD(generate_keypair)(pEp_identity_s * ident, BSTR * fpr);
    STDMETHOD(delete_keypair)(BSTR fpr);
    STDMETHOD(import_key)(BSTR key_data);
    STDMETHOD(import_key_b)(SAFEARRAY * key_data);
    STDMETHOD(export_key)(BSTR fpr, BSTR * key_data);
    STDMETHOD(recv_key)(BSTR pattern);
    STDMETHOD(find_keys)(BSTR pattern, LPSAFEARRAY * key_list);
    STDMETHOD(send_key)(BSTR pattern);
    STDMETHOD(examine_identity)(pEp_identity_s * ident);
    STDMETHOD(examine_myself)(pEp_identity_s * myself);
    STDMETHOD(verify)(BSTR text, BSTR signature, LPSAFEARRAY * key_list, pEp_STATUS * verify_status);
    STDMETHOD(myself)(struct pEp_identity_s *ident, struct pEp_identity_s *result);
    STDMETHOD(update_identity)(struct pEp_identity_s *ident, struct pEp_identity_s *result);

    // IMessageAPI_Outlook
    STDMETHOD(key_compromized)(BSTR fpr);
    STDMETHOD(get_outlook)(IMessageAPI_Outlook* pVal);
};

OBJECT_ENTRY_AUTO(__uuidof(pEpEngine), CpEpEngine)
