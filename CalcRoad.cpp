#include "stdafx.h"
#include "CalcRoad.h"


CalcRoad::CalcRoad(void)
{
	CreateGraph(G);
}


CalcRoad::~CalcRoad(void)
{
}


void CalcRoad::CreateGraph(graph& G)
{
	G.locarr[0].locinfo.index = 1;
	G.locarr[0].locinfo.loacalname = "食堂";
	G.locarr[0].locinfo.loccoord.x = 50;
	G.locarr[0].locinfo.loccoord.y = 50;
	CreateConnect(G.locarr[0], 2, 500);
	CreateConnect(G.locarr[0], 3, 400);
	
	G.locarr[1].locinfo.index = 2;
	G.locarr[1].locinfo.loacalname = "宿舍";
	G.locarr[1].locinfo.loccoord.x = 450;
	G.locarr[1].locinfo.loccoord.y = 350;
	CreateConnect(G.locarr[1], 1, 500);
	CreateConnect(G.locarr[1], 3, 400);

	G.locarr[2].locinfo.index = 3;
	G.locarr[2].locinfo.loacalname = "教室";
	G.locarr[2].locinfo.loccoord.x = 50;
	G.locarr[2].locinfo.loccoord.y = 350;
	CreateConnect(G.locarr[2], 1, 300);
	CreateConnect(G.locarr[2], 2, 400);


}


void CalcRoad::CreateConnect(local& mylocal, int locpnnum, int locpath)
{
	nextlocal* tempnxtloc = new nextlocal;
	for(int i = 0; i < MAXNUM; i++)
	{
		mylocal.nextloc = NULL;
	}
	tempnxtloc->locpntnum = locpnnum;
	tempnxtloc->locpath = locpath;
	tempnxtloc->nxtloc = mylocal.nextloc;
	mylocal.nextloc = tempnxtloc;
}


void CalcRoad::CreateMarix(graph& G)
{
	for(int i = 0; i < MAXNUM; i++)
	{
		for(int j = 0; j < MAXNUM; j++)
		{
			G.maxtrix[i][j] = INFINITE;
		}
	}
}
