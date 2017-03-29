
#include "ConnectDatabase.h"


ConnectDatabase::ConnectDatabase()
{
	CoInitialize(NULL);//³õÊ¼»¯COM¿â
	m_ConnectionString = "Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=Test;Data Source=ELITE";
}


ConnectDatabase::~ConnectDatabase()
{
	CoUninitialize();//Ð¶ÔØCOM¿â
}

void ConnectDatabase::getRecordCount(int & RecordCount)
{
	_ConnectionPtr pConn(__uuidof(Connection));
	_RecordsetPtr PRst(__uuidof(Recordset));
	pConn->ConnectionString = m_ConnectionString;
	pConn->Open("", "", "", adConnectUnspecified);

}