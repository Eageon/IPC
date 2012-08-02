#pragma once

#include "CppSQLite3.h"
#include "ADODatabase.h"
#include "MConfig.h"
//#include <list>

// CDBCenter ����Ŀ��

class CDBCenter : public CObject
{
	DECLARE_DYNAMIC(CDBCenter)

public:
	CDBCenter();
	virtual ~CDBCenter();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	
	IDBTarget *m_db;
	CppSQLite3DB *m_SQLitedb;
	CADODatabase *m_ADOdb;
	//IDatabase* db;
	CList<CString> m_DataQueue;
	int MaxQueue;
	

//Singleton
private:
	static CDBCenter *_instance;
public:
	static CDBCenter* Instance(void);
	

//����
private:
	CCriticalSection m_CritSection;

/***********************���ݿ����*********************************/
public:
	BOOL Query(CString szSQL);
	BOOL QueryAll(void);
	void WriteFmtMsg(CAN_MSG_T* msg);
	int WriteSQL(CString& sql);
	void Flush(void);

	void Config(CMConfig *m_config);
	static void ExitInstance(void);
};


