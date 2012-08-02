#pragma once


// CDialogDBSetting �Ի���

class CDialogDBSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogDBSetting)

public:
	CDialogDBSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogDBSetting();

// �Ի�������
	enum { IDD = IDD_DIALOG_ADOSETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit_SQLServer_PWD;
	CEdit m_edit_SQLServer_Usr;
	CEdit m_edit_SQLServer_Name;
	CIPAddressCtrl m_IP_SQLServer;
	afx_msg void OnBnClickedRadioSettingNative();
	afx_msg void OnBnClickedRadioSettingServer();

	BOOL m_bNativeDB;
	BOOL m_bServerDB;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	void EnableServerControls(BOOL m_bEnable);
};
