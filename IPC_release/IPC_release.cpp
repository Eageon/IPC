// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// IPC_release.cpp : ����Ӧ�ó��������Ϊ��
//
#include <crtdbg.h>

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "IPC_release.h"
#include "MainFrm.h"
#include "CANCenter.h"
#include "DBCenter.h"
#include "MConfig.h"
#include "Station.h"
#include "StationManager.h"
#include "IPC_releaseDoc.h"
#include "IPC_releaseView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIPC_releaseApp

BEGIN_MESSAGE_MAP(CIPC_releaseApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CIPC_releaseApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CIPC_releaseApp ����

CIPC_releaseApp::CIPC_releaseApp()
{
	m_bHiColorIcons = TRUE;

	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("IPC_release.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	
	
	//m_Config = new CMConfig;
	
	
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CIPC_releaseApp ����

CIPC_releaseApp theApp;


// CIPC_releaseApp ��ʼ��

BOOL CIPC_releaseApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CIPC_releaseDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CIPC_releaseView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	//((CMainFrame *)pDocTemplate->Get)


	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand ֮����

	InitStationClass();
	m_threadCANRead = AfxBeginThread(ThreadCANRead, CCANCenter::Instance(), 0, 0, CREATE_SUSPENDED);
	m_threadCANWrite = AfxBeginThread(ThreadCANWrite, CCANCenter::Instance(), 0, 0, CREATE_SUSPENDED);
	m_threadDBWrite = AfxBeginThread(ThreadDBWrite, CDBCenter::Instance(), 0, 0, CREATE_SUSPENDED);
	
	//m_threadCANRead->ResumeThread();
	m_threadCANWrite->ResumeThread();
	

	return TRUE;
}

int CIPC_releaseApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	//delete m_Config;
	theApp.m_threadCANRead->SuspendThread();
	theApp.m_threadCANWrite->SuspendThread();
	theApp.m_threadDBWrite->SuspendThread();
	theApp.m_threadCANRead->ExitInstance();
	theApp.m_threadCANWrite->ExitInstance();
	theApp.m_threadDBWrite->ExitInstance();

	delete theApp.m_threadCANRead;
	delete theApp.m_threadCANWrite;
	delete theApp.m_threadDBWrite;
	
	
	//theApp.m_threadCAN->Delete();
	
	CCANCenter::ExitInstance();
	CDBCenter::ExitInstance();
	CMConfig::ExitInstance();
	ExitStationClass();
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CIPC_releaseApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_TIMER()
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CIPC_releaseApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CIPC_releaseApp �Զ������/���淽��

void CIPC_releaseApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CIPC_releaseApp::LoadCustomState()
{
}

void CIPC_releaseApp::SaveCustomState()
{
}

// CIPC_releaseApp ��Ϣ�������





BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


//void CAboutDlg::OnTimer(UINT_PTR nIDEvent)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	CDialogEx::OnTimer(nIDEvent);
//}


void CIPC_releaseApp::InitStationClass(void)
{
	//��ʼ����λ���󣬲���CCANCenter����
	(CCANCenter::Instance())->Config(CMConfig::Instance());

	m_StationMngr = new CStationManager(CMConfig::Instance()->StationNBR);
	CCANCenter::Instance()->AttachStations(m_StationMngr);
}




void CIPC_releaseApp::Log(CString info)
{
	this->m_Monitor.Log(info);
}


int CIPC_releaseApp::ExitStationClass(void)
{
	delete m_StationMngr;

	return 0;
}


UINT ThreadCANRead(LPVOID pThreadParam)
{
	CCANCenter *m_CAN = (CCANCenter *)pThreadParam;

	if(m_CAN->IsPortOpen() == false)
		m_CAN->Openport();

	//::WaitForSingleObject(m_CAN->m_CANOpened.m_hObject, INFINITE);
	while(1)
	{
		::Sleep(1);
		m_CAN->TestRecv();
		//m_CAN->ParseMsg();
		//m_CAN->ParseCAN(
		//m_CAN->Deliver((i % theApp.m_Config.StationNBR) + 1, _T("test"));
	}
	
	return 0;
}

UINT ThreadCANWrite(LPVOID pThreadParam)
{
	CCANCenter *m_CAN = (CCANCenter *)pThreadParam;
	//m_CAN->Openport();
	CEvent *m_WriteFinished = new CEvent(FALSE, FALSE);
	delete m_WriteFinished;

	while(1)
	{
		::WaitForSingleObject(m_CAN->m_WriteEvent.m_hObject, INFINITE);
		m_CAN->SendMsg();
	}
}

UINT ThreadDBWrite(LPVOID pThreadParam)
{
	CDBCenter *m_DB = (CDBCenter *)pThreadParam;
	while(1)
	{
		::Sleep(100);
		m_DB->Flush();
	}
}