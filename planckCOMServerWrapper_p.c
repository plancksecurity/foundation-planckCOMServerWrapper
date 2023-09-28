

/* this ALWAYS GENERATED file contains the proxy stub code */


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

#if !defined(_M_IA64) && !defined(_M_AMD64) && !defined(_ARM_)


#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "planckCOMServerWrapper_i.h"

#define TYPE_FORMAT_STRING_SIZE   1263                              
#define PROC_FORMAT_STRING_SIZE   3211                              
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   2            

typedef struct _planckCOMServerWrapper_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } planckCOMServerWrapper_MIDL_TYPE_FORMAT_STRING;

typedef struct _planckCOMServerWrapper_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } planckCOMServerWrapper_MIDL_PROC_FORMAT_STRING;

typedef struct _planckCOMServerWrapper_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } planckCOMServerWrapper_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const planckCOMServerWrapper_MIDL_TYPE_FORMAT_STRING planckCOMServerWrapper__MIDL_TypeFormatString;
extern const planckCOMServerWrapper_MIDL_PROC_FORMAT_STRING planckCOMServerWrapper__MIDL_ProcFormatString;
extern const planckCOMServerWrapper_MIDL_EXPR_FORMAT_STRING planckCOMServerWrapper__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IpEpEngineCallbacks_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IpEpEngineCallbacks_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IpEpEngine_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IpEpEngine_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif
#if !(TARGET_IS_NT60_OR_LATER)
#error You need Windows Vista or later to run this stub because it uses these features:
#error   forced complex structure or array, compiled for Windows Vista.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const planckCOMServerWrapper_MIDL_PROC_FORMAT_STRING planckCOMServerWrapper__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure MessageToSend */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 16 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x1 ),	/* 1 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter msg */

/* 24 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 26 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 28 */	NdrFcShort( 0x448 ),	/* Type Offset=1096 */

	/* Return value */

/* 30 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 32 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 34 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure NotifyHandshake */

/* 36 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 38 */	NdrFcLong( 0x0 ),	/* 0 */
/* 42 */	NdrFcShort( 0x4 ),	/* 4 */
/* 44 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 46 */	NdrFcShort( 0x8 ),	/* 8 */
/* 48 */	NdrFcShort( 0x8 ),	/* 8 */
/* 50 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 52 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 54 */	NdrFcShort( 0x0 ),	/* 0 */
/* 56 */	NdrFcShort( 0x1 ),	/* 1 */
/* 58 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter self */

/* 60 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 62 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 64 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter partner */

/* 66 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 68 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 70 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter signal */

/* 72 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 74 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 76 */	0xe,		/* FC_ENUM32 */
			0x0,		/* 0 */

	/* Return value */

/* 78 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 80 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 82 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VerboseLogging */

/* 84 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 86 */	NdrFcLong( 0x0 ),	/* 0 */
/* 90 */	NdrFcShort( 0x3 ),	/* 3 */
/* 92 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 94 */	NdrFcShort( 0x6 ),	/* 6 */
/* 96 */	NdrFcShort( 0x8 ),	/* 8 */
/* 98 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 100 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 102 */	NdrFcShort( 0x0 ),	/* 0 */
/* 104 */	NdrFcShort( 0x0 ),	/* 0 */
/* 106 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enable */

/* 108 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 110 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 112 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 114 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 116 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 118 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure PassiveMode */

/* 120 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 122 */	NdrFcLong( 0x0 ),	/* 0 */
/* 126 */	NdrFcShort( 0x4 ),	/* 4 */
/* 128 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 130 */	NdrFcShort( 0x6 ),	/* 6 */
/* 132 */	NdrFcShort( 0x8 ),	/* 8 */
/* 134 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 136 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 138 */	NdrFcShort( 0x0 ),	/* 0 */
/* 140 */	NdrFcShort( 0x0 ),	/* 0 */
/* 142 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enable */

/* 144 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 146 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 148 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 150 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 152 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 154 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure UnencryptedSubject */

/* 156 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 158 */	NdrFcLong( 0x0 ),	/* 0 */
/* 162 */	NdrFcShort( 0x5 ),	/* 5 */
/* 164 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 166 */	NdrFcShort( 0x6 ),	/* 6 */
/* 168 */	NdrFcShort( 0x8 ),	/* 8 */
/* 170 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 172 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 174 */	NdrFcShort( 0x0 ),	/* 0 */
/* 176 */	NdrFcShort( 0x0 ),	/* 0 */
/* 178 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enable */

/* 180 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 182 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 184 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 186 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 188 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 190 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ExportKey */

/* 192 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 194 */	NdrFcLong( 0x0 ),	/* 0 */
/* 198 */	NdrFcShort( 0x6 ),	/* 6 */
/* 200 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 202 */	NdrFcShort( 0x0 ),	/* 0 */
/* 204 */	NdrFcShort( 0x8 ),	/* 8 */
/* 206 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 208 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 210 */	NdrFcShort( 0x1 ),	/* 1 */
/* 212 */	NdrFcShort( 0x1 ),	/* 1 */
/* 214 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter fpr */

/* 216 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 218 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 220 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter keyData */

/* 222 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 224 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 226 */	NdrFcShort( 0x4a4 ),	/* Type Offset=1188 */

	/* Return value */

/* 228 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 230 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 232 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Log */

/* 234 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 236 */	NdrFcLong( 0x0 ),	/* 0 */
/* 240 */	NdrFcShort( 0x7 ),	/* 7 */
/* 242 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 244 */	NdrFcShort( 0x0 ),	/* 0 */
/* 246 */	NdrFcShort( 0x8 ),	/* 8 */
/* 248 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 250 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 252 */	NdrFcShort( 0x0 ),	/* 0 */
/* 254 */	NdrFcShort( 0x1 ),	/* 1 */
/* 256 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter title */

/* 258 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 260 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 262 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter entity */

/* 264 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 266 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 268 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter description */

/* 270 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 272 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 274 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter comment */

/* 276 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 278 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 280 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 282 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 284 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 286 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Trustwords */

/* 288 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 290 */	NdrFcLong( 0x0 ),	/* 0 */
/* 294 */	NdrFcShort( 0x8 ),	/* 8 */
/* 296 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 298 */	NdrFcShort( 0x8 ),	/* 8 */
/* 300 */	NdrFcShort( 0x8 ),	/* 8 */
/* 302 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 304 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 306 */	NdrFcShort( 0x1 ),	/* 1 */
/* 308 */	NdrFcShort( 0x1 ),	/* 1 */
/* 310 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter fpr */

/* 312 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 314 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 316 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter lang */

/* 318 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 320 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 322 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter maxWords */

/* 324 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 326 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 328 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter words */

/* 330 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 332 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 334 */	NdrFcShort( 0x4a4 ),	/* Type Offset=1188 */

	/* Return value */

/* 336 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 338 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 340 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetTrustwords */

/* 342 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 344 */	NdrFcLong( 0x0 ),	/* 0 */
/* 348 */	NdrFcShort( 0x9 ),	/* 9 */
/* 350 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 352 */	NdrFcShort( 0x6 ),	/* 6 */
/* 354 */	NdrFcShort( 0x8 ),	/* 8 */
/* 356 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 358 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 360 */	NdrFcShort( 0x1 ),	/* 1 */
/* 362 */	NdrFcShort( 0x1 ),	/* 1 */
/* 364 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter id1 */

/* 366 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 368 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 370 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter id2 */

/* 372 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 374 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 376 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter lang */

/* 378 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 380 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 382 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter full */

/* 384 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 386 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 388 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter words */

/* 390 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 392 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 394 */	NdrFcShort( 0x4a4 ),	/* Type Offset=1188 */

	/* Return value */

/* 396 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 398 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 400 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetCrashdumpLog */

/* 402 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 404 */	NdrFcLong( 0x0 ),	/* 0 */
/* 408 */	NdrFcShort( 0xa ),	/* 10 */
/* 410 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 412 */	NdrFcShort( 0x8 ),	/* 8 */
/* 414 */	NdrFcShort( 0x8 ),	/* 8 */
/* 416 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 418 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 420 */	NdrFcShort( 0x1 ),	/* 1 */
/* 422 */	NdrFcShort( 0x0 ),	/* 0 */
/* 424 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter maxlines */

/* 426 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 428 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 430 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter log */

/* 432 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 434 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 436 */	NdrFcShort( 0x4a4 ),	/* Type Offset=1188 */

	/* Return value */

/* 438 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 440 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 442 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetEngineVersion */

/* 444 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 446 */	NdrFcLong( 0x0 ),	/* 0 */
/* 450 */	NdrFcShort( 0xb ),	/* 11 */
/* 452 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 454 */	NdrFcShort( 0x0 ),	/* 0 */
/* 456 */	NdrFcShort( 0x8 ),	/* 8 */
/* 458 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 460 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 462 */	NdrFcShort( 0x1 ),	/* 1 */
/* 464 */	NdrFcShort( 0x0 ),	/* 0 */
/* 466 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter engineVersion */

/* 468 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 470 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 472 */	NdrFcShort( 0x4a4 ),	/* Type Offset=1188 */

	/* Return value */

/* 474 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 476 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 478 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetLanguageList */

/* 480 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 482 */	NdrFcLong( 0x0 ),	/* 0 */
/* 486 */	NdrFcShort( 0xc ),	/* 12 */
/* 488 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 490 */	NdrFcShort( 0x0 ),	/* 0 */
/* 492 */	NdrFcShort( 0x8 ),	/* 8 */
/* 494 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 496 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 498 */	NdrFcShort( 0x1 ),	/* 1 */
/* 500 */	NdrFcShort( 0x0 ),	/* 0 */
/* 502 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter languages */

/* 504 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 506 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 508 */	NdrFcShort( 0x4a4 ),	/* Type Offset=1188 */

	/* Return value */

/* 510 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 512 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 514 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetIdentityFlags */

/* 516 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 518 */	NdrFcLong( 0x0 ),	/* 0 */
/* 522 */	NdrFcShort( 0xd ),	/* 13 */
/* 524 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 526 */	NdrFcShort( 0x8 ),	/* 8 */
/* 528 */	NdrFcShort( 0x8 ),	/* 8 */
/* 530 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 532 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 534 */	NdrFcShort( 0x0 ),	/* 0 */
/* 536 */	NdrFcShort( 0x1 ),	/* 1 */
/* 538 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter identity */

/* 540 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 542 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 544 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter flags */

/* 546 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 548 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 550 */	0xe,		/* FC_ENUM32 */
			0x0,		/* 0 */

	/* Return value */

/* 552 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 554 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 556 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure UnsetIdentityFlags */

/* 558 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 560 */	NdrFcLong( 0x0 ),	/* 0 */
/* 564 */	NdrFcShort( 0xe ),	/* 14 */
/* 566 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 568 */	NdrFcShort( 0x8 ),	/* 8 */
/* 570 */	NdrFcShort( 0x8 ),	/* 8 */
/* 572 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 574 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 576 */	NdrFcShort( 0x0 ),	/* 0 */
/* 578 */	NdrFcShort( 0x1 ),	/* 1 */
/* 580 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter identity */

/* 582 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 584 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 586 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter flags */

/* 588 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 590 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 592 */	0xe,		/* FC_ENUM32 */
			0x0,		/* 0 */

	/* Return value */

/* 594 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 596 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 598 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Myself */

/* 600 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 602 */	NdrFcLong( 0x0 ),	/* 0 */
/* 606 */	NdrFcShort( 0xf ),	/* 15 */
/* 608 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 610 */	NdrFcShort( 0x0 ),	/* 0 */
/* 612 */	NdrFcShort( 0x8 ),	/* 8 */
/* 614 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 616 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 618 */	NdrFcShort( 0x1 ),	/* 1 */
/* 620 */	NdrFcShort( 0x1 ),	/* 1 */
/* 622 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ident */

/* 624 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 626 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 628 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter result */

/* 630 */	NdrFcShort( 0xa113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=40 */
/* 632 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 634 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 636 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 638 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 640 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure UpdateIdentity */

/* 642 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 644 */	NdrFcLong( 0x0 ),	/* 0 */
/* 648 */	NdrFcShort( 0x10 ),	/* 16 */
/* 650 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 652 */	NdrFcShort( 0x0 ),	/* 0 */
/* 654 */	NdrFcShort( 0x8 ),	/* 8 */
/* 656 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 658 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 660 */	NdrFcShort( 0x1 ),	/* 1 */
/* 662 */	NdrFcShort( 0x1 ),	/* 1 */
/* 664 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ident */

/* 666 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 668 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 670 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter result */

/* 672 */	NdrFcShort( 0xa113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=40 */
/* 674 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 676 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 678 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 680 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 682 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure KeyMistrusted */

/* 684 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 686 */	NdrFcLong( 0x0 ),	/* 0 */
/* 690 */	NdrFcShort( 0x11 ),	/* 17 */
/* 692 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 694 */	NdrFcShort( 0x0 ),	/* 0 */
/* 696 */	NdrFcShort( 0x8 ),	/* 8 */
/* 698 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 700 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 702 */	NdrFcShort( 0x0 ),	/* 0 */
/* 704 */	NdrFcShort( 0x1 ),	/* 1 */
/* 706 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ident */

/* 708 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 710 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 712 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 714 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 716 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 718 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure KeyResetTrust */

/* 720 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 722 */	NdrFcLong( 0x0 ),	/* 0 */
/* 726 */	NdrFcShort( 0x12 ),	/* 18 */
/* 728 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 730 */	NdrFcShort( 0x0 ),	/* 0 */
/* 732 */	NdrFcShort( 0x8 ),	/* 8 */
/* 734 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 736 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 738 */	NdrFcShort( 0x0 ),	/* 0 */
/* 740 */	NdrFcShort( 0x1 ),	/* 1 */
/* 742 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ident */

/* 744 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 746 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 748 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 750 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 752 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 754 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure TrustPersonalKey */

/* 756 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 758 */	NdrFcLong( 0x0 ),	/* 0 */
/* 762 */	NdrFcShort( 0x13 ),	/* 19 */
/* 764 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 766 */	NdrFcShort( 0x0 ),	/* 0 */
/* 768 */	NdrFcShort( 0x8 ),	/* 8 */
/* 770 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 772 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 774 */	NdrFcShort( 0x1 ),	/* 1 */
/* 776 */	NdrFcShort( 0x1 ),	/* 1 */
/* 778 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ident */

/* 780 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 782 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 784 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter result */

/* 786 */	NdrFcShort( 0xa113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=40 */
/* 788 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 790 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 792 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 794 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 796 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure OwnIdentitiesRetrieve */

/* 798 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 800 */	NdrFcLong( 0x0 ),	/* 0 */
/* 804 */	NdrFcShort( 0x14 ),	/* 20 */
/* 806 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 808 */	NdrFcShort( 0x0 ),	/* 0 */
/* 810 */	NdrFcShort( 0x8 ),	/* 8 */
/* 812 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 814 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 816 */	NdrFcShort( 0x1 ),	/* 1 */
/* 818 */	NdrFcShort( 0x0 ),	/* 0 */
/* 820 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ownIdentities */

/* 822 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 824 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 826 */	NdrFcShort( 0x4be ),	/* Type Offset=1214 */

	/* Return value */

/* 828 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 830 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 832 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IspEpUser */

/* 834 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 836 */	NdrFcLong( 0x0 ),	/* 0 */
/* 840 */	NdrFcShort( 0x15 ),	/* 21 */
/* 842 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 844 */	NdrFcShort( 0x0 ),	/* 0 */
/* 846 */	NdrFcShort( 0x22 ),	/* 34 */
/* 848 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 850 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 852 */	NdrFcShort( 0x0 ),	/* 0 */
/* 854 */	NdrFcShort( 0x1 ),	/* 1 */
/* 856 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ident */

/* 858 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 860 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 862 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter ispEp */

/* 864 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 866 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 868 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 870 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 872 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 874 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure OpenPGPListKeyinfo */

/* 876 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 878 */	NdrFcLong( 0x0 ),	/* 0 */
/* 882 */	NdrFcShort( 0x16 ),	/* 22 */
/* 884 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 886 */	NdrFcShort( 0x0 ),	/* 0 */
/* 888 */	NdrFcShort( 0x8 ),	/* 8 */
/* 890 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 892 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 894 */	NdrFcShort( 0x1 ),	/* 1 */
/* 896 */	NdrFcShort( 0x1 ),	/* 1 */
/* 898 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter searchPattern */

/* 900 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 902 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 904 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter keyinfoList */

/* 906 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 908 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 910 */	NdrFcShort( 0x4be ),	/* Type Offset=1214 */

	/* Return value */

/* 912 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 914 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 916 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EncryptMessage */

/* 918 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 920 */	NdrFcLong( 0x0 ),	/* 0 */
/* 924 */	NdrFcShort( 0x17 ),	/* 23 */
/* 926 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 928 */	NdrFcShort( 0x10 ),	/* 16 */
/* 930 */	NdrFcShort( 0x8 ),	/* 8 */
/* 932 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 934 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 936 */	NdrFcShort( 0x1 ),	/* 1 */
/* 938 */	NdrFcShort( 0x1 ),	/* 1 */
/* 940 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter src */

/* 942 */	NdrFcShort( 0x11b ),	/* Flags:  must size, must free, in, out, simple ref, */
/* 944 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 946 */	NdrFcShort( 0x448 ),	/* Type Offset=1096 */

	/* Parameter dst */

/* 948 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 950 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 952 */	NdrFcShort( 0x448 ),	/* Type Offset=1096 */

	/* Parameter extra */

/* 954 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 956 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 958 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Parameter flags */

/* 960 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 962 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 964 */	0xe,		/* FC_ENUM32 */
			0x0,		/* 0 */

	/* Parameter encFormat */

/* 966 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 968 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 970 */	0xe,		/* FC_ENUM32 */
			0x0,		/* 0 */

	/* Return value */

/* 972 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 974 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 976 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure DecryptMessage */

/* 978 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 980 */	NdrFcLong( 0x0 ),	/* 0 */
/* 984 */	NdrFcShort( 0x18 ),	/* 24 */
/* 986 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 988 */	NdrFcShort( 0x1c ),	/* 28 */
/* 990 */	NdrFcShort( 0x40 ),	/* 64 */
/* 992 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 994 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 996 */	NdrFcShort( 0x1 ),	/* 1 */
/* 998 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1000 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter src */

/* 1002 */	NdrFcShort( 0x11b ),	/* Flags:  must size, must free, in, out, simple ref, */
/* 1004 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1006 */	NdrFcShort( 0x448 ),	/* Type Offset=1096 */

	/* Parameter dst */

/* 1008 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 1010 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1012 */	NdrFcShort( 0x448 ),	/* Type Offset=1096 */

	/* Parameter keylist */

/* 1014 */	NdrFcShort( 0x11b ),	/* Flags:  must size, must free, in, out, simple ref, */
/* 1016 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1018 */	NdrFcShort( 0x4be ),	/* Type Offset=1214 */

	/* Parameter flags */

/* 1020 */	NdrFcShort( 0x158 ),	/* Flags:  in, out, base type, simple ref, */
/* 1022 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1024 */	0xe,		/* FC_ENUM32 */
			0x0,		/* 0 */

	/* Parameter rating */

/* 1026 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1028 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1030 */	0xe,		/* FC_ENUM32 */
			0x0,		/* 0 */

	/* Return value */

/* 1032 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1034 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1036 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure OutgoingMessageRating */

/* 1038 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1040 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1044 */	NdrFcShort( 0x19 ),	/* 25 */
/* 1046 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1048 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1050 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1052 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1054 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1056 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1058 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1060 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter msg */

/* 1062 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1064 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1066 */	NdrFcShort( 0x448 ),	/* Type Offset=1096 */

	/* Parameter pVal */

/* 1068 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1070 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1072 */	0xe,		/* FC_ENUM32 */
			0x0,		/* 0 */

	/* Return value */

/* 1074 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1076 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1078 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IdentityRating */

/* 1080 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1082 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1086 */	NdrFcShort( 0x1a ),	/* 26 */
/* 1088 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1090 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1092 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1094 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1096 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1098 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1100 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1102 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ident */

/* 1104 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1106 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1108 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter pVal */

/* 1110 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1112 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1114 */	0xe,		/* FC_ENUM32 */
			0x0,		/* 0 */

	/* Return value */

/* 1116 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1118 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1120 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ColorFromRating */

/* 1122 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1124 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1128 */	NdrFcShort( 0x1b ),	/* 27 */
/* 1130 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1132 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1134 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1136 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 1138 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1140 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1142 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1144 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter rating */

/* 1146 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1148 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1150 */	0xe,		/* FC_ENUM32 */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 1152 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1154 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1156 */	0xe,		/* FC_ENUM32 */
			0x0,		/* 0 */

	/* Return value */

/* 1158 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1160 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1162 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetMessageTrustwords */

/* 1164 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1166 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1170 */	NdrFcShort( 0x1c ),	/* 28 */
/* 1172 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 1174 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1176 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1178 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x7,		/* 7 */
/* 1180 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 1182 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1184 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1186 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter msg */

/* 1188 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1190 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1192 */	NdrFcShort( 0x448 ),	/* Type Offset=1096 */

	/* Parameter receivedBy */

/* 1194 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1196 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1198 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter keylist */

/* 1200 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1202 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1204 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Parameter lang */

/* 1206 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1208 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1210 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter full */

/* 1212 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1214 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1216 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter words */

/* 1218 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1220 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1222 */	NdrFcShort( 0x4a4 ),	/* Type Offset=1188 */

	/* Return value */

/* 1224 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1226 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 1228 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EncryptMessageForSelf */

/* 1230 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1232 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1236 */	NdrFcShort( 0x1d ),	/* 29 */
/* 1238 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 1240 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1242 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1244 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 1246 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 1248 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1250 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1252 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter targetId */

/* 1254 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1256 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1258 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter src */

/* 1260 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1262 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1264 */	NdrFcShort( 0x448 ),	/* Type Offset=1096 */

	/* Parameter extra */

/* 1266 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1268 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1270 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Parameter dst */

/* 1272 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 1274 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1276 */	NdrFcShort( 0x448 ),	/* Type Offset=1096 */

	/* Parameter flags */

/* 1278 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1280 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1282 */	0xe,		/* FC_ENUM32 */
			0x0,		/* 0 */

	/* Return value */

/* 1284 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1286 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1288 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ReEvaluateMessageRating */

/* 1290 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1292 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1296 */	NdrFcShort( 0x1e ),	/* 30 */
/* 1298 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1300 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1302 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1304 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 1306 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 1308 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1310 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1312 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter src */

/* 1314 */	NdrFcShort( 0x11b ),	/* Flags:  must size, must free, in, out, simple ref, */
/* 1316 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1318 */	NdrFcShort( 0x448 ),	/* Type Offset=1096 */

	/* Parameter x_KeyList */

/* 1320 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1322 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1324 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Parameter x_EncStatus */

/* 1326 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1328 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1330 */	0xe,		/* FC_ENUM32 */
			0x0,		/* 0 */

	/* Parameter rating */

/* 1332 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1334 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1336 */	0xe,		/* FC_ENUM32 */
			0x0,		/* 0 */

	/* Return value */

/* 1338 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1340 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1342 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure RegisterCallbacks */

/* 1344 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1346 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1350 */	NdrFcShort( 0x1f ),	/* 31 */
/* 1352 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1354 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1356 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1358 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1360 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1362 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1364 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1366 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newCallback */

/* 1368 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1370 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1372 */	NdrFcShort( 0x4d8 ),	/* Type Offset=1240 */

	/* Return value */

/* 1374 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1376 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1378 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure UnregisterCallbacks */

/* 1380 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1382 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1386 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1388 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1390 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1392 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1394 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 1396 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1398 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1400 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1402 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 1404 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1406 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1408 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetOwnKey */

/* 1410 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1412 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1416 */	NdrFcShort( 0x21 ),	/* 33 */
/* 1418 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1420 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1422 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1424 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 1426 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 1428 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1430 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1432 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ident */

/* 1434 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1436 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1438 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter fpr */

/* 1440 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1442 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1444 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter result */

/* 1446 */	NdrFcShort( 0xa113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=40 */
/* 1448 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1450 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 1452 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1454 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1456 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EncryptMessageAndAddPrivKey */

/* 1458 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1460 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1464 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1466 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 1468 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1470 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1472 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 1474 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 1476 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1478 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1480 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter src */

/* 1482 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1484 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1486 */	NdrFcShort( 0x448 ),	/* Type Offset=1096 */

	/* Parameter dst */

/* 1488 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 1490 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1492 */	NdrFcShort( 0x448 ),	/* Type Offset=1096 */

	/* Parameter to_fpr */

/* 1494 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1496 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1498 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter flags */

/* 1500 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1502 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1504 */	0xe,		/* FC_ENUM32 */
			0x0,		/* 0 */

	/* Parameter encFormat */

/* 1506 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1508 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1510 */	0xe,		/* FC_ENUM32 */
			0x0,		/* 0 */

	/* Return value */

/* 1512 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1514 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1516 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure UpdateNow */

/* 1518 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1520 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1524 */	NdrFcShort( 0x23 ),	/* 35 */
/* 1526 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1528 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1530 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1532 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1534 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1536 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1538 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1540 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter productCode */

/* 1542 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1544 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1546 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter didUpdate */

/* 1548 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1550 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1552 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1554 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1556 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1558 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure OutgoingMessageRatingPreview */

/* 1560 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1562 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1566 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1568 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1570 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1572 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1574 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1576 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1578 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1580 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1582 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter msg */

/* 1584 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1586 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1588 */	NdrFcShort( 0x448 ),	/* Type Offset=1096 */

	/* Parameter rating */

/* 1590 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1592 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1594 */	0xe,		/* FC_ENUM32 */
			0x0,		/* 0 */

	/* Return value */

/* 1596 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1598 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1600 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure TrustOwnKey */

/* 1602 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1604 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1608 */	NdrFcShort( 0x25 ),	/* 37 */
/* 1610 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1612 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1614 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1616 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1618 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1620 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1622 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1624 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ident */

/* 1626 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1628 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1630 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 1632 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1634 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1636 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Startup */

/* 1638 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1640 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1644 */	NdrFcShort( 0x26 ),	/* 38 */
/* 1646 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1648 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1650 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1652 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 1654 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1656 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1658 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1660 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 1662 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1664 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1666 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetKeyRatingForUser */

/* 1668 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1670 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1674 */	NdrFcShort( 0x27 ),	/* 39 */
/* 1676 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1678 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1680 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1682 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 1684 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1686 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1688 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1690 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter userId */

/* 1692 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1694 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1696 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter fpr */

/* 1698 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1700 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1702 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter rating */

/* 1704 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1706 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1708 */	0xe,		/* FC_ENUM32 */
			0x0,		/* 0 */

	/* Return value */

/* 1710 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1712 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1714 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure KeyResetIdentity */

/* 1716 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1718 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1722 */	NdrFcShort( 0x28 ),	/* 40 */
/* 1724 */	NdrFcShort( 0x30 ),	/* x86 Stack size/offset = 48 */
/* 1726 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1728 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1730 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1732 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1734 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1736 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1738 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ident */

/* 1740 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1742 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1744 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter fpr */

/* 1746 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1748 */	NdrFcShort( 0x28 ),	/* x86 Stack size/offset = 40 */
/* 1750 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1752 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1754 */	NdrFcShort( 0x2c ),	/* x86 Stack size/offset = 44 */
/* 1756 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure KeyResetUser */

/* 1758 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1760 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1764 */	NdrFcShort( 0x29 ),	/* 41 */
/* 1766 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1768 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1770 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1772 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1774 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1776 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1778 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1780 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter userId */

/* 1782 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1784 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1786 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter fpr */

/* 1788 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1790 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1792 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1794 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1796 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1798 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure KeyResetAllOwnKeys */

/* 1800 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1802 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1806 */	NdrFcShort( 0x2a ),	/* 42 */
/* 1808 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1810 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1812 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1814 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 1816 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1818 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1820 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1822 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 1824 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1826 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1828 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure DeliverHandshakeResult */

/* 1830 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1832 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1836 */	NdrFcShort( 0x2b ),	/* 43 */
/* 1838 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1840 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1842 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1844 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1846 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1848 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1850 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1852 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter result */

/* 1854 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1856 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1858 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter identities_sharing */

/* 1860 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1862 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1864 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Return value */

/* 1866 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1868 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1870 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ImportKey */

/* 1872 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1874 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1878 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1880 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1882 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1884 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1886 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1888 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 1890 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1892 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1894 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter keyData */

/* 1896 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1898 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1900 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter privateKeys */

/* 1902 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1904 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1906 */	NdrFcShort( 0x4be ),	/* Type Offset=1214 */

	/* Return value */

/* 1908 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1910 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1912 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ConfigCipherSuite */

/* 1914 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1916 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1920 */	NdrFcShort( 0x2d ),	/* 45 */
/* 1922 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1924 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1926 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1928 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1930 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1932 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1934 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1936 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter cipherSuite */

/* 1938 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1940 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1942 */	0xe,		/* FC_ENUM32 */
			0x0,		/* 0 */

	/* Return value */

/* 1944 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1946 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1948 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure LeaveDeviceGroup */

/* 1950 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1952 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1956 */	NdrFcShort( 0x2e ),	/* 46 */
/* 1958 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1960 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1962 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1964 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 1966 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1968 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1970 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1972 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 1974 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1976 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1978 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetTrustwordsForFprs */

/* 1980 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1982 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1986 */	NdrFcShort( 0x2f ),	/* 47 */
/* 1988 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 1990 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1992 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1994 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 1996 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 1998 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2000 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2002 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter fpr1 */

/* 2004 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2006 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2008 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter fpr2 */

/* 2010 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2012 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2014 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter lang */

/* 2016 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2018 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2020 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter full */

/* 2022 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2024 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2026 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter words */

/* 2028 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2030 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2032 */	NdrFcShort( 0x4a4 ),	/* Type Offset=1188 */

	/* Return value */

/* 2034 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2036 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2038 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetKeyRating */

/* 2040 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2042 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2046 */	NdrFcShort( 0x30 ),	/* 48 */
/* 2048 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2050 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2052 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2054 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2056 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2058 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2060 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2062 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter fpr */

/* 2064 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2066 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2068 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter commType */

/* 2070 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2072 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2074 */	0xe,		/* FC_ENUM32 */
			0x0,		/* 0 */

	/* Return value */

/* 2076 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2078 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2080 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure PERToXERSyncMessage */

/* 2082 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2084 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2088 */	NdrFcShort( 0x31 ),	/* 49 */
/* 2090 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2092 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2094 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2096 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2098 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2100 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2102 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2104 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter msg */

/* 2106 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2108 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2110 */	NdrFcShort( 0x448 ),	/* Type Offset=1096 */

	/* Parameter xer */

/* 2112 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2114 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2116 */	NdrFcShort( 0x4a4 ),	/* Type Offset=1188 */

	/* Return value */

/* 2118 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2120 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2122 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure DisableIdentityForSync */

/* 2124 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2126 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2130 */	NdrFcShort( 0x32 ),	/* 50 */
/* 2132 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2134 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2136 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2138 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2140 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2142 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2144 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2146 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ident */

/* 2148 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2150 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2152 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 2154 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2156 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2158 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EnableIdentityForSync */

/* 2160 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2162 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2166 */	NdrFcShort( 0x33 ),	/* 51 */
/* 2168 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2170 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2172 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2174 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2176 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2178 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2180 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2182 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ident */

/* 2184 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2186 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2188 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 2190 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2192 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2194 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure PerMachineDirectory */

/* 2196 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2198 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2202 */	NdrFcShort( 0x34 ),	/* 52 */
/* 2204 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2206 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2208 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2210 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2212 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2214 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2216 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2218 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter directory */

/* 2220 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2222 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2224 */	NdrFcShort( 0x4a4 ),	/* Type Offset=1188 */

	/* Return value */

/* 2226 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2228 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2230 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure PerUserDirectory */

/* 2232 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2234 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2238 */	NdrFcShort( 0x35 ),	/* 53 */
/* 2240 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2242 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2244 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2246 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2248 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2250 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2252 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2254 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter directory */

/* 2256 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2258 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2260 */	NdrFcShort( 0x4a4 ),	/* Type Offset=1188 */

	/* Return value */

/* 2262 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2264 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2266 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure RatingFromCommType */

/* 2268 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2270 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2274 */	NdrFcShort( 0x36 ),	/* 54 */
/* 2276 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2278 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2280 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2282 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 2284 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2286 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2288 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2290 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter commType */

/* 2292 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2294 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2296 */	0xe,		/* FC_ENUM32 */
			0x0,		/* 0 */

	/* Parameter rating */

/* 2298 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2300 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2302 */	0xe,		/* FC_ENUM32 */
			0x0,		/* 0 */

	/* Return value */

/* 2304 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2306 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2308 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetIsSyncRunning */

/* 2310 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2312 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2316 */	NdrFcShort( 0x37 ),	/* 55 */
/* 2318 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2320 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2322 */	NdrFcShort( 0x22 ),	/* 34 */
/* 2324 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2326 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2328 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2330 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2332 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter running */

/* 2334 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2336 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2338 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 2340 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2342 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2344 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ShutDownSync */

/* 2346 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2348 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2352 */	NdrFcShort( 0x38 ),	/* 56 */
/* 2354 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2356 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2358 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2360 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 2362 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2364 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2366 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2368 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 2370 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2372 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2374 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure MIMEDecodeMessage */

/* 2376 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2378 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2382 */	NdrFcShort( 0x39 ),	/* 57 */
/* 2384 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2386 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2388 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2390 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2392 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2394 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2396 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2398 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter mimeText */

/* 2400 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2402 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2404 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter msg */

/* 2406 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 2408 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2410 */	NdrFcShort( 0x448 ),	/* Type Offset=1096 */

	/* Return value */

/* 2412 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2414 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2416 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure MIMEEncodeMessage */

/* 2418 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2420 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2424 */	NdrFcShort( 0x3a ),	/* 58 */
/* 2426 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2428 */	NdrFcShort( 0x6 ),	/* 6 */
/* 2430 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2432 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 2434 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2436 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2438 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2440 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter msg */

/* 2442 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2444 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2446 */	NdrFcShort( 0x448 ),	/* Type Offset=1096 */

	/* Parameter omitFields */

/* 2448 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2450 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2452 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter mimeText */

/* 2454 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2456 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2458 */	NdrFcShort( 0x4a4 ),	/* Type Offset=1188 */

	/* Return value */

/* 2460 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2462 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2464 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ConfigPassphrase */

/* 2466 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2468 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2472 */	NdrFcShort( 0x3b ),	/* 59 */
/* 2474 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2476 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2478 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2480 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2482 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2484 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2486 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2488 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter passphrase */

/* 2490 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2492 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2494 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 2496 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2498 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2500 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ConfigPassphraseForNewKeys */

/* 2502 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2504 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2508 */	NdrFcShort( 0x3c ),	/* 60 */
/* 2510 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2512 */	NdrFcShort( 0x6 ),	/* 6 */
/* 2514 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2516 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2518 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2520 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2522 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2524 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enable */

/* 2526 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2528 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2530 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter passphrase */

/* 2532 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2534 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2536 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 2538 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2540 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2542 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ShowNotification */

/* 2544 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2546 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2550 */	NdrFcShort( 0x3d ),	/* 61 */
/* 2552 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2554 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2556 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2558 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2560 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2562 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2564 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2566 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter title */

/* 2568 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2570 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2572 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter message */

/* 2574 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2576 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2578 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 2580 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2582 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2584 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ExportSecretKey */

/* 2586 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2588 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2592 */	NdrFcShort( 0x3e ),	/* 62 */
/* 2594 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2596 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2598 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2600 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2602 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2604 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2606 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2608 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter fpr */

/* 2610 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2612 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2614 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter keyData */

/* 2616 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2618 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2620 */	NdrFcShort( 0x4a4 ),	/* Type Offset=1188 */

	/* Return value */

/* 2622 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2624 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2626 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure DisableAllSyncChannels */

/* 2628 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2630 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2634 */	NdrFcShort( 0x3f ),	/* 63 */
/* 2636 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2638 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2640 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2642 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 2644 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2646 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2648 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2650 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 2652 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2654 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2656 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SyncReinit */

/* 2658 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2660 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2664 */	NdrFcShort( 0x40 ),	/* 64 */
/* 2666 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2668 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2670 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2672 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 2674 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2676 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2678 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2680 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 2682 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2684 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2686 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GroupCreate */

/* 2688 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2690 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2694 */	NdrFcShort( 0x41 ),	/* 65 */
/* 2696 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2698 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2700 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2702 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 2704 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2706 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2708 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2710 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter groupIdentity */

/* 2712 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2714 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2716 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter manager */

/* 2718 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2720 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2722 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter memberlist */

/* 2724 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2726 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2728 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Return value */

/* 2730 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2732 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2734 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GroupJoin */

/* 2736 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2738 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2742 */	NdrFcShort( 0x42 ),	/* 66 */
/* 2744 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2746 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2748 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2750 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 2752 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2754 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2756 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2758 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter groupIdentity */

/* 2760 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2762 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2764 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter asMember */

/* 2766 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2768 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2770 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter manager */

/* 2772 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2774 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2776 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 2778 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2780 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2782 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GroupDissolve */

/* 2784 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2786 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2790 */	NdrFcShort( 0x43 ),	/* 67 */
/* 2792 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2794 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2796 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2798 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2800 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2802 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2804 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2806 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter groupIdentity */

/* 2808 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2810 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2812 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter manager */

/* 2814 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2816 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2818 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 2820 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2822 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2824 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GroupInviteMember */

/* 2826 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2828 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2832 */	NdrFcShort( 0x44 ),	/* 68 */
/* 2834 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2836 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2838 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2840 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2842 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2844 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2846 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2848 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter groupIdentity */

/* 2850 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2852 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2854 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter groupMember */

/* 2856 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2858 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2860 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 2862 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2864 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2866 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GroupRemoveMember */

/* 2868 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2870 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2874 */	NdrFcShort( 0x45 ),	/* 69 */
/* 2876 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2878 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2880 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2882 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2884 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2886 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2888 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2890 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter groupIdentity */

/* 2892 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2894 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2896 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter groupMember */

/* 2898 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2900 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2902 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 2904 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2906 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2908 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GroupRating */

/* 2910 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2912 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2916 */	NdrFcShort( 0x46 ),	/* 70 */
/* 2918 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2920 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2922 */	NdrFcShort( 0x22 ),	/* 34 */
/* 2924 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 2926 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2928 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2930 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2932 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter groupIdentity */

/* 2934 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2936 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2938 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter manager */

/* 2940 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2942 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2944 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter rating */

/* 2946 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 2948 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2950 */	NdrFcShort( 0x4ea ),	/* Type Offset=1258 */

	/* Return value */

/* 2952 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2954 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2956 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GroupQueryGroups */

/* 2958 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2960 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2964 */	NdrFcShort( 0x47 ),	/* 71 */
/* 2966 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2968 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2970 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2972 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2974 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2976 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2978 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2980 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter manager */

/* 2982 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2984 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2986 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter groupList */

/* 2988 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2990 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2992 */	NdrFcShort( 0x4be ),	/* Type Offset=1214 */

	/* Return value */

/* 2994 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2996 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2998 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GroupQueryManager */

/* 3000 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3002 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3006 */	NdrFcShort( 0x48 ),	/* 72 */
/* 3008 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3010 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3012 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3014 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 3016 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 3018 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3020 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3022 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter groupIdentity */

/* 3024 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 3026 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3028 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter manager */

/* 3030 */	NdrFcShort( 0xa113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=40 */
/* 3032 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3034 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 3036 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3038 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3040 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GroupQueryMembers */

/* 3042 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3044 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3048 */	NdrFcShort( 0x49 ),	/* 73 */
/* 3050 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3052 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3054 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3056 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 3058 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 3060 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3062 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3064 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter groupIdentity */

/* 3066 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 3068 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3070 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter members */

/* 3072 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 3074 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3076 */	NdrFcShort( 0x4be ),	/* Type Offset=1214 */

	/* Return value */

/* 3078 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3080 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3082 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetIdentity */

/* 3084 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3086 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3090 */	NdrFcShort( 0x4a ),	/* 74 */
/* 3092 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3094 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3096 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3098 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 3100 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3102 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3104 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3106 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter identity */

/* 3108 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 3110 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3112 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 3114 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3116 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3118 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetCommPartnerKey */

/* 3120 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3122 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3126 */	NdrFcShort( 0x4b ),	/* 75 */
/* 3128 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3130 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3132 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3134 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 3136 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3138 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3140 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3142 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter identity */

/* 3144 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 3146 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3148 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter fpr */

/* 3150 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3152 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3154 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 3156 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3158 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3160 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ImportKeyWithFprReturn */

/* 3162 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3164 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3168 */	NdrFcShort( 0x4c ),	/* 76 */
/* 3170 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3172 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3174 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3176 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 3178 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 3180 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3182 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3184 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter keyData */

/* 3186 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3188 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3190 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter privateKeys */

/* 3192 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 3194 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3196 */	NdrFcShort( 0x4be ),	/* Type Offset=1214 */

	/* Parameter importedKeys */

/* 3198 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 3200 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3202 */	NdrFcShort( 0x4be ),	/* Type Offset=1214 */

	/* Return value */

/* 3204 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3206 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3208 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const planckCOMServerWrapper_MIDL_TYPE_FORMAT_STRING planckCOMServerWrapper__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x0,	/* FC_RP */
/*  4 */	NdrFcShort( 0x444 ),	/* Offset= 1092 (1096) */
/*  6 */	
			0x12, 0x0,	/* FC_UP */
/*  8 */	NdrFcShort( 0xe ),	/* Offset= 14 (22) */
/* 10 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 12 */	NdrFcShort( 0x2 ),	/* 2 */
/* 14 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 16 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 18 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 20 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 22 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 24 */	NdrFcShort( 0x8 ),	/* 8 */
/* 26 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (10) */
/* 28 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 30 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 32 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 34 */	NdrFcShort( 0x0 ),	/* 0 */
/* 36 */	NdrFcShort( 0x4 ),	/* 4 */
/* 38 */	NdrFcShort( 0x0 ),	/* 0 */
/* 40 */	NdrFcShort( 0xffde ),	/* Offset= -34 (6) */
/* 42 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 44 */	NdrFcShort( 0x2 ),	/* Offset= 2 (46) */
/* 46 */	
			0x12, 0x0,	/* FC_UP */
/* 48 */	NdrFcShort( 0x3d8 ),	/* Offset= 984 (1032) */
/* 50 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 52 */	NdrFcShort( 0x18 ),	/* 24 */
/* 54 */	NdrFcShort( 0xa ),	/* 10 */
/* 56 */	NdrFcLong( 0x8 ),	/* 8 */
/* 60 */	NdrFcShort( 0x5a ),	/* Offset= 90 (150) */
/* 62 */	NdrFcLong( 0xd ),	/* 13 */
/* 66 */	NdrFcShort( 0x90 ),	/* Offset= 144 (210) */
/* 68 */	NdrFcLong( 0x9 ),	/* 9 */
/* 72 */	NdrFcShort( 0xc2 ),	/* Offset= 194 (266) */
/* 74 */	NdrFcLong( 0xc ),	/* 12 */
/* 78 */	NdrFcShort( 0x2bc ),	/* Offset= 700 (778) */
/* 80 */	NdrFcLong( 0x24 ),	/* 36 */
/* 84 */	NdrFcShort( 0x2e6 ),	/* Offset= 742 (826) */
/* 86 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 90 */	NdrFcShort( 0x302 ),	/* Offset= 770 (860) */
/* 92 */	NdrFcLong( 0x10 ),	/* 16 */
/* 96 */	NdrFcShort( 0x31c ),	/* Offset= 796 (892) */
/* 98 */	NdrFcLong( 0x2 ),	/* 2 */
/* 102 */	NdrFcShort( 0x336 ),	/* Offset= 822 (924) */
/* 104 */	NdrFcLong( 0x3 ),	/* 3 */
/* 108 */	NdrFcShort( 0x350 ),	/* Offset= 848 (956) */
/* 110 */	NdrFcLong( 0x14 ),	/* 20 */
/* 114 */	NdrFcShort( 0x36a ),	/* Offset= 874 (988) */
/* 116 */	NdrFcShort( 0xffff ),	/* Offset= -1 (115) */
/* 118 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 120 */	NdrFcShort( 0x4 ),	/* 4 */
/* 122 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 124 */	NdrFcShort( 0x0 ),	/* 0 */
/* 126 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 128 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 130 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 132 */	NdrFcShort( 0x4 ),	/* 4 */
/* 134 */	NdrFcShort( 0x0 ),	/* 0 */
/* 136 */	NdrFcShort( 0x1 ),	/* 1 */
/* 138 */	NdrFcShort( 0x0 ),	/* 0 */
/* 140 */	NdrFcShort( 0x0 ),	/* 0 */
/* 142 */	0x12, 0x0,	/* FC_UP */
/* 144 */	NdrFcShort( 0xff86 ),	/* Offset= -122 (22) */
/* 146 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 148 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 150 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 152 */	NdrFcShort( 0x8 ),	/* 8 */
/* 154 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 156 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 158 */	NdrFcShort( 0x4 ),	/* 4 */
/* 160 */	NdrFcShort( 0x4 ),	/* 4 */
/* 162 */	0x11, 0x0,	/* FC_RP */
/* 164 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (118) */
/* 166 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 168 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 170 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 172 */	NdrFcLong( 0x0 ),	/* 0 */
/* 176 */	NdrFcShort( 0x0 ),	/* 0 */
/* 178 */	NdrFcShort( 0x0 ),	/* 0 */
/* 180 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 182 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 184 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 186 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 188 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 190 */	NdrFcShort( 0x0 ),	/* 0 */
/* 192 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 194 */	NdrFcShort( 0x0 ),	/* 0 */
/* 196 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 198 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 202 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 204 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 206 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (170) */
/* 208 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 210 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 212 */	NdrFcShort( 0x8 ),	/* 8 */
/* 214 */	NdrFcShort( 0x0 ),	/* 0 */
/* 216 */	NdrFcShort( 0x6 ),	/* Offset= 6 (222) */
/* 218 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 220 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 222 */	
			0x11, 0x0,	/* FC_RP */
/* 224 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (188) */
/* 226 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 228 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 232 */	NdrFcShort( 0x0 ),	/* 0 */
/* 234 */	NdrFcShort( 0x0 ),	/* 0 */
/* 236 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 238 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 240 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 242 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 244 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 246 */	NdrFcShort( 0x0 ),	/* 0 */
/* 248 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 250 */	NdrFcShort( 0x0 ),	/* 0 */
/* 252 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 254 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 258 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 260 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 262 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (226) */
/* 264 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 266 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 268 */	NdrFcShort( 0x8 ),	/* 8 */
/* 270 */	NdrFcShort( 0x0 ),	/* 0 */
/* 272 */	NdrFcShort( 0x6 ),	/* Offset= 6 (278) */
/* 274 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 276 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 278 */	
			0x11, 0x0,	/* FC_RP */
/* 280 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (244) */
/* 282 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 284 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 286 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 288 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 290 */	NdrFcShort( 0x2 ),	/* Offset= 2 (292) */
/* 292 */	NdrFcShort( 0x10 ),	/* 16 */
/* 294 */	NdrFcShort( 0x2f ),	/* 47 */
/* 296 */	NdrFcLong( 0x14 ),	/* 20 */
/* 300 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 302 */	NdrFcLong( 0x3 ),	/* 3 */
/* 306 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 308 */	NdrFcLong( 0x11 ),	/* 17 */
/* 312 */	NdrFcShort( 0x8001 ),	/* Simple arm type: FC_BYTE */
/* 314 */	NdrFcLong( 0x2 ),	/* 2 */
/* 318 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 320 */	NdrFcLong( 0x4 ),	/* 4 */
/* 324 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 326 */	NdrFcLong( 0x5 ),	/* 5 */
/* 330 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 332 */	NdrFcLong( 0xb ),	/* 11 */
/* 336 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 338 */	NdrFcLong( 0xa ),	/* 10 */
/* 342 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 344 */	NdrFcLong( 0x6 ),	/* 6 */
/* 348 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (580) */
/* 350 */	NdrFcLong( 0x7 ),	/* 7 */
/* 354 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 356 */	NdrFcLong( 0x8 ),	/* 8 */
/* 360 */	NdrFcShort( 0xfe9e ),	/* Offset= -354 (6) */
/* 362 */	NdrFcLong( 0xd ),	/* 13 */
/* 366 */	NdrFcShort( 0xff3c ),	/* Offset= -196 (170) */
/* 368 */	NdrFcLong( 0x9 ),	/* 9 */
/* 372 */	NdrFcShort( 0xff6e ),	/* Offset= -146 (226) */
/* 374 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 378 */	NdrFcShort( 0xd0 ),	/* Offset= 208 (586) */
/* 380 */	NdrFcLong( 0x24 ),	/* 36 */
/* 384 */	NdrFcShort( 0xd2 ),	/* Offset= 210 (594) */
/* 386 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 390 */	NdrFcShort( 0xcc ),	/* Offset= 204 (594) */
/* 392 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 396 */	NdrFcShort( 0xfc ),	/* Offset= 252 (648) */
/* 398 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 402 */	NdrFcShort( 0xfa ),	/* Offset= 250 (652) */
/* 404 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 408 */	NdrFcShort( 0xf8 ),	/* Offset= 248 (656) */
/* 410 */	NdrFcLong( 0x4014 ),	/* 16404 */
/* 414 */	NdrFcShort( 0xf6 ),	/* Offset= 246 (660) */
/* 416 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 420 */	NdrFcShort( 0xf4 ),	/* Offset= 244 (664) */
/* 422 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 426 */	NdrFcShort( 0xf2 ),	/* Offset= 242 (668) */
/* 428 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 432 */	NdrFcShort( 0xdc ),	/* Offset= 220 (652) */
/* 434 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 438 */	NdrFcShort( 0xda ),	/* Offset= 218 (656) */
/* 440 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 444 */	NdrFcShort( 0xe4 ),	/* Offset= 228 (672) */
/* 446 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 450 */	NdrFcShort( 0xda ),	/* Offset= 218 (668) */
/* 452 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 456 */	NdrFcShort( 0xdc ),	/* Offset= 220 (676) */
/* 458 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 462 */	NdrFcShort( 0xda ),	/* Offset= 218 (680) */
/* 464 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 468 */	NdrFcShort( 0xd8 ),	/* Offset= 216 (684) */
/* 470 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 474 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (688) */
/* 476 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 480 */	NdrFcShort( 0xdc ),	/* Offset= 220 (700) */
/* 482 */	NdrFcLong( 0x10 ),	/* 16 */
/* 486 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 488 */	NdrFcLong( 0x12 ),	/* 18 */
/* 492 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 494 */	NdrFcLong( 0x13 ),	/* 19 */
/* 498 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 500 */	NdrFcLong( 0x15 ),	/* 21 */
/* 504 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 506 */	NdrFcLong( 0x16 ),	/* 22 */
/* 510 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 512 */	NdrFcLong( 0x17 ),	/* 23 */
/* 516 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 518 */	NdrFcLong( 0xe ),	/* 14 */
/* 522 */	NdrFcShort( 0xba ),	/* Offset= 186 (708) */
/* 524 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 528 */	NdrFcShort( 0xbe ),	/* Offset= 190 (718) */
/* 530 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 534 */	NdrFcShort( 0xbc ),	/* Offset= 188 (722) */
/* 536 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 540 */	NdrFcShort( 0x70 ),	/* Offset= 112 (652) */
/* 542 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 546 */	NdrFcShort( 0x6e ),	/* Offset= 110 (656) */
/* 548 */	NdrFcLong( 0x4015 ),	/* 16405 */
/* 552 */	NdrFcShort( 0x6c ),	/* Offset= 108 (660) */
/* 554 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 558 */	NdrFcShort( 0x62 ),	/* Offset= 98 (656) */
/* 560 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 564 */	NdrFcShort( 0x5c ),	/* Offset= 92 (656) */
/* 566 */	NdrFcLong( 0x0 ),	/* 0 */
/* 570 */	NdrFcShort( 0x0 ),	/* Offset= 0 (570) */
/* 572 */	NdrFcLong( 0x1 ),	/* 1 */
/* 576 */	NdrFcShort( 0x0 ),	/* Offset= 0 (576) */
/* 578 */	NdrFcShort( 0xffff ),	/* Offset= -1 (577) */
/* 580 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 582 */	NdrFcShort( 0x8 ),	/* 8 */
/* 584 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 586 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 588 */	NdrFcShort( 0x2 ),	/* Offset= 2 (590) */
/* 590 */	
			0x12, 0x0,	/* FC_UP */
/* 592 */	NdrFcShort( 0x1b8 ),	/* Offset= 440 (1032) */
/* 594 */	
			0x12, 0x0,	/* FC_UP */
/* 596 */	NdrFcShort( 0x20 ),	/* Offset= 32 (628) */
/* 598 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 600 */	NdrFcLong( 0x2f ),	/* 47 */
/* 604 */	NdrFcShort( 0x0 ),	/* 0 */
/* 606 */	NdrFcShort( 0x0 ),	/* 0 */
/* 608 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 610 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 612 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 614 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 616 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 618 */	NdrFcShort( 0x1 ),	/* 1 */
/* 620 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 622 */	NdrFcShort( 0x4 ),	/* 4 */
/* 624 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 626 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 628 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 630 */	NdrFcShort( 0x10 ),	/* 16 */
/* 632 */	NdrFcShort( 0x0 ),	/* 0 */
/* 634 */	NdrFcShort( 0xa ),	/* Offset= 10 (644) */
/* 636 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 638 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 640 */	NdrFcShort( 0xffd6 ),	/* Offset= -42 (598) */
/* 642 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 644 */	
			0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 646 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (616) */
/* 648 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 650 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 652 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 654 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 656 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 658 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 660 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 662 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/* 664 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 666 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 668 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 670 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 672 */	
			0x12, 0x0,	/* FC_UP */
/* 674 */	NdrFcShort( 0xffa2 ),	/* Offset= -94 (580) */
/* 676 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 678 */	NdrFcShort( 0xfd60 ),	/* Offset= -672 (6) */
/* 680 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 682 */	NdrFcShort( 0xfe00 ),	/* Offset= -512 (170) */
/* 684 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 686 */	NdrFcShort( 0xfe34 ),	/* Offset= -460 (226) */
/* 688 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 690 */	NdrFcShort( 0x2 ),	/* Offset= 2 (692) */
/* 692 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 694 */	NdrFcShort( 0x2 ),	/* Offset= 2 (696) */
/* 696 */	
			0x12, 0x0,	/* FC_UP */
/* 698 */	NdrFcShort( 0x14e ),	/* Offset= 334 (1032) */
/* 700 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 702 */	NdrFcShort( 0x2 ),	/* Offset= 2 (704) */
/* 704 */	
			0x12, 0x0,	/* FC_UP */
/* 706 */	NdrFcShort( 0x14 ),	/* Offset= 20 (726) */
/* 708 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 710 */	NdrFcShort( 0x10 ),	/* 16 */
/* 712 */	0x6,		/* FC_SHORT */
			0x1,		/* FC_BYTE */
/* 714 */	0x1,		/* FC_BYTE */
			0x8,		/* FC_LONG */
/* 716 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 718 */	
			0x12, 0x0,	/* FC_UP */
/* 720 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (708) */
/* 722 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 724 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 726 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 728 */	NdrFcShort( 0x20 ),	/* 32 */
/* 730 */	NdrFcShort( 0x0 ),	/* 0 */
/* 732 */	NdrFcShort( 0x0 ),	/* Offset= 0 (732) */
/* 734 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 736 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 738 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 740 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 742 */	NdrFcShort( 0xfe34 ),	/* Offset= -460 (282) */
/* 744 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 746 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 748 */	NdrFcShort( 0x4 ),	/* 4 */
/* 750 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 752 */	NdrFcShort( 0x0 ),	/* 0 */
/* 754 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 756 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 758 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 760 */	NdrFcShort( 0x4 ),	/* 4 */
/* 762 */	NdrFcShort( 0x0 ),	/* 0 */
/* 764 */	NdrFcShort( 0x1 ),	/* 1 */
/* 766 */	NdrFcShort( 0x0 ),	/* 0 */
/* 768 */	NdrFcShort( 0x0 ),	/* 0 */
/* 770 */	0x12, 0x0,	/* FC_UP */
/* 772 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (726) */
/* 774 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 776 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 778 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 780 */	NdrFcShort( 0x8 ),	/* 8 */
/* 782 */	NdrFcShort( 0x0 ),	/* 0 */
/* 784 */	NdrFcShort( 0x6 ),	/* Offset= 6 (790) */
/* 786 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 788 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 790 */	
			0x11, 0x0,	/* FC_RP */
/* 792 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (746) */
/* 794 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 796 */	NdrFcShort( 0x4 ),	/* 4 */
/* 798 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 800 */	NdrFcShort( 0x0 ),	/* 0 */
/* 802 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 804 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 806 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 808 */	NdrFcShort( 0x4 ),	/* 4 */
/* 810 */	NdrFcShort( 0x0 ),	/* 0 */
/* 812 */	NdrFcShort( 0x1 ),	/* 1 */
/* 814 */	NdrFcShort( 0x0 ),	/* 0 */
/* 816 */	NdrFcShort( 0x0 ),	/* 0 */
/* 818 */	0x12, 0x0,	/* FC_UP */
/* 820 */	NdrFcShort( 0xff40 ),	/* Offset= -192 (628) */
/* 822 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 824 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 826 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 828 */	NdrFcShort( 0x8 ),	/* 8 */
/* 830 */	NdrFcShort( 0x0 ),	/* 0 */
/* 832 */	NdrFcShort( 0x6 ),	/* Offset= 6 (838) */
/* 834 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 836 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 838 */	
			0x11, 0x0,	/* FC_RP */
/* 840 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (794) */
/* 842 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 844 */	NdrFcShort( 0x8 ),	/* 8 */
/* 846 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 848 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 850 */	NdrFcShort( 0x10 ),	/* 16 */
/* 852 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 854 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 856 */	0x0,		/* 0 */
			NdrFcShort( 0xfff1 ),	/* Offset= -15 (842) */
			0x5b,		/* FC_END */
/* 860 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 862 */	NdrFcShort( 0x18 ),	/* 24 */
/* 864 */	NdrFcShort( 0x0 ),	/* 0 */
/* 866 */	NdrFcShort( 0xa ),	/* Offset= 10 (876) */
/* 868 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 870 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 872 */	NdrFcShort( 0xffe8 ),	/* Offset= -24 (848) */
/* 874 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 876 */	
			0x11, 0x0,	/* FC_RP */
/* 878 */	NdrFcShort( 0xfd4e ),	/* Offset= -690 (188) */
/* 880 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 882 */	NdrFcShort( 0x1 ),	/* 1 */
/* 884 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 886 */	NdrFcShort( 0x0 ),	/* 0 */
/* 888 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 890 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 892 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 894 */	NdrFcShort( 0x8 ),	/* 8 */
/* 896 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 898 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 900 */	NdrFcShort( 0x4 ),	/* 4 */
/* 902 */	NdrFcShort( 0x4 ),	/* 4 */
/* 904 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 906 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (880) */
/* 908 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 910 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 912 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 914 */	NdrFcShort( 0x2 ),	/* 2 */
/* 916 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 918 */	NdrFcShort( 0x0 ),	/* 0 */
/* 920 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 922 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 924 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 926 */	NdrFcShort( 0x8 ),	/* 8 */
/* 928 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 930 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 932 */	NdrFcShort( 0x4 ),	/* 4 */
/* 934 */	NdrFcShort( 0x4 ),	/* 4 */
/* 936 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 938 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (912) */
/* 940 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 942 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 944 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 946 */	NdrFcShort( 0x4 ),	/* 4 */
/* 948 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 950 */	NdrFcShort( 0x0 ),	/* 0 */
/* 952 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 954 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 956 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 958 */	NdrFcShort( 0x8 ),	/* 8 */
/* 960 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 962 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 964 */	NdrFcShort( 0x4 ),	/* 4 */
/* 966 */	NdrFcShort( 0x4 ),	/* 4 */
/* 968 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 970 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (944) */
/* 972 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 974 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 976 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 978 */	NdrFcShort( 0x8 ),	/* 8 */
/* 980 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 982 */	NdrFcShort( 0x0 ),	/* 0 */
/* 984 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 986 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 988 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 990 */	NdrFcShort( 0x8 ),	/* 8 */
/* 992 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 994 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 996 */	NdrFcShort( 0x4 ),	/* 4 */
/* 998 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1000 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 1002 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (976) */
/* 1004 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1006 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 1008 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 1010 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1012 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1014 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1016 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 1018 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1020 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 1022 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 1024 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1026 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1028 */	NdrFcShort( 0xffec ),	/* Offset= -20 (1008) */
/* 1030 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1032 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1034 */	NdrFcShort( 0x28 ),	/* 40 */
/* 1036 */	NdrFcShort( 0xffec ),	/* Offset= -20 (1016) */
/* 1038 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1038) */
/* 1040 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1042 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1044 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1046 */	NdrFcShort( 0xfc1c ),	/* Offset= -996 (50) */
/* 1048 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1050 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1052 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1054 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1056 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1058 */	NdrFcShort( 0xfc08 ),	/* Offset= -1016 (42) */
/* 1060 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1062 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1064 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1066 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1066) */
/* 1068 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1070 */	NdrFcShort( 0xfbf2 ),	/* Offset= -1038 (32) */
/* 1072 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1074 */	NdrFcShort( 0xfbee ),	/* Offset= -1042 (32) */
/* 1076 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1078 */	NdrFcShort( 0xfbea ),	/* Offset= -1046 (32) */
/* 1080 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1082 */	NdrFcShort( 0xfbe6 ),	/* Offset= -1050 (32) */
/* 1084 */	0xe,		/* FC_ENUM32 */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1086 */	0x0,		/* 0 */
			NdrFcShort( 0xfbe1 ),	/* Offset= -1055 (32) */
			0x6,		/* FC_SHORT */
/* 1090 */	0x3e,		/* FC_STRUCTPAD2 */
			0xe,		/* FC_ENUM32 */
/* 1092 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1094 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1096 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 1098 */	NdrFcShort( 0xa0 ),	/* 160 */
/* 1100 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1102 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1102) */
/* 1104 */	0xe,		/* FC_ENUM32 */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1106 */	0x0,		/* 0 */
			NdrFcShort( 0xfbcd ),	/* Offset= -1075 (32) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1110 */	0x0,		/* 0 */
			NdrFcShort( 0xfbc9 ),	/* Offset= -1079 (32) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1114 */	0x0,		/* 0 */
			NdrFcShort( 0xfbc5 ),	/* Offset= -1083 (32) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1118 */	0x0,		/* 0 */
			NdrFcShort( 0xfbc1 ),	/* Offset= -1087 (32) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1122 */	0x0,		/* 0 */
			NdrFcShort( 0xffb7 ),	/* Offset= -73 (1050) */
			0xb,		/* FC_HYPER */
/* 1126 */	0xb,		/* FC_HYPER */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1128 */	0x0,		/* 0 */
			NdrFcShort( 0xffbb ),	/* Offset= -69 (1060) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1132 */	0x0,		/* 0 */
			NdrFcShort( 0xffad ),	/* Offset= -83 (1050) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1136 */	0x0,		/* 0 */
			NdrFcShort( 0xffb3 ),	/* Offset= -77 (1060) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1140 */	0x0,		/* 0 */
			NdrFcShort( 0xffa5 ),	/* Offset= -91 (1050) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1144 */	0x0,		/* 0 */
			NdrFcShort( 0xffa1 ),	/* Offset= -95 (1050) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1148 */	0x0,		/* 0 */
			NdrFcShort( 0xff9d ),	/* Offset= -99 (1050) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1152 */	0x0,		/* 0 */
			NdrFcShort( 0xff99 ),	/* Offset= -103 (1050) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1156 */	0x0,		/* 0 */
			NdrFcShort( 0xff95 ),	/* Offset= -107 (1050) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1160 */	0x0,		/* 0 */
			NdrFcShort( 0xfb97 ),	/* Offset= -1129 (32) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1164 */	0x0,		/* 0 */
			NdrFcShort( 0xff8d ),	/* Offset= -115 (1050) */
			0xe,		/* FC_ENUM32 */
/* 1168 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1170 */	NdrFcShort( 0xfb8e ),	/* Offset= -1138 (32) */
/* 1172 */	0xe,		/* FC_ENUM32 */
			0x40,		/* FC_STRUCTPAD4 */
/* 1174 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1176 */	
			0x11, 0x0,	/* FC_RP */
/* 1178 */	NdrFcShort( 0xff8a ),	/* Offset= -118 (1060) */
/* 1180 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1182 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1188) */
/* 1184 */	
			0x13, 0x0,	/* FC_OP */
/* 1186 */	NdrFcShort( 0xfb74 ),	/* Offset= -1164 (22) */
/* 1188 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1190 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1192 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1194 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1196 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (1184) */
/* 1198 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1200 */	NdrFcShort( 0xff74 ),	/* Offset= -140 (1060) */
/* 1202 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1204 */	NdrFcShort( 0xa ),	/* Offset= 10 (1214) */
/* 1206 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 1208 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1210) */
/* 1210 */	
			0x13, 0x0,	/* FC_OP */
/* 1212 */	NdrFcShort( 0xff4c ),	/* Offset= -180 (1032) */
/* 1214 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1216 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1218 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1220 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1222 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (1206) */
/* 1224 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1226 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 1228 */	
			0x11, 0x0,	/* FC_RP */
/* 1230 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (1214) */
/* 1232 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 1234 */	0xe,		/* FC_ENUM32 */
			0x5c,		/* FC_PAD */
/* 1236 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1238 */	0xe,		/* FC_ENUM32 */
			0x5c,		/* FC_PAD */
/* 1240 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1242 */	NdrFcLong( 0x4da92647 ),	/* 1302931015 */
/* 1246 */	NdrFcShort( 0xa858 ),	/* -22440 */
/* 1248 */	NdrFcShort( 0x448e ),	/* 17550 */
/* 1250 */	0xb0,		/* 176 */
			0x1f,		/* 31 */
/* 1252 */	0xbe,		/* 190 */
			0x4d,		/* 77 */
/* 1254 */	0xcb,		/* 203 */
			0x8c,		/* 140 */
/* 1256 */	0x86,		/* 134 */
			0xa1,		/* 161 */
/* 1258 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1260 */	0xd,		/* FC_ENUM16 */
			0x5c,		/* FC_PAD */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            },
            {
            LPSAFEARRAY_UserSize
            ,LPSAFEARRAY_UserMarshal
            ,LPSAFEARRAY_UserUnmarshal
            ,LPSAFEARRAY_UserFree
            }

        };



/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IpEpEngineCallbacks, ver. 0.0,
   GUID={0x4DA92647,0xA858,0x448E,{0xB0,0x1F,0xBE,0x4D,0xCB,0x8C,0x86,0xA1}} */

#pragma code_seg(".orpc")
static const unsigned short IpEpEngineCallbacks_FormatStringOffsetTable[] =
    {
    0,
    36
    };

static const MIDL_STUBLESS_PROXY_INFO IpEpEngineCallbacks_ProxyInfo =
    {
    &Object_StubDesc,
    planckCOMServerWrapper__MIDL_ProcFormatString.Format,
    &IpEpEngineCallbacks_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IpEpEngineCallbacks_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    planckCOMServerWrapper__MIDL_ProcFormatString.Format,
    &IpEpEngineCallbacks_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _IpEpEngineCallbacksProxyVtbl = 
{
    &IpEpEngineCallbacks_ProxyInfo,
    &IID_IpEpEngineCallbacks,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IpEpEngineCallbacks::MessageToSend */ ,
    (void *) (INT_PTR) -1 /* IpEpEngineCallbacks::NotifyHandshake */
};

const CInterfaceStubVtbl _IpEpEngineCallbacksStubVtbl =
{
    &IID_IpEpEngineCallbacks,
    &IpEpEngineCallbacks_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IpEpEngine, ver. 0.0,
   GUID={0x045E49AF,0x0975,0x4876,{0xA5,0x3B,0x8C,0xA5,0xAB,0x28,0xC0,0xF8}} */

#pragma code_seg(".orpc")
static const unsigned short IpEpEngine_FormatStringOffsetTable[] =
    {
    84,
    120,
    156,
    192,
    234,
    288,
    342,
    402,
    444,
    480,
    516,
    558,
    600,
    642,
    684,
    720,
    756,
    798,
    834,
    876,
    918,
    978,
    1038,
    1080,
    1122,
    1164,
    1230,
    1290,
    1344,
    1380,
    1410,
    1458,
    1518,
    1560,
    1602,
    1638,
    1668,
    1716,
    1758,
    1800,
    1830,
    1872,
    1914,
    1950,
    1980,
    2040,
    2082,
    2124,
    2160,
    2196,
    2232,
    2268,
    2310,
    2346,
    2376,
    2418,
    2466,
    2502,
    2544,
    2586,
    2628,
    2658,
    2688,
    2736,
    2784,
    2826,
    2868,
    2910,
    2958,
    3000,
    3042,
    3084,
    3120,
    3162
    };

static const MIDL_STUBLESS_PROXY_INFO IpEpEngine_ProxyInfo =
    {
    &Object_StubDesc,
    planckCOMServerWrapper__MIDL_ProcFormatString.Format,
    &IpEpEngine_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IpEpEngine_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    planckCOMServerWrapper__MIDL_ProcFormatString.Format,
    &IpEpEngine_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(77) _IpEpEngineProxyVtbl = 
{
    &IpEpEngine_ProxyInfo,
    &IID_IpEpEngine,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IpEpEngine::VerboseLogging */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::PassiveMode */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::UnencryptedSubject */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::ExportKey */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::Log */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::Trustwords */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::GetTrustwords */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::GetCrashdumpLog */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::GetEngineVersion */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::GetLanguageList */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::SetIdentityFlags */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::UnsetIdentityFlags */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::Myself */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::UpdateIdentity */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::KeyMistrusted */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::KeyResetTrust */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::TrustPersonalKey */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::OwnIdentitiesRetrieve */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::IspEpUser */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::OpenPGPListKeyinfo */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::EncryptMessage */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::DecryptMessage */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::OutgoingMessageRating */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::IdentityRating */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::ColorFromRating */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::GetMessageTrustwords */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::EncryptMessageForSelf */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::ReEvaluateMessageRating */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::RegisterCallbacks */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::UnregisterCallbacks */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::SetOwnKey */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::EncryptMessageAndAddPrivKey */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::UpdateNow */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::OutgoingMessageRatingPreview */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::TrustOwnKey */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::Startup */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::GetKeyRatingForUser */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::KeyResetIdentity */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::KeyResetUser */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::KeyResetAllOwnKeys */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::DeliverHandshakeResult */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::ImportKey */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::ConfigCipherSuite */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::LeaveDeviceGroup */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::GetTrustwordsForFprs */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::GetKeyRating */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::PERToXERSyncMessage */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::DisableIdentityForSync */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::EnableIdentityForSync */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::PerMachineDirectory */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::PerUserDirectory */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::RatingFromCommType */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::GetIsSyncRunning */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::ShutDownSync */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::MIMEDecodeMessage */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::MIMEEncodeMessage */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::ConfigPassphrase */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::ConfigPassphraseForNewKeys */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::ShowNotification */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::ExportSecretKey */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::DisableAllSyncChannels */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::SyncReinit */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::GroupCreate */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::GroupJoin */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::GroupDissolve */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::GroupInviteMember */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::GroupRemoveMember */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::GroupRating */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::GroupQueryGroups */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::GroupQueryManager */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::GroupQueryMembers */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::SetIdentity */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::SetCommPartnerKey */ ,
    (void *) (INT_PTR) -1 /* IpEpEngine::ImportKeyWithFprReturn */
};

const CInterfaceStubVtbl _IpEpEngineStubVtbl =
{
    &IID_IpEpEngine,
    &IpEpEngine_ServerInfo,
    77,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    planckCOMServerWrapper__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x60001, /* Ndr library version */
    0,
    0x801026e, /* MIDL Version 8.1.622 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _planckCOMServerWrapper_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IpEpEngineCallbacksProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IpEpEngineProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _planckCOMServerWrapper_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IpEpEngineCallbacksStubVtbl,
    ( CInterfaceStubVtbl *) &_IpEpEngineStubVtbl,
    0
};

PCInterfaceName const _planckCOMServerWrapper_InterfaceNamesList[] = 
{
    "IpEpEngineCallbacks",
    "IpEpEngine",
    0
};


#define _planckCOMServerWrapper_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _planckCOMServerWrapper, pIID, n)

int __stdcall _planckCOMServerWrapper_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _planckCOMServerWrapper, 2, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _planckCOMServerWrapper, 2, *pIndex )
    
}

const ExtendedProxyFileInfo planckCOMServerWrapper_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _planckCOMServerWrapper_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _planckCOMServerWrapper_StubVtblList,
    (const PCInterfaceName * ) & _planckCOMServerWrapper_InterfaceNamesList,
    0, /* no delegation */
    & _planckCOMServerWrapper_IID_Lookup, 
    2,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64) && !defined(_ARM_) */

