#include "graph.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int getCost(int w, VNode vex)
{
	ArcNode * cur = vex.firstArc;
	while (cur != NULL)
	{
		if (cur->adjVex == w)
			return cur->info->cost;

		cur = cur->nextArc;
	}

	return INFINITY;
}

int getTime(int w, VNode vex)
{
	ArcNode * cur = vex.firstArc;
	while (cur != NULL)
	{
		if (cur->adjVex == w)
			return cur->info->time;

		cur = cur->nextArc;
	}

	return INFINITY;
}

void CreateGraph(ALGraph * G, AdjList V, ArcNode ** Arclist)
{
	G->vexnum = MAX_VERTEX_NUM;
	
	int arcNum = 0;
	ArcNode * tmp = NULL;
	for (int i = 0; i < MAX_VERTEX_NUM; ++i)
	{
		V[i].firstArc = Arclist[i];
		tmp = Arclist[i];
		while (tmp != NULL)
		{
			//printf("%d ", tmp->info);
			++arcNum;
			tmp = tmp->nextArc;
		}
		
		for (int j = 0; j < MAX_VERTEX_NUM; ++j)
		{
			G->arcs[i][j].cost = getCost(j, V[i]);
			G->arcs[i][j].time = getTime(j, V[i]);
		}
		G->vertices[i] = V[i];
	}
	G->arcNum = arcNum;
}

void DestroyGraph(ALGraph * G)
{
	if (NULL == G)
	{
		return;
	}
	if (G->vertices != NULL)
	{
		for (int i = 0; i < MAX_VERTEX_NUM; ++i)
		{
			if (G->vertices[i].data != NULL)
				free(G->vertices[i].data);

			ArcNode * del = NULL;
			ArcNode * cur = G->vertices[i].firstArc;
			while (NULL != cur)
			{
				del = cur;
				cur = cur->nextArc;
				if(del->info != NULL)
					free(del->info);
				free(del);
			}
		}
	}
	free(G);
	printf("free over\n");
}

int LocateVex(const ALGraph * G, char * u)
{
	if (NULL == G)
	{
		return -1;
	}

	for (int i = 0; i < MAX_VERTEX_NUM; ++i)
	{
		if (strcmp(G->vertices[i].data, u) == 0)
		{
			return i;
		}
	}
	
	return -2;
}
