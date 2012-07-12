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

// IPC_releaseView.h : CIPC_releaseView ��Ľӿ�
//

#pragma once

#include "resource.h"

#include "MainFrm.h"
#include "DialogMain.h"
#include "IPC_releaseDoc.h"
#include <vector>

class CIPC_releaseView : public CFormView
{
protected: // �������л�����
	CIPC_releaseView();
	DECLARE_DYNCREATE(CIPC_releaseView)

public:
	enum{ IDD = IDD_IPC_RELEASE_FORM };

// ����
public:
	CIPC_releaseDoc* GetDocument() const;

// ����


// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CIPC_releaseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	CDialogMain m_wndDialog;
	int m_iMinWidth;
	int m_iMinHeight;

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnViewStationlist();
protected:
	afx_msg LRESULT OnNmSwitchdlg(WPARAM wParam, LPARAM lParam);
};

#ifndef _DEBUG  // IPC_releaseView.cpp �еĵ��԰汾
inline CIPC_releaseDoc* CIPC_releaseView::GetDocument() const
   { return reinterpret_cast<CIPC_releaseDoc*>(m_pDocument); }
#endif

