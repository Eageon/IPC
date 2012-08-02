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
	m_ADOdb = 0;
#if 0
	try
	{
		m_SQLitedb = new CppSQLite3DB;
		CFileFind fFind;
		if(!fFind.FindFile(dbFileName))
		{
			theApp.Log(_T("δ�ҵ����ݿ��ļ����½�history.db"));
			m_SQLitedb->open(dbFileName);//�����ļ�
			theApp.Log(_T("history.db�������"));
			if(m_SQLitedb->tableExists(_T("test_tbl")) == false)
			{
				theApp.Log(_T("No file, table do exist!"));
				m_SQLitedb->execDML(_T("CREATE TABLE test_tbl(id INTEGER PRIMARY KEY AUTOINCREMENT,\
							byte0 TEXT(4), byte1 TEXT(4), byte2 TEXT(4), byte3 TEXT(4), byte4 TEXT(4), \
							byte5 TEXT(4), byte6 TEXT(4), byte7 TEXT(4));"));
				m_SQLitedb->execDML(_T("insert into test_tbl (byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7) \
							values('0xFF', '0xFF','0xFF','0xFF','0xFF','0xFF','0xFF','0xFF')"));
				m_SQLitedb->execDML(_T("insert into test_tbl (byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7) \
							values('0xAA', '0xAA','0xAA','0xAA','0xAA','0xAA','0xAA','0xAA')"));	
				m_SQLitedb->execDML(_T("insert into test_tbl (byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7) \
							values('0xAA', '0xAA','0xAA','0xAA','0xAA','0xAA','0xAA','0xAA')"));	
				m_SQLitedb->execDML(_T("insert into test_tbl (byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7) \
							values('0xAA', '0xAA','0xAA','0xAA','0xAA','0xAA','0xAA','0xAA')"));	
			}
			/*db->execDML("CREATE TABLE log_tbl(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,\
			   name TEXT(10), age INT(2));");*/
			//db->execDML("insert into log_tbl values(1, '�ῡ', 23)");
			theApp.Log(_T("����db�ɹ���"));
		}
		else
		{
			//strcpy_s(str, (char *)dbFileName.GetBuffer());
			//AfxMessageBox((char *)dbFileName.GetBuffer());
			DeleteFile(dbFileName);//�����ļ�
			m_SQLitedb->open(dbFileName);
			if(m_SQLitedb->tableExists(_T("test_tbl")) == false)
			{
				theApp.Log(_T("File exist, table do exist!"));
				m_SQLitedb->execDML(_T("CREATE TABLE test_tbl(id INTEGER PRIMARY KEY AUTOINCREMENT,\
							byte0 TEXT(4), byte1 TEXT(4), byte2 TEXT(4), byte3 TEXT(4), byte4 TEXT(4), \
							byte5 TEXT(4), byte6 TEXT(4), byte7 TEXT(4));"));
				m_SQLitedb->execDML(_T("insert into test_tbl (byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7) \
							values('0xFF', '0xFF','0xFF','0xFF','0xFF','0xFF','0xFF','0xFF')"));
				m_SQLitedb->execDML(_T("insert into test_tbl (byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7) \
							values('0xAA', '0xAA','0xAA','0xAA','0xAA','0xAA','0xAA','0xAA')"));	
				m_SQLitedb->execDML(_T("insert into test_tbl (byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7) \
							values('0xAA', '0xAA','0xAA','0xAA','0xAA','0xAA','0xAA','0xAA')"));	
				m_SQLitedb->execDML(_T("insert into test_tbl (byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7) \
							values('����', '0xAA','0xAA','0xAA','0xAA','0xAA','0xAA','0xAA')"));	
				theApp.Log(_T("��db�ɹ���"));
			}
		}
	}
	catch(CppSQLite3Exception& e)
	{
		AfxMessageBox(CString(e.errorMessage()));
	}
#endif
	TCHAR *dbFileName = ".\\history\\history.db";
	TCHAR *dbFileFolder = ".\\history";

	try
	{
		m_SQLitedb = new CppSQLite3DB;
		m_db = m_SQLitedb;

		if (!PathIsDirectory(dbFileFolder)) 
		{ 
			CreateDirectory(dbFileFolder, NULL); 
		}
		CFileFind fFind;
		if(!fFind.FindFile(dbFileName))
		{
			theApp.Log(_T("δ�ҵ����ݿ��ļ����½�history.db"));
			m_SQLitedb->Open(dbFileName);//�����ļ�
			theApp.Log(_T("history.db�������"));
		}
		else
		{
			m_SQLitedb->Open(dbFileName);//���ļ�
			theApp.Log(_T("history.db�����"));
		}

		if(m_SQLitedb->tableExists(_T("test_tbl")) == false)
		{
			theApp.Log(_T("Neither file nor table do exist!"));
			m_SQLitedb->execDML(_T("CREATE TABLE test_tbl(id INTEGER PRIMARY KEY AUTOINCREMENT,\
						byte0 TEXT(4), byte1 TEXT(4), byte2 TEXT(4), byte3 TEXT(4), byte4 TEXT(4), \
						byte5 TEXT(4), byte6 TEXT(4), byte7 TEXT(4));"));
			m_SQLitedb->execDML(_T("insert into test_tbl (byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7) \
						values('0xFF', '0xFF','0xFF','0xFF','0xFF','0xFF','0xFF','0xFF')"));
			m_SQLitedb->execDML(_T("insert into test_tbl (byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7) \
						values('0xAA', '0xAA','0xAA','0xAA','0xAA','0xAA','0xAA','0xAA')"));	
			m_SQLitedb->execDML(_T("insert into test_tbl (byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7) \
						values('0xAA', '0xAA','0xAA','0xAA','0xAA','0xAA','0xAA','0xAA')"));	
			m_SQLitedb->execDML(_T("insert into test_tbl (byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7) \
						values('����', '0xAA','0xAA','0xAA','0xAA','0xAA','0xAA','0xAA')"));	
		}
			
		theApp.Log(_T("����db�ɹ���"));
	}
	catch(CppSQLite3Exception& e)
	{
		if(e.errorCode() == 1)
		{
			theApp.Log(CString(e.errorMessage()));
		}
		else
		{
			AfxMessageBox(CString(e.errorMessage()));
		}
	}

}

CDBCenter::~CDBCenter()
{
	this->Flush();

	if(m_SQLitedb != 0)
	{
		delete m_SQLitedb;
		m_SQLitedb = 0;
	}

	if(m_ADOdb != 0)
	{
		delete m_ADOdb;
		m_ADOdb = 0;
	}
	
	m_db = 0;
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
			m_db->Excute(sql);
			m_DataQueue.RemoveHead();  //������ˢ�����ݿ⣬��ɾ����ˢԪ��
		}

		singleLock.Unlock();
	}
}


BOOL CDBCenter::Query(CString szSQL)
{
	return m_db->Query(szSQL);
}


BOOL CDBCenter::QueryAll(void)
{
	return m_db->Query(_T("select * from test_tbl order by id;"));
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
