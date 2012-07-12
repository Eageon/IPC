// DialogMain.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IPC_release.h"
#include "DialogMain.h"
#include "afxdialogex.h"


// CDialogMain �Ի���

IMPLEMENT_DYNAMIC(CDialogMain, CDialog)

CDialogMain::CDialogMain(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogMain::IDD, pParent)
{

}

CDialogMain::~CDialogMain()
{
}

void CDialogMain::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_TAB_MAIN, m_wndTab);
}


BEGIN_MESSAGE_MAP(CDialogMain, CDialog)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(NM_SWITCHDLG, &CDialogMain::OnNmSwitchdlg)
END_MESSAGE_MAP()


// CDialogMain ��Ϣ�������


BOOL CDialogMain::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetParentFrame()->RecalcLayout();
	//ResizeParentToFit();
	CreateTab();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


BOOL CDialogMain::CreateTab(void)
{
	//���������Ի���

	//m_dialogPipeline.Create(IDD_DIALOG_PIPELINE, GetDlgItem(IDC_TAB_MAIN));
	//m_dialogPipeline.ModifyStyle(0, WS_SIZEBOX);
	//m_dialogBasic.Create(IDD_DIALOG_BASIC, GetDlgItem(IDC_TAB_MAIN));
	//m_dialogBasic.ModifyStyle(0, WS_SIZEBOX);
	//�趨��Tab����ʾ�ķ�Χ
	m_dialogPipeline.Create(IDD_DIALOG_PIPELINE, this);
	//m_dialogPipeline.ConnectToCANCenter(CCANCenter::Instance());
	m_dialogBasic.Create(IDD_DIALOG_BASIC, this);
	m_dialogData.Create(IDD_DIALOG_DATA, this);

	CRect rw;
	//m_wndTab.GetWindowRect(rw);
	//m_iMinWidth = rw.Width();
	//m_iMinHeight = rw.Height();
	CRect rectClient;
	GetClientRect(rectClient);
	m_iClientWidth = rectClient.Width();
	m_iClientHeight = rectClient.Height();

	rectClient.top += 0;    //0���ر�ǩ��20��ʾ��ǩ
	rectClient.bottom -= 0;
	rectClient.left += 0;
	rectClient.right -= 0;
	m_dialogPipeline.MoveWindow(&rectClient);
	m_dialogBasic.MoveWindow(&rectClient);
	m_dialogData.MoveWindow(&rectClient);

	//�ѶԻ������ָ�뱣������
	pDialog[0] = &m_dialogPipeline;
	CCANCenter::Instance()->pDialog[0] = &m_dialogPipeline;
	pDialog[1] = &m_dialogBasic;
	CCANCenter::Instance()->pDialog[1] = &m_dialogPipeline;
	pDialog[2] = &m_dialogData;
	CCANCenter::Instance()->pDialog[2] = &m_dialogData;


	//��ʾ��ʼҳ��
	pDialog[0]->ShowWindow(SW_SHOW);
	pDialog[1]->ShowWindow(SW_HIDE);
	pDialog[2]->ShowWindow(SW_HIDE);
	//���浱ǰѡ��
	m_CurSelTab = 0;
	
	return TRUE;
}


int CDialogMain::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}


//void CDialogMain::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);  
//
//    //�õ��µ�ҳ������  
//    m_CurSelTab = m_wndTab.GetCurSel();  
//  
//    //���µ�ҳ����ʾ����  
//    pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);  
//
//	*pResult = 0;
//}


void CDialogMain::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	CWnd *pWnd;
	CWnd *pDialog;
	CRect rect;
	/*pWnd = (CTabCtrl *)GetDlgItem(IDC_TAB_MAIN);*/
	//AfxMessageBox(_T("ִ�гɹ�"));

	/*if(pWnd)
	{
		GetClientRect(rect);
		pWnd->MoveWindow(rect);
		pWnd->ShowWindow(SW_SHOW);
	}*/

	pDialog = (CDialogPipeline *)GetDlgItem(IDD_DIALOG_PIPELINE);
	if(pDialog)
	{
		GetClientRect(&rect);
		rect.top += 5;    //0���ر�ǩ��20��ʾ��ǩ
		rect.bottom -= 5;
		rect.left += 5;
		rect.right -= 5;
		pDialog->MoveWindow(&rect);
	}

	pDialog = (CDialogBasic *)GetDlgItem(IDD_DIALOG_BASIC);
	if(pDialog)
	{
		GetClientRect(&rect);
		rect.top += 5;    
		rect.bottom -= 5;
		rect.left += 5;
		rect.right -= 5;
		pDialog->MoveWindow(&rect);
	}
}



afx_msg LRESULT CDialogMain::OnNmSwitchdlg(WPARAM wParam, LPARAM lParam)
{
	//int nDialogIndex = wParam - 1;
	
	for(int i = 0; i < sizeof(pDialog)/sizeof(pDialog[0]); i++)
	{
		pDialog[i]->ShowWindow(SW_HIDE);
	}

	pDialog[wParam]->ShowWindow(SW_SHOW);

	return 0;
}


//void CDialogMain::OnButtonGlobal()
//{
//	// TODO: �ڴ���������������
//	//SendMessage(NM_SWITCHDLG, 0);
//}
