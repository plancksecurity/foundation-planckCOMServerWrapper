// CpEpEngine.h : Declaration of the CpEpEngine

#pragma once
#include "resource.h"       // main symbols

#include "pEpComServerAdapter_i.h"
#include "..\libpEpAdapter\locked_queue.hh"
#include "utf8_helper.h"
#include "pEp_utility.h"
#include "..\libpEpAdapter\Adapter.hh"
#include <queue>
#include <mutex>
#include <vector>
#include "..\libpEpAdapter\pc_container.hh"
#include "..\pEp\sync_codec.h"
#include "..\pEp\mime.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;
using namespace utility;
using namespace pEp::utility;
using namespace pEp::Adapter;

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
        ++count;
    }

    ~CpEpEngine()
    {
        --count;
        if (!count) {
            StopKeyserverLookup();
            ::log_event(session(), "Shutdown", "pEp COM Adapter", NULL, NULL);
            session(pEp::Adapter::release);
            shutdown();

            sync_callbacks.clear([](CpEpEngine::MarshaledCallbacks *p) {
                if (p) {
                    if (p->marshaled)
                        p->marshaled->Release();
                    if (p->unmarshaled)
                        p->unmarshaled->Release();
                    delete p;
                }
            });
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
        try {
            if (!_messageToSend) {
                _messageToSend = messageToSend;
            }
            session();
        }
        catch (pEp::RuntimeError& e) {
            HRESULT res = MAKE_HRESULT(1, FACILITY_ITF, (0xFFFF & e.status));
            return res;
        }       

        ::register_examine_function(session(), CpEpEngine::examine_identity, (void *)this);
        ::log_event(session(), "FinalConstruct", "pEp COM Adapter", NULL, NULL);

        return S_OK;
    }

    void FinalRelease()
    {
    }

    struct MarshaledCallbacks {
        IpEpEngineCallbacks *unmarshaled;
        LPSTREAM marshaled;
    };

    typedef pEp::pc_container< MarshaledCallbacks, IpEpEngineCallbacks > callback_container;

protected:
    typedef locked_queue<pEp_identity_cpp> identity_queue_t;
    static ::pEp_identity * retrieve_next_identity(void *management);

    static PEP_STATUS messageToSend(message *msg);
    static PEP_STATUS notifyHandshake(pEp_identity *self, pEp_identity *partner, sync_handshake_signal signal);

    HRESULT error(_bstr_t msg);
    HRESULT error(_bstr_t msg, PEP_STATUS errorcode);

    void verbose(string text)
    {
        if (verbose_mode) {
            stringstream ss;
            ss << __FILE__ << ":" << __LINE__ << " " << text;
            ::log_event(session(), "verbose", "pEp COM Server Adapter", ss.str().c_str(), NULL);
        }
    }

private:
    // callbacks for sync

    static callback_container sync_callbacks;

    void Startup_sync()
    {
        HRESULT r = CoInitializeEx(NULL, COINIT_MULTITHREADED);
        if (!SUCCEEDED(r))
            throw runtime_error("CoInitializeEx() failed on sync thread");
    }

    void Shutdown_sync()
    {
        CoUninitialize();
    }

    atomic< identity_queue_t * > identity_queue;
    thread *keymanagement_thread;
    bool verbose_mode;

    IpEpEngineCallbacks* client_callbacks = NULL;
    bool client_last_signalled_polling_state = true;

    static std::mutex init_mutex;
    static atomic< int > count;

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
    STDMETHOD(GetTrustwordsForFprs)(BSTR fpr1, BSTR fpr2, BSTR lang, VARIANT_BOOL full, BSTR *words);
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
    STDMETHOD(ImportKey)(BSTR keyData, LPSAFEARRAY *privateKeys);

    // keymanagement API

    STDMETHOD(StartKeyserverLookup)();
    STDMETHOD(StopKeyserverLookup)();

    STDMETHOD(Myself)(struct pEpIdentity *ident, struct pEpIdentity *result);
    STDMETHOD(UpdateIdentity)(struct pEpIdentity *ident, struct pEpIdentity *result);
    STDMETHOD(KeyMistrusted)(struct pEpIdentity *ident);
    STDMETHOD(KeyResetIdentity)(pEpIdentity ident, BSTR fpr);
    STDMETHOD(KeyResetUser)(BSTR userId, BSTR fpr);
    STDMETHOD(KeyResetAllOwnKeys)();
    STDMETHOD(KeyResetTrust)(struct pEpIdentity *ident);
    STDMETHOD(TrustPersonalKey)(struct pEpIdentity *ident, struct pEpIdentity *result);
    STDMETHOD(OwnIdentitiesRetrieve)(LPSAFEARRAY* ownIdentities);
    STDMETHOD(ConfigCipherSuite)(pEpCipherSuite cipherSuite);

    // STDMETHOD(UndoLastMistrust)(); 
    
    STDMETHOD(IspEpUser)(
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

    STDMETHOD(EncryptMessageAndAddPrivKey)(
        /* [in] */ struct TextMessage *src,
        /* [out] */ struct TextMessage *dst,
        /* [in] */ BSTR to_fpr,
        /* [defaultvalue][in] */ pEpEncryptFlags flags = pEpEncryptFlagDefault,
        /* [defaultvalue][in] */ pEpEncFormat encFormat = pEpEncPep);

    STDMETHOD(DecryptMessage)(TextMessage * src, TextMessage * dst, SAFEARRAY ** keylist, pEpDecryptFlags* flags, pEpRating *rating);
    STDMETHOD(ReEvaluateMessageRating)(TextMessage * msg, SAFEARRAY * x_KeyList, pEpRating x_EncStatus, pEpRating *rating);
    STDMETHOD(OutgoingMessageRating)(TextMessage *msg, pEpRating * pVal);
    STDMETHOD(OutgoingMessageRatingPreview)(TextMessage *msg, pEpRating * pVal);
    STDMETHOD(IdentityRating)(pEpIdentity * ident, pEpRating * pVal);
    STDMETHOD(ColorFromRating)(pEpRating rating, pEpColor * pVal);
    STDMETHOD(RatingFromCommType)(pEpComType commType, pEpRating * rating);

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
    STDMETHOD(TrustOwnKey)(pEpIdentity * ident);

    // Trigger an immediate update
    STDMETHOD(UpdateNow)(BSTR productCode, VARIANT_BOOL *didUpdate);

    STDMETHOD(Startup)();

    STDMETHOD(GetKeyRatingForUser)(BSTR userId, BSTR fpr, pEpRating *rating);
    STDMETHOD(GetKeyRating)(BSTR fpr, pEpComType *commType);

    // sync API
    STDMETHOD(DeliverHandshakeResult)(enum SyncHandshakeResult result, SAFEARRAY *identities_sharing);
    STDMETHOD(LeaveDeviceGroup)();
    STDMETHOD(DisableIdentityForSync)(struct pEpIdentity * ident);
    STDMETHOD(EnableIdentityForSync)(struct pEpIdentity * ident);
    STDMETHOD(GetIsSyncRunning)(VARIANT_BOOL *running);
    STDMETHOD(ShutDownSync)();

    STDMETHOD(PERToXERSyncMessage)(TextMessage *msg, BSTR *xer);
    STDMETHOD(MIMEDecodeMessage)(BSTR mimeText, TextMessage *msg);
    STDMETHOD(MIMEEncodeMessage)(TextMessage *msg, VARIANT_BOOL omitFields, BSTR *mimeText);

    STDMETHOD(PerMachineDirectory)(BSTR * directory);
    STDMETHOD(PerUserDirectory)(BSTR * directory);
};

OBJECT_ENTRY_AUTO(__uuidof(pEpEngine), CpEpEngine)
