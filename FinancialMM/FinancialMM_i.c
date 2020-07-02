

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Wed Jul 01 14:20:54 2020
 */
/* Compiler settings for FinancialMM.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
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

MIDL_DEFINE_GUID(IID, LIBID_FinancialMMLib,0x899CCE5E,0x66D1,0x4B75,0x8B,0xED,0xBC,0x00,0xFC,0xCE,0x8E,0xAE);


MIDL_DEFINE_GUID(IID, DIID__DFinancialMM,0xA8A2175D,0x85E3,0x405E,0x9C,0x65,0xC6,0x50,0x66,0xEC,0xFB,0x27);


MIDL_DEFINE_GUID(IID, DIID__DFinancialMMEvents,0x8448F1E8,0xBBA7,0x420B,0xA4,0x1A,0x37,0x46,0x40,0xCE,0x6B,0x9A);


MIDL_DEFINE_GUID(CLSID, CLSID_FinancialMM,0xF4B89D89,0xEAF4,0x411E,0xAF,0xBE,0x76,0xC1,0x76,0x54,0x53,0xC3);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



