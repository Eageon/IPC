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

// IPC_release.h : IPC_release Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "MConfig.h"
#include "Monitor.h"
#include "CANCenter.h"
#include "DBCenter.h"
#include "ADO.h"

// CIPC_releaseApp:
// �йش����ʵ�֣������ IPC_release.cpp
//

class CIPC_releaseApp : public CWinAppEx
{
public:
	CIPC_releaseApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:
	CStationManager *m_StationMngr;
	CMonitor m_Monitor;

	int SelStation;   //��ѡ�еĹ�λ

public:
	CWinThread *m_threadCANRead;
	CWinThread *m_threadCANWrite;
	CWinThread *m_threadDBWrite;   //���ݿ��߳�

private:
	void InitStationClass(void);
public:
	void Log(CString info);
	int ExitStationClass(void);
};

extern CIPC_releaseApp theApp;

UINT ThreadCANRead(LPVOID pThreadParam);
UINT ThreadCANWrite(LPVOID pThreadParam);
UINT ThreadDBWrite(LPVOID pThreadParam);