#pragma once
#include <vector>
#include <string>
using std::string;
using std::vector;

struct mapInfo
{
	int id;
	double longitude;
	double latitude;
	int pointtype;
	int namedid;
	int fillcolor;
};

class ConnectDatabase
{
private:
	vector<mapInfo> m_mapInfoArray;
	string m_ConnectionString;
	int m_RecordCount;
public:
	ConnectDatabase();
	~ConnectDatabase();
	void getRecordCount(int & RecordCount);
};

