

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for planckCOMServerWrapper.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __planckCOMServerWrapper_i_h__
#define __planckCOMServerWrapper_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IpEpEngineCallbacks_FWD_DEFINED__
#define __IpEpEngineCallbacks_FWD_DEFINED__
typedef interface IpEpEngineCallbacks IpEpEngineCallbacks;

#endif 	/* __IpEpEngineCallbacks_FWD_DEFINED__ */


#ifndef __IpEpEngine_FWD_DEFINED__
#define __IpEpEngine_FWD_DEFINED__
typedef interface IpEpEngine IpEpEngine;

#endif 	/* __IpEpEngine_FWD_DEFINED__ */


#ifndef __pEpEngine_FWD_DEFINED__
#define __pEpEngine_FWD_DEFINED__

#ifdef __cplusplus
typedef class pEpEngine pEpEngine;
#else
typedef struct pEpEngine pEpEngine;
#endif /* __cplusplus */

#endif 	/* __pEpEngine_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IpEpEngineCallbacks_INTERFACE_DEFINED__
#define __IpEpEngineCallbacks_INTERFACE_DEFINED__

/* interface IpEpEngineCallbacks */
/* [unique][nonextensible][oleautomation][uuid][object] */ 

typedef /* [v1_enum] */ 
enum SyncHandshakeSignal
    {
        SyncNotifyUndefined	= 0,
        SyncNotifyInitAddOurDevice	= 1,
        SyncNotifyInitAddOtherDevice	= 2,
        SyncNotifyInitFormGroup	= 3,
        SyncNotifyTimeout	= 5,
        SyncNotifyAcceptedDeviceAdded	= 6,
        SyncNotifyAcceptedGroupCreated	= 7,
        SyncNotifyAcceptedDeviceAccepted	= 8,
        SyncNotifyOutgoingRatingChange	= 64,
        SyncNotifyStart	= 126,
        SyncNotifyStop	= 127,
        SyncNotifyPassphraseRequired	= 128,
        SyncNotifyGroupInvitation	= 192,
        SyncNotifySole	= 254,
        SyncNotifyInGroup	= 255
    } 	SyncHandshakeSignal;


EXTERN_C const IID IID_IpEpEngineCallbacks;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4DA92647-A858-448E-B01F-BE4DCB8C86A1")
    IpEpEngineCallbacks : public IUnknown
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE MessageToSend( 
            /* [in] */ struct TextMessage *msg) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE NotifyHandshake( 
            /* [in] */ struct pEpIdentity *self,
            /* [in] */ struct pEpIdentity *partner,
            /* [in] */ SyncHandshakeSignal signal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IpEpEngineCallbacksVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IpEpEngineCallbacks * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IpEpEngineCallbacks * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IpEpEngineCallbacks * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *MessageToSend )( 
            IpEpEngineCallbacks * This,
            /* [in] */ struct TextMessage *msg);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *NotifyHandshake )( 
            IpEpEngineCallbacks * This,
            /* [in] */ struct pEpIdentity *self,
            /* [in] */ struct pEpIdentity *partner,
            /* [in] */ SyncHandshakeSignal signal);
        
        END_INTERFACE
    } IpEpEngineCallbacksVtbl;

    interface IpEpEngineCallbacks
    {
        CONST_VTBL struct IpEpEngineCallbacksVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IpEpEngineCallbacks_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IpEpEngineCallbacks_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IpEpEngineCallbacks_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IpEpEngineCallbacks_MessageToSend(This,msg)	\
    ( (This)->lpVtbl -> MessageToSend(This,msg) ) 

#define IpEpEngineCallbacks_NotifyHandshake(This,self,partner,signal)	\
    ( (This)->lpVtbl -> NotifyHandshake(This,self,partner,signal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IpEpEngineCallbacks_INTERFACE_DEFINED__ */


#ifndef __IpEpEngine_INTERFACE_DEFINED__
#define __IpEpEngine_INTERFACE_DEFINED__

/* interface IpEpEngine */
/* [unique][nonextensible][oleautomation][uuid][object] */ 

typedef /* [v1_enum] */ 
enum pEpComType
    {
        pEpCtUnknown	= 0,
        pEpCtNoEncryption	= 0x1,
        pEpCtNoEncryptedChannel	= 0x2,
        pEpCtKeyNotFound	= 0x3,
        pEpCtKeyExpired	= 0x4,
        pEpCtKeyRevoked	= 0x5,
        pEpCtKeyB0rken	= 0x6,
        pEpCtMyKeyNotIncluded	= 0x9,
        pEpCtSecurityByObscurity	= 0xa,
        pEpCtB0rkenCrypto	= 0xb,
        pEpCtKeyTooShort	= 0xc,
        pEpCtCompromised	= 0xe,
        pEpCtMistrusted	= 0xf,
        pEpCtUnconfirmedEncryption	= 0x10,
        pEpCtOpenPGPWeakUnconfirmed	= 0x11,
        pEpCtToBeChecked	= 0x20,
        pEpCtSMIMEUnconfirmed	= 0x21,
        pEpCtCMSUnconfirmed	= 0x22,
        pEpCtStrongButUnconfirmed	= 0x30,
        pEpCtOpenPGPUnconfirmed	= 0x38,
        pEpCtOTRUnconfirmed	= 0x3a,
        pEpCtUnconfirmedEncAnon	= 0x40,
        pEpCtpEpUnconfirmed	= 0x7f,
        pEpCtConfirmed	= 0x80,
        pEpCtConfirmedEncryption	= 0x90,
        pEpCtOpenPGPWeak	= 0x91,
        pEpCtToBeCheckedConfirmed	= 0xa0,
        pEpCtSMIME	= 0xa1,
        pEpCtCMS	= 0xa2,
        pEpCtStrongEncryption	= 0xb0,
        pEpCtOpenPGP	= 0xb8,
        pEpCtOTR	= 0xba,
        pEpCtConfirmedEncAnon	= 0xc0,
        pEpCtpEp	= 0xff
    } 	pEpComType;

typedef 
enum pEpStatus
    {
        pEpStatusOk	= 0,
        pEpInitCannotLoadGpgme	= 0x110,
        pEpInitGpgmeInitFailed	= 0x111,
        pEpInitNoGpgHome	= 0x112,
        pEpInitNetpgpInitFailed	= 0x113,
        pEpInitCannotDetermineGpgVersion	= 0x114,
        pEpInitUnsupportedGpgVersion	= 0x115,
        pEpInitCannotConfigGpgAgent	= 0x116,
        pEpInitSqlite3WithoutMutex	= 0x120,
        pEpInitCannotOpenDb	= 0x121,
        pEpInitCannotOpenSystemDb	= 0x122,
        pEpKeyNotFound	= 0x201,
        pEpKeyHasAmbigName	= 0x202,
        pEpGetKeyFailed	= 0x203,
        pEpCannotExportKey	= 0x204,
        pEpCannotEditKey	= 0x205,
        pEpKeyUnsuitable	= 0x206,
        pEpCannotFindIdentity	= 0x301,
        pEpCannotSetPerson	= 0x381,
        pEpCannotSetPgpKeypair	= 0x382,
        pEpCannotSetIdentity	= 0x383,
        pEpCannotSetTrust	= 0x384,
        pEpKeyBlacklisted	= 0x385,
        pEpCannotFindPerson	= 0x386,
        pEpCannotFindAlias	= 0x391,
        pEpCannotSetAlias	= 0x392,
        pEpUnencrypted	= 0x400,
        pEpVerified	= 0x401,
        pEpDecrypted	= 0x402,
        pEpDecryptedAndVerified	= 0x403,
        pEpDecryptWrongFormat	= 0x404,
        pEpDecryptNoKey	= 0x405,
        pEpDecryptSignatureDoesNotMatch	= 0x406,
        pEpVerifyNoKey	= 0x407,
        pEpVerifiedAndTrusted	= 0x408,
        pEpCannotDecryptUnknown	= 0x4ff,
        pEpTrustwordNotFound	= 0x501,
        pEpTrustwordsFprWrongLength	= 0x502,
        pEpTrustwordsDuplicateFpr	= 0x503,
        pEpCannotCreateKey	= 0x601,
        pEpCannotSendKey	= 0x602,
        pEpPhraseNotFound	= 0x701,
        pEpSendFunctionNotRegistered	= 0x801,
        pEpContraintsViolated	= 0x802,
        pEpCannotEncode	= 0x803,
        pEpSyncNoNotifyCallback	= 0x901,
        pEpSyncIllegalMessage	= 0x902,
        pEpSyncNoInjectCallback	= 0x903,
        pEpSequenceViolated	= 0x970,
        pEpCannotIncreaseSequence	= 0x971,
        pEpCannotSetSequenceValue	= 0x972,
        pEpOwnSequence	= 0x97f,
        pEpSyncStatemachineError	= 0x980,
        pEpSyncNoTrust	= 0x981,
        pEpStatemachineInvalidState	= 0x982,
        pEpStatemachineInvalidEvent	= 0x983,
        pEpStatemachineInvalidCondition	= 0x984,
        pEpStatemachineInvalidAction	= 0x985,
        pEpStatemachineInhibitedEvent	= 0x986,
        pEpCommitFailed	= 0xff01,
        pEpMessageConsume	= 0xff02,
        pEpMessageIgnore	= 0xff03,
        pEpRecordNotFound	= -6,
        pEpCannotCreateTempFile	= -5,
        pEpIllegalValue	= -4,
        pEpBufferTooSmall	= -3,
        pEpOutOfMemory	= -2,
        pEpUnknownError	= -1,
        pEpVersionMismatch	= -7
    } 	pEpStatus;

typedef /* [v1_enum] */ 
enum pEpIdentityFlags
    {
        pEpIdfNone	= 0,
        pEpIdfNotForSync	= 0x1,
        pEpIdfList	= 0x2,
        pEpIdfDevicegroup	= 0x100,
        pEpIdfOrgIdent	= 0x512,
        pEpIdfGroupIdent	= 0x1024
    } 	pEpIdentityFlags;

/* [uuid] */ struct  DECLSPEC_UUID("C3A3814E-567F-4D1C-9F44-9B1DA3957A89") pEpIdentity
    {
    BSTR Address;
    BSTR Fpr;
    BSTR UserId;
    BSTR UserName;
    pEpComType CommType;
    BSTR Lang;
    VARIANT_BOOL Me;
    pEpIdentityFlags Flags;
    USHORT MajorVersion;
    USHORT MinorVersion;
    } ;
typedef /* [v1_enum] */ 
enum pEpRating
    {
        pEpRatingUndefined	= 0,
        pEpRatingCannotDecrypt	= ( pEpRatingUndefined + 1 ) ,
        pEpRatingHaveNoKey	= ( pEpRatingCannotDecrypt + 1 ) ,
        pEpRatingUnencrypted	= ( pEpRatingHaveNoKey + 1 ) ,
        pEpRatingUnreliable	= ( pEpRatingUnencrypted + 1 ) ,
        pEpMediaKeyProtected	= ( pEpRatingUnreliable + 1 ) ,
        pEpRatingReliable	= ( pEpMediaKeyProtected + 1 ) ,
        pEpRatingTrusted	= ( pEpRatingReliable + 1 ) ,
        pEpRatingTrustedAndAnonymized	= ( pEpRatingTrusted + 1 ) ,
        pEpRatingFullyAnonymous	= ( pEpRatingTrustedAndAnonymized + 1 ) ,
        pEpRatingMistrust	= -1,
        pEpRatingB0rken	= -2,
        pEpRatingUnderAttack	= -3
    } 	pEpRating;

typedef /* [v1_enum] */ 
enum pEpColor
    {
        pEpColorNoColor	= 0,
        pEpColorYellow	= ( pEpColorNoColor + 1 ) ,
        pEpColorGreen	= ( pEpColorYellow + 1 ) ,
        pEpColorRed	= -1
    } 	pEpColor;

typedef /* [v1_enum] */ 
enum pEpEncryptFlags
    {
        pEpEncryptFlagDefault	= 0,
        pEpEncryptFlagForceEncryption	= 0x1,
        pEpEncryptFlagForceUnsigned	= 0x2,
        pEpEncryptFlagForceNoAttachedKey	= 0x4,
        pEpEncryptFlagForceVersion1	= 0x16
    } 	pEpEncryptFlags;

typedef /* [v1_enum] */ 
enum pEpDecryptFlags
    {
        pEpDecryptFlagsNone	= 0,
        pEpDecryptFlagOwnPrivateKey	= 0x1,
        pEpDecryptFlagConsume	= 0x2,
        pEpDecryptFlagIgnore	= 0x4,
        pEpDecryptFlagSrcModified	= 0x8,
        pEpDecryptFlagUntrustedServer	= 0x100,
        pEpDecryptFlagDontTriggerSync	= 0x200
    } 	pEpDecryptFlags;

typedef /* [v1_enum] */ 
enum pEpMsgDirection
    {
        pEpDirIncoming	= 0,
        pEpDirOutgoing	= ( pEpDirIncoming + 1 ) 
    } 	pEpMsgDirection;

typedef /* [v1_enum] */ 
enum pEpEncFormat
    {
        pEpEncNone	= 0,
        pEpEncPieces	= ( pEpEncNone + 1 ) ,
        pEpEncSMime	= ( pEpEncPieces + 1 ) ,
        pEpEncPgpMime	= ( pEpEncSMime + 1 ) ,
        pEpEncPep	= ( pEpEncPgpMime + 1 ) ,
        pEpEncPgpMimeOutlook1	= ( pEpEncPep + 1 ) 
    } 	pEpEncFormat;

/* [uuid] */ struct  DECLSPEC_UUID("47FB0795-6B64-455C-BB0E-54998CAB8ACB") StringPair
    {
    BSTR Name;
    BSTR Value;
    } ;
/* [uuid] */ struct  DECLSPEC_UUID("634EB7CE-99AA-460D-BDF8-F7CDA7232CA6") Blob
    {
    SAFEARRAY * value;
    BSTR MimeType;
    BSTR Filename;
    } ;
/* [uuid] */ struct  DECLSPEC_UUID("B6F40887-E761-4A47-B204-A0193EE0284D") TextMessage
    {
    pEpMsgDirection Dir;
    BSTR Id;
    BSTR ShortMsg;
    BSTR LongMsg;
    BSTR LongMsgFormatted;
    SAFEARRAY * Attachments;
    hyper Sent;
    hyper Recv;
    struct pEpIdentity From;
    SAFEARRAY * To;
    struct pEpIdentity RecvBy;
    SAFEARRAY * Cc;
    SAFEARRAY * Bcc;
    SAFEARRAY * ReplyTo;
    SAFEARRAY * References;
    SAFEARRAY * Keywords;
    BSTR Comments;
    SAFEARRAY * OptFields;
    pEpEncFormat EncFormat;
    /* [readonly] */ BSTR SenderFpr;
    pEpRating Rating;
    } ;
typedef /* [v1_enum] */ 
enum SyncHandshakeResult
    {
        SyncHandshakeCancel	= -1,
        SyncHandshakeAccepted	= 0,
        SyncHandshakeRejected	= 1
    } 	SyncHandshakeResult;

typedef /* [v1_enum] */ 
enum pEpCipherSuite
    {
        pEpCipherSuiteDefault	= 0,
        pEpCipherSuiteCV25519	= 1,
        pEpCipherSuiteP256	= 2,
        pEpCipherSuiteP384	= 3,
        pEpCipherSuiteP521	= 4,
        pEpCipherSuiteRSA2K	= 5,
        pEpCipherSuiteRSA3K	= 6,
        pEpCipherSuiteRSA4K	= 7,
        pEpCipherSuiteRSA8K	= 8
    } 	pEpCipherSuite;


EXTERN_C const IID IID_IpEpEngine;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("045E49AF-0975-4876-A53B-8CA5AB28C0F8")
    IpEpEngine : public IUnknown
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE VerboseLogging( 
            /* [in] */ VARIANT_BOOL enable) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE PassiveMode( 
            /* [in] */ VARIANT_BOOL enable) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE UnencryptedSubject( 
            /* [in] */ VARIANT_BOOL enable) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ExportKey( 
            /* [in] */ BSTR fpr,
            /* [retval][out] */ BSTR *keyData) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Log( 
            /* [in] */ BSTR title,
            /* [in] */ BSTR entity,
            /* [defaultvalue][in] */ BSTR description = (BSTR)L"",
            /* [defaultvalue][in] */ BSTR comment = (BSTR)L"") = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Trustwords( 
            /* [in] */ BSTR fpr,
            /* [defaultvalue][in] */ BSTR lang,
            /* [defaultvalue][in] */ LONG maxWords,
            /* [retval][out] */ BSTR *words) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetTrustwords( 
            /* [in] */ struct pEpIdentity *id1,
            /* [in] */ struct pEpIdentity *id2,
            /* [defaultvalue][in] */ BSTR lang,
            /* [defaultvalue][in] */ VARIANT_BOOL full,
            /* [retval][out] */ BSTR *words) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetCrashdumpLog( 
            /* [defaultvalue][in] */ LONG maxlines,
            /* [retval][out] */ BSTR *log) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetEngineVersion( 
            /* [retval][out] */ BSTR *engineVersion) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetLanguageList( 
            /* [retval][out] */ BSTR *languages) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetIdentityFlags( 
            /* [in] */ struct pEpIdentity *identity,
            /* [in] */ pEpIdentityFlags flags) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE UnsetIdentityFlags( 
            /* [in] */ struct pEpIdentity *identity,
            /* [in] */ pEpIdentityFlags flags) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Myself( 
            /* [in] */ struct pEpIdentity *ident,
            /* [retval][out] */ struct pEpIdentity *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE UpdateIdentity( 
            /* [in] */ struct pEpIdentity *ident,
            /* [retval][out] */ struct pEpIdentity *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE KeyMistrusted( 
            /* [in] */ struct pEpIdentity *ident) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE KeyResetTrust( 
            /* [in] */ struct pEpIdentity *ident) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE TrustPersonalKey( 
            /* [in] */ struct pEpIdentity *ident,
            /* [retval][out] */ struct pEpIdentity *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE OwnIdentitiesRetrieve( 
            /* [retval][out] */ SAFEARRAY * *ownIdentities) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE IspEpUser( 
            /* [in] */ struct pEpIdentity *ident,
            /* [retval][out] */ VARIANT_BOOL *ispEp) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE OpenPGPListKeyinfo( 
            /* [in] */ BSTR searchPattern,
            /* [retval][out] */ SAFEARRAY * *keyinfoList) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE EncryptMessage( 
            /* [out][in] */ struct TextMessage *src,
            /* [out] */ struct TextMessage *dst,
            /* [in] */ SAFEARRAY * extra,
            /* [defaultvalue][in] */ pEpEncryptFlags flags = pEpEncryptFlagDefault,
            /* [defaultvalue][in] */ pEpEncFormat encFormat = pEpEncPep) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE DecryptMessage( 
            /* [out][in] */ struct TextMessage *src,
            /* [out] */ struct TextMessage *dst,
            /* [out][in] */ SAFEARRAY * *keylist,
            /* [out][in] */ pEpDecryptFlags *flags,
            /* [retval][out] */ pEpRating *rating) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE OutgoingMessageRating( 
            /* [in] */ struct TextMessage *msg,
            /* [retval][out] */ pEpRating *pVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE IdentityRating( 
            /* [in] */ struct pEpIdentity *ident,
            /* [retval][out] */ pEpRating *pVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ColorFromRating( 
            /* [in] */ pEpRating rating,
            /* [retval][out] */ pEpColor *pVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetMessageTrustwords( 
            /* [in] */ struct TextMessage *msg,
            /* [in] */ struct pEpIdentity *receivedBy,
            /* [in] */ SAFEARRAY * keylist,
            /* [defaultvalue][in] */ BSTR lang,
            /* [defaultvalue][in] */ VARIANT_BOOL full,
            /* [retval][out] */ BSTR *words) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE EncryptMessageForSelf( 
            /* [in] */ struct pEpIdentity *targetId,
            /* [in] */ struct TextMessage *src,
            /* [in] */ SAFEARRAY * extra,
            /* [out] */ struct TextMessage *dst,
            /* [defaultvalue][in] */ pEpEncryptFlags flags = pEpEncryptFlagDefault) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ReEvaluateMessageRating( 
            /* [out][in] */ struct TextMessage *src,
            /* [in] */ SAFEARRAY * x_KeyList,
            /* [in] */ pEpRating x_EncStatus,
            /* [retval][out] */ pEpRating *rating) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RegisterCallbacks( 
            /* [in] */ IpEpEngineCallbacks *newCallback) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE UnregisterCallbacks( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetOwnKey( 
            /* [in] */ struct pEpIdentity *ident,
            /* [in] */ BSTR fpr,
            /* [retval][out] */ struct pEpIdentity *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE EncryptMessageAndAddPrivKey( 
            /* [in] */ struct TextMessage *src,
            /* [out] */ struct TextMessage *dst,
            /* [in] */ BSTR to_fpr,
            /* [defaultvalue][in] */ pEpEncryptFlags flags = pEpEncryptFlagDefault,
            /* [defaultvalue][in] */ pEpEncFormat encFormat = pEpEncPep) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE UpdateNow( 
            /* [in] */ BSTR productCode,
            /* [out] */ VARIANT_BOOL *didUpdate) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE OutgoingMessageRatingPreview( 
            /* [in] */ struct TextMessage *msg,
            /* [retval][out] */ pEpRating *rating) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE TrustOwnKey( 
            /* [in] */ struct pEpIdentity *ident) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Startup( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetKeyRatingForUser( 
            /* [in] */ BSTR userId,
            /* [in] */ BSTR fpr,
            /* [retval][out] */ pEpRating *rating) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE KeyResetIdentity( 
            /* [in] */ struct pEpIdentity ident,
            /* [in] */ BSTR fpr) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE KeyResetUser( 
            /* [in] */ BSTR userId,
            /* [in] */ BSTR fpr) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE KeyResetAllOwnKeys( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE DeliverHandshakeResult( 
            /* [in] */ enum SyncHandshakeResult result,
            /* [in] */ SAFEARRAY * identities_sharing) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ImportKey( 
            /* [in] */ BSTR keyData,
            /* [out] */ SAFEARRAY * *privateKeys) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ConfigCipherSuite( 
            /* [defaultvalue][in] */ pEpCipherSuite cipherSuite = pEpCipherSuiteDefault) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE LeaveDeviceGroup( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetTrustwordsForFprs( 
            /* [in] */ BSTR fpr1,
            /* [in] */ BSTR fpr2,
            /* [defaultvalue][in] */ BSTR lang,
            /* [defaultvalue][in] */ VARIANT_BOOL full,
            /* [retval][out] */ BSTR *words) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetKeyRating( 
            /* [in] */ BSTR fpr,
            /* [retval][out] */ pEpComType *commType) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE PERToXERSyncMessage( 
            /* [in] */ struct TextMessage *msg,
            /* [retval][out] */ BSTR *xer) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE DisableIdentityForSync( 
            /* [in] */ struct pEpIdentity *ident) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE EnableIdentityForSync( 
            /* [in] */ struct pEpIdentity *ident) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE PerMachineDirectory( 
            /* [retval][out] */ BSTR *directory) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE PerUserDirectory( 
            /* [retval][out] */ BSTR *directory) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RatingFromCommType( 
            /* [in] */ pEpComType commType,
            /* [retval][out] */ pEpRating *rating) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetIsSyncRunning( 
            /* [retval][out] */ VARIANT_BOOL *running) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ShutDownSync( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE MIMEDecodeMessage( 
            /* [in] */ BSTR mimeText,
            /* [retval][out] */ struct TextMessage *msg) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE MIMEEncodeMessage( 
            /* [in] */ struct TextMessage *msg,
            /* [in] */ VARIANT_BOOL omitFields,
            /* [retval][out] */ BSTR *mimeText) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ConfigPassphrase( 
            /* [in] */ BSTR passphrase) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ConfigPassphraseForNewKeys( 
            /* [in] */ VARIANT_BOOL enable,
            /* [in] */ BSTR passphrase) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ShowNotification( 
            /* [in] */ BSTR title,
            /* [in] */ BSTR message) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ExportSecretKey( 
            /* [in] */ BSTR fpr,
            /* [retval][out] */ BSTR *keyData) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE DisableAllSyncChannels( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SyncReinit( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GroupCreate( 
            /* [in] */ struct pEpIdentity *groupIdentity,
            /* [in] */ struct pEpIdentity *manager,
            /* [in] */ SAFEARRAY * memberlist) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GroupJoin( 
            /* [in] */ struct pEpIdentity *groupIdentity,
            /* [in] */ struct pEpIdentity *asMember,
            /* [in] */ struct pEpIdentity *manager) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GroupDissolve( 
            /* [in] */ struct pEpIdentity *groupIdentity,
            /* [in] */ struct pEpIdentity *manager) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GroupInviteMember( 
            /* [in] */ struct pEpIdentity *groupIdentity,
            /* [in] */ struct pEpIdentity *groupMember) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GroupRemoveMember( 
            /* [in] */ struct pEpIdentity *groupIdentity,
            /* [in] */ struct pEpIdentity *groupMember) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GroupRating( 
            /* [in] */ struct pEpIdentity *groupIdentity,
            /* [in] */ struct pEpIdentity *manager,
            /* [retval][out] */ enum pEpRating *rating) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GroupQueryGroups( 
            /* [in] */ struct pEpIdentity *manager,
            /* [retval][out] */ SAFEARRAY * *groupList) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GroupQueryManager( 
            /* [in] */ struct pEpIdentity *groupIdentity,
            /* [retval][out] */ struct pEpIdentity *manager) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GroupQueryMembers( 
            /* [in] */ struct pEpIdentity *groupIdentity,
            /* [retval][out] */ SAFEARRAY * *members) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetIdentity( 
            /* [in] */ struct pEpIdentity *identity) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetCommPartnerKey( 
            /* [in] */ struct pEpIdentity *identity,
            /* [in] */ BSTR fpr) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ImportKeyWithFprReturn( 
            /* [in] */ BSTR keyData,
            /* [out] */ SAFEARRAY * *privateKeys,
            /* [out] */ SAFEARRAY * *importedKeys) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IpEpEngineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IpEpEngine * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IpEpEngine * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IpEpEngine * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *VerboseLogging )( 
            IpEpEngine * This,
            /* [in] */ VARIANT_BOOL enable);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *PassiveMode )( 
            IpEpEngine * This,
            /* [in] */ VARIANT_BOOL enable);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *UnencryptedSubject )( 
            IpEpEngine * This,
            /* [in] */ VARIANT_BOOL enable);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ExportKey )( 
            IpEpEngine * This,
            /* [in] */ BSTR fpr,
            /* [retval][out] */ BSTR *keyData);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Log )( 
            IpEpEngine * This,
            /* [in] */ BSTR title,
            /* [in] */ BSTR entity,
            /* [defaultvalue][in] */ BSTR description,
            /* [defaultvalue][in] */ BSTR comment);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Trustwords )( 
            IpEpEngine * This,
            /* [in] */ BSTR fpr,
            /* [defaultvalue][in] */ BSTR lang,
            /* [defaultvalue][in] */ LONG maxWords,
            /* [retval][out] */ BSTR *words);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetTrustwords )( 
            IpEpEngine * This,
            /* [in] */ struct pEpIdentity *id1,
            /* [in] */ struct pEpIdentity *id2,
            /* [defaultvalue][in] */ BSTR lang,
            /* [defaultvalue][in] */ VARIANT_BOOL full,
            /* [retval][out] */ BSTR *words);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetCrashdumpLog )( 
            IpEpEngine * This,
            /* [defaultvalue][in] */ LONG maxlines,
            /* [retval][out] */ BSTR *log);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetEngineVersion )( 
            IpEpEngine * This,
            /* [retval][out] */ BSTR *engineVersion);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetLanguageList )( 
            IpEpEngine * This,
            /* [retval][out] */ BSTR *languages);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetIdentityFlags )( 
            IpEpEngine * This,
            /* [in] */ struct pEpIdentity *identity,
            /* [in] */ pEpIdentityFlags flags);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *UnsetIdentityFlags )( 
            IpEpEngine * This,
            /* [in] */ struct pEpIdentity *identity,
            /* [in] */ pEpIdentityFlags flags);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Myself )( 
            IpEpEngine * This,
            /* [in] */ struct pEpIdentity *ident,
            /* [retval][out] */ struct pEpIdentity *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *UpdateIdentity )( 
            IpEpEngine * This,
            /* [in] */ struct pEpIdentity *ident,
            /* [retval][out] */ struct pEpIdentity *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *KeyMistrusted )( 
            IpEpEngine * This,
            /* [in] */ struct pEpIdentity *ident);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *KeyResetTrust )( 
            IpEpEngine * This,
            /* [in] */ struct pEpIdentity *ident);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *TrustPersonalKey )( 
            IpEpEngine * This,
            /* [in] */ struct pEpIdentity *ident,
            /* [retval][out] */ struct pEpIdentity *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *OwnIdentitiesRetrieve )( 
            IpEpEngine * This,
            /* [retval][out] */ SAFEARRAY * *ownIdentities);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *IspEpUser )( 
            IpEpEngine * This,
            /* [in] */ struct pEpIdentity *ident,
            /* [retval][out] */ VARIANT_BOOL *ispEp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *OpenPGPListKeyinfo )( 
            IpEpEngine * This,
            /* [in] */ BSTR searchPattern,
            /* [retval][out] */ SAFEARRAY * *keyinfoList);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *EncryptMessage )( 
            IpEpEngine * This,
            /* [out][in] */ struct TextMessage *src,
            /* [out] */ struct TextMessage *dst,
            /* [in] */ SAFEARRAY * extra,
            /* [defaultvalue][in] */ pEpEncryptFlags flags,
            /* [defaultvalue][in] */ pEpEncFormat encFormat);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *DecryptMessage )( 
            IpEpEngine * This,
            /* [out][in] */ struct TextMessage *src,
            /* [out] */ struct TextMessage *dst,
            /* [out][in] */ SAFEARRAY * *keylist,
            /* [out][in] */ pEpDecryptFlags *flags,
            /* [retval][out] */ pEpRating *rating);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *OutgoingMessageRating )( 
            IpEpEngine * This,
            /* [in] */ struct TextMessage *msg,
            /* [retval][out] */ pEpRating *pVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *IdentityRating )( 
            IpEpEngine * This,
            /* [in] */ struct pEpIdentity *ident,
            /* [retval][out] */ pEpRating *pVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ColorFromRating )( 
            IpEpEngine * This,
            /* [in] */ pEpRating rating,
            /* [retval][out] */ pEpColor *pVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetMessageTrustwords )( 
            IpEpEngine * This,
            /* [in] */ struct TextMessage *msg,
            /* [in] */ struct pEpIdentity *receivedBy,
            /* [in] */ SAFEARRAY * keylist,
            /* [defaultvalue][in] */ BSTR lang,
            /* [defaultvalue][in] */ VARIANT_BOOL full,
            /* [retval][out] */ BSTR *words);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *EncryptMessageForSelf )( 
            IpEpEngine * This,
            /* [in] */ struct pEpIdentity *targetId,
            /* [in] */ struct TextMessage *src,
            /* [in] */ SAFEARRAY * extra,
            /* [out] */ struct TextMessage *dst,
            /* [defaultvalue][in] */ pEpEncryptFlags flags);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ReEvaluateMessageRating )( 
            IpEpEngine * This,
            /* [out][in] */ struct TextMessage *src,
            /* [in] */ SAFEARRAY * x_KeyList,
            /* [in] */ pEpRating x_EncStatus,
            /* [retval][out] */ pEpRating *rating);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *RegisterCallbacks )( 
            IpEpEngine * This,
            /* [in] */ IpEpEngineCallbacks *newCallback);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *UnregisterCallbacks )( 
            IpEpEngine * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetOwnKey )( 
            IpEpEngine * This,
            /* [in] */ struct pEpIdentity *ident,
            /* [in] */ BSTR fpr,
            /* [retval][out] */ struct pEpIdentity *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *EncryptMessageAndAddPrivKey )( 
            IpEpEngine * This,
            /* [in] */ struct TextMessage *src,
            /* [out] */ struct TextMessage *dst,
            /* [in] */ BSTR to_fpr,
            /* [defaultvalue][in] */ pEpEncryptFlags flags,
            /* [defaultvalue][in] */ pEpEncFormat encFormat);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *UpdateNow )( 
            IpEpEngine * This,
            /* [in] */ BSTR productCode,
            /* [out] */ VARIANT_BOOL *didUpdate);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *OutgoingMessageRatingPreview )( 
            IpEpEngine * This,
            /* [in] */ struct TextMessage *msg,
            /* [retval][out] */ pEpRating *rating);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *TrustOwnKey )( 
            IpEpEngine * This,
            /* [in] */ struct pEpIdentity *ident);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Startup )( 
            IpEpEngine * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetKeyRatingForUser )( 
            IpEpEngine * This,
            /* [in] */ BSTR userId,
            /* [in] */ BSTR fpr,
            /* [retval][out] */ pEpRating *rating);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *KeyResetIdentity )( 
            IpEpEngine * This,
            /* [in] */ struct pEpIdentity ident,
            /* [in] */ BSTR fpr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *KeyResetUser )( 
            IpEpEngine * This,
            /* [in] */ BSTR userId,
            /* [in] */ BSTR fpr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *KeyResetAllOwnKeys )( 
            IpEpEngine * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *DeliverHandshakeResult )( 
            IpEpEngine * This,
            /* [in] */ enum SyncHandshakeResult result,
            /* [in] */ SAFEARRAY * identities_sharing);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ImportKey )( 
            IpEpEngine * This,
            /* [in] */ BSTR keyData,
            /* [out] */ SAFEARRAY * *privateKeys);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ConfigCipherSuite )( 
            IpEpEngine * This,
            /* [defaultvalue][in] */ pEpCipherSuite cipherSuite);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *LeaveDeviceGroup )( 
            IpEpEngine * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetTrustwordsForFprs )( 
            IpEpEngine * This,
            /* [in] */ BSTR fpr1,
            /* [in] */ BSTR fpr2,
            /* [defaultvalue][in] */ BSTR lang,
            /* [defaultvalue][in] */ VARIANT_BOOL full,
            /* [retval][out] */ BSTR *words);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetKeyRating )( 
            IpEpEngine * This,
            /* [in] */ BSTR fpr,
            /* [retval][out] */ pEpComType *commType);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *PERToXERSyncMessage )( 
            IpEpEngine * This,
            /* [in] */ struct TextMessage *msg,
            /* [retval][out] */ BSTR *xer);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *DisableIdentityForSync )( 
            IpEpEngine * This,
            /* [in] */ struct pEpIdentity *ident);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *EnableIdentityForSync )( 
            IpEpEngine * This,
            /* [in] */ struct pEpIdentity *ident);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *PerMachineDirectory )( 
            IpEpEngine * This,
            /* [retval][out] */ BSTR *directory);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *PerUserDirectory )( 
            IpEpEngine * This,
            /* [retval][out] */ BSTR *directory);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *RatingFromCommType )( 
            IpEpEngine * This,
            /* [in] */ pEpComType commType,
            /* [retval][out] */ pEpRating *rating);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetIsSyncRunning )( 
            IpEpEngine * This,
            /* [retval][out] */ VARIANT_BOOL *running);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ShutDownSync )( 
            IpEpEngine * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *MIMEDecodeMessage )( 
            IpEpEngine * This,
            /* [in] */ BSTR mimeText,
            /* [retval][out] */ struct TextMessage *msg);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *MIMEEncodeMessage )( 
            IpEpEngine * This,
            /* [in] */ struct TextMessage *msg,
            /* [in] */ VARIANT_BOOL omitFields,
            /* [retval][out] */ BSTR *mimeText);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ConfigPassphrase )( 
            IpEpEngine * This,
            /* [in] */ BSTR passphrase);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ConfigPassphraseForNewKeys )( 
            IpEpEngine * This,
            /* [in] */ VARIANT_BOOL enable,
            /* [in] */ BSTR passphrase);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ShowNotification )( 
            IpEpEngine * This,
            /* [in] */ BSTR title,
            /* [in] */ BSTR message);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ExportSecretKey )( 
            IpEpEngine * This,
            /* [in] */ BSTR fpr,
            /* [retval][out] */ BSTR *keyData);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *DisableAllSyncChannels )( 
            IpEpEngine * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SyncReinit )( 
            IpEpEngine * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GroupCreate )( 
            IpEpEngine * This,
            /* [in] */ struct pEpIdentity *groupIdentity,
            /* [in] */ struct pEpIdentity *manager,
            /* [in] */ SAFEARRAY * memberlist);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GroupJoin )( 
            IpEpEngine * This,
            /* [in] */ struct pEpIdentity *groupIdentity,
            /* [in] */ struct pEpIdentity *asMember,
            /* [in] */ struct pEpIdentity *manager);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GroupDissolve )( 
            IpEpEngine * This,
            /* [in] */ struct pEpIdentity *groupIdentity,
            /* [in] */ struct pEpIdentity *manager);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GroupInviteMember )( 
            IpEpEngine * This,
            /* [in] */ struct pEpIdentity *groupIdentity,
            /* [in] */ struct pEpIdentity *groupMember);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GroupRemoveMember )( 
            IpEpEngine * This,
            /* [in] */ struct pEpIdentity *groupIdentity,
            /* [in] */ struct pEpIdentity *groupMember);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GroupRating )( 
            IpEpEngine * This,
            /* [in] */ struct pEpIdentity *groupIdentity,
            /* [in] */ struct pEpIdentity *manager,
            /* [retval][out] */ enum pEpRating *rating);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GroupQueryGroups )( 
            IpEpEngine * This,
            /* [in] */ struct pEpIdentity *manager,
            /* [retval][out] */ SAFEARRAY * *groupList);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GroupQueryManager )( 
            IpEpEngine * This,
            /* [in] */ struct pEpIdentity *groupIdentity,
            /* [retval][out] */ struct pEpIdentity *manager);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GroupQueryMembers )( 
            IpEpEngine * This,
            /* [in] */ struct pEpIdentity *groupIdentity,
            /* [retval][out] */ SAFEARRAY * *members);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetIdentity )( 
            IpEpEngine * This,
            /* [in] */ struct pEpIdentity *identity);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetCommPartnerKey )( 
            IpEpEngine * This,
            /* [in] */ struct pEpIdentity *identity,
            /* [in] */ BSTR fpr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ImportKeyWithFprReturn )( 
            IpEpEngine * This,
            /* [in] */ BSTR keyData,
            /* [out] */ SAFEARRAY * *privateKeys,
            /* [out] */ SAFEARRAY * *importedKeys);
        
        END_INTERFACE
    } IpEpEngineVtbl;

    interface IpEpEngine
    {
        CONST_VTBL struct IpEpEngineVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IpEpEngine_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IpEpEngine_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IpEpEngine_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IpEpEngine_VerboseLogging(This,enable)	\
    ( (This)->lpVtbl -> VerboseLogging(This,enable) ) 

#define IpEpEngine_PassiveMode(This,enable)	\
    ( (This)->lpVtbl -> PassiveMode(This,enable) ) 

#define IpEpEngine_UnencryptedSubject(This,enable)	\
    ( (This)->lpVtbl -> UnencryptedSubject(This,enable) ) 

#define IpEpEngine_ExportKey(This,fpr,keyData)	\
    ( (This)->lpVtbl -> ExportKey(This,fpr,keyData) ) 

#define IpEpEngine_Log(This,title,entity,description,comment)	\
    ( (This)->lpVtbl -> Log(This,title,entity,description,comment) ) 

#define IpEpEngine_Trustwords(This,fpr,lang,maxWords,words)	\
    ( (This)->lpVtbl -> Trustwords(This,fpr,lang,maxWords,words) ) 

#define IpEpEngine_GetTrustwords(This,id1,id2,lang,full,words)	\
    ( (This)->lpVtbl -> GetTrustwords(This,id1,id2,lang,full,words) ) 

#define IpEpEngine_GetCrashdumpLog(This,maxlines,log)	\
    ( (This)->lpVtbl -> GetCrashdumpLog(This,maxlines,log) ) 

#define IpEpEngine_GetEngineVersion(This,engineVersion)	\
    ( (This)->lpVtbl -> GetEngineVersion(This,engineVersion) ) 

#define IpEpEngine_GetLanguageList(This,languages)	\
    ( (This)->lpVtbl -> GetLanguageList(This,languages) ) 

#define IpEpEngine_SetIdentityFlags(This,identity,flags)	\
    ( (This)->lpVtbl -> SetIdentityFlags(This,identity,flags) ) 

#define IpEpEngine_UnsetIdentityFlags(This,identity,flags)	\
    ( (This)->lpVtbl -> UnsetIdentityFlags(This,identity,flags) ) 

#define IpEpEngine_Myself(This,ident,result)	\
    ( (This)->lpVtbl -> Myself(This,ident,result) ) 

#define IpEpEngine_UpdateIdentity(This,ident,result)	\
    ( (This)->lpVtbl -> UpdateIdentity(This,ident,result) ) 

#define IpEpEngine_KeyMistrusted(This,ident)	\
    ( (This)->lpVtbl -> KeyMistrusted(This,ident) ) 

#define IpEpEngine_KeyResetTrust(This,ident)	\
    ( (This)->lpVtbl -> KeyResetTrust(This,ident) ) 

#define IpEpEngine_TrustPersonalKey(This,ident,result)	\
    ( (This)->lpVtbl -> TrustPersonalKey(This,ident,result) ) 

#define IpEpEngine_OwnIdentitiesRetrieve(This,ownIdentities)	\
    ( (This)->lpVtbl -> OwnIdentitiesRetrieve(This,ownIdentities) ) 

#define IpEpEngine_IspEpUser(This,ident,ispEp)	\
    ( (This)->lpVtbl -> IspEpUser(This,ident,ispEp) ) 

#define IpEpEngine_OpenPGPListKeyinfo(This,searchPattern,keyinfoList)	\
    ( (This)->lpVtbl -> OpenPGPListKeyinfo(This,searchPattern,keyinfoList) ) 

#define IpEpEngine_EncryptMessage(This,src,dst,extra,flags,encFormat)	\
    ( (This)->lpVtbl -> EncryptMessage(This,src,dst,extra,flags,encFormat) ) 

#define IpEpEngine_DecryptMessage(This,src,dst,keylist,flags,rating)	\
    ( (This)->lpVtbl -> DecryptMessage(This,src,dst,keylist,flags,rating) ) 

#define IpEpEngine_OutgoingMessageRating(This,msg,pVal)	\
    ( (This)->lpVtbl -> OutgoingMessageRating(This,msg,pVal) ) 

#define IpEpEngine_IdentityRating(This,ident,pVal)	\
    ( (This)->lpVtbl -> IdentityRating(This,ident,pVal) ) 

#define IpEpEngine_ColorFromRating(This,rating,pVal)	\
    ( (This)->lpVtbl -> ColorFromRating(This,rating,pVal) ) 

#define IpEpEngine_GetMessageTrustwords(This,msg,receivedBy,keylist,lang,full,words)	\
    ( (This)->lpVtbl -> GetMessageTrustwords(This,msg,receivedBy,keylist,lang,full,words) ) 

#define IpEpEngine_EncryptMessageForSelf(This,targetId,src,extra,dst,flags)	\
    ( (This)->lpVtbl -> EncryptMessageForSelf(This,targetId,src,extra,dst,flags) ) 

#define IpEpEngine_ReEvaluateMessageRating(This,src,x_KeyList,x_EncStatus,rating)	\
    ( (This)->lpVtbl -> ReEvaluateMessageRating(This,src,x_KeyList,x_EncStatus,rating) ) 

#define IpEpEngine_RegisterCallbacks(This,newCallback)	\
    ( (This)->lpVtbl -> RegisterCallbacks(This,newCallback) ) 

#define IpEpEngine_UnregisterCallbacks(This)	\
    ( (This)->lpVtbl -> UnregisterCallbacks(This) ) 

#define IpEpEngine_SetOwnKey(This,ident,fpr,result)	\
    ( (This)->lpVtbl -> SetOwnKey(This,ident,fpr,result) ) 

#define IpEpEngine_EncryptMessageAndAddPrivKey(This,src,dst,to_fpr,flags,encFormat)	\
    ( (This)->lpVtbl -> EncryptMessageAndAddPrivKey(This,src,dst,to_fpr,flags,encFormat) ) 

#define IpEpEngine_UpdateNow(This,productCode,didUpdate)	\
    ( (This)->lpVtbl -> UpdateNow(This,productCode,didUpdate) ) 

#define IpEpEngine_OutgoingMessageRatingPreview(This,msg,rating)	\
    ( (This)->lpVtbl -> OutgoingMessageRatingPreview(This,msg,rating) ) 

#define IpEpEngine_TrustOwnKey(This,ident)	\
    ( (This)->lpVtbl -> TrustOwnKey(This,ident) ) 

#define IpEpEngine_Startup(This)	\
    ( (This)->lpVtbl -> Startup(This) ) 

#define IpEpEngine_GetKeyRatingForUser(This,userId,fpr,rating)	\
    ( (This)->lpVtbl -> GetKeyRatingForUser(This,userId,fpr,rating) ) 

#define IpEpEngine_KeyResetIdentity(This,ident,fpr)	\
    ( (This)->lpVtbl -> KeyResetIdentity(This,ident,fpr) ) 

#define IpEpEngine_KeyResetUser(This,userId,fpr)	\
    ( (This)->lpVtbl -> KeyResetUser(This,userId,fpr) ) 

#define IpEpEngine_KeyResetAllOwnKeys(This)	\
    ( (This)->lpVtbl -> KeyResetAllOwnKeys(This) ) 

#define IpEpEngine_DeliverHandshakeResult(This,result,identities_sharing)	\
    ( (This)->lpVtbl -> DeliverHandshakeResult(This,result,identities_sharing) ) 

#define IpEpEngine_ImportKey(This,keyData,privateKeys)	\
    ( (This)->lpVtbl -> ImportKey(This,keyData,privateKeys) ) 

#define IpEpEngine_ConfigCipherSuite(This,cipherSuite)	\
    ( (This)->lpVtbl -> ConfigCipherSuite(This,cipherSuite) ) 

#define IpEpEngine_LeaveDeviceGroup(This)	\
    ( (This)->lpVtbl -> LeaveDeviceGroup(This) ) 

#define IpEpEngine_GetTrustwordsForFprs(This,fpr1,fpr2,lang,full,words)	\
    ( (This)->lpVtbl -> GetTrustwordsForFprs(This,fpr1,fpr2,lang,full,words) ) 

#define IpEpEngine_GetKeyRating(This,fpr,commType)	\
    ( (This)->lpVtbl -> GetKeyRating(This,fpr,commType) ) 

#define IpEpEngine_PERToXERSyncMessage(This,msg,xer)	\
    ( (This)->lpVtbl -> PERToXERSyncMessage(This,msg,xer) ) 

#define IpEpEngine_DisableIdentityForSync(This,ident)	\
    ( (This)->lpVtbl -> DisableIdentityForSync(This,ident) ) 

#define IpEpEngine_EnableIdentityForSync(This,ident)	\
    ( (This)->lpVtbl -> EnableIdentityForSync(This,ident) ) 

#define IpEpEngine_PerMachineDirectory(This,directory)	\
    ( (This)->lpVtbl -> PerMachineDirectory(This,directory) ) 

#define IpEpEngine_PerUserDirectory(This,directory)	\
    ( (This)->lpVtbl -> PerUserDirectory(This,directory) ) 

#define IpEpEngine_RatingFromCommType(This,commType,rating)	\
    ( (This)->lpVtbl -> RatingFromCommType(This,commType,rating) ) 

#define IpEpEngine_GetIsSyncRunning(This,running)	\
    ( (This)->lpVtbl -> GetIsSyncRunning(This,running) ) 

#define IpEpEngine_ShutDownSync(This)	\
    ( (This)->lpVtbl -> ShutDownSync(This) ) 

#define IpEpEngine_MIMEDecodeMessage(This,mimeText,msg)	\
    ( (This)->lpVtbl -> MIMEDecodeMessage(This,mimeText,msg) ) 

#define IpEpEngine_MIMEEncodeMessage(This,msg,omitFields,mimeText)	\
    ( (This)->lpVtbl -> MIMEEncodeMessage(This,msg,omitFields,mimeText) ) 

#define IpEpEngine_ConfigPassphrase(This,passphrase)	\
    ( (This)->lpVtbl -> ConfigPassphrase(This,passphrase) ) 

#define IpEpEngine_ConfigPassphraseForNewKeys(This,enable,passphrase)	\
    ( (This)->lpVtbl -> ConfigPassphraseForNewKeys(This,enable,passphrase) ) 

#define IpEpEngine_ShowNotification(This,title,message)	\
    ( (This)->lpVtbl -> ShowNotification(This,title,message) ) 

#define IpEpEngine_ExportSecretKey(This,fpr,keyData)	\
    ( (This)->lpVtbl -> ExportSecretKey(This,fpr,keyData) ) 

#define IpEpEngine_DisableAllSyncChannels(This)	\
    ( (This)->lpVtbl -> DisableAllSyncChannels(This) ) 

#define IpEpEngine_SyncReinit(This)	\
    ( (This)->lpVtbl -> SyncReinit(This) ) 

#define IpEpEngine_GroupCreate(This,groupIdentity,manager,memberlist)	\
    ( (This)->lpVtbl -> GroupCreate(This,groupIdentity,manager,memberlist) ) 

#define IpEpEngine_GroupJoin(This,groupIdentity,asMember,manager)	\
    ( (This)->lpVtbl -> GroupJoin(This,groupIdentity,asMember,manager) ) 

#define IpEpEngine_GroupDissolve(This,groupIdentity,manager)	\
    ( (This)->lpVtbl -> GroupDissolve(This,groupIdentity,manager) ) 

#define IpEpEngine_GroupInviteMember(This,groupIdentity,groupMember)	\
    ( (This)->lpVtbl -> GroupInviteMember(This,groupIdentity,groupMember) ) 

#define IpEpEngine_GroupRemoveMember(This,groupIdentity,groupMember)	\
    ( (This)->lpVtbl -> GroupRemoveMember(This,groupIdentity,groupMember) ) 

#define IpEpEngine_GroupRating(This,groupIdentity,manager,rating)	\
    ( (This)->lpVtbl -> GroupRating(This,groupIdentity,manager,rating) ) 

#define IpEpEngine_GroupQueryGroups(This,manager,groupList)	\
    ( (This)->lpVtbl -> GroupQueryGroups(This,manager,groupList) ) 

#define IpEpEngine_GroupQueryManager(This,groupIdentity,manager)	\
    ( (This)->lpVtbl -> GroupQueryManager(This,groupIdentity,manager) ) 

#define IpEpEngine_GroupQueryMembers(This,groupIdentity,members)	\
    ( (This)->lpVtbl -> GroupQueryMembers(This,groupIdentity,members) ) 

#define IpEpEngine_SetIdentity(This,identity)	\
    ( (This)->lpVtbl -> SetIdentity(This,identity) ) 

#define IpEpEngine_SetCommPartnerKey(This,identity,fpr)	\
    ( (This)->lpVtbl -> SetCommPartnerKey(This,identity,fpr) ) 

#define IpEpEngine_ImportKeyWithFprReturn(This,keyData,privateKeys,importedKeys)	\
    ( (This)->lpVtbl -> ImportKeyWithFprReturn(This,keyData,privateKeys,importedKeys) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IpEpEngine_INTERFACE_DEFINED__ */



#ifndef __pEpCOMServerAdapterLib_LIBRARY_DEFINED__
#define __pEpCOMServerAdapterLib_LIBRARY_DEFINED__

/* library pEpCOMServerAdapterLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_pEpCOMServerAdapterLib;

EXTERN_C const CLSID CLSID_pEpEngine;

#ifdef __cplusplus

class DECLSPEC_UUID("5FF6682B-727B-4DFE-A68D-28982874C0C7")
pEpEngine;
#endif
#endif /* __pEpCOMServerAdapterLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

unsigned long             __RPC_USER  BSTR_UserSize64(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree64(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize64(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal64(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal64(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree64(     unsigned long *, LPSAFEARRAY * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


