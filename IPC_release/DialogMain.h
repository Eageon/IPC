#pragma once

#include "stdafx.h"
#include "resource.h"
#include "DialogBasic.h"
#include "DialogPipeline.h"
#include "CANCenter.h"
#include "DialogData.h"
// CDialogMain �Ի���

class CDialogMain : public CDialog
{
	DECLARE_DYNAMIC(CDialogMain)

public:
	CDialogMain(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogMain();

// �Ի�������
	enum { IDD = IDD_DIALOG_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	CDialogPipeline m_dialogPipeline;//��������ͼ
	CDialogBasic m_dialogBasic;//����λ��ͼ
	CDialogData m_dialogData;//���ݿ���ͼ
	CDialog *pDialog[3];
	int m_CurSelTab;
	int m_iMinWidth;
	int m_iMinHeight;
	int m_iClientWidth;
	int m_iClientHeight;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	BOOL CreateTab(void);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	afx_msg LRESULT OnNmSwitchdlg(WPARAM wParam, LPARAM lParam);//�л���ͼ��Ӧ����
public:
//	afx_msg void OnButtonGlobal();
};
