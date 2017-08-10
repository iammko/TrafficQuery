#ifndef _GRAPH_H_
#define _GRAPH_H_

#define MAX_VERTEX_NUM 6
#define INFINITY (INT_MAX/2)


typedef struct ArcInfo
{
	int cost;
	int time;
}ArcInfo;

typedef struct ArcNode
{
	int adjVex;					// 该弧所指向的顶点的所在位置
	ArcInfo * info;				// 该弧相关的信息的指针 这里用费用权重
	struct ArcNode * nextArc;	// 指向下一条弧的指针
}ArcNode;

typedef struct VNode
{
	char * data;				// 顶点数据类型
	ArcNode * firstArc;			// 指向依附于该顶点第一条弧的 指针   
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct
{
	AdjList vertices;
	ArcInfo arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int vexnum, arcNum;			// 图的当前顶点数量，弧数量
	//int trainArcNum;
	//int coachArcNum;
	//int kind;					// 图的种类
}ALGraph;

void CreateGraph(ALGraph * G, AdjList V, ArcNode ** ArcList);

void DestroyGraph(ALGraph * G);

int LocateVex(const ALGraph * G, char * u);

VNode GetVex(const ALGraph * G, VNode v);

void PutVex(ALGraph * G, VNode v, char * value);

VNode FirstAdjVex(const ALGraph * G, VNode v);

VNode NextAdjVex(const ALGraph * G, VNode v,VNode W);

void InsertVex(ALGraph * G, VNode v);

void DeleteVex(ALGraph * G, VNode v);

void InsertArc(ALGraph * G, VNode v,VNode W);

void DeleteArc(ALGraph * G, VNode v,VNode W);

//DFSTraverse(const ALGraph * G, 

#endif



