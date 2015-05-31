

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sun May 31 17:28:45 2015
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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IpEpEngine,0x9A9F4422,0xCF0A,0x45D7,0x90,0xCD,0x1D,0x1B,0x7B,0x2A,0x45,0x40);


MIDL_DEFINE_GUID(IID, LIBID_pEpCOMServerAdapterLib,0x3EC2E1A4,0x40E8,0x48E4,0xA7,0xB0,0x18,0x76,0xD3,0x4F,0x94,0x62);


MIDL_DEFINE_GUID(IID, DIID__IpEpEngineEvents,0xB6BC9B8E,0xD9E2,0x4419,0xA3,0xA4,0x7B,0x4B,0x58,0x17,0x55,0x49);


MIDL_DEFINE_GUID(CLSID, CLSID_pEpEngine,0xEF1B073D,0x5058,0x4E0E,0x82,0x9E,0xB4,0xD2,0x2C,0xA2,0x1E,0xA2);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



