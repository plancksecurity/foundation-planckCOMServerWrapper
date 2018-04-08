// CpEpEngine.h : Declaration of the CpEpEngine

#pragma once
#include "resource.h"       // main symbols

#include "pEpComServerAdapter_i.h"
#include "locked_queue.hh"
#include "utf8_helper.h"
#include "pEp_utility.h"
#include <queue>
#include <mutex>

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
        // See FinalConstruct() below for most initialization work, and an
        // explanation why it had to be moved there...
    }

    ~CpEpEngine()
    {
        stop_keysync();
        StopKeyserverLookup();
        if (m_session) // may be zero when FinalConstruct failed to initialize the engine
        {
            ::log_event(m_session, "Shutdown", "pEp COM Adapter", NULL, NULL);
            std::lock_guard<std::mutex> lock(init_mutex);
            ::release(m_session);
        }
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

    // Unfortunately, neither FAIL nor error() work in the constructor, as 
    // CreateErrorInfo/SetErrorInfo cannot work when the instance is not constructed.
    // AtlThrow works, but the exception is caught in CComCreator.CreateInstance, and
    // unconditionally turned into E_OUTOFMEMORY. Thus, we need to do most constructor
    // work in FinalConstruct. CreateErrorInfo/SetErrorInfo still won't work, but at least,
    // we can return a meaningful HRESULT. Thus, we pack our PEP_STATUS into a custom HRESULT.	
    HRESULT FinalConstruct()
    {
        std::lock_guard<std::mutex> lock(init_mutex);
        PEP_STATUS status = ::init(&m_session);
        assert(status == PEP_STATUS_OK);
        if (status != PEP_STATUS_OK) {
            HRESULT res = MAKE_HRESULT(1, FACILITY_ITF, (0xFFFF & status));
            return res;
        }

        ::register_examine_function(m_session, CpEpEngine::examine_identity, (void *)this);
        ::log_event(m_session, "Startup", "pEp COM Adapter", NULL, NULL);
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
    static PEP_STATUS messageToSend(void * obj, message *msg);
    static PEP_STATUS notifyHandshake(void * obj, pEp_identity *self, pEp_identity *partner, sync_handshake_signal signal);


    HRESULT error(_bstr_t msg);
    HRESULT error(_bstr_t msg, PEP_STATUS errorcode);

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


    IpEpEngineCallbacks* client_callbacks = NULL;
    IpEpEngineCallbacks* client_callbacks_on_sync_thread = NULL;
    bool client_last_signalled_polling_state = true;

    // Keysync members
    static int inject_sync_msg(void *msg, void* management);
    static void* retrieve_next_sync_msg(void* management, time_t *timeout);
    void start_keysync();
    static void do_keysync_in_thread(CpEpEngine* self, LPSTREAM marshaled_callbacks);
    void stop_keysync();

    static std::mutex init_mutex;

    std::recursive_mutex keysync_mutex;
    std::condition_variable_any keysync_condition;
    std::thread *keysync_thread = NULL;
    std::queue<void*> keysync_queue;
    bool keysync_abort_requested = false;
    PEP_SESSION keysync_session;

    // Members used for handshake notification dispatch to the background thread.
    static void notify_handshake_background_thread(CpEpEngine* self, LPSTREAM marshaled_callbacks);
    void notify_handshake_deliver_result();
    bool notify_handshake_active = false;
    bool notify_handshake_finished = false;
    std::thread *notify_handshake_thread = NULL;
    pEpIdentity notify_handshake_self;
    pEpIdentity notify_handshake_partner;
    SyncHandshakeSignal notify_handshake_signal;
    SyncHandshakeResult notify_handshake_result;
    LPSTREAM notify_handshake_error_info = NULL;
    HRESULT notify_handshake_error;

public:
    // runtime config of the adapter

    STDMETHOD(VerboseLogging)(VARIANT_BOOL enable);

    // runtime config of the engine

    STDMETHOD(PassiveMode)(VARIANT_BOOL enable);
    STDMETHOD(UnencryptedSubject)(VARIANT_BOOL enable);

    // basic API

    STDMETHOD(ExportKey)(BSTR fpr, BSTR * keyData);
    STDMETHOD(Log)(BSTR title, BSTR entity, BSTR description, BSTR comment);
    STDMETHOD(Trustwords)(BSTR fpr, BSTR lang, LONG max_words, BSTR * words);
    STDMETHOD(GetTrustwords)(struct pEpIdentity *id1, struct pEpIdentity *id2, BSTR lang, VARIANT_BOOL full, BSTR *words);
    STDMETHOD(GetMessageTrustwords)(
        /* [in] */ struct TextMessage *msg,
        /* [in] */ struct pEpIdentity *receivedBy,
        /* [in] */ SAFEARRAY *keylist,
        /* [defaultvalue][in] */ BSTR lang,
        /* [defaultvalue][in] */ VARIANT_BOOL full,
        /* [retval][out] */ BSTR *words);
    STDMETHOD(GetCrashdumpLog)(LONG maxlines, BSTR * log);
    STDMETHOD(GetEngineVersion)(BSTR * engineVersion);
    STDMETHOD(GetLanguageList)(BSTR * languages);
    STDMETHOD(SetIdentityFlags)(struct pEpIdentity *identity, pEpIdentityFlags flags);
    STDMETHOD(UnsetIdentityFlags)(struct pEpIdentity *identity, pEpIdentityFlags flags);

    // keymanagement API

    STDMETHOD(StartKeyserverLookup)();
    STDMETHOD(StopKeyserverLookup)();

    STDMETHOD(Myself)(struct pEpIdentity *ident, struct pEpIdentity *result);
    STDMETHOD(UpdateIdentity)(struct pEpIdentity *ident, struct pEpIdentity *result);
    STDMETHOD(KeyMistrusted)(struct pEpIdentity *ident);
    STDMETHOD(KeyResetTrust)(struct pEpIdentity *ident);
    STDMETHOD(TrustPersonalKey)(struct pEpIdentity *ident, struct pEpIdentity *result);
    STDMETHOD(OwnIdentitiesRetrieve)(LPSAFEARRAY* ownIdentities);

    STDMETHOD(UndoLastMistrust)(); 
    
    STDMETHOD(IsPepUser)(
        /* [in] */ struct pEpIdentity *ident,
        /* [retval][out] */ VARIANT_BOOL *ispEp);

    // Blacklist API

    STDMETHOD(BlacklistAdd)(BSTR fpr);
    STDMETHOD(BlacklistDelete)(BSTR fpr);
    STDMETHOD(BlacklistIsListed)(BSTR fpr, VARIANT_BOOL *listed);
    STDMETHOD(BlacklistRetrieve)(SAFEARRAY **blacklist);

    // Message API

    STDMETHOD(EncryptMessage)(
        /* [in] */ struct TextMessage *src,
        /* [out] */ struct TextMessage *dst,
        /* [in] */ SAFEARRAY * extra,
        /* [defaultvalue][in] */ pEpEncryptFlags flags = pEpEncryptFlagDefault,
        /* [defaultvalue][in] */ pEpEncFormat encFormat = pEpEncPep);

    STDMETHOD(DecryptMessage)(TextMessage * src, TextMessage * dst, SAFEARRAY ** keylist, pEpDecryptFlags* flags, pEpRating *rating);
    STDMETHOD(ReEvaluateMessageRating)(TextMessage * msg, SAFEARRAY * x_KeyList, pEpRating x_EncStatus, pEpRating *rating);
    STDMETHOD(OutgoingMessageRating)(TextMessage *msg, pEpRating * pVal);
    STDMETHOD(IdentityRating)(pEpIdentity * ident, pEpRating * pVal);
    STDMETHOD(ColorFromRating)(pEpRating rating, pEpColor * pVal);

    STDMETHOD(EncryptMessageForSelf)(
        pEpIdentity * targetId,
        TextMessage* src,
        /* [in] */ SAFEARRAY *extra,
        TextMessage *dst,
        pEpEncryptFlags flags
        );

    // Event callbacks

    STDMETHOD(RegisterCallbacks)(IpEpEngineCallbacks *new_callback);
    STDMETHOD(UnregisterCallbacks)();

    // PGP compatibility functions
    STDMETHOD(OpenPGPListKeyinfo)(BSTR search_pattern, LPSAFEARRAY* keyinfo_list);
	STDMETHOD(SetOwnKey)(pEpIdentity * ident, BSTR fpr, struct pEpIdentity *result);


protected:
    HRESULT Fire_MessageToSend(
        /* [in] */ struct TextMessage *msg);
};

OBJECT_ENTRY_AUTO(__uuidof(pEpEngine), CpEpEngine)
