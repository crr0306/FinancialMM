// FinancialMMCtrl.cpp : Implementation of the CFinancialMMCtrl ActiveX Control class.

#include "stdafx.h"
#include "FinancialMM.h"
#include "FinancialMMCtrl.h"
#include "FinancialMMPropPage.h"
#include "afxdialogex.h"
#pragma comment(lib,"comsuppw.lib")

#include <stdio.h>
HANDLE hComm;
OVERLAPPED m_ov;//重叠方式
COMSTAT comstat;
COMSTAT comstat2;
DWORD m_dwCommEvents;
DWORD dwBytesRead2 = 1024;//长度数

//线程
#include <iostream>
#include <windows.h>
#include<string.h>
using namespace std;
HANDLE hSerial;
HANDLE hPinpad;

CString kh = NULL;//卡号
CString cspassword = NULL;//密码

#define WM_THREADFIREEVENT1 (WM_APP+101)
#define WM_THREADFIREEVENT2 (WM_APP+102)
/*BYTE b[ 6 ] =		{0x1A,0x0D,0x00,0x00,0x1B,0x42} ; // 全部复位
BYTE a[ 6 ] =	{0x1A,0x06,0x66,0x01,0x1B,0xA2	} ; // 串口全部启动数据 1A 06 66 01 1B A2
BYTE a[ 6 ] =	{0x1A,0x06,0x65,0x01,0x1B,0xA1} ; // 密码键盘启动数据 1A 06 65 01 1B A1
82：告诉串口，我准备发送数据了，无返回值
0D: 确认键返回值，也代表串口关闭，不能再往里面写数据了。
BYTE a[ 6 ] =	{0x1A,0x06,0x66,0x02,0x1B,0xA3} ; // 全部关闭串口 1A 06 66 02 1B A3*/
#include <time.h>   
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CFinancialMMCtrl, COleControl)

// Message map

BEGIN_MESSAGE_MAP(CFinancialMMCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_MESSAGE(WM_THREADFIREEVENT1, OnFireEventForThread1)
	ON_MESSAGE(WM_THREADFIREEVENT2, OnFireEventForThread2)
END_MESSAGE_MAP()

// Dispatch map

BEGIN_DISPATCH_MAP(CFinancialMMCtrl, COleControl)
	DISP_FUNCTION_ID(CFinancialMMCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CFinancialMMCtrl, "OpenPort", dispidOpenPort, OpenPort, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CFinancialMMCtrl, "ClosePort", dispidClosePort, ClosePort, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CFinancialMMCtrl, "Pidpad", dispidPidpad, Pidpad, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(CFinancialMMCtrl, "SerialPort", dispidSerialPort, SerialPort, VT_EMPTY, VTS_BSTR)
	
END_DISPATCH_MAP()

// Event map

BEGIN_EVENT_MAP(CFinancialMMCtrl, COleControl)
	EVENT_CUSTOM_ID("ReadKh", eventidReadKh, ReadKh, VTS_BSTR)
	EVENT_CUSTOM_ID("ReceivePad", eventidReceivePad, ReceivePad, VTS_BSTR)
END_EVENT_MAP()

// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CFinancialMMCtrl, 1)
	PROPPAGEID(CFinancialMMPropPage::guid)
END_PROPPAGEIDS(CFinancialMMCtrl)

// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CFinancialMMCtrl, "FINANCIALMM.FinancialMMCtrl.1",
	0xf4b89d89, 0xeaf4, 0x411e, 0xaf, 0xbe, 0x76, 0xc1, 0x76, 0x54, 0x53, 0xc3)

// Type library ID and version

IMPLEMENT_OLETYPELIB(CFinancialMMCtrl, _tlid, _wVerMajor, _wVerMinor)

// Interface IDs

const IID IID_DFinancialMM = { 0xA8A2175D, 0x85E3, 0x405E, { 0x9C, 0x65, 0xC6, 0x50, 0x66, 0xEC, 0xFB, 0x27 } };
const IID IID_DFinancialMMEvents = { 0x8448F1E8, 0xBBA7, 0x420B, { 0xA4, 0x1A, 0x37, 0x46, 0x40, 0xCE, 0x6B, 0x9A } };

// Control type information

static const DWORD _dwFinancialMMOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CFinancialMMCtrl, IDS_FINANCIALMM, _dwFinancialMMOleMisc)

// CFinancialMMCtrl::CFinancialMMCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CFinancialMMCtrl

BOOL CFinancialMMCtrl::CFinancialMMCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_FINANCIALMM,
			IDB_FINANCIALMM,
			afxRegApartmentThreading,
			_dwFinancialMMOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


// CFinancialMMCtrl::CFinancialMMCtrl - Constructor

CFinancialMMCtrl::CFinancialMMCtrl()
{
	InitializeIIDs(&IID_DFinancialMM, &IID_DFinancialMMEvents);
	// TODO: Initialize your control's instance data here.
}

// CFinancialMMCtrl::~CFinancialMMCtrl - Destructor

CFinancialMMCtrl::~CFinancialMMCtrl()
{
	// TODO: Cleanup your control's instance data here.
}

// CFinancialMMCtrl::OnDraw - Drawing function

void CFinancialMMCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& /* rcInvalid */)
{
	if (!pdc)
		return;

	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}

// CFinancialMMCtrl::DoPropExchange - Persistence support

void CFinancialMMCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
}


// CFinancialMMCtrl::OnResetState - Reset control to default state

void CFinancialMMCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


// CFinancialMMCtrl::AboutBox - Display an "About" box to the user

void CFinancialMMCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_FINANCIALMM);
	dlgAbout.DoModal();
}


// CFinancialMMCtrl message handlers


LONG CFinancialMMCtrl::OpenPort(LPCTSTR portname)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	hComm = CreateFile((LPTSTR)portname, //串口号
		GENERIC_READ | GENERIC_WRITE, //允许读写
		0, //通讯设备必须以独占方式打开
		0, //无安全属性
		OPEN_EXISTING, //通讯设备已存在
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, //重叠
		0); //通讯设备不能用模板打开
	if (hComm == (HANDLE)-1)
	{
		CloseHandle(hComm);
		hComm = NULL;
		return 0;
	}
	SetupComm(hComm, 10024, 1024); //输入缓冲区和输出缓冲区的大小都是100  
	COMMTIMEOUTS TimeOuts;
	//设定读超时  
	TimeOuts.ReadIntervalTimeout = MAXDWORD;
	TimeOuts.ReadTotalTimeoutMultiplier = 0;
	TimeOuts.ReadTotalTimeoutConstant = 0;
	//在读一次输入缓冲区的内容后读操作就立即返回，  
	//而不管是否读入了要求的字符。  
	//设定写超时  
	TimeOuts.WriteTotalTimeoutMultiplier = 100;
	TimeOuts.WriteTotalTimeoutConstant = 500;
	SetCommTimeouts(hComm, &TimeOuts); //设置超时  

	DCB dcb;
	GetCommState(hComm, &dcb);
	dcb.BaudRate = 9600; //波特率为9600  
	dcb.ByteSize = 8; //每个字节有8位  
	dcb.Parity = NOPARITY; //无奇偶校验位  
	dcb.StopBits = 1; //两个停止位  
	SetCommState(hComm, &dcb);
	PurgeComm(hComm, PURGE_TXCLEAR | PURGE_RXCLEAR);
	return 1;
}
/*
刷卡串口或者密码键盘连续打开的时候需要先关闭，保证可以连续使用
*/
//void CFinancialMMCtrl::CloseComm1(){
//	//禁止串行端口所有事件
//	SetCommMask(hComm, 0);
//	//清除数据终端就绪信号
//	EscapeCommFunction(hComm, CLRDTR);
//	//丢弃通信资源的输出或输入缓冲区字符并终止在通信资源上挂起的读、写操操作
//	PurgeComm(hComm, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
//	CloseHandle(hComm);
//	hComm = NULL;
//
//}
/*
连续启动失败的时候，则显示提示
*/
//void CFinancialMMCtrl::CloseComm(){
//	//禁止串行端口所有事件
//	SetCommMask(hComm, 0);
//	//清除数据终端就绪信号
//	EscapeCommFunction(hComm, CLRDTR);
//	//丢弃通信资源的输出或输入缓冲区字符并终止在通信资源上挂起的读、写操操作
//	PurgeComm(hComm, PURGE_TXCLEAR | PURGE_RXCLEAR);
//	CloseHandle(hComm);
//	hComm = NULL;
//	AfxMessageBox(_T("请重新点击按钮"));
//
//}

/*对外关闭串口*/
void CFinancialMMCtrl::ClosePort()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	//禁止串行端口所有事件
	SetCommMask(hComm, 0);
	//清除数据终端就绪信号
	EscapeCommFunction(hComm, CLRDTR);
	//丢弃通信资源的输出或输入缓冲区字符并终止在通信资源上挂起的读、写操操作
	PurgeComm(hComm, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
	CloseHandle(hComm);
	hComm = NULL;
	CloseHandle(hSerial);
	CloseHandle(hPinpad);
	/*DWORD dwExitCode;
	GetExitCodeThread(hPinpad, &dwExitCode);*/
	/*TerminateThread(hPinpad, 0);
	TerminateThread(hSerial, 0);*/
	MessageBox(_T("串口已关闭"));
}

void  CFinancialMMCtrl::WriteChar(BYTE buffer[6])
{
	
	DWORD  dwBytesWritten = 6;//长度
	BOOL bWriteStat;//判断是否写好数据
	bWriteStat = WriteFile(hComm, buffer, dwBytesWritten, &dwBytesWritten, &m_ov);
	if (!bWriteStat){
		if (GetLastError() == ERROR_IO_PENDING)
		{
			/* 使用WaitForSingleObject函数等待，直到读操作完成或延时已达到2秒钟,当串口读操作进行完毕后，m_osRead的hEvent事件会变为有信号  
			参数1为句柄，
			参数2为时间间隔，当它为INFINITE时，对象被触发信号后，函数才会返回*/
			WaitForSingleObject(m_ov.hEvent, INFINITE);
			Sleep(200);//特别标注：此处的时间不能太短，不然不能将数据写进去
		}
	}
}
void  CFinancialMMCtrl::WriteChar2(BYTE buffer[1])
{
	
	DWORD  dwBytesWritten = 1;//长度
	BOOL bWriteStat;//判断是否写好数据
	bWriteStat = WriteFile(hComm, buffer, dwBytesWritten, &dwBytesWritten, &m_ov);
	if (!bWriteStat){
		if (GetLastError() == ERROR_IO_PENDING)
		{
			WaitForSingleObject(m_ov.hEvent, INFINITE);
			Sleep(200);

		}
	}
}
char CFinancialMMCtrl::ReceiveChar()
{
	
	char lpInBuffer[6];//存储
	//BSTR lpInBuffer=NULL;
	DWORD dwBytesRead = 6;//长度数
	BOOL bReadStatus;//读之后结果
	DWORD dwErrorFlags;
	ClearCommError(hComm, &dwErrorFlags, &comstat);
	printf("输入缓冲区中的字节数：%d\n", comstat.cbInQue); //等于1
	if (!comstat.cbInQue)
	{
		return 0;
	}

	dwBytesRead = max(dwBytesRead, (DWORD)comstat.cbInQue);
	bReadStatus = ReadFile(hComm, lpInBuffer, dwBytesRead, &dwBytesRead, &m_ov);
	if (!bReadStatus)
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			GetOverlappedResult(hComm, &m_ov, &dwBytesRead, TRUE);
			return lpInBuffer[0];
		}
		return lpInBuffer[0];
	}
	return lpInBuffer[0];
}
char* CFinancialMMCtrl::ReceiveChar2()
{
	
	char* str = new char[100]; //存储
	BOOL bReadStatus;//是否读取成功
	DWORD dwErrorFlags;
	/*此函数清除硬件的通讯错误以及获取通讯设备的当前状态comstat*/
	ClearCommError(hComm, &dwErrorFlags, &comstat2);
	//cbInQue成员变量，该成员变量的值代表输入缓冲区的字节数，即接收到的数据数量 
	dwBytesRead2 = max(dwBytesRead2, (DWORD)comstat2.cbInQue);
	bReadStatus = ReadFile(hComm, str, dwBytesRead2, &dwBytesRead2, &m_ov);
	if (!bReadStatus)
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			GetOverlappedResult(hComm, &m_ov, &dwBytesRead2, TRUE);
			return str;
		}
		return str;
	}
	return str;
}

void CFinancialMMCtrl::SerialThread()
{
	// PurgeComm(hComm, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
	//防止前面几次没有读取到，那么需要循环多读取几次。
	//不用考虑用户多次刷一张卡，而多次得到这张卡号。
	time_t timeBegin, timeEnd;
	timeBegin = time(NULL);
	timeEnd = time(NULL);
	char *str;//读取串口中的数据，返回一个数组
	//kh = _T("");
	int count = 0;
	str = ReceiveChar2();
	while ((timeEnd-timeBegin)<20)
	{
		//Sleep(5000);
		kh = _T("");
		str = ReceiveChar2();
		CString cs1[1024] = { 0 };//临时数据，存储字符数组
		//只取16进制的后两位
		for (int i = 0; i < comstat2.cbInQue; i++)
		{
			cs1[i].Format(_T("%02x"), str[i] & 0xFF);
			kh = kh + cs1[i];
		}
		//将字符剔除，只输出
		for (int i = 0; i < 6; i++)
		{
			kh.Remove('a' + i);
		}
		//kh不为空,则退出
		if (kh != _T(""))
		{
			return;
		}
		timeEnd = time(NULL);	
	}
	if ((timeEnd-timeBegin)>=20)
	{
		kh = _T("");
		AfxMessageBox(_T("超时20秒，请重新点击按钮"));
	}
	
}
void CFinancialMMCtrl::PinpadThread()
{
	time_t timeBegin, timeEnd;
	timeBegin = time(NULL);
	timeEnd = time(NULL);
	cspassword = _T("");
	BYTE spw;//密码
	CString strMsg=_T("");
	spw = ReceiveChar();
	//在while不断地读取串口
	while ((timeEnd - timeBegin)<15)
	{
		Sleep(10);
		if (spw == 0x0D)
		{
			//MessageBox(cspassword);
			//break;
			return ;
		}	
		if (spw != 0)
		{
			strMsg.Format(_T("%0x"), spw);
			cspassword = cspassword + strMsg + _T("-");
			//MessageBox(cspassword);
		}		
		spw = ReceiveChar();
		timeEnd = time(NULL);
	}
	if ((timeEnd - timeBegin)>=15)
	{
		cspassword = _T("");
		AfxMessageBox(_T("超时15秒，请重新点击按钮"));
	}
}


DWORD WINAPI  TmpCallInstance1(LPVOID lpParamter){
	CFinancialMMCtrl *t = (CFinancialMMCtrl*)lpParamter;
	t->SerialThread();
	PostMessage(t->m_hWnd,
				WM_THREADFIREEVENT1,
				(WPARAM)NULL,
				(LPARAM)NULL);
	return 1;
}
DWORD WINAPI  TmpCallInstance2(LPVOID lpParamter){
	
	CFinancialMMCtrl *t = (CFinancialMMCtrl*)lpParamter;
	t->PinpadThread();
		PostMessage(t->m_hWnd,
					WM_THREADFIREEVENT2,
					(WPARAM)NULL,
					(LPARAM)NULL);
		return 1;
	
}

LRESULT CFinancialMMCtrl::OnFireEventForThread1(WPARAM wParam, LPARAM lParam)
{
	ReadKh(kh);
	CloseHandle(hSerial);
	return true;
}
LRESULT CFinancialMMCtrl::OnFireEventForThread2(WPARAM wParam, LPARAM lParam)
{
	ReceivePad(cspassword);
	CloseHandle(hPinpad);
	return true;
}
void CFinancialMMCtrl::SerialPort(LPCTSTR portname)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	kh = _T("");
	CloseHandle(hComm);//直接关闭串口
	CloseHandle(hSerial);//关闭线程
	/*BYTE close[6] = { 0x1A, 0x06, 0x66, 0x02, 0x1B, 0xA3 };
	WriteChar(close); */
		BYTE buffer1[6] = { 0x1A, 0x0D, 0x00, 0x00, 0x1B, 0x42 };//复位 1A 0D 00 00 1B 42
		BYTE buffer2[6] = { 0x1A, 0x06, 0x66, 0x01, 0x1B, 0xA2 };//串口全部启动数据 1A 06 66 01 1B A2
		BYTE sfw = NULL;
		BYTE sqd = NULL;
		//PurgeComm(hComm, PURGE_TXABORT | PURGE_RXABORT|PURGE_TXCLEAR | PURGE_RXCLEAR);
		if (OpenPort(portname) == 1)
		{
			//MessageBox(_T("串口打开成功,且稍等刷卡"));	
			PurgeComm(hComm, PURGE_TXCLEAR | PURGE_RXCLEAR);
			//Sleep(2000);
			WriteChar(buffer1);
			sfw = ReceiveChar();
			/*CString sfw1;
			sfw1.Format(_T("%0X"),sfw);
			MessageBox(sfw1);*/

			if (sfw == (0xAA))
			{
				WriteChar(buffer2);
				sqd = ReceiveChar();
				if (sqd == (0xAA))
				{
					MessageBox(_T("串口启动数据写入成功，且请刷卡"));
					//Sleep(600);
					hSerial = CreateThread(NULL, 0, &TmpCallInstance1, this, 0, 0);
					CloseHandle(hSerial);
				}
				else
				{
					MessageBox(_T("串口启动数据写入失败，请重新点击启动按钮"));
				}

			}
			else
			{
				MessageBox(_T("复位数据写入失败，请重新点击启动按钮"));
			}
		}
		else
		{
			MessageBox(_T("串口打开失败，请重新点击启动按钮"));

		}

}

void CFinancialMMCtrl::Pidpad(LPCTSTR portname)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// TODO: Add your dispatch handler code here
	cspassword = _T("");
	CloseHandle(hComm);//打开串口前先将串口关闭
	CloseHandle(hPinpad);//关闭线程
	PurgeComm(hComm, PURGE_TXCLEAR | PURGE_RXCLEAR);
	if (OpenPort(portname) == 1)
	{
		MessageBox(_T("打开成功"));

		BYTE b[6] = { 0x1A, 0x0D, 0x00, 0x00, 0x1B, 0x42 }; // 全部复位 1A 0D 00 00 1B 42
		BYTE s1=NULL;
		WriteChar(b);
		s1 = ReceiveChar();
		if (s1 == 0xAA)
		{
			BYTE a[6] = { 0x1A, 0x06, 0x65, 0x01, 0x1B, 0xA1 }; // 密码键盘启动数据 1A 06 65 01 1B A1
			BYTE s2=NULL;
			WriteChar(a);
			s2 = ReceiveChar();
			if (s2 == 0xAA)
			{
				//输入0x82:代表准备输入密码
				BYTE p[1] = { 0x82 };
				WriteChar2(p);
				//Sleep(600);
				hPinpad = CreateThread(NULL, 0, &TmpCallInstance2, this, 0, NULL);
				CloseHandle(hPinpad);
			}
			else
			{			
				MessageBox(_T("启动失败,请重新点击启动按钮"));
			}
		}
		else
		{		
			MessageBox(_T("复位失败，请重新点击启动按钮"));
		}
	}
	else
	{
	
		MessageBox(_T("打开失败，请重新点击启动按钮"));
	}
}



