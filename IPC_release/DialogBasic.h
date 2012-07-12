#pragma once


#include "NotifyClass.h"

// CDialogBasic �Ի���

class CDialogBasic : public CDialog
{
	DECLARE_DYNAMIC(CDialogBasic)

public:
	CDialogBasic(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogBasic();

// �Ի�������
	enum { IDD = IDD_DIALOG_BASIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit_Vy;  //ֱ����ϵ���ؼ�
	CEdit m_edit_Vz;
	CEdit m_edit_z;
	CEdit m_edit_to_x;
	CEdit m_edit_to_y;
	CEdit m_edit_to_z;
	CEdit m_edit_Vx;
	CEdit m_edit_x;
	CEdit m_edit_y;

	CEdit *m_edit_set[9];

	/*CString m_Vy;
	CString m_Vz;
	CString m_z;
	CString m_to_x;
	CString m_to_y;
	CString m_to_z;
	CString m_Vx;
	CString m_x;
	CString m_y;*/
	

protected:
	afx_msg LRESULT OnNmNotifyctrl(WPARAM wParam, LPARAM lParam);//�Զ�����Ϣ��Ӧ����������֪ͨ��Ӧ�ؼ�����X��������ֵ�ı� 
private:
	void BuildCollection(void);
};
