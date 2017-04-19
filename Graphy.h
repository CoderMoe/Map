#ifndef GRAPHY_H_INCLUDED
#define GRAPHY_H_INCLUDED
#define MAX_VERTEX_NUM 17
#define TRUE 1
#define FALSE 0
#define INFINITY 10000
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

typedef int InfoTupe;       //路径的长度

typedef int Status;

typedef int ArcMatriz[MAX_VERTEX_NUM][MAX_VERTEX_NUM];      //图的相邻矩阵

typedef int ShortPathTable[MAX_VERTEX_NUM];                 //存放起点到其余每个顶点的最短路径的值

typedef int Path[MAX_VERTEX_NUM];         //记录路径的数组

typedef struct VertexTyoe {
    int index;      //地点编号
    string siteName;  //地名
}VertexTyoe;

typedef struct ArcNode {//弧（此处为道路信息）
    int   adjvex;                   //该弧所指向的顶点的位置(此处为道路通往的地点)
    struct ArcNode *nextarc;        //指向下一条弧的指针（此处为下一条通往该地点的道路）
    InfoTupe info;                 //该弧相关信息（此处为道路的长度）
}ArcNode;

typedef struct VNode {//顶点（此处为地点）
    VertexTyoe data;                 //顶点信息（此次为地点名称）
    ArcNode * firstarc;              //指向第一条依附该顶点的弧的指针（此次为通往该地点的道路）
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct MGraph { //图
    ArcMatriz arcMatriz;
    AdjList siteList;
}MGraph;

/*
*往弧链表后面添加弧结点
*@param  vNode   需要添加弧结点的顶点
*@param  adjvex  添加弧结点指向的顶点编号
*@param  info    添加弧结点的权值
*/
void addArcNode(VNode &vNode,int adjvex,int info)
{
    ArcNode *newArc = (ArcNode*)malloc(sizeof(ArcNode));
    if(!newArc)
        exit(0);
    newArc->adjvex = adjvex;
    newArc->info = info;
    newArc->nextarc = vNode.firstarc;
    vNode.firstarc = newArc;
}

/*
*生成邻接矩阵
*@param M   传入的图的引用
*/
void createArcsMatriz(MGraph &M)
{
    for(int i = 0; i < MAX_VERTEX_NUM;i++)
        for(int j = 0; j < MAX_VERTEX_NUM;j++)
            M.arcMatriz[i][j] = INFINITY;

    for(int i = 0; i < MAX_VERTEX_NUM;i++)
    {
        ArcNode *temp = M.siteList[i].firstarc;
        while(temp != NULL)
        {
            M.arcMatriz[i][temp->adjvex-1] = temp->info;
            temp = temp->nextarc;
        }
    }
}

/*
*展示图的邻接矩阵
*@param M  需要展示的图
*/
void showArcsMatriz(MGraph M)
{
    for(int i = 0;i < MAX_VERTEX_NUM;i++)
        for(int j = 0;j < MAX_VERTEX_NUM;j++)
        {
            cout << M.arcMatriz[i][j] << "\t";
        }
}


/*
*生成图
*@param siteList 图结构的引用
*/
void createGraphy(MGraph & M)
{
    for(int i = 0;i < MAX_VERTEX_NUM;i++)
    {
        M.siteList[i].firstarc = NULL;
    }
    M.siteList[0].data.index = 1;
    M.siteList[0].data.siteName = "出入口";
    addArcNode(M.siteList[0],2,20);
    addArcNode(M.siteList[0],5,20);

    M.siteList[1].data.index = 2;
    M.siteList[1].data.siteName = "研究院";
    addArcNode(M.siteList[1],1,20);
    addArcNode(M.siteList[1],3,30);


    M.siteList[2].data.index = 3;
    M.siteList[2].data.siteName = "后勤";
    addArcNode(M.siteList[2],2,30);
    addArcNode(M.siteList[2],4,20);
    addArcNode(M.siteList[2],6,30);

    M.siteList[3].data.index = 4;
    M.siteList[3].data.siteName = "留学生公寓";
    addArcNode(M.siteList[3],3,20);


    M.siteList[4].data.index = 5;
    M.siteList[4].data.siteName = "音乐广场";
    addArcNode(M.siteList[4],1,20);
    addArcNode(M.siteList[4],6,10);


    M.siteList[5].data.index = 6;
    M.siteList[5].data.siteName = "H楼";

    addArcNode(M.siteList[5],3,30);
    addArcNode(M.siteList[5],5,10);
    addArcNode(M.siteList[5],7,20);
    addArcNode(M.siteList[5],8,50);

    M.siteList[6].data.index = 7;
    M.siteList[6].data.siteName = "G楼";
    addArcNode(M.siteList[6],6,20);
    addArcNode(M.siteList[6],8,40);
    addArcNode(M.siteList[6],9,10);

    M.siteList[7].data.index = 8;
    M.siteList[7].data.siteName = "五公寓";
    addArcNode(M.siteList[7],6,50);
    addArcNode(M.siteList[7],7,40);
    addArcNode(M.siteList[7],10,20);
    addArcNode(M.siteList[7],11,20);


    M.siteList[8].data.index = 9;
    M.siteList[8].data.siteName = "M楼";
    addArcNode(M.siteList[8],7,10);
    addArcNode(M.siteList[8],10,20);
    addArcNode(M.siteList[8],14,30);

    M.siteList[9].data.index = 10;
    M.siteList[9].data.siteName = "三公寓";
    addArcNode(M.siteList[9],8,20);
    addArcNode(M.siteList[9],9,20);
    addArcNode(M.siteList[9],11,20);

    M.siteList[10].data.index = 11;
    M.siteList[10].data.siteName = "四公寓";
    addArcNode(M.siteList[10],8,20);
    addArcNode(M.siteList[10],10,20);
    addArcNode(M.siteList[10],12,20);

    M.siteList[11].data.index = 12;
    M.siteList[11].data.siteName = "六公寓";
    addArcNode(M.siteList[11],11,20);
    addArcNode(M.siteList[11],13,10);

    M.siteList[12].data.index = 13;
    M.siteList[12].data.siteName = "学子餐厅";
    addArcNode(M.siteList[12],12,10);
    addArcNode(M.siteList[12],16,20);

    M.siteList[13].data.index = 14;
    M.siteList[13].data.siteName = "七公寓";
    addArcNode(M.siteList[13],9,30);
    addArcNode(M.siteList[13],15,20);

    M.siteList[14].data.index = 15;
    M.siteList[14].data.siteName = "八公寓";
    addArcNode(M.siteList[14],14,20);
    addArcNode(M.siteList[14],16,20);

    M.siteList[15].data.index = 16;
    M.siteList[15].data.siteName = "九公寓";
    addArcNode(M.siteList[15],13,20);
    addArcNode(M.siteList[15],15,20);
    addArcNode(M.siteList[15],17,40);

    M.siteList[16].data.index = 17;
    M.siteList[16].data.siteName = "N楼";
    addArcNode(M.siteList[16],16,40);

    createArcsMatriz(M);        //建立邻接矩阵
}

/*
*展现顶点所以的弧
*@param vNode 需要展示的顶点
*/
void showArc(VNode vNode)
{
    ArcNode *temp = vNode.firstarc;
    while(temp != NULL)
    {
        cout << "(" << temp->adjvex << "," << temp->info << ")   ";
        temp = temp->nextarc;
    }
}

/*
*展现地图
*@param siteList 需要展示的图
*/
void showGraphy(AdjList siteList)
{
    cout << "哈尔滨工业大学（威海）地形图 \n" << endl;
    cout << "17|" << endl;
    cout << "16| ------ 13|" << endl;
    cout << "15|        12|" << endl;
    cout << "14|        11|--------8___         |4" << endl;
    cout << "  |        10|--------|    |       |"  << endl;
    cout << "  |________9|________7|__|6_______|3" << endl;
    cout << "                          |        | " << endl;
    cout << "                          |5       | " << endl;
    cout << "                          |       2| " << endl;
    cout << "                          |    _|" << endl;
    cout << "                          1_|" << endl;
}

/*
*展现全图的地点信息
*@param siteList 需要展示的图
*/
void showSite(AdjList siteList)
{
    cout << " 地点编号        （可以通往地点编号，路径长度）  " << endl;
    for(int i = 0; i < 17;i++)
    {
        cout << siteList[i].data.index << " :" << siteList[i].data.siteName << "    ";
        showArc(siteList[i]);
        cout << endl;
    }
}
/*
*找出两点间的最短路径
*@param  G              地图信息
*@param  resourse       起点的编号
*@param  P              记录路径的数组
*@param  ShortPathTable 存放到起点每个顶点最路径的值
*/
void findMinWay(MGraph G,int resourse,Path &P,ShortPathTable &D)
{
    int v,min;
    Status final[MAX_VERTEX_NUM];                //判断顶点是否加入S表，若为TRUE，则该顶点在S表里面
    for(v = 0; v < MAX_VERTEX_NUM;v++)
    {
        final[v] = FALSE;                        //将所有的点都加入到S-V表
        D[v] = G.arcMatriz[resourse-1][v];      //若顶点到起点可达，将权值赋值给D[v],不可达，D[v]为正无穷
        P[v] = -1;  //设空路径
        if(D[v] < INFINITY)                      //若顶点到起点的值不是正无穷，说明可达
        {
            P[v] = resourse-1;
        }
    }
    D[resourse-1] = 0;                           //出发点到出发点的距离当然是0
    final[resourse-1] = TRUE;                    //初始化，resourse顶点属于S集
    P[resourse-1] = -1;
    for(int i = 1;i < MAX_VERTEX_NUM;i++)
    {
        min = INFINITY;
        for(int w = 0;w < MAX_VERTEX_NUM;w++)
            if(!final[w])                       //遍历V-S表中所有的顶点，从可达起点的点中找出权最小的点
                if(D[w] < min)
                {
                    v = w;
                    min = D[w];
                }
        final [v] = TRUE;                       //将找出的顶点加入到S表
        for(int w = 0;w < MAX_VERTEX_NUM;w++)   //更新D中的数据
        {
            if(!final[w] && min < INFINITY && G.arcMatriz[v][w] < INFINITY && (min + G.arcMatriz[v][w] < D[w]))
            {   //在S表中寻找当前顶点可达的顶点，并比较权值的大小
                D[w] = min + G.arcMatriz[v][w];
                P[w] = v;
            }
        }

    }
}

#endif // GRAPHY_H_INCLUDED
