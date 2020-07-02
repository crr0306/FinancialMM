// FinancialMMPropPage.cpp : Implementation of the CFinancialMMPropPage property page class.

#include "stdafx.h"
#include "FinancialMM.h"
#include "FinancialMMPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CFinancialMMPropPage, COlePropertyPage)

// Message map

BEGIN_MESSAGE_MAP(CFinancialMMPropPage, COlePropertyPage)
END_MESSAGE_MAP()

// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CFinancialMMPropPage, "FINANCIALMM.FinancialMMPropPage.1",
	0x5d94b992, 0x35a9, 0x4f14, 0x86, 0xea, 0xac, 0xa5, 0x7, 0xae, 0xb8, 0xc2)

// CFinancialMMPropPage::CFinancialMMPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CFinancialMMPropPage

BOOL CFinancialMMPropPage::CFinancialMMPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_FINANCIALMM_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}

// CFinancialMMPropPage::CFinancialMMPropPage - Constructor

CFinancialMMPropPage::CFinancialMMPropPage() :
	COlePropertyPage(IDD, IDS_FINANCIALMM_PPG_CAPTION)
{
}

// CFinancialMMPropPage::DoDataExchange - Moves data between page and properties

void CFinancialMMPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// CFinancialMMPropPage message handlers
