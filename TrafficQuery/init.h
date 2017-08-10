#ifndef _INIT_H_
#define _INIT_H_

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define COACHPATH "coach.info"	//�ͳ��ļ�
#define TRAINPATH "train.info"	//�����ļ�

bool hasShortPath[MAX_VERTEX_NUM];
int Dist[MAX_VERTEX_NUM];
int Path[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

enum { BEIHAI, QINZHOU, NANNING, GUILIN, LIUZHOU, WUZHOU };
enum {TRAIN = 1, COACH};
enum {LEASTCOST = 1, LEASTTURNS};

//��ʼ��ͼ
ALGraph * init(int path);

//��ʼ���߱�
ArcNode ** initArcList(FILE * fp);

//��ñ���Ϣ
int getArcInfo(int * pindexNum1, int * pindexNum2, ArcInfo * pinfo, FILE * fp);

//��ӱ߽ڵ�
void addArcNode(ArcNode ** arcList, int tail, int head, ArcInfo info);

//��ʼ���ڽӱ�
void initAdjList(AdjList * trafficNet);

//��ʼ���ڽӱ��е�����
void initAdjListData(const char * p, AdjList * trafficNet, int i);

//��ó�����ͼ�е������±�
int getIndex(const char * p);

#endif