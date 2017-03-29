
#include "ConnectDatabase.h"


ConnectDatabase::ConnectDatabase()
{
	CoInitialize(NULL);//��ʼ��COM��
	m_ConnectionString = "Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=Test;Data Source=ELITE";
}


ConnectDatabase::~ConnectDatabase()
{
	CoUninitialize();//ж��COM��
}

void ConnectDatabase::getRecordCount(int & RecordCount)
{
	_ConnectionPtr pConn(__uuidof(Connection));
	_RecordsetPtr PRst(__uuidof(Recordset));
	pConn->ConnectionString = m_ConnectionString;
	pConn->Open("", "", "", adConnectUnspecified);

}