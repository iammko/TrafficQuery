#include "menu.h"
#include "init.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void printChars(int len, char c)
{
	for (int i = 0; i < len; ++i)
	{
		printf("%c", c);
	}
}

void printRowSpaceLines(int len)
{
	for (int i = 0; i < ROWSPACES; ++i)
	{
		printf("*");
		printChars(len - 2, ' ');
		printf("*");
		printf("\n");
	}
}

void printStrLine(const char * str)
{
	int len = strlen(str);
	int len2 = (MAXLEN - len - 2) / 2;
	printf("*");
	printChars(len2, ' ');
	printf("%s", str);
	printChars(MAXLEN - len - len2 - 2, ' ');
	printf("*");
	printf("\n");
}

void titleTemplate(const char * str)
{
	printChars(MAXLEN, '*');
	printf("\n");
	printRowSpaceLines(MAXLEN);

	printStrLine(str);

	printRowSpaceLines(MAXLEN);
	printChars(MAXLEN, '*');
	printf("\n");
}

int menuOne()
{
	titleTemplate("������������������");
	printRowSpaceLines(MAXLEN);

	printStrLine("�����ṩ��ѯ��ʽ");
	printStrLine("----------------");
	printStrLine("1. ���ٷ���·��");
	printStrLine("2. ����ת��·��");
	printStrLine("q. �˳�");

	printRowSpaceLines(MAXLEN);
	printChars(MAXLEN, '*');
	printf("\n");
	printf("��ѡ���Ӧ���֣�");
	return getSelect(3);
}

int menuFrom(ALGraph * G, const char * method)
{
	titleTemplate(method);
	printRowSpaceLines(MAXLEN);

	char str[128] = { 0 };
	printStrLine("-->");
	printStrLine("������");
	printStrLine("----------------");

	int max = G->vexnum;
	int i = 0;
	for (i = 0; i < max; ++i)
	{
		sprintf(str, "%d. %s", i+1, G->vertices[i].data);
		printStrLine(str);
	}
	sprintf(str, "%d. %s", i + 1, "�˳�");
	printStrLine(str);

	printRowSpaceLines(MAXLEN);
	printChars(MAXLEN, '*');
	printf("\n");
	printf("��ѡ���Ӧ���֣�");
	return getSelect(max+1);
}

int menuTo(ALGraph * G, const char * method, int from)
{
	titleTemplate(method);
	printRowSpaceLines(MAXLEN);
	char str[128] = { 0 };
	sprintf(str, "%s -->", G->vertices[from -1].data);
	printStrLine(str);
	printStrLine("----------------");

	int k = 0;
	int max = G->vexnum;
	for (int i = 0; i < max; ++i)
	{
		if (i + 1 == from)
		{
			continue;
		}
		sprintf(str, "%d. %s", ++k, G->vertices[i].data);
		printStrLine(str);
	}
	sprintf(str, "%d. %s", ++k, "�˳�");
	printStrLine(str);

	printRowSpaceLines(MAXLEN);
	printChars(MAXLEN, '*');
	printf("\n");
	printf("��ѡ���Ӧ���֣�");
	int ret = getSelect(max);
	return ret >= from ? (ret + 1) : ret;
}

int way(ALGraph * G, const char * method, int from, int to)
{
	titleTemplate(method);
	printRowSpaceLines(MAXLEN);
	char str[128] = { 0 };
	sprintf(str, "%s --> %s", G->vertices[from - 1].data, G->vertices[to - 1].data);
	printStrLine(str);
	printStrLine("��ͨ��ʽ");
	printStrLine("----------------");
	printStrLine("1. ����");
	printStrLine("2. �ͳ�");
	printStrLine("q. �˳�");

	printRowSpaceLines(MAXLEN);
	printChars(MAXLEN, '*');
	printf("\n");
	printf("��ѡ���Ӧ���֣�");
	return getSelect(3);
}

void result(ALGraph * G, const char * method, int from, int to, int whichMin, int transport)
{
	from -= 1;
	to -= 1;
	char * strway = NULL;
	if (transport == TRAIN)
	{
		strway = "����";
	}
	else
	{
		strway = "�ͳ�";
	}
	char tmp[128] = { 0 };
	if (whichMin == LEASTCOST)
	{
		sprintf(tmp, "�ܽ�� %d", Dist[to]);
	}
	else if (whichMin == LEASTTURNS)
	{
		sprintf(tmp, "ת������ %d", Dist[to]);
	}
	

	titleTemplate(method);
	printRowSpaceLines(MAXLEN);
	char str[128] = { 0 };
	sprintf(str, "%s --> %s", G->vertices[from].data, G->vertices[to].data);
	printStrLine(str);
	printStrLine(strway);
	printStrLine("----------------");

	memset(str, 0, sizeof(str));
	strcat(str, G->vertices[from].data);
	strcat(str, " -> ");
	for (int i = 0; i < MAX_VERTEX_NUM; ++i)
	{
		if (Path[to][i] != -1)
		{
			strcat(str, G->vertices[Path[to][i]].data);
		}
		else
			break;
		if (Path[to][i+1] != -1 && i < MAX_VERTEX_NUM - 1)
		{
			strcat(str, " -> ");
		}
	}

	printStrLine(str);
	printStrLine(tmp);
	printRowSpaceLines(MAXLEN);
	printStrLine("1. ������ѯ");
	printStrLine("q. �˳�");
	printChars(MAXLEN, '*');

	printf("\n");
	printf("��ѡ���Ӧ���֣�");
	getSelect(2);
}

int getSelect(int n)
{
	int input = 0;
	char buf[4096];
	while (1)
	{
		if (gets(buf) == NULL)
		{
			perror("gets error");
			return -1;
		}
		if (strlen(buf) > 2 || isalpha(buf[0]) || isalpha(buf[1]))
		{
			if (tolower(buf[0]) == 'q')
			{
				system("cls");
				exit(0);
			}

			printf("������Ч.\n");
			printf("����������:");
			continue;
		}

		input = atoi(buf);

		if (input > n - 1)
		{
			printf("������Ч.\n");
			printf("����������:");
			continue;
		}

		return input;
	}
}
