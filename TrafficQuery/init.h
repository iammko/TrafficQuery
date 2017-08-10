#ifndef _INIT_H_
#define _INIT_H_

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define COACHPATH "coach.info"	//客车文件
#define TRAINPATH "train.info"	//动车文件

bool hasShortPath[MAX_VERTEX_NUM];
int Dist[MAX_VERTEX_NUM];
int Path[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

enum { BEIHAI, QINZHOU, NANNING, GUILIN, LIUZHOU, WUZHOU };
enum {TRAIN = 1, COACH};
enum {LEASTCOST = 1, LEASTTURNS};

//初始化图
ALGraph * init(int path);

//初始化边表
ArcNode ** initArcList(FILE * fp);

//获得边信息
int getArcInfo(int * pindexNum1, int * pindexNum2, ArcInfo * pinfo, FILE * fp);

//添加边节点
void addArcNode(ArcNode ** arcList, int tail, int head, ArcInfo info);

//初始化邻接表
void initAdjList(AdjList * trafficNet);

//初始化邻接表中的数据
void initAdjListData(const char * p, AdjList * trafficNet, int i);

//获得城市在图中的索引下标
int getIndex(const char * p);

#endif