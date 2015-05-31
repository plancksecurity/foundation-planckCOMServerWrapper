

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sun May 31 16:53:30 2015
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


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


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

/* [uuid] */ struct  DECLSPEC_UUID("3A8A4F13-3402-4C4C-94AB-598D87869380") opt_field
    {
    BSTR name;
    BSTR value;
    } ;
/* [uuid] */ struct  DECLSPEC_UUID("61DA7AD4-192E-4616-8678-B19AEFB45B45") blob
    {
    SAFEARRAY * value;
    BSTR mime_type;
    BSTR filename;
    } ;
/* [uuid] */ struct  DECLSPEC_UUID("D763A8F3-BA23-4229-A037-1BB7BDC3E0C8") text_message
    {
    pEp_msg_direction dir;
    BSTR id;
    BSTR shortmsg;
    BSTR longmsg;
    BSTR longmsg_formatted;
    SAFEARRAY * attachments;
    hyper sent;
    hyper recv;
    struct pEp_identity_s from;
    SAFEARRAY * to;
    struct pEp_identity_s recv_by;
    SAFEARRAY * cc;
    SAFEARRAY * bcc;
    SAFEARRAY * reply_to;
    SAFEARRAY * references;
    SAFEARRAY * keywords;
    BSTR comments;
    SAFEARRAY * opt_fields;
    } ;

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
        
        virtual HRESULT STDMETHODCALLTYPE myself( 
            /* [in] */ struct pEp_identity_s *ident,
            /* [retval][out] */ struct pEp_identity_s *result) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE update_identity( 
            /* [in] */ struct pEp_identity_s *ident,
            /* [retval][out] */ struct pEp_identity_s *result) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE key_compromized( 
            /* [in] */ BSTR fpr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE encrypt_message( 
            /* [in] */ struct text_message *src,
            /* [out] */ struct text_message *dst,
            /* [in] */ SAFEARRAY * extra) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE decrypt_message( 
            /* [in] */ struct text_message *src,
            /* [out] */ struct text_message *dst,
            /* [out] */ SAFEARRAY * *keylist,
            /* [retval][out] */ pEp_color *rating) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE outgoing_message_color( 
            /* [in] */ struct text_message *msg,
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
            /* [in] */ struct text_message *src,
            /* [out] */ struct text_message *dst,
            /* [in] */ SAFEARRAY * extra);
        
        HRESULT ( STDMETHODCALLTYPE *decrypt_message )( 
            IpEpEngine * This,
            /* [in] */ struct text_message *src,
            /* [out] */ struct text_message *dst,
            /* [out] */ SAFEARRAY * *keylist,
            /* [retval][out] */ pEp_color *rating);
        
        HRESULT ( STDMETHODCALLTYPE *outgoing_message_color )( 
            IpEpEngine * This,
            /* [in] */ struct text_message *msg,
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


