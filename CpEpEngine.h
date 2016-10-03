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


// TODO: Remove this enum, it is not needed in the interface, but it currently is still used in the code which is
// not removed / reworked yet...
typedef enum pEpStatus {
     pEpStatusOK = 0,

     pEp_INIT_CANNOT_LOAD_GPGME = 0x0110,
     pEp_INIT_GPGME_INIT_FAILED = 0x0111,
     pEp_INIT_NO_GPG_HOME = 0x0112,
     pEp_INIT_NETPGP_INIT_FAILED = 0x0113,

     pEp_INIT_SQLITE3_WITHOUT_MUTEX = 0x0120,
     pEp_INIT_CANNOT_OPEN_DB = 0x0121,
     pEp_INIT_CANNOT_OPEN_SYSTEM_DB = 0x0122,

     pEp_KEY_NOT_FOUND = 0x0201,
     pEp_KEY_HAS_AMBIG_NAME = 0x0202,
     pEp_GET_KEY_FAILED = 0x0203,

     pEp_CANNOT_FIND_IDENTITY = 0x0301,
     pEp_CANNOT_SET_PERSON = 0x0381,
     pEp_CANNOT_SET_PGP_KEYPAIR = 0x0382,
     pEp_CANNOT_SET_IDENTITY = 0x0383,
     pEp_CANNOT_SET_TRUST = 0x0384,

     pEp_UNENCRYPTED = 0x0400,
     pEp_VERIFIED = 0x0401,
     pEp_DECRYPTED = 0x0402,
     pEp_DECRYPTED_AND_VERIFIED = 0x0403,
     pEp_DECRYPT_WRONG_FORMAT = 0x0404,
     pEp_DECRYPT_NO_KEY = 0x0405,
     pEp_DECRYPT_SIGNATURE_DOES_NOT_MATCH = 0x0406,
     pEp_VERIFY_NO_KEY = 0x0407,
     pEp_VERIFIED_AND_TRUSTED = 0x0408,
     pEp_CANNOT_DECRYPT_UNKNOWN = 0x04ff,

     pEp_TRUSTWORD_NOT_FOUND = 0x0501,

     pEp_CANNOT_CREATE_KEY = 0x0601,
     pEp_CANNOT_SEND_KEY = 0x0602,

     pEp_PHRASE_NOT_FOUND = 0x0701,

     pEp_COMMIT_FAILED = 0xff01,

     pEp_CANNOT_CREATE_TEMP_FILE = -5,
     pEp_ILLEGAL_VALUE = -4,
     pEp_BUFFER_TOO_SMALL = -3,
     pEp_OUT_OF_MEMORY = -2,
     pEp_UNKNOWN_ERROR = -1
 } pEpStatus;

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
        ::register_sync_callbacks(m_session, (void*)this, messageToSend, showHandshake, inject_sync_msg, retreive_next_sync_msg);
        ::log_event(m_session, "Startup", "pEp COM Adapter", NULL, NULL);
    }

    ~CpEpEngine()
    {
        stop_keysync();
        StopKeyserverLookup();
        ::unregister_sync_callbacks(m_session);
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

    STDMETHOD(log)(BSTR title, BSTR entity, BSTR description, BSTR comment);
    STDMETHOD(decrypt)(BSTR ctext, BSTR * ptext, LPSAFEARRAY * key_list, pEpStatus * decrypt_status);
    STDMETHOD(decrypt_b)(BSTR ctext, LPSAFEARRAY * ptext, LPSAFEARRAY * key_list, pEpStatus * decrypt_status);
    STDMETHOD(encrypt)(SAFEARRAY * key_list, BSTR ptext, BSTR * ctext, pEpStatus * status);
    STDMETHOD(encrypt_b)(SAFEARRAY * key_list, SAFEARRAY * ptext, BSTR * ctext, pEpStatus * status);
    STDMETHOD(trustword)(LONG value, BSTR lang, BSTR * word);
    STDMETHOD(TrustWords)(BSTR fpr, BSTR lang, LONG max_words, BSTR * words);
    STDMETHOD(get_identity)(BSTR address, BSTR user_id, pEpIdentity * ident);
    STDMETHOD(set_identity)(pEpIdentity * ident);
    STDMETHOD(generate_keypair)(pEpIdentity * ident, BSTR * fpr);
    STDMETHOD(delete_keypair)(BSTR fpr);
    STDMETHOD(import_key)(BSTR key_data);
    STDMETHOD(import_key_b)(SAFEARRAY * key_data);
    STDMETHOD(export_key)(BSTR fpr, BSTR * key_data);
    STDMETHOD(recv_key)(BSTR pattern);
    STDMETHOD(find_keys)(BSTR pattern, LPSAFEARRAY * key_list);
    STDMETHOD(send_key)(BSTR pattern);
    STDMETHOD(GetCrashdumpLog)(LONG maxlines, BSTR * log);
    STDMETHOD(GetEngineVersion)(BSTR * engine_version);
    STDMETHOD(GetLanguagelist)(BSTR * languages);
    STDMETHOD(get_phrase)(BSTR lang, LONG phrase_id, BSTR * phrase);

    // keymanagement API

    STDMETHOD(StartKeyserverLookup)();
    STDMETHOD(StopKeyserverLookup)();

    STDMETHOD(examine_identity)(pEpIdentity * ident);
    STDMETHOD(verify)(BSTR text, BSTR signature, LPSAFEARRAY * key_list, pEpStatus * verify_status);
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
    STDMETHOD(OpenPGP_list_keyinfo)(BSTR search_pattern, LPSAFEARRAY* keyinfo_list);

protected:
	HRESULT Fire_MessageToSend(
		/* [in] */ struct TextMessage *msg);

	HRESULT Fire_ShowHandshake(
		/* [in] */ struct pEpIdentity *self,
		/* [in] */ struct pEpIdentity *partner,
		/* [retval][out] */ SyncHandshakeResult *result);
};

OBJECT_ENTRY_AUTO(__uuidof(pEpEngine), CpEpEngine)
