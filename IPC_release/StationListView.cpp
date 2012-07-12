// StationListView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IPC_release.h"
#include "StationListView.h"
#include "MainFrm.h"
#include "IPC_releaseView.h"


// CStationListView

IMPLEMENT_DYNAMIC(CStationListView, CDockablePane)

CStationListView::CStationListView()
{
	m_nSelStation = 1;
}

CStationListView::~CStationListView()
{
}


BEGIN_MESSAGE_MAP(CStationListView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
//	ON_WM_LBUTTONDOWN()
ON_COMMAND(ID_POPUP_ITEM_CHECK, &CStationListView::OnPopupItemCheck)
END_MESSAGE_MAP()



// CStationListView ��Ϣ�������



void CStationListView::FillStationView(int nStation)
{
	m_wndStationView.InsertColumn(0,_T("��λ"),LVCFMT_LEFT,50); //������
	m_wndStationView.InsertColumn(1,_T("״̬"),LVCFMT_LEFT,50); //
	
	for(int i=0; i < nStation; i++)
	{
		m_wndStationView.InsertItem(i, _T(""));
		//m_wndStationView.InsertItem(1, _T("Build"));
		CString str;
		str.Format(_T("%d"), i+1);
		m_wndStationView.SetItemText(i, 0, str);
		m_wndStationView.SetItemText(i, 1, _T("����"));
	}
}

int CStationListView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// ������ͼ:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	if (!m_wndStationView.Create(dwViewStyle, rectDummy, this, 5))
	{
		TRACE0("δ�ܴ����ļ���ͼ\n");
		return -1;      // δ�ܴ���
	}

	LONG lStyle;
    lStyle = GetWindowLong(m_wndStationView.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
    lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
    lStyle |= LVS_REPORT; //����style
    SetWindowLong(m_wndStationView.m_hWnd, GWL_STYLE, lStyle);//����style

	// ������ͼͼ��:
	//m_FileViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	//m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);

	//OnChangeVisualStyle();


	// �������ͨ���˿ؼ�·�ɣ�������ͨ�������·��:
	//m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	// ����һЩ��̬����ͼ����(�˴�ֻ������������룬�����Ǹ��ӵ�����)
	m_wndStationView.SetExtendedStyle(LVS_EX_FLATSB
		| LVS_EX_FULLROWSELECT
		| LVS_EX_HEADERDRAGDROP
		| LVS_EX_ONECLICKACTIVATE
		| LVS_EX_GRIDLINES);
	

	FillStationView(CMConfig::Instance()->StationNBR);
	//AdjustLayout();


	return 0;
}


void CStationListView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (GetSafeHwnd() == NULL)
	{
		return;
	}
	
	CRect rectClient;
	GetClientRect(rectClient);
	m_wndStationView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + 1, rectClient.Width() - 2, rectClient.Height() - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}


void CStationListView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: �ڴ˴������Ϣ����������

	CListCtrl* pWndList = (CListCtrl*) &m_wndStationView;
	ASSERT_VALID(pWndList);

	if (pWnd != pWndList)
	{
		//CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// ѡ���ѵ�������:
		CPoint ptList = point;
		ScreenToClient(&ptList);

		UINT flags = 0;
		int hListItem = pWndList->HitTest(ptList, &flags);
		if (hListItem != -1)
		{
			pWndList->SetSelectionMark(hListItem);
			this->m_nSelStation = hListItem + 1;

			pWndList->SetFocus();
			CMenu menu;
			menu.LoadMenu(IDR_POPUP_STATION); //��ȡ��Դ
			menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON, point.x, point.y,this);
		}
	}

}


void CStationListView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDockablePane::OnPaint()
	CRect rectList;
	m_wndStationView.GetWindowRect(rectList);
	ScreenToClient(rectList);

	rectList.InflateRect(1, 1);
	dc.Draw3dRect(rectList, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}


void CStationListView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	// TODO: �ڴ˴������Ϣ����������
	m_wndStationView.SetFocus();
}


void CStationListView::OnHello()
{
	// TODO: �ڴ���������������
}


//void CStationListView::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	CStationView* pWndList = (CStationView*) &m_wndStationView;
//	ASSERT_VALID(pWndList);
//	//AfxMessageBox(_T("test"));
//
//	if (point != CPoint(-1, -1))
//	{
//		// ѡ���ѵ�������:
//		CPoint ptList = point;
//		ScreenToClient(&ptList);
//
//		UINT flags = 0;
//		int hListItem = pWndList->HitTest(ptList, &flags);
//		if (hListItem != -1)
//		{
//			int re = pWndList->SetSelectionMark(hListItem);
//
//			pWndList->SetFocus();
//			LVCOLUMN column;
//			pWndList->GetColumn(hListItem, &column);
//			CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
//			CIPC_releaseView *pView=(CIPC_releaseView *)pMain->GetActiveView();
//			pView->m_wndDialog.PostMessage(NM_SWITCHDLG, 1, 0);
//			AfxMessageBox(_T("test"));
//		}
//	}
//
//	CDockablePane::OnLButtonDown(nFlags, point);
//}


void CStationListView::OnPopupItemCheck()
{
	// TODO: �ڴ���������������

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	CIPC_releaseView *pView=(CIPC_releaseView *)pMain->GetActiveView();
	pView->m_wndDialog.PostMessage(NM_SWITCHDLG, 1, 0);	//���Ż�������Ѿ��ɼ������ػ�
}
