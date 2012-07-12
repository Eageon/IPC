#pragma once

#include "StaticLED.h"
#include "CANCenter.h"
#include <vector>
// CDialogPipeline �Ի���

#include "NotifyClass.h"
//#define ID_CLASS_LED 1

class CDialogPipeline : public CDialog
{
	DECLARE_DYNAMIC(CDialogPipeline)

public:
	CDialogPipeline(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogPipeline();

// �Ի�������
	enum { IDD = IDD_DIALOG_PIPELINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStaticLED m_LED_1;       //���й�λ��״̬��
	CStaticLED m_LED_10;
	CStaticLED m_LED_11;
	CStaticLED m_LED_12;
	CStaticLED m_LED_13;
	CStaticLED m_LED_14;
	CStaticLED m_LED_15;
	CStaticLED m_LED_16;
	CStaticLED m_LED_17;
	CStaticLED m_LED_18;
	CStaticLED m_LED_19;
	CStaticLED m_LED_2;
	CStaticLED m_LED_3;
	CStaticLED m_LED_4;
	CStaticLED m_LED_5;
	CStaticLED m_LED_6;
	CStaticLED m_LED_7;
	CStaticLED m_LED_8;
	CStaticLED m_LED_9;

	//vector<CStaticLED *> *m_LED_set;
	CStaticLED *m_LED_set[19];


	afx_msg void OnPaint();

protected:
	afx_msg LRESULT OnNmNotifyctrl(WPARAM wParam, LPARAM lParam);
private:
	int NotifyStatus(int status);
	void BuildCollection(void);
};
