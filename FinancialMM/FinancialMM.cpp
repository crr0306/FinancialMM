// FinancialMM.cpp : Implementation of CFinancialMMApp and DLL registration.

#include "stdafx.h"
#include "FinancialMM.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CFinancialMMApp theApp;

const GUID CDECL _tlid = { 0x899CCE5E, 0x66D1, 0x4B75, { 0x8B, 0xED, 0xBC, 0x0, 0xFC, 0xCE, 0x8E, 0xAE } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CFinancialMMApp::InitInstance - DLL initialization

BOOL CFinancialMMApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CFinancialMMApp::ExitInstance - DLL termination

int CFinancialMMApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
