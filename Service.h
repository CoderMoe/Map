#ifndef SERVICE_H_INCLUDED
#define SERVICE_H_INCLUDED
#include "Graphy.h"
#include <stdio.h>
#include <string>
void printPath(MGraph G,Path P,int destination)
{
    cout << G.siteList[destination].data.siteName << "<----";
    while(P[destination] != -1)
    {
        cout << P[destination];
        destination = P[destination];
        cout << G.siteList[destination].data.siteName << "<----";
    }
    cout << "你所在的位置";
    cout << endl;
}

void findWay(MGraph G)
{
    int resourse,destination;
    Path P;
    ShortPathTable D;
    cout << "请输入出发点和目标点编号：" << endl;
    cin >> resourse;
    findMinWay(G,resourse,P,D);
    cin >> destination;
    cout << "最短路径为：" << D[destination-1] << endl;
    printPath(G,P,destination-1);

}



void schoolSerive(MGraph &M)
{
    int choice = 1;
    while(choice)
    {
        cout << "****************欢迎使用校园导航系统*******************" << endl;
        cout << "*      1.查看地图         *" << endl;
        cout << "*      2.查询地点信息     *" << endl;
        cout << "*      3.问路查询         *" << endl;
        cout << "*      4.退出系统         *" << endl;
        cin >> choice;
        switch(choice)
        {
            case 1:
                showGraphy(M.siteList);
                    break;
            case 2:
                showSite(M.siteList);
                    break;
            case 3:
                findWay(M);
                    break;
            case 4:
                cout << "欢迎使用！" << endl;
                choice = 0;
                    break;
            default :
                cout << "输入无效" << endl;
                break;
        }
        while(getchar()!= '\n') {}
    }

}
#endif // SERVICE_H_INCLUDED
