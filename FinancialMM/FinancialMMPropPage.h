#pragma once

// FinancialMMPropPage.h : Declaration of the CFinancialMMPropPage property page class.


// CFinancialMMPropPage : See FinancialMMPropPage.cpp for implementation.

class CFinancialMMPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CFinancialMMPropPage)
	DECLARE_OLECREATE_EX(CFinancialMMPropPage)

// Constructor
public:
	CFinancialMMPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_FINANCIALMM };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

