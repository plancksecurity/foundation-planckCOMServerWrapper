

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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
        EXTERN_C __declspec(selectany) const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif // !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IpEpEngineCallbacks,0x4DA92647,0xA858,0x448E,0xB0,0x1F,0xBE,0x4D,0xCB,0x8C,0x86,0xA1);


MIDL_DEFINE_GUID(IID, IID_IpEpEngine,0x045E49AF,0x0975,0x4876,0xA5,0x3B,0x8C,0xA5,0xAB,0x28,0xC0,0xF8);


MIDL_DEFINE_GUID(IID, LIBID_pEpCOMServerAdapterLib,0x564A4350,0x419E,0x47F1,0xB0,0xDF,0x6F,0xCC,0xF0,0xCD,0x0B,0xBC);


MIDL_DEFINE_GUID(CLSID, CLSID_pEpEngine,0x5FF6682B,0x727B,0x4DFE,0xA6,0x8D,0x28,0x98,0x28,0x74,0xC0,0xC7);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



