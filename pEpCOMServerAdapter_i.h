

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sat May 30 01:09:44 2015
 */
/* Compiler settings for pEpCOMServerAdapter.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __pEpCOMServerAdapter_i_h__
#define __pEpCOMServerAdapter_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITextMessage_FWD_DEFINED__
#define __ITextMessage_FWD_DEFINED__
typedef interface ITextMessage ITextMessage;

#endif 	/* __ITextMessage_FWD_DEFINED__ */


#ifndef __IpEpEngine_FWD_DEFINED__
#define __IpEpEngine_FWD_DEFINED__
typedef interface IpEpEngine IpEpEngine;

#endif 	/* __IpEpEngine_FWD_DEFINED__ */


#ifndef ___IpEpEngineEvents_FWD_DEFINED__
#define ___IpEpEngineEvents_FWD_DEFINED__
typedef interface _IpEpEngineEvents _IpEpEngineEvents;

#endif 	/* ___IpEpEngineEvents_FWD_DEFINED__ */


#ifndef __pEpEngine_FWD_DEFINED__
#define __pEpEngine_FWD_DEFINED__

#ifdef __cplusplus
typedef class pEpEngine pEpEngine;
#else
typedef struct pEpEngine pEpEngine;
#endif /* __cplusplus */

#endif 	/* __pEpEngine_FWD_DEFINED__ */


#ifndef ___ITextMessageEvents_FWD_DEFINED__
#define ___ITextMessageEvents_FWD_DEFINED__
typedef interface _ITextMessageEvents _ITextMessageEvents;

#endif 	/* ___ITextMessageEvents_FWD_DEFINED__ */


#ifndef __TextMessage_FWD_DEFINED__
#define __TextMessage_FWD_DEFINED__

#ifdef __cplusplus
typedef class TextMessage TextMessage;
#else
typedef struct TextMessage TextMessage;
#endif /* __cplusplus */

#endif 	/* __TextMessage_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ITextMessage_INTERFACE_DEFINED__
#define __ITextMessage_INTERFACE_DEFINED__

/* interface ITextMessage */
/* [unique][nonextensible][oleautomation][uuid][object] */ 

typedef 
enum _pEp_text_format
    {
        pEp_text_format_plain	= 0,
        pEp_text_format_html	= ( pEp_text_format_plain + 1 ) ,
        pEp_text_format_other	= 0xff
    } 	pEp_text_format;

typedef 
enum _pEp_msg_direction
    {
        pEp_dir_incoming	= 0,
        pEp_dir_outgoing	= ( pEp_dir_incoming + 1 ) 
    } 	pEp_msg_direction;

typedef 
enum _pEp_MIME_format
    {
        pEp_MIME_none	= 0,
        pEp_MIME_fields_omitted	= ( pEp_MIME_none + 1 ) ,
        pEp_MIME	= ( pEp_MIME_fields_omitted + 1 ) 
    } 	pEp_MIME_format;

typedef 
enum _pEp_enc_format
    {
        pEp_enc_none	= 0,
        pEp_enc_pieces	= ( pEp_enc_none + 1 ) ,
        pEp_enc_S_MIME	= ( pEp_enc_pieces + 1 ) ,
        pEp_enc_PGP_MIME	= ( pEp_enc_S_MIME + 1 ) ,
        pEp_enc_pEp	= ( pEp_enc_PGP_MIME + 1 ) 
    } 	pEp_enc_format;

/* [uuid] */ struct  DECLSPEC_UUID("1292C31A-6486-427F-B29F-7F03607836DC") opt_field
    {
    BSTR name;
    BSTR value;
    } ;

EXTERN_C const IID IID_ITextMessage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("161538F9-53C8-4D9C-8BA4-0FB43AEC7106")
    ITextMessage : public IUnknown
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_dir( 
            /* [retval][out] */ pEp_msg_direction *pVal) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_dir( 
            /* [in] */ pEp_msg_direction newVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_id( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_id( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_shortmsg( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_shortmsg( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_longmsg( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_longmsg( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_longmsg_formatted( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_longmsg_formatted( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE add_attachment( 
            /* [in] */ SAFEARRAY * data,
            /* [in] */ BSTR mime_type,
            /* [in] */ BSTR filename) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE has_attachments( 
            /* [retval][out] */ boolean *result) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE next_attachment( 
            /* [out] */ SAFEARRAY * *data,
            /* [out] */ BSTR *mime_type,
            /* [out] */ BSTR *filename,
            /* [retval][out] */ boolean *result) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_sent( 
            /* [retval][out] */ hyper *result) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_sent( 
            /* [in] */ hyper val) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_recv( 
            /* [retval][out] */ hyper *result) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_recv( 
            /* [in] */ hyper val) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_from( 
            /* [retval][out] */ struct pEp_identity_s *pVal) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_from( 
            /* [in] */ struct pEp_identity_s *newVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_to( 
            /* [retval][out] */ SAFEARRAY * *pVal) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_to( 
            /* [in] */ SAFEARRAY * newVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_recv_by( 
            /* [retval][out] */ struct pEp_identity_s *pVal) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_recv_by( 
            /* [in] */ struct pEp_identity_s *newVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_cc( 
            /* [retval][out] */ SAFEARRAY * *pVal) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_cc( 
            /* [in] */ SAFEARRAY * newVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_bcc( 
            /* [retval][out] */ SAFEARRAY * *pVal) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_bcc( 
            /* [in] */ SAFEARRAY * newVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_reply_to( 
            /* [retval][out] */ SAFEARRAY * *pVal) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_reply_to( 
            /* [in] */ SAFEARRAY * newVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_references( 
            /* [retval][out] */ SAFEARRAY * *pVal) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_references( 
            /* [in] */ SAFEARRAY * newVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_keywords( 
            /* [retval][out] */ SAFEARRAY * *pVal) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_keywords( 
            /* [in] */ SAFEARRAY * newVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_comments( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_comments( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_opt_fields( 
            /* [retval][out] */ SAFEARRAY * *pVal) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_opt_fields( 
            /* [in] */ SAFEARRAY * newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ITextMessageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITextMessage * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITextMessage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITextMessage * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_dir )( 
            ITextMessage * This,
            /* [retval][out] */ pEp_msg_direction *pVal);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_dir )( 
            ITextMessage * This,
            /* [in] */ pEp_msg_direction newVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_id )( 
            ITextMessage * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_id )( 
            ITextMessage * This,
            /* [in] */ BSTR newVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_shortmsg )( 
            ITextMessage * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_shortmsg )( 
            ITextMessage * This,
            /* [in] */ BSTR newVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_longmsg )( 
            ITextMessage * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_longmsg )( 
            ITextMessage * This,
            /* [in] */ BSTR newVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_longmsg_formatted )( 
            ITextMessage * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_longmsg_formatted )( 
            ITextMessage * This,
            /* [in] */ BSTR newVal);
        
        HRESULT ( STDMETHODCALLTYPE *add_attachment )( 
            ITextMessage * This,
            /* [in] */ SAFEARRAY * data,
            /* [in] */ BSTR mime_type,
            /* [in] */ BSTR filename);
        
        HRESULT ( STDMETHODCALLTYPE *has_attachments )( 
            ITextMessage * This,
            /* [retval][out] */ boolean *result);
        
        HRESULT ( STDMETHODCALLTYPE *next_attachment )( 
            ITextMessage * This,
            /* [out] */ SAFEARRAY * *data,
            /* [out] */ BSTR *mime_type,
            /* [out] */ BSTR *filename,
            /* [retval][out] */ boolean *result);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_sent )( 
            ITextMessage * This,
            /* [retval][out] */ hyper *result);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_sent )( 
            ITextMessage * This,
            /* [in] */ hyper val);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_recv )( 
            ITextMessage * This,
            /* [retval][out] */ hyper *result);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_recv )( 
            ITextMessage * This,
            /* [in] */ hyper val);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_from )( 
            ITextMessage * This,
            /* [retval][out] */ struct pEp_identity_s *pVal);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_from )( 
            ITextMessage * This,
            /* [in] */ struct pEp_identity_s *newVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_to )( 
            ITextMessage * This,
            /* [retval][out] */ SAFEARRAY * *pVal);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_to )( 
            ITextMessage * This,
            /* [in] */ SAFEARRAY * newVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_recv_by )( 
            ITextMessage * This,
            /* [retval][out] */ struct pEp_identity_s *pVal);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_recv_by )( 
            ITextMessage * This,
            /* [in] */ struct pEp_identity_s *newVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_cc )( 
            ITextMessage * This,
            /* [retval][out] */ SAFEARRAY * *pVal);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_cc )( 
            ITextMessage * This,
            /* [in] */ SAFEARRAY * newVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_bcc )( 
            ITextMessage * This,
            /* [retval][out] */ SAFEARRAY * *pVal);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_bcc )( 
            ITextMessage * This,
            /* [in] */ SAFEARRAY * newVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_reply_to )( 
            ITextMessage * This,
            /* [retval][out] */ SAFEARRAY * *pVal);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_reply_to )( 
            ITextMessage * This,
            /* [in] */ SAFEARRAY * newVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_references )( 
            ITextMessage * This,
            /* [retval][out] */ SAFEARRAY * *pVal);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_references )( 
            ITextMessage * This,
            /* [in] */ SAFEARRAY * newVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_keywords )( 
            ITextMessage * This,
            /* [retval][out] */ SAFEARRAY * *pVal);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_keywords )( 
            ITextMessage * This,
            /* [in] */ SAFEARRAY * newVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_comments )( 
            ITextMessage * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_comments )( 
            ITextMessage * This,
            /* [in] */ BSTR newVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_opt_fields )( 
            ITextMessage * This,
            /* [retval][out] */ SAFEARRAY * *pVal);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_opt_fields )( 
            ITextMessage * This,
            /* [in] */ SAFEARRAY * newVal);
        
        END_INTERFACE
    } ITextMessageVtbl;

    interface ITextMessage
    {
        CONST_VTBL struct ITextMessageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITextMessage_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITextMessage_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITextMessage_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITextMessage_get_dir(This,pVal)	\
    ( (This)->lpVtbl -> get_dir(This,pVal) ) 

#define ITextMessage_put_dir(This,newVal)	\
    ( (This)->lpVtbl -> put_dir(This,newVal) ) 

#define ITextMessage_get_id(This,pVal)	\
    ( (This)->lpVtbl -> get_id(This,pVal) ) 

#define ITextMessage_put_id(This,newVal)	\
    ( (This)->lpVtbl -> put_id(This,newVal) ) 

#define ITextMessage_get_shortmsg(This,pVal)	\
    ( (This)->lpVtbl -> get_shortmsg(This,pVal) ) 

#define ITextMessage_put_shortmsg(This,newVal)	\
    ( (This)->lpVtbl -> put_shortmsg(This,newVal) ) 

#define ITextMessage_get_longmsg(This,pVal)	\
    ( (This)->lpVtbl -> get_longmsg(This,pVal) ) 

#define ITextMessage_put_longmsg(This,newVal)	\
    ( (This)->lpVtbl -> put_longmsg(This,newVal) ) 

#define ITextMessage_get_longmsg_formatted(This,pVal)	\
    ( (This)->lpVtbl -> get_longmsg_formatted(This,pVal) ) 

#define ITextMessage_put_longmsg_formatted(This,newVal)	\
    ( (This)->lpVtbl -> put_longmsg_formatted(This,newVal) ) 

#define ITextMessage_add_attachment(This,data,mime_type,filename)	\
    ( (This)->lpVtbl -> add_attachment(This,data,mime_type,filename) ) 

#define ITextMessage_has_attachments(This,result)	\
    ( (This)->lpVtbl -> has_attachments(This,result) ) 

#define ITextMessage_next_attachment(This,data,mime_type,filename,result)	\
    ( (This)->lpVtbl -> next_attachment(This,data,mime_type,filename,result) ) 

#define ITextMessage_get_sent(This,result)	\
    ( (This)->lpVtbl -> get_sent(This,result) ) 

#define ITextMessage_put_sent(This,val)	\
    ( (This)->lpVtbl -> put_sent(This,val) ) 

#define ITextMessage_get_recv(This,result)	\
    ( (This)->lpVtbl -> get_recv(This,result) ) 

#define ITextMessage_put_recv(This,val)	\
    ( (This)->lpVtbl -> put_recv(This,val) ) 

#define ITextMessage_get_from(This,pVal)	\
    ( (This)->lpVtbl -> get_from(This,pVal) ) 

#define ITextMessage_put_from(This,newVal)	\
    ( (This)->lpVtbl -> put_from(This,newVal) ) 

#define ITextMessage_get_to(This,pVal)	\
    ( (This)->lpVtbl -> get_to(This,pVal) ) 

#define ITextMessage_put_to(This,newVal)	\
    ( (This)->lpVtbl -> put_to(This,newVal) ) 

#define ITextMessage_get_recv_by(This,pVal)	\
    ( (This)->lpVtbl -> get_recv_by(This,pVal) ) 

#define ITextMessage_put_recv_by(This,newVal)	\
    ( (This)->lpVtbl -> put_recv_by(This,newVal) ) 

#define ITextMessage_get_cc(This,pVal)	\
    ( (This)->lpVtbl -> get_cc(This,pVal) ) 

#define ITextMessage_put_cc(This,newVal)	\
    ( (This)->lpVtbl -> put_cc(This,newVal) ) 

#define ITextMessage_get_bcc(This,pVal)	\
    ( (This)->lpVtbl -> get_bcc(This,pVal) ) 

#define ITextMessage_put_bcc(This,newVal)	\
    ( (This)->lpVtbl -> put_bcc(This,newVal) ) 

#define ITextMessage_get_reply_to(This,pVal)	\
    ( (This)->lpVtbl -> get_reply_to(This,pVal) ) 

#define ITextMessage_put_reply_to(This,newVal)	\
    ( (This)->lpVtbl -> put_reply_to(This,newVal) ) 

#define ITextMessage_get_references(This,pVal)	\
    ( (This)->lpVtbl -> get_references(This,pVal) ) 

#define ITextMessage_put_references(This,newVal)	\
    ( (This)->lpVtbl -> put_references(This,newVal) ) 

#define ITextMessage_get_keywords(This,pVal)	\
    ( (This)->lpVtbl -> get_keywords(This,pVal) ) 

#define ITextMessage_put_keywords(This,newVal)	\
    ( (This)->lpVtbl -> put_keywords(This,newVal) ) 

#define ITextMessage_get_comments(This,pVal)	\
    ( (This)->lpVtbl -> get_comments(This,pVal) ) 

#define ITextMessage_put_comments(This,newVal)	\
    ( (This)->lpVtbl -> put_comments(This,newVal) ) 

#define ITextMessage_get_opt_fields(This,pVal)	\
    ( (This)->lpVtbl -> get_opt_fields(This,pVal) ) 

#define ITextMessage_put_opt_fields(This,newVal)	\
    ( (This)->lpVtbl -> put_opt_fields(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITextMessage_INTERFACE_DEFINED__ */


#ifndef __IpEpEngine_INTERFACE_DEFINED__
#define __IpEpEngine_INTERFACE_DEFINED__

/* interface IpEpEngine */
/* [unique][nonextensible][oleautomation][uuid][object] */ 

typedef 
enum _pEp_STATUS
    {
        pEp_STATUS_OK	= 0,
        pEp_KEY_NOT_FOUND	= 0x201,
        pEp_KEY_HAS_AMBIG_NAME	= 0x202,
        pEp_GET_KEY_FAILED	= 0x203,
        pEp_UNENCRYPTED	= 0x400,
        pEp_VERIFIED	= 0x401,
        pEp_DECRYPTED	= 0x402,
        pEp_DECRYPTED_AND_VERIFIED	= 0x403,
        pEp_DECRYPT_WRONG_FORMAT	= 0x404,
        pEp_DECRYPT_NO_KEY	= 0x405,
        pEp_DECRYPT_SIGNATURE_DOES_NOT_MATCH	= 0x406,
        pEp_VERIFY_NO_KEY	= 0x407,
        pEp_VERIFIED_AND_TRUSTED	= 0x408,
        pEp_ILLEGAL_VALUE	= -4,
        pEp_BUFFER_TOO_SMALL	= -3,
        pEp_OUT_OF_MEMORY	= -2,
        pEp_UNKNOWN_ERROR	= -1
    } 	pEp_STATUS;

typedef 
enum _pEp_comm_type
    {
        pEp_ct_unknown	= 0,
        pEp_ct_no_encryption	= 0x1,
        pEp_ct_no_encrypted_channel	= 0x2,
        pEp_ct_key_not_found	= 0x3,
        pEp_ct_key_expired	= 0x4,
        pEp_ct_key_revoked	= 0x5,
        pEp_ct_key_b0rken	= 0x6,
        pEp_ct_my_key_not_included	= 0x9,
        pEp_ct_security_by_obscurity	= 0xa,
        pEp_ct_b0rken_crypto	= 0xb,
        pEp_ct_key_too_short	= 0xe,
        pEp_ct_compromized	= 0xf,
        pEp_ct_unconfirmed_encryption	= 0x10,
        pEp_ct_OpenPGP_1024_RSA_unconfirmed	= 0x11,
        pEp_ct_OpenPGP_unconfirmed	= 0x3f,
        pEp_ct_unconfirmed_enc_anon	= 0x40,
        pEp_ct_pEp_unconfirmed	= 0x7f,
        pEp_ct_confirmed	= 0x80,
        pEp_ct_confirmed_encryption	= 0x90,
        pEp_ct_OpenPGP_1024_RSA	= 0x91,
        pEp_ct_OpenPGP	= 0xbf,
        pEp_ct_confirmed_enc_anon	= 0xc0,
        pEp_ct_pEp	= 0xff
    } 	pEp_comm_type;

/* [uuid] */ struct  DECLSPEC_UUID("0CB90E62-8A6A-4CA0-99D7-481704051FF0") pEp_identity_s
    {
    BSTR address;
    BSTR fpr;
    BSTR user_id;
    BSTR username;
    pEp_comm_type comm_type;
    BSTR lang;
    } ;
typedef 
enum _pEp_color
    {
        pEp_rating_undefined	= 0,
        pEp_rating_cannot_decrypt	= ( pEp_rating_undefined + 1 ) ,
        pEp_rating_have_no_key	= ( pEp_rating_cannot_decrypt + 1 ) ,
        pEp_rating_unencrypted	= ( pEp_rating_have_no_key + 1 ) ,
        pEp_rating_unreliable	= ( pEp_rating_unencrypted + 1 ) ,
        pEp_rating_reliable	= ( pEp_rating_unreliable + 1 ) ,
        pEp_rating_yellow	= pEp_rating_reliable,
        pEp_rating_trusted	= ( pEp_rating_yellow + 1 ) ,
        pEp_rating_green	= pEp_rating_trusted,
        pEp_rating_trusted_and_anonymized	= ( pEp_rating_green + 1 ) ,
        pEp_rating_fully_anonymous	= ( pEp_rating_trusted_and_anonymized + 1 ) ,
        pEp_rating_under_attack	= -1,
        pEp_rating_red	= pEp_rating_under_attack,
        pEp_rating_b0rken	= -2
    } 	pEp_color;


EXTERN_C const IID IID_IpEpEngine;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9A9F4422-CF0A-45D7-90CD-1D1B7B2A4540")
    IpEpEngine : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE log( 
            /* [in] */ BSTR title,
            /* [in] */ BSTR entity,
            /* [defaultvalue][in] */ BSTR description = L"",
            /* [defaultvalue][in] */ BSTR comment = L"") = 0;
        
        virtual HRESULT STDMETHODCALLTYPE decrypt( 
            /* [in] */ BSTR ctext,
            /* [out] */ BSTR *ptext,
            /* [out] */ SAFEARRAY * *key_list,
            /* [retval][out] */ pEp_STATUS *decrypt_status) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE decrypt_b( 
            /* [in] */ BSTR ctext,
            /* [out] */ SAFEARRAY * *ptext,
            /* [out] */ SAFEARRAY * *key_list,
            /* [retval][out] */ pEp_STATUS *decrypt_status) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE encrypt( 
            /* [in] */ SAFEARRAY * key_list,
            /* [in] */ BSTR ptext,
            /* [out] */ BSTR *ctext,
            /* [retval][out] */ pEp_STATUS *status) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE encrypt_b( 
            /* [in] */ SAFEARRAY * key_list,
            /* [in] */ SAFEARRAY * ptext,
            /* [out] */ BSTR *ctext,
            /* [retval][out] */ pEp_STATUS *status) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE verify( 
            /* [in] */ BSTR text,
            /* [in] */ BSTR signature,
            /* [out] */ SAFEARRAY * *key_list,
            /* [retval][out] */ pEp_STATUS *verify_status) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE trustword( 
            /* [in] */ LONG value,
            /* [defaultvalue][in] */ BSTR lang,
            /* [retval][out] */ BSTR *word) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE trustwords( 
            /* [in] */ BSTR fpr,
            /* [defaultvalue][in] */ BSTR lang,
            /* [defaultvalue][in] */ LONG max_words,
            /* [retval][out] */ BSTR *words) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_identity( 
            /* [in] */ BSTR address,
            /* [retval][out] */ struct pEp_identity_s *ident) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE set_identity( 
            /* [in] */ struct pEp_identity_s *ident) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE generate_keypair( 
            /* [in] */ struct pEp_identity_s *ident,
            /* [retval][out] */ BSTR *fpr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE delete_keypair( 
            /* [in] */ BSTR fpr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE import_key( 
            /* [in] */ BSTR key_data) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE import_key_b( 
            /* [in] */ SAFEARRAY * key_data) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE export_key( 
            /* [in] */ BSTR fpr,
            /* [retval][out] */ BSTR *key_data) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE recv_key( 
            /* [in] */ BSTR pattern) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE find_keys( 
            /* [in] */ BSTR pattern,
            /* [retval][out] */ SAFEARRAY * *key_list) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE send_key( 
            /* [in] */ BSTR pattern) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE start_keyserver_lookup( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE stop_keyserver_lookup( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE examine_identity( 
            /* [in] */ struct pEp_identity_s *ident) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE examine_myself( 
            /* [in] */ struct pEp_identity_s *myself) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE myself( 
            /* [in] */ struct pEp_identity_s *ident,
            /* [retval][out] */ struct pEp_identity_s *result) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE update_identity( 
            /* [in] */ struct pEp_identity_s *ident,
            /* [retval][out] */ struct pEp_identity_s *result) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE key_compromized( 
            /* [in] */ BSTR fpr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE encrypt_message( 
            /* [in] */ ITextMessage *src,
            /* [out] */ ITextMessage **dst,
            /* [in] */ SAFEARRAY * extra) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE decrypt_message( 
            /* [in] */ ITextMessage *src,
            /* [out] */ ITextMessage **dst,
            /* [out] */ SAFEARRAY * *keylist,
            /* [retval][out] */ pEp_color *rating) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE outgoing_message_color( 
            /* [in] */ ITextMessage *msg,
            /* [retval][out] */ pEp_color *pVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE identity_color( 
            /* [in] */ struct pEp_identity_s *ident,
            /* [retval][out] */ pEp_color *pVal) = 0;
        
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
        
        HRESULT ( STDMETHODCALLTYPE *log )( 
            IpEpEngine * This,
            /* [in] */ BSTR title,
            /* [in] */ BSTR entity,
            /* [defaultvalue][in] */ BSTR description,
            /* [defaultvalue][in] */ BSTR comment);
        
        HRESULT ( STDMETHODCALLTYPE *decrypt )( 
            IpEpEngine * This,
            /* [in] */ BSTR ctext,
            /* [out] */ BSTR *ptext,
            /* [out] */ SAFEARRAY * *key_list,
            /* [retval][out] */ pEp_STATUS *decrypt_status);
        
        HRESULT ( STDMETHODCALLTYPE *decrypt_b )( 
            IpEpEngine * This,
            /* [in] */ BSTR ctext,
            /* [out] */ SAFEARRAY * *ptext,
            /* [out] */ SAFEARRAY * *key_list,
            /* [retval][out] */ pEp_STATUS *decrypt_status);
        
        HRESULT ( STDMETHODCALLTYPE *encrypt )( 
            IpEpEngine * This,
            /* [in] */ SAFEARRAY * key_list,
            /* [in] */ BSTR ptext,
            /* [out] */ BSTR *ctext,
            /* [retval][out] */ pEp_STATUS *status);
        
        HRESULT ( STDMETHODCALLTYPE *encrypt_b )( 
            IpEpEngine * This,
            /* [in] */ SAFEARRAY * key_list,
            /* [in] */ SAFEARRAY * ptext,
            /* [out] */ BSTR *ctext,
            /* [retval][out] */ pEp_STATUS *status);
        
        HRESULT ( STDMETHODCALLTYPE *verify )( 
            IpEpEngine * This,
            /* [in] */ BSTR text,
            /* [in] */ BSTR signature,
            /* [out] */ SAFEARRAY * *key_list,
            /* [retval][out] */ pEp_STATUS *verify_status);
        
        HRESULT ( STDMETHODCALLTYPE *trustword )( 
            IpEpEngine * This,
            /* [in] */ LONG value,
            /* [defaultvalue][in] */ BSTR lang,
            /* [retval][out] */ BSTR *word);
        
        HRESULT ( STDMETHODCALLTYPE *trustwords )( 
            IpEpEngine * This,
            /* [in] */ BSTR fpr,
            /* [defaultvalue][in] */ BSTR lang,
            /* [defaultvalue][in] */ LONG max_words,
            /* [retval][out] */ BSTR *words);
        
        HRESULT ( STDMETHODCALLTYPE *get_identity )( 
            IpEpEngine * This,
            /* [in] */ BSTR address,
            /* [retval][out] */ struct pEp_identity_s *ident);
        
        HRESULT ( STDMETHODCALLTYPE *set_identity )( 
            IpEpEngine * This,
            /* [in] */ struct pEp_identity_s *ident);
        
        HRESULT ( STDMETHODCALLTYPE *generate_keypair )( 
            IpEpEngine * This,
            /* [in] */ struct pEp_identity_s *ident,
            /* [retval][out] */ BSTR *fpr);
        
        HRESULT ( STDMETHODCALLTYPE *delete_keypair )( 
            IpEpEngine * This,
            /* [in] */ BSTR fpr);
        
        HRESULT ( STDMETHODCALLTYPE *import_key )( 
            IpEpEngine * This,
            /* [in] */ BSTR key_data);
        
        HRESULT ( STDMETHODCALLTYPE *import_key_b )( 
            IpEpEngine * This,
            /* [in] */ SAFEARRAY * key_data);
        
        HRESULT ( STDMETHODCALLTYPE *export_key )( 
            IpEpEngine * This,
            /* [in] */ BSTR fpr,
            /* [retval][out] */ BSTR *key_data);
        
        HRESULT ( STDMETHODCALLTYPE *recv_key )( 
            IpEpEngine * This,
            /* [in] */ BSTR pattern);
        
        HRESULT ( STDMETHODCALLTYPE *find_keys )( 
            IpEpEngine * This,
            /* [in] */ BSTR pattern,
            /* [retval][out] */ SAFEARRAY * *key_list);
        
        HRESULT ( STDMETHODCALLTYPE *send_key )( 
            IpEpEngine * This,
            /* [in] */ BSTR pattern);
        
        HRESULT ( STDMETHODCALLTYPE *start_keyserver_lookup )( 
            IpEpEngine * This);
        
        HRESULT ( STDMETHODCALLTYPE *stop_keyserver_lookup )( 
            IpEpEngine * This);
        
        HRESULT ( STDMETHODCALLTYPE *examine_identity )( 
            IpEpEngine * This,
            /* [in] */ struct pEp_identity_s *ident);
        
        HRESULT ( STDMETHODCALLTYPE *examine_myself )( 
            IpEpEngine * This,
            /* [in] */ struct pEp_identity_s *myself);
        
        HRESULT ( STDMETHODCALLTYPE *myself )( 
            IpEpEngine * This,
            /* [in] */ struct pEp_identity_s *ident,
            /* [retval][out] */ struct pEp_identity_s *result);
        
        HRESULT ( STDMETHODCALLTYPE *update_identity )( 
            IpEpEngine * This,
            /* [in] */ struct pEp_identity_s *ident,
            /* [retval][out] */ struct pEp_identity_s *result);
        
        HRESULT ( STDMETHODCALLTYPE *key_compromized )( 
            IpEpEngine * This,
            /* [in] */ BSTR fpr);
        
        HRESULT ( STDMETHODCALLTYPE *encrypt_message )( 
            IpEpEngine * This,
            /* [in] */ ITextMessage *src,
            /* [out] */ ITextMessage **dst,
            /* [in] */ SAFEARRAY * extra);
        
        HRESULT ( STDMETHODCALLTYPE *decrypt_message )( 
            IpEpEngine * This,
            /* [in] */ ITextMessage *src,
            /* [out] */ ITextMessage **dst,
            /* [out] */ SAFEARRAY * *keylist,
            /* [retval][out] */ pEp_color *rating);
        
        HRESULT ( STDMETHODCALLTYPE *outgoing_message_color )( 
            IpEpEngine * This,
            /* [in] */ ITextMessage *msg,
            /* [retval][out] */ pEp_color *pVal);
        
        HRESULT ( STDMETHODCALLTYPE *identity_color )( 
            IpEpEngine * This,
            /* [in] */ struct pEp_identity_s *ident,
            /* [retval][out] */ pEp_color *pVal);
        
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


#define IpEpEngine_log(This,title,entity,description,comment)	\
    ( (This)->lpVtbl -> log(This,title,entity,description,comment) ) 

#define IpEpEngine_decrypt(This,ctext,ptext,key_list,decrypt_status)	\
    ( (This)->lpVtbl -> decrypt(This,ctext,ptext,key_list,decrypt_status) ) 

#define IpEpEngine_decrypt_b(This,ctext,ptext,key_list,decrypt_status)	\
    ( (This)->lpVtbl -> decrypt_b(This,ctext,ptext,key_list,decrypt_status) ) 

#define IpEpEngine_encrypt(This,key_list,ptext,ctext,status)	\
    ( (This)->lpVtbl -> encrypt(This,key_list,ptext,ctext,status) ) 

#define IpEpEngine_encrypt_b(This,key_list,ptext,ctext,status)	\
    ( (This)->lpVtbl -> encrypt_b(This,key_list,ptext,ctext,status) ) 

#define IpEpEngine_verify(This,text,signature,key_list,verify_status)	\
    ( (This)->lpVtbl -> verify(This,text,signature,key_list,verify_status) ) 

#define IpEpEngine_trustword(This,value,lang,word)	\
    ( (This)->lpVtbl -> trustword(This,value,lang,word) ) 

#define IpEpEngine_trustwords(This,fpr,lang,max_words,words)	\
    ( (This)->lpVtbl -> trustwords(This,fpr,lang,max_words,words) ) 

#define IpEpEngine_get_identity(This,address,ident)	\
    ( (This)->lpVtbl -> get_identity(This,address,ident) ) 

#define IpEpEngine_set_identity(This,ident)	\
    ( (This)->lpVtbl -> set_identity(This,ident) ) 

#define IpEpEngine_generate_keypair(This,ident,fpr)	\
    ( (This)->lpVtbl -> generate_keypair(This,ident,fpr) ) 

#define IpEpEngine_delete_keypair(This,fpr)	\
    ( (This)->lpVtbl -> delete_keypair(This,fpr) ) 

#define IpEpEngine_import_key(This,key_data)	\
    ( (This)->lpVtbl -> import_key(This,key_data) ) 

#define IpEpEngine_import_key_b(This,key_data)	\
    ( (This)->lpVtbl -> import_key_b(This,key_data) ) 

#define IpEpEngine_export_key(This,fpr,key_data)	\
    ( (This)->lpVtbl -> export_key(This,fpr,key_data) ) 

#define IpEpEngine_recv_key(This,pattern)	\
    ( (This)->lpVtbl -> recv_key(This,pattern) ) 

#define IpEpEngine_find_keys(This,pattern,key_list)	\
    ( (This)->lpVtbl -> find_keys(This,pattern,key_list) ) 

#define IpEpEngine_send_key(This,pattern)	\
    ( (This)->lpVtbl -> send_key(This,pattern) ) 

#define IpEpEngine_start_keyserver_lookup(This)	\
    ( (This)->lpVtbl -> start_keyserver_lookup(This) ) 

#define IpEpEngine_stop_keyserver_lookup(This)	\
    ( (This)->lpVtbl -> stop_keyserver_lookup(This) ) 

#define IpEpEngine_examine_identity(This,ident)	\
    ( (This)->lpVtbl -> examine_identity(This,ident) ) 

#define IpEpEngine_examine_myself(This,myself)	\
    ( (This)->lpVtbl -> examine_myself(This,myself) ) 

#define IpEpEngine_myself(This,ident,result)	\
    ( (This)->lpVtbl -> myself(This,ident,result) ) 

#define IpEpEngine_update_identity(This,ident,result)	\
    ( (This)->lpVtbl -> update_identity(This,ident,result) ) 

#define IpEpEngine_key_compromized(This,fpr)	\
    ( (This)->lpVtbl -> key_compromized(This,fpr) ) 

#define IpEpEngine_encrypt_message(This,src,dst,extra)	\
    ( (This)->lpVtbl -> encrypt_message(This,src,dst,extra) ) 

#define IpEpEngine_decrypt_message(This,src,dst,keylist,rating)	\
    ( (This)->lpVtbl -> decrypt_message(This,src,dst,keylist,rating) ) 

#define IpEpEngine_outgoing_message_color(This,msg,pVal)	\
    ( (This)->lpVtbl -> outgoing_message_color(This,msg,pVal) ) 

#define IpEpEngine_identity_color(This,ident,pVal)	\
    ( (This)->lpVtbl -> identity_color(This,ident,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IpEpEngine_INTERFACE_DEFINED__ */



#ifndef __pEpCOMServerAdapterLib_LIBRARY_DEFINED__
#define __pEpCOMServerAdapterLib_LIBRARY_DEFINED__

/* library pEpCOMServerAdapterLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_pEpCOMServerAdapterLib;

#ifndef ___IpEpEngineEvents_DISPINTERFACE_DEFINED__
#define ___IpEpEngineEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IpEpEngineEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__IpEpEngineEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B6BC9B8E-D9E2-4419-A3A4-7B4B58175549")
    _IpEpEngineEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IpEpEngineEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IpEpEngineEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IpEpEngineEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IpEpEngineEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IpEpEngineEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IpEpEngineEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IpEpEngineEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IpEpEngineEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _IpEpEngineEventsVtbl;

    interface _IpEpEngineEvents
    {
        CONST_VTBL struct _IpEpEngineEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IpEpEngineEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IpEpEngineEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IpEpEngineEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IpEpEngineEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IpEpEngineEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IpEpEngineEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IpEpEngineEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IpEpEngineEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_pEpEngine;

#ifdef __cplusplus

class DECLSPEC_UUID("EF1B073D-5058-4E0E-829E-B4D22CA21EA2")
pEpEngine;
#endif

#ifndef ___ITextMessageEvents_DISPINTERFACE_DEFINED__
#define ___ITextMessageEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ITextMessageEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__ITextMessageEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("844B5363-4EF4-4A39-A030-16452783A6F7")
    _ITextMessageEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ITextMessageEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ITextMessageEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ITextMessageEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ITextMessageEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ITextMessageEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ITextMessageEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ITextMessageEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ITextMessageEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _ITextMessageEventsVtbl;

    interface _ITextMessageEvents
    {
        CONST_VTBL struct _ITextMessageEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ITextMessageEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _ITextMessageEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _ITextMessageEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _ITextMessageEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _ITextMessageEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _ITextMessageEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _ITextMessageEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ITextMessageEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_TextMessage;

#ifdef __cplusplus

class DECLSPEC_UUID("B6CC444F-FE14-4DFE-8315-81E4EA16C1CC")
TextMessage;
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

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


