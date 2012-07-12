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

// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "OutputWnd.h"
#include "StationListView.h"
#include "IPC_releaseView.h"
#include "resource.h"

//����Ribbon�ؼ���Ϣ��Ӧ����ӳ�䵽CMainFrame��
class CMainFrame : public CFrameWndEx
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
//public:

// ����
//public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;
	COutputWnd        m_wndOutput;
	CStationListView  m_wndStationView;

	//CIPC_releaseView *m_pIPC_ClassView;

//  ����
	//CTabCtrl *m_tab;
	

	BOOL CreateTabWindow();

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
public:
//	void OnClickTest(void);
//	afx_msg void OnButton2();
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnButtonGlobal();
//	afx_msg void OnButtonOpencan();
	afx_msg void OnButtonOpencan();
	afx_msg void OnButtonDataCheck();
	afx_msg void OnUpdateCheckRecvStandard(CCmdUI *pCmdUI);
	afx_msg void OnCheckRecvStandard();
	afx_msg void OnCheckRecvRemote();
	afx_msg void OnUpdateCheckRecvRemote(CCmdUI *pCmdUI);
	afx_msg void OnCheckSendStandard();
	afx_msg void OnUpdateCheckSendStandard(CCmdUI *pCmdUI);
	afx_msg void OnCheckSendRemote();
	afx_msg void OnUpdateCheckSendRemote(CCmdUI *pCmdUI);
	afx_msg void OnButtonSaveconfig();
};


