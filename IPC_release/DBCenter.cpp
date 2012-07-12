// DBCenter.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IPC_release.h"
#include "DBCenter.h"


// CDBCenter
IMPLEMENT_DYNAMIC(CDBCenter, CObject)

// CDBCenter ���

#ifdef _DEBUG
void CDBCenter::AssertValid() const
{
	CObject::AssertValid();
}

void CDBCenter::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

CDBCenter::CDBCenter()
{
	CString strFolderPath = _T(".\\history");
	if (!PathIsDirectory(strFolderPath)) 
	{ 
		CreateDirectory(strFolderPath, NULL); 
	}
	
	CString dbFileName = _T(".\\history\\history.db");
	CString dbFile = _T("history.db");
	char * dbFile_c = "history.db";

	CString strInfo;
	//strInfo += GetCurTimeString();
	 char str[100];

	try
	{
		db = new CppSQLite3DB;
		//AfxMessageBox(dbFileName);
		CFileFind fFind;
		if(!fFind.FindFile(dbFileName))
		{
			theApp.Log(_T("δ�ҵ����ݿ��ļ����½�history.db"));
			//LPSTR str = CW2A(dbFile.GetBuffer());
			db->open(dbFileName);//�����ļ�
			theApp.Log(_T("history.db�������"));
			if(db->tableExists(_T("test_tbl")) == false)
			{
				theApp.Log(_T("No file, table do exist!"));
				db->execDML(_T("CREATE TABLE test_tbl(id INTEGER PRIMARY KEY AUTOINCREMENT,\
							byte0 TEXT(4), byte1 TEXT(4), byte2 TEXT(4), byte3 TEXT(4), byte4 TEXT(4), \
							byte5 TEXT(4), byte6 TEXT(4), byte7 TEXT(4));"));
				db->execDML(_T("insert into test_tbl (byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7) \
							values('0xFF', '0xFF','0xFF','0xFF','0xFF','0xFF','0xFF','0xFF')"));
				db->execDML(_T("insert into test_tbl (byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7) \
							values('0xAA', '0xAA','0xAA','0xAA','0xAA','0xAA','0xAA','0xAA')"));	
				db->execDML(_T("insert into test_tbl (byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7) \
							values('0xAA', '0xAA','0xAA','0xAA','0xAA','0xAA','0xAA','0xAA')"));	
				db->execDML(_T("insert into test_tbl (byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7) \
							values('0xAA', '0xAA','0xAA','0xAA','0xAA','0xAA','0xAA','0xAA')"));	
			}
			/*db->execDML("CREATE TABLE log_tbl(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,\
			   name TEXT(10), age INT(2));");*/
			//db->execDML("insert into log_tbl values(1, '�ῡ', 23)");
			strInfo += _T("����db�ɹ���\r\n");
		}
		else
		{
			//strcpy_s(str, (char *)dbFileName.GetBuffer());
			//AfxMessageBox((char *)dbFileName.GetBuffer());
			DeleteFile(dbFileName);//�����ļ�
			db->open(dbFileName);
			if(db->tableExists(_T("test_tbl")) == false)
			{
				theApp.Log(_T("File exist, table do exist!"));
				db->execDML(_T("CREATE TABLE test_tbl(id INTEGER PRIMARY KEY AUTOINCREMENT,\
							byte0 TEXT(4), byte1 TEXT(4), byte2 TEXT(4), byte3 TEXT(4), byte4 TEXT(4), \
							byte5 TEXT(4), byte6 TEXT(4), byte7 TEXT(4));"));
				db->execDML(_T("insert into test_tbl (byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7) \
							values('0xFF', '0xFF','0xFF','0xFF','0xFF','0xFF','0xFF','0xFF')"));
				db->execDML(_T("insert into test_tbl (byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7) \
							values('0xAA', '0xAA','0xAA','0xAA','0xAA','0xAA','0xAA','0xAA')"));	
				db->execDML(_T("insert into test_tbl (byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7) \
							values('0xAA', '0xAA','0xAA','0xAA','0xAA','0xAA','0xAA','0xAA')"));	
				db->execDML(_T("insert into test_tbl (byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7) \
							values('0xAA', '0xAA','0xAA','0xAA','0xAA','0xAA','0xAA','0xAA')"));	
				strInfo += _T("��db�ɹ���\r\n");
			}
		}
	}
	catch(CppSQLite3Exception& e)
	{
		AfxMessageBox(CString(e.errorMessage()));
	}

	//this->m_StringBuffer->
}

CDBCenter::~CDBCenter()
{
	this->Flush();
	delete db;
	db = 0;
}


// CDBCenter ��Ա����


int CDBCenter::WriteSQL(CString& sql)
{
	//SYSTEMTIME st;
	//CString strDate,strTime;
	//GetLocalTime(&st);

	//strDate.Format(_T("%4d-%2d-%2d"),st.wYear,st.wMonth,st.wDay);
	//strTime.Format(_T("%2d:%2d:%2d"),st.wHour,st.wMinute,st.wSecond);

	//CString text = strDate + _T(" ") + strTime + msg;
	m_DataQueue.AddTail(sql);

	/*if(m_DataQueue.GetCount() >= MaxQueue)
	{
		this->Flush();//����������ˢ�����ӳ����Ѷȣ�Ŀǰֻʵ�ֶ�ʱˢ��
	}*/

	return 0;
}

CDBCenter* CDBCenter::_instance = 0;

CDBCenter* CDBCenter::Instance()
{
	if(_instance == 0)
		_instance = new CDBCenter;
	return _instance;
}


void CDBCenter::Flush(void)
{
	//ֻˢ����ǰ�����е���Ϣ����ζ�Ż������������������Ϣ���������ٴ�ʱˢ��
	CSingleLock singleLock(&m_CritSection);
	if (singleLock.Lock())
	{
		int count = m_DataQueue.GetCount();
		for(int i = 0; i < count; i++)
		{
			CString sql = m_DataQueue.GetHead();
			this->db->execDML(sql);
			m_DataQueue.RemoveHead();  //������ˢ�����ݿ⣬��ɾ����ˢԪ��
		}

		singleLock.Unlock();
	}
}


CppSQLite3Query* CDBCenter::Query(CString szSQL)
{
	return db->execQuery(szSQL);
}


CppSQLite3Query* CDBCenter::QueryAll(void)
{
	return db->execQuery(_T("select * from test_tbl order by id;"));
}


void CDBCenter::WriteFmtMsg(CAN_MSG_T* msg)
{
	CString sql;
	sql.Format(_T("insert into test_tbl (byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7) \
				values('%2.2XH', '%2.2XH','%2.2XH','%2.2XH','%2.2XH','%2.2XH','%2.2XH','%2.2XH')"),
				msg->data[0], msg->data[1], msg->data[2], msg->data[3], msg->data[4], 
				msg->data[5], msg->data[6], msg->data[7]);
	this->WriteSQL(sql);
}


void CDBCenter::ExitInstance(void)
{
	if(_instance != 0)
		delete _instance;
}
