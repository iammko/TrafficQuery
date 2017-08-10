#include "init.h"
#include "menu.h"


int getMethod(ALGraph * G, int v, int i, int select)
{
	int method;
	if (select == 1)
	{
		method = G->arcs[v][i].cost;
	}
	else
	{
		method = ((G->arcs[v][i].cost < INFINITY) ? 1 : INFINITY);
	}
	return method;
}

void Dijkstra(ALGraph * G, int k, int P[][MAX_VERTEX_NUM], int D[], int select)
{
	int v = k;
	int i = 0;
	int j = 0;
	for (i = 0; i < G->vexnum; ++i)
	{
		int method = getMethod(G, v, i, select);
		hasShortPath[i] = false;
		D[i] = method;
		for (j = 0; j < G->vexnum; ++j)
		{
			P[i][j] = -1;
			//P[i][0] = k;
			if(D[i] < INFINITY)
				P[i][0] = i;
		}
		
	}

	D[k] = 0; 
	hasShortPath[k] = true;
	
	for (i = 1; i < G->vexnum; ++i)
	{
		int min = INFINITY;
		for (j = 0; j < G->vexnum; ++j)
		{
			if (!hasShortPath[j] && D[j] < min)
			{
				v = j;
				min = D[j];
			}
		}
		hasShortPath[v] = true;

		for (j = 0; j < G->vexnum; ++j)
		{
			int method = getMethod(G, v, j, select);
			if (!hasShortPath[j] && (min + method < D[j]))
			{
				D[j] = min + method;
				//P[j] = v;
				for(int n = 0; n < G->vexnum; ++n)
				{
					P[j][n] = P[v][n];
					if(P[j][n] == -1)
					{
						P[j][n] = j;
						break;
					}
				}
			}
		}
	}
}

void test()
{
	ALGraph * G;
	ALGraph * train = init(TRAIN);
	ALGraph * coach = init(COACH);
	G = train;
	int whichMin;
	int transport;
	int from = 0;
	int to = 0;
	char buf[128];
	char * str1 = "最少费用路径查询";
	char * str2 = "最少转车路径查询";
	char * p = NULL;
	while (1)
	{
		system("cls");
		whichMin = menuOne();
		system("cls");
		if (whichMin == 1)
		{
			p = str1;
		}
		else
		{
			p = str2;
		}
		from = menuFrom(G, p);
		system("cls");
		to = menuTo(G, p, from);
		system("cls");
		transport = way(G, p, from, to);
		if (transport == TRAIN)
		{
			G = train;
		}
		else if (transport == COACH)
		{
			G = coach;
		}
		Dijkstra(G, from - 1, Path, Dist, whichMin);
		system("cls");
		result(G, p, from, to, whichMin, transport);
	}
	DestroyGraph(train);
	DestroyGraph(coach);
}

int main()
{
	test();
#if 0
	for (int i = 0; i < MAX_VERTEX_NUM; ++i)
	{
		//printf("%s -> %s  %d\n", GTrain->vertices[5].data, GTrain->vertices[i].data, D[i]);
		for(int j = 0; j < MAX_VERTEX_NUM; ++j)
		{
			if(Path[i][j] != -1)
				printf("%s", GTrain->vertices[Path[i][j]].data);
			else
				break;
			if(Path[i][j+1] != -1 && j < MAX_VERTEX_NUM - 1)
				printf(" -> ");
		}
		printf(" %d\n", Dist[i]);
	}
#endif

#if 0
	//printf("graph vexnum = %d\ncoachArcNum = %d\ntrainArcNum = %d\n", GTrain->vexnum, GCoach->arcNum, GTrain->arcNum);
	printf("place list:\n");
	for (int i = 0; i < MAX_VERTEX_NUM; ++i)
	{
		printf("%s\n", GTrain->vertices[i].data);
		printf("node cost list:\n");
		ArcNode * tmp = GTrain->vertices[i].firstArc;
		while (tmp != NULL)
		{
			printf("%d %d\n", tmp->adjVex, tmp->info);
			tmp = tmp->nextArc;
		}
	}
#endif

#if 0
	for (int i = 0; i < MAX_VERTEX_NUM; ++i)
	{
		for (int j = 0; j < MAX_VERTEX_NUM; ++j)
		{
			if (GTrain->arcs[i][j].cost == INFINITY)
			{
				printf("%5s", "@");
			}
			else
				printf("%5d", GTrain->arcs[i][j].cost);
		}
		printf("\n");
	}
#endif
	return 0;
}