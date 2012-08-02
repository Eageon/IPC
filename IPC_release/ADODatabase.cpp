#include "StdAfx.h"
#include "ADODatabase.h"


CADODatabase::CADODatabase(void)
{
}


CADODatabase::~CADODatabase(void)
{
	m_pConnection->Close();
	m_pConnection.Release();
	m_pRecordset->Close();
	m_pRecordset.Release();
}


BOOL CADODatabase::Open(LPCTSTR DbString, LPCTSTR UserID, LPCTSTR Password)
{
	return OpenConnection(DbString, UserID, Password);
}


BOOL CADODatabase::OpenConnection(CString strConnection, CString UserID, CString Password)
{
	HRESULT hr = ::CoInitialize(NULL);
	if (!SUCCEEDED(hr)) // ��ʼ��ʧ��
	{
		TRACE(_T("��ʼ��COMʧ��\n"));
		return FALSE;
	}

	_bstr_t strConnect(strConnection);
	_bstr_t strUserID(UserID);
	_bstr_t strPassword(Password);

	try
	{
		// ����Connection����
		hr = m_pConnection.CreateInstance("ADODB.Connection");
		
		if (SUCCEEDED(hr))
		{
			// �������ݿ�
			if (SUCCEEDED(m_pConnection->Open(strConnect, strUserID, strPassword, adModeReadWrite)))
			{
				return TRUE;
			}
		}
	}
	catch (_com_error e)
	{
		TRACE(_T("�������ݿⷢ������%s\n"), e.ErrorMessage());
	}
	
	return FALSE;
}


BOOL CADODatabase::Close(void)
{
	if(CloseConnection()==FALSE)
	{
		AfxMessageBox(_T("�ر����ݿ����"));
		return FALSE;
	}
	return TRUE;
}


BOOL CADODatabase::CloseConnection(void)
{
	if (m_pConnection == NULL)
	{
		// ��������Ѿ�Ϊ��
		return TRUE;
	}
	try
	{
		m_pConnection->Close();
		m_pConnection = NULL;
		return TRUE;
	}
	catch (_com_error e)
	{
		TRACE(_T("�ر����ݿⷢ������%s\n"), e.ErrorMessage());
	}
	return FALSE;
}


_RecordsetPtr CADODatabase::Select(CString sql)
{
	_bstr_t CommandText(sql);  // ����Ҫִ�е�sql����ַ���
	m_pRecordset.CreateInstance("ADODB.Recordset");  // ����_RecordsetPtrʵ��
	m_pRecordset->Open(CommandText,  // �������ݿ��ѯ
		m_pConnection.GetInterfacePtr(),
		adOpenDynamic,
		adLockBatchOptimistic,
		adCmdText);
	return m_pRecordset;
}


BOOL CADODatabase::Excute(LPCTSTR sql)
{
	_bstr_t CommandText(sql);
	_variant_t RecordsAffected;
	m_pConnection->Execute(CommandText, &RecordsAffected, adCmdText);
	return TRUE;
}


BOOL CADODatabase::Query(LPCTSTR sql)
{
	return FALSE;
}


BOOL CADODatabase::DbEOF(void)
{
	return this->m_pRecordset->adoEOF;
}


void CADODatabase::NextRow(void)
{
	//TODO: insert return statement here
	m_pRecordset->MoveNext();
}


LPCTSTR CADODatabase::GetFieldByString(LPCTSTR field)
{
	//TODO: insert return statement here
	_bstr_t FieldText(field);
	CString temp = m_pRecordset->GetCollect(FieldText);
	return temp;
}

LPCTSTR CADODatabase::GetFieldByIndex(int index)
{
	//TODO: insert return statement here
	//_bstr_t FieldText(field);
	//CString temp = m_pRecordset->GetCollect(FieldText);
	CString temp = m_pRecordset->GetCollect(index);
	return temp;
}

void CADODatabase::Finalize(void)
{
}

void CADODatabase::Reset(void)
{
}