// CpEpEngine.h : Declaration of the CpEpEngine

#pragma once
#include "resource.h"       // main symbols

#include "pEpComServerAdapter_i.h"
#include "locked_queue.hh"
#include "utf8_helper.h"
#include "pEp_utility.h"
#include <queue>

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
        stop_keysync();
        StopKeyserverLookup();
        ::log_event(m_session, "Shutdown", "pEp COM Adapter", NULL, NULL);
        ::release(m_session);
    }

DECLARE_REGISTRY_RESOURCEID(IDR_PEPENGINE)

DECLARE_NOT_AGGREGATABLE(CpEpEngine)

BEGIN_COM_MAP(CpEpEngine)
    COM_INTERFACE_ENTRY(IpEpEngine)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

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

	class callbacks
	{
	private:
		CpEpEngine *me;

	public:
		callbacks(CpEpEngine *myself)
		{
			me = myself;
			me->callback_mutex.lock();
		}

		~callbacks()
		{
			me->callback_mutex.unlock();
		}

		operator vector<IpEpEngineCallbacks *>& ()
		{
			return me->callback_vector;
		}
	};

	callbacks get_callbacks()
	{
		return callbacks(this);
	}

    typedef locked_queue<pEp_identity_cpp> identity_queue_t;
    static ::pEp_identity * retrieve_next_identity(void *management);
    static PEP_STATUS messageToSend(void * obj, message *msg);
    static PEP_STATUS showHandshake(void * obj, pEp_identity *self, pEp_identity *partner);


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

	mutex callback_mutex;
	vector<IpEpEngineCallbacks*> callback_vector;

	// Keysync members
    static int inject_sync_msg(void *msg, void* management);
    static void* retreive_next_sync_msg(void* management);
    void start_keysync();
    void stop_keysync();

    std::mutex keysync_mutex;
    std::condition_variable keysync_condition;
    std::thread *keysync_thread = NULL;
    std::queue<void*> keysync_queue;
    bool keysync_thread_running = false;
    bool keysync_abort_requested = false;
    PEP_SESSION keysync_session;

public:
    // runtime config of the adapter

    STDMETHOD(VerboseLogging)(VARIANT_BOOL enable);

    // runtime config of the engine

    STDMETHOD(PassiveMode)(VARIANT_BOOL enable);
    STDMETHOD(UnencryptedSubject)(VARIANT_BOOL enable);

    // basic API

    STDMETHOD(ExportKey)(BSTR fpr, BSTR * key_data);
    STDMETHOD(Log)(BSTR title, BSTR entity, BSTR description, BSTR comment);
    STDMETHOD(TrustWords)(BSTR fpr, BSTR lang, LONG max_words, BSTR * words);
    STDMETHOD(GetCrashdumpLog)(LONG maxlines, BSTR * log);
    STDMETHOD(GetEngineVersion)(BSTR * engineVersion);
    STDMETHOD(GetLanguageList)(BSTR * languages);

    // keymanagement API

    STDMETHOD(StartKeyserverLookup)();
    STDMETHOD(StopKeyserverLookup)();

    STDMETHOD(Myself)(struct pEpIdentity *ident, struct pEpIdentity *result);
    STDMETHOD(UpdateIdentity)(struct pEpIdentity *ident, struct pEpIdentity *result);
    STDMETHOD(KeyMistrusted)(struct pEpIdentity *ident);
    STDMETHOD(KeyResetTrust)(struct pEpIdentity *ident);
    STDMETHOD(TrustPersonalKey)(struct pEpIdentity *ident, struct pEpIdentity *result);


    // Blacklist API

    STDMETHOD(BlacklistAdd)(BSTR fpr);
    STDMETHOD(BlacklistDelete)(BSTR fpr);
    STDMETHOD(BlacklistIsListed)(BSTR fpr, VARIANT_BOOL *listed);
    STDMETHOD(BlacklistRetreive)(SAFEARRAY **blacklist);

    // Message API

    STDMETHOD(EncryptMessage)(TextMessage * src, TextMessage * dst, SAFEARRAY * extra, pEpEncryptFlags flags);
    STDMETHOD(DecryptMessage)(TextMessage * src, TextMessage * dst, SAFEARRAY ** keylist, pEpDecryptFlags* flags, pEpRating *rating);
    STDMETHOD(OutgoingMessageRating)(TextMessage *msg, pEpRating * pVal);
    STDMETHOD(IdentityRating)(pEpIdentity * ident, pEpRating * pVal);
	STDMETHOD(ColorFromRating)(pEpRating rating, pEpColor * pVal);

	// Event callbacks

	STDMETHOD(RegisterCallbacks)(IpEpEngineCallbacks *new_callback);
	STDMETHOD(UnregisterCallbacks)(IpEpEngineCallbacks *obsolete_callback);

    // PGP compatibility functions
    STDMETHOD(OpenPGPListKeyinfo)(BSTR search_pattern, LPSAFEARRAY* keyinfo_list);

protected:
	HRESULT Fire_MessageToSend(
		/* [in] */ struct TextMessage *msg);

	HRESULT Fire_ShowHandshake(
		/* [in] */ struct pEpIdentity *self,
		/* [in] */ struct pEpIdentity *partner,
		/* [retval][out] */ SyncHandshakeResult *result);
};

OBJECT_ENTRY_AUTO(__uuidof(pEpEngine), CpEpEngine)
