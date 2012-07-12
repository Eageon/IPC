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

// IPC_releaseView.cpp : CIPC_releaseView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "IPC_release.h"
#endif

#include "IPC_releaseDoc.h"
#include "IPC_releaseView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIPC_releaseView

IMPLEMENT_DYNCREATE(CIPC_releaseView, CFormView)

BEGIN_MESSAGE_MAP(CIPC_releaseView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_STATIONLIST, &CIPC_releaseView::OnViewStationlist)
	ON_MESSAGE(NM_SWITCHDLG, &CIPC_releaseView::OnNmSwitchdlg)
END_MESSAGE_MAP()

// CIPC_releaseView ����/����

CIPC_releaseView::CIPC_releaseView()
	: CFormView(CIPC_releaseView::IDD)
{
	// TODO: �ڴ˴���ӹ������
	//m_pFrame = NULL; 
}

CIPC_releaseView::~CIPC_releaseView()
{
}

void CIPC_releaseView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CIPC_releaseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void CIPC_releaseView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

}

void CIPC_releaseView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CIPC_releaseView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CIPC_releaseView ���

#ifdef _DEBUG
void CIPC_releaseView::AssertValid() const
{
	CFormView::AssertValid();
}

void CIPC_releaseView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CIPC_releaseDoc* CIPC_releaseView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIPC_releaseDoc)));
	return (CIPC_releaseDoc*)m_pDocument;
}
#endif //_DEBUG


// CIPC_releaseView ��Ϣ�������




//BOOL CIPC_releaseView::CreateTab(void)
//{
//	
//
//	return TRUE;
//}


int CIPC_releaseView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	CRect rect;
	GetClientRect(rect);
	
	m_wndDialog.Create(IDD_DIALOG_MAIN,this);
	CRect tmpRect;
	m_wndDialog.GetWindowRect(tmpRect);
	this->m_iMinHeight = tmpRect.Height();
	this->m_iMinWidth = tmpRect.Width();
	//m_wndDialog.MoveWindow(rect);
	m_wndDialog.ShowWindow(SW_SHOW);
	
	return 0;
}





void CIPC_releaseView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	CRect rect;
	GetClientRect(&rect);
	if(rect.Height() < this->m_iMinHeight)
		rect.bottom = rect.top + this->m_iMinHeight;
	if(rect.Width() < this->m_iMinWidth)
		rect.right = rect.left + this->m_iMinWidth;
	//m_wndDialog.MoveWindow(&rect);
	m_wndDialog.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}


//void CIPC_releaseView::OnButton_Single()
//{
//	// TODO: �ڴ���������������
//
//}


//void CIPC_releaseView::OnButton_AC()
//{
//	// TODO: �ڴ���������������
//
//}


void CIPC_releaseView::OnViewStationlist()
{
	// TODO: �ڴ���������������
	//AfxMessageBox(_T("asdfsdf"));
}


//afx_msg LRESULT CIPC_releaseView::OnMmListselect(WPARAM wParam, LPARAM lParam)
//{
//	pDialog[1]->ShowWindow(SW_HIDE);
//	m_wndTab.SetCurSel(1);
//	pDialog[0]->ShowWindow(SW_SHOW);
//	return 0;
//}


afx_msg LRESULT CIPC_releaseView::OnNmSwitchdlg(WPARAM wParam, LPARAM lParam)
{
	m_wndDialog.PostMessage(NM_SWITCHDLG, wParam, lParam);
	
	return 0;
}
