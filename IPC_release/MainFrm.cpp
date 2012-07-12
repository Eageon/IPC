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

// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "IPC_release.h"
#include "StationListView.h"
#include "MConfig.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_WM_SETTINGCHANGE()
	ON_COMMAND(ID_BUTTON_GLOBAL, &CMainFrame::OnButtonGlobal)
	ON_COMMAND(ID_BUTTON_OPENCAN, &CMainFrame::OnButtonOpencan)
	ON_COMMAND(ID_BUTTON_DATA_CHECK, &CMainFrame::OnButtonDataCheck)
	ON_UPDATE_COMMAND_UI(ID_CHECK_RECV_STANDARD, &CMainFrame::OnUpdateCheckRecvStandard)
	ON_COMMAND(ID_CHECK_RECV_STANDARD, &CMainFrame::OnCheckRecvStandard)
	ON_COMMAND(ID_CHECK_RECV_REMOTE, &CMainFrame::OnCheckRecvRemote)
	ON_UPDATE_COMMAND_UI(ID_CHECK_RECV_REMOTE, &CMainFrame::OnUpdateCheckRecvRemote)
	ON_COMMAND(ID_CHECK_SEND_STANDARD, &CMainFrame::OnCheckSendStandard)
	ON_UPDATE_COMMAND_UI(ID_CHECK_SEND_STANDARD, &CMainFrame::OnUpdateCheckSendStandard)
	ON_COMMAND(ID_CHECK_SEND_REMOTE, &CMainFrame::OnCheckSendRemote)
	ON_UPDATE_COMMAND_UI(ID_CHECK_SEND_REMOTE, &CMainFrame::OnUpdateCheckSendRemote)
	ON_COMMAND(ID_BUTTON_SAVECONFIG, &CMainFrame::OnButtonSaveconfig)
END_MESSAGE_MAP()

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLACK);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// ���ڳ־�ֵ�����Ӿ�����������ʽ
	OnApplicationLook(theApp.m_nAppLook);

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	CDockingManager::SetDockingMode(DT_SMART);
	// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// ���ز˵���ͼ��(�����κα�׼��������):
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	// ����ͣ������
	if (!CreateDockingWindows())
	{
		TRACE0("δ�ܴ���ͣ������\n");
		return -1;
	}

	
	m_wndStationView.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndStationView);
	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndOutput);
	theApp.m_Monitor.SetScreen(&m_wndOutput.m_wndOutputBuild);

	CreateTabWindow();


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	CString strStationView;
	bNameValid = strStationView.LoadString(IDS_STATIONLIST_VIEW);
	ASSERT(bNameValid);
	if (!m_wndStationView.Create(strStationView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_STATIONLIST, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT, AFX_CBRS_REGULAR_TABS, AFX_CBRS_RESIZE))
	{
		TRACE0("δ�ܴ������ļ���ͼ������\n");
		return FALSE; // δ�ܴ���
	}


	// �����������
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI, AFX_CBRS_REGULAR_TABS, AFX_CBRS_RESIZE))
	{
		TRACE0("δ�ܴ����������\n");
		return FALSE; // δ�ܴ���
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{

	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CFrameWndEx::OnSettingChange(uFlags, lpszSection);
	m_wndOutput.UpdateFonts();
}


//void CMainFrame::OnClickTest(void)
//{
//	//AfxMessageBox(_T("���Գɹ���"));
//}


//void CMainFrame::OnButton2()
//{
//	// TODO: �ڴ���������������
//	//AfxMessageBox(_T("���Գɹ���"));
//}


void CMainFrame::DoDataExchange(CDataExchange* pDX)
{
	// TODO: �ڴ����ר�ô����/����û���

	CFrameWndEx::DoDataExchange(pDX);
}

BOOL CMainFrame::CreateTabWindow()
{
	return TRUE;
}


void CMainFrame::OnButtonGlobal()
{
	// TODO: �ڴ���������������
	CIPC_releaseView *pView=(CIPC_releaseView *)this->GetActiveView();
	pView->PostMessage(NM_SWITCHDLG, 0, 0);

	theApp.m_Monitor.Log(_T("test"));
}


void CMainFrame::OnButtonOpencan()
{
	// TODO: �ڴ���������������
	//AfxMessageBox(_T("ohhhhhhhh"));
	theApp.Log(_T("���ڴ�CAN"));
	//theApp.m_threadCANRead->Run();
	if(CCANCenter::Instance()->IsPortOpen() == false)
		CCANCenter::Instance()->Openport();
	if(CCANCenter::Instance()->IsPortOpen() == true)
	{
		theApp.m_threadCANRead->ResumeThread();
		theApp.Log(_T("��CAN�ɹ�"));
	}
}


void CMainFrame::OnButtonDataCheck()
{
	// TODO: �ڴ���������������
	CIPC_releaseView *pView=(CIPC_releaseView *)this->GetActiveView();
	pView->PostMessage(NM_SWITCHDLG, 2, 0);
}


void CMainFrame::OnCheckRecvStandard()
{
	// TODO: �ڴ���������������
	CCANCenter::Instance()->m_ChkSffR = TRUE;
}

void CMainFrame::OnUpdateCheckRecvStandard(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(CCANCenter::Instance()->m_ChkSffR);
}

void CMainFrame::OnCheckRecvRemote()
{
	// TODO: �ڴ���������������
	CCANCenter::Instance()->m_ChkSffR = FALSE;
}


void CMainFrame::OnUpdateCheckRecvRemote(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(!(CCANCenter::Instance()->m_ChkSffR));
}


void CMainFrame::OnCheckSendStandard()
{
	// TODO: �ڴ���������������
	CCANCenter::Instance()->m_ChkSffS = TRUE;
}


void CMainFrame::OnUpdateCheckSendStandard(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(CCANCenter::Instance()->m_ChkSffS);
}


void CMainFrame::OnCheckSendRemote()
{
	// TODO: �ڴ���������������
	CCANCenter::Instance()->m_ChkSffS = FALSE;
}


void CMainFrame::OnUpdateCheckSendRemote(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(!(CCANCenter::Instance()->m_ChkSffS));
}


void CMainFrame::OnButtonSaveconfig()
{
	// TODO: �ڴ���������������
	CMConfig::Instance()->Save();
}
