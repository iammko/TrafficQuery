#include "init.h"

FILE * openFile(const char * path)
{
	FILE * fp = fopen(path, "rb");
	if (NULL == fp)
	{
		perror("fopen error");
		exit(0);
	}
	return fp;
}

ALGraph * init(int path)
{
	ALGraph * G = (ALGraph *)malloc(sizeof(ALGraph));
	if (NULL == G)
	{
		perror("[func: init]malloc error");
		exit(0);
	}

	AdjList myAdjList;
	initAdjList(&myAdjList);

	FILE * fp = NULL;

	if (path == TRAIN)
	{
		fp = openFile(TRAINPATH);
	}
	else if (path == COACH)
	{
		fp = openFile(COACHPATH);
	}

	ArcNode ** arcList = initArcList(fp);

	CreateGraph(G, myAdjList, arcList);

	return G;
}

ArcNode ** initArcList(FILE * fp)
{
	ArcNode ** arcList = (ArcNode **)malloc(sizeof(ArcNode*) * MAX_VERTEX_NUM);
	for (int i = 0; i < MAX_VERTEX_NUM; ++i)
	{
		arcList[i] = NULL;
	}

	int indexNum1 = 0;
	int indexNum2 = 0;
	int cost = 0;
	ArcInfo info;
	int arcNum = 0;
	while (1)
	{
		if (getArcInfo(&indexNum1, &indexNum2, &info, fp) == -1)
		{
			break;
		}
		addArcNode(arcList, indexNum1, indexNum2, info);

		//printf("indexNum1 = %d indexNum2 = %d cost = %d\n", indexNum1, indexNum2, cost);
	}
	
	rewind(fp);

	while (1)
	{
		if (getArcInfo(&indexNum1, &indexNum2, &info, fp) == -1)
		{
			break;
		}
		addArcNode(arcList, indexNum2, indexNum1, info);
	}
	
	return arcList;
}

int getArcInfo(int * pindexNum1, int * pindexNum2, ArcInfo * pinfo, FILE * fp)
{
	char buf[256];
	if (fgets(buf, sizeof(buf), fp) == NULL)
	{
		return -1;
	}

	char * p = strrchr(buf, '|');

	*p = 0;

	*pindexNum1 = getIndex(strtok(buf, "|"));
	*pindexNum2 = getIndex(strtok(NULL, "|"));
	pinfo->cost = atoi(strtok(NULL, "|"));
	pinfo->time = atoi(strtok(NULL, "|"));

	//printf("%d %d %d\n", *pindexNum1, *pindexNum2, *pcost);
	memset(buf, 0, sizeof(buf));	
	return 0;
}

void addArcNode(ArcNode ** arcList, int tail, int head, ArcInfo info)
{
	ArcNode * tmp = (ArcNode *)malloc(sizeof(ArcNode));
	tmp->info = (ArcInfo *)malloc(sizeof(ArcInfo));
	tmp->adjVex = head;
	*tmp->info = info;
	tmp->nextArc = arcList[tail];

	arcList[tail] = tmp;
}

void initAdjList(AdjList * trafficNet)
{
	for (int i = 0; i < MAX_VERTEX_NUM; ++i)
	{
		switch (i)
		{
		case BEIHAI:
			initAdjListData("北海", trafficNet, i);
			break;
		case QINZHOU:
			initAdjListData("钦州", trafficNet, i);
			break;
		case NANNING:
			initAdjListData("南宁", trafficNet, i);
			break;
		case GUILIN:
			initAdjListData("桂林", trafficNet, i);
			break;
		case LIUZHOU:
			initAdjListData("柳州", trafficNet, i);
			break;
		case WUZHOU:
			initAdjListData("梧州", trafficNet, i);
			break;
		default:
			break;
		}
	}
}

void initAdjListData(const char * p, AdjList * trafficNet, int i)
{
	int len = strlen(p) + 1;
	char * tmp = (char *)malloc(sizeof(char) * len);
	if (NULL == tmp)
	{
		perror("[func: initAdjListData]malloc error");
		exit(0);
	}

	memset(tmp, 0, sizeof(char) * len);
	strcpy(tmp, p);
	(*trafficNet)[i].data = tmp;
	(*trafficNet)[i].firstArc = NULL;
}

int getIndex(const char * p)
{
	if (strcmp(p, "北海") == 0)
		return BEIHAI;
	else if (strcmp(p, "钦州") == 0)
		return QINZHOU;
	else if (strcmp(p, "南宁") == 0)
		return NANNING;
	else if (strcmp(p, "桂林") == 0)
		return GUILIN;
	else if (strcmp(p, "柳州") == 0)
		return LIUZHOU;
	else if (strcmp(p, "梧州") == 0)
		return WUZHOU;
}