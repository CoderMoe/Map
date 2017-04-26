#include <string>
#pragma once
#define MAXNUM 3
#define INFINITE 10000
using std::string;


struct nextlocal
{
	int locpntnum;
	int locpath;
	nextlocal* nxtloc;
};
struct localinfo
{
	int index;
	string loacalname;
	POINT loccoord;
};
typedef struct local
{
	localinfo locinfo;
	nextlocal* nextloc;
}loc[MAXNUM];
struct graph
{
	int maxtrix[MAXNUM][MAXNUM];
	loc locarr;
};
class CalcRoad
{
public:
	CalcRoad(void);
	~CalcRoad(void);
private:
	
public:
	graph G;
	void CreateGraph(graph& G);
	void CreateConnect(local& mylocal, int locpnnum, int locpath);
	void CreateMarix(graph& G);
};

