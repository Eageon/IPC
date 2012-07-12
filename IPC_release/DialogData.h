#pragma once


// CDialogData �Ի���

class CDialogData : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogData)

public:
	CDialogData(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogData();

// �Ի�������
	enum { IDD = IDD_DIALOG_DATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//CListCtrl m_wndListCtrl;
	CDateTimeCtrl m_DateFrom;
	CDateTimeCtrl m_DateTo;
	CDateTimeCtrl m_TimeFrom;
	CDateTimeCtrl m_TimeTo;
	CListCtrl m_ListDB;
	virtual BOOL OnInitDialog();
protected:
	void AdjustColumnWidth(void);
public:
	afx_msg void OnBnClickedButtonDbQueryAll();  //��ѯ���ݿ�����������
	afx_msg void OnBnClickedButtonDblistClear();
};
