

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __FinancialMMidl_h__
#define __FinancialMMidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DFinancialMM_FWD_DEFINED__
#define ___DFinancialMM_FWD_DEFINED__
typedef interface _DFinancialMM _DFinancialMM;
#endif 	/* ___DFinancialMM_FWD_DEFINED__ */


#ifndef ___DFinancialMMEvents_FWD_DEFINED__
#define ___DFinancialMMEvents_FWD_DEFINED__
typedef interface _DFinancialMMEvents _DFinancialMMEvents;
#endif 	/* ___DFinancialMMEvents_FWD_DEFINED__ */


#ifndef __FinancialMM_FWD_DEFINED__
#define __FinancialMM_FWD_DEFINED__

#ifdef __cplusplus
typedef class FinancialMM FinancialMM;
#else
typedef struct FinancialMM FinancialMM;
#endif /* __cplusplus */

#endif 	/* __FinancialMM_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __FinancialMMLib_LIBRARY_DEFINED__
#define __FinancialMMLib_LIBRARY_DEFINED__

/* library FinancialMMLib */
/* [control][version][uuid] */ 


EXTERN_C const IID LIBID_FinancialMMLib;

#ifndef ___DFinancialMM_DISPINTERFACE_DEFINED__
#define ___DFinancialMM_DISPINTERFACE_DEFINED__

/* dispinterface _DFinancialMM */
/* [uuid] */ 


EXTERN_C const IID DIID__DFinancialMM;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("A8A2175D-85E3-405E-9C65-C65066ECFB27")
    _DFinancialMM : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DFinancialMMVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DFinancialMM * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DFinancialMM * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DFinancialMM * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DFinancialMM * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DFinancialMM * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DFinancialMM * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DFinancialMM * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DFinancialMMVtbl;

    interface _DFinancialMM
    {
        CONST_VTBL struct _DFinancialMMVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DFinancialMM_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DFinancialMM_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DFinancialMM_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DFinancialMM_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DFinancialMM_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DFinancialMM_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DFinancialMM_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DFinancialMM_DISPINTERFACE_DEFINED__ */


#ifndef ___DFinancialMMEvents_DISPINTERFACE_DEFINED__
#define ___DFinancialMMEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DFinancialMMEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DFinancialMMEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("8448F1E8-BBA7-420B-A41A-374640CE6B9A")
    _DFinancialMMEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DFinancialMMEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DFinancialMMEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DFinancialMMEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DFinancialMMEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DFinancialMMEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DFinancialMMEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DFinancialMMEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DFinancialMMEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DFinancialMMEventsVtbl;

    interface _DFinancialMMEvents
    {
        CONST_VTBL struct _DFinancialMMEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DFinancialMMEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DFinancialMMEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DFinancialMMEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DFinancialMMEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DFinancialMMEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DFinancialMMEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DFinancialMMEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DFinancialMMEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_FinancialMM;

#ifdef __cplusplus

class DECLSPEC_UUID("F4B89D89-EAF4-411E-AFBE-76C1765453C3")
FinancialMM;
#endif
#endif /* __FinancialMMLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


