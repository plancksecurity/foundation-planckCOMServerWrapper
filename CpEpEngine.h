// CpEpEngine.h : Declaration of the CpEpEngine

#pragma once
#include "resource.h"       // main symbols

#include "pEpComServerAdapter_i.h"
#include "_IpEpEngineEvents_CP.h"
#include "locked_queue.hh"
#include "utf8_helper.h"
#include "pEp_utility.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;
using namespace utility;
using namespace pEp::utility;

// CpEpEngine

class ATL_NO_VTABLE CpEpEngine :
    public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CpEpEngine, &CLSID_pEpEngine>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CpEpEngine>,
	public CProxy_IpEpEngineEvents<CpEpEngine>,
	public IpEpEngine
{
protected:
    static int examine_identity(pEp_identity *ident, void *management);

public:
    CpEpEngine() : keymanagement_thread(NULL), identity_queue(NULL), verbose_mode(false)
	{
        PEP_STATUS status = ::init(&m_session);
        assert(status == PEP_STATUS_OK);
        ::register_examine_function(m_session, CpEpEngine::examine_identity, (void *)this);
        ::log_event(m_session, "Startup", "pEp COM Adapter", NULL, NULL);
    }

    ~CpEpEngine()
    {
        stop_keyserver_lookup();
        ::log_event(m_session, "Shutdown", "pEp COM Adapter", NULL, NULL);
        ::release(m_session);
    }

DECLARE_REGISTRY_RESOURCEID(IDR_PEPENGINE)

DECLARE_NOT_AGGREGATABLE(CpEpEngine)

BEGIN_COM_MAP(CpEpEngine)
    COM_INTERFACE_ENTRY(IpEpEngine)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
    COM_INTERFACE_ENTRY(IConnectionPointContainer)
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

    typedef locked_queue<pEp_identity_cpp> identity_queue_t;
    static ::pEp_identity * retrieve_next_identity(void *management);
    HRESULT error(_bstr_t msg);

    void verbose(string text)
    {
        if (verbose_mode) {
            stringstream ss;
            ss << __FILE__ << ":" << __LINE__ << " " << text;
            ::log_event(get_session(), "verbose", "pEp COM Server Adapter", ss.str().c_str(), NULL);
        }
    }

private:
    PEP_SESSION m_session;
    mutex session_mutex;
    atomic< identity_queue_t * > identity_queue;
    thread *keymanagement_thread;
    bool verbose_mode;

public:
    // runtime config of the adapter

    STDMETHOD(verbose_logging)(BOOL enable);
    
    // runtime config of the engine

    STDMETHOD(passive_mode)(BOOL enable);
    STDMETHOD(unencrypted_subject)(BOOL enable);

    // basic API

    STDMETHOD(log)(BSTR title, BSTR entity, BSTR description, BSTR comment);
    STDMETHOD(decrypt)(BSTR ctext, BSTR * ptext, LPSAFEARRAY * key_list, pEp_STATUS * decrypt_status);
    STDMETHOD(decrypt_b)(BSTR ctext, LPSAFEARRAY * ptext, LPSAFEARRAY * key_list, pEp_STATUS * decrypt_status);
    STDMETHOD(encrypt)(SAFEARRAY * key_list, BSTR ptext, BSTR * ctext, pEp_STATUS * status);
    STDMETHOD(encrypt_b)(SAFEARRAY * key_list, SAFEARRAY * ptext, BSTR * ctext, pEp_STATUS * status);
    STDMETHOD(trustword)(LONG value, BSTR lang, BSTR * word);
    STDMETHOD(trustwords)(BSTR fpr, BSTR lang, LONG max_words, BSTR * words);
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
    STDMETHOD(get_crashdump_log)(LONG maxlines, BSTR * log);
    STDMETHOD(get_languagelist)(BSTR * languages);
    STDMETHOD(get_phrase)(BSTR lang, LONG phrase_id, BSTR * phrase);

    // keymanagement API

    STDMETHOD(start_keyserver_lookup)();
    STDMETHOD(stop_keyserver_lookup)();

    STDMETHOD(examine_identity)(pEp_identity_s * ident);
    STDMETHOD(verify)(BSTR text, BSTR signature, LPSAFEARRAY * key_list, pEp_STATUS * verify_status);
    STDMETHOD(myself)(struct pEp_identity_s *ident, struct pEp_identity_s *result);
    STDMETHOD(update_identity)(struct pEp_identity_s *ident, struct pEp_identity_s *result);
    STDMETHOD(key_compromized)(struct pEp_identity_s *ident);
    STDMETHOD(key_reset_trust)(struct pEp_identity_s *ident);
    STDMETHOD(trust_personal_key)(struct pEp_identity_s *ident, struct pEp_identity_s *result);

    // Message API

    STDMETHOD(encrypt_message)(text_message * src, text_message * dst, SAFEARRAY * extra);
    STDMETHOD(decrypt_message)(text_message * src, text_message * dst, SAFEARRAY ** keylist, pEp_color *rating);
    STDMETHOD(outgoing_message_color)(text_message *msg, pEp_color * pVal);
    STDMETHOD(identity_color)(pEp_identity_s * ident, pEp_color * pVal);

};

OBJECT_ENTRY_AUTO(__uuidof(pEpEngine), CpEpEngine)
