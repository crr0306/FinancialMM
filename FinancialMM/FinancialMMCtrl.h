#pragma once

// FinancialMMCtrl.h : Declaration of the CFinancialMMCtrl ActiveX Control class.


// CFinancialMMCtrl : See FinancialMMCtrl.cpp for implementation.

class CFinancialMMCtrl : public COleControl
{
	DECLARE_DYNCREATE(CFinancialMMCtrl)

// Constructor
public:
	CFinancialMMCtrl();

// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// Implementation
protected:
	~CFinancialMMCtrl();

	DECLARE_OLECREATE_EX(CFinancialMMCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CFinancialMMCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CFinancialMMCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CFinancialMMCtrl)		// Type name and misc status

// Message maps
	afx_msg LRESULT OnFireEventForThread1(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnFireEventForThread2(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	DECLARE_DISPATCH_MAP()
	//afx_msg void StartLengthyProcess();
	afx_msg  void SerialPort(LPCTSTR portname);
	afx_msg  void Pidpad(LPCTSTR portname);
	afx_msg void AboutBox();

// Event maps
	DECLARE_EVENT_MAP()
public:
	void  WriteChar(BYTE buffer[6]);
	void  WriteChar2(BYTE buffer[1]);//写入一个字符
	char ReceiveChar();
	char* ReceiveChar2();//返回一个数组
	void CloseComm1();//串口启动前先关闭串口
	void CloseComm();//串口失败显示信息
	void SerialThread();
	void PinpadThread();
// Dispatch and event IDs
public:
	enum {
		

		eventidReceivePad = 2L,
		eventidReadKh = 1L,

		dispidSerialPort = 4L,
		dispidPidpad = 3L,
		dispidClosePort = 2L,
		dispidOpenPort = 1L
	};
protected:
	LONG OpenPort(LPCTSTR portname);
	void ClosePort();
	//void Pidpad(LPCTSTR portname);
	//void SerialPort(LPCTSTR portname);
	

	void ReadKh(LPCTSTR kh)
	{
		FireEvent(eventidReadKh, EVENT_PARAM(VTS_BSTR), kh);
	}

	void ReceivePad(LPCTSTR password)
	{
		FireEvent(eventidReceivePad, EVENT_PARAM(VTS_BSTR), password);
	}

};

