#include "list.h"

void initList(MyList * mylist)
{
	if(NULL == mylist)
	{
		return ;
	}
	
	List * newList = (List *)malloc(sizeof(List));
	if(NULL == newList)
	{
		perror("[Func initList:]malloc error");
		return;
	}
	newList->size = 0;
	newList->header->buf = NULL;
	newList->header->next = NULL;
	
	*mylist = newList;
}

void frontInsertList(MyList mylist, void * data)
{
	if (NULL == mylist || NULL == data)
	{
		return ;
	}
		
	List * tmp = (List *)mylist;
	Node * newNode = (Node *)malloc(sizeof(Node));
	if(NULL == newNode)
	{
		perror("[Func frontInsertList:newNode]malloc error");
		return;
	}
	
	char * str = (char *)data;
	newNode->data = (char *)malloc(sizeof(char) * strlen(str) + 1);
	if(NULL == newNode->data)
	{
		perror("[Func frontInsertList:newNode->data]malloc error");
		return;
	}
	strcpy(newNode->data, str);
	newNode->next = tmp->header->next;
	tmp->header->next = newNode;
	
	++tmp->size;
}

void destroyList(MyList * mylist)
{
	if (NULL == mylist)
	{
		return ;
	}
		
	List * tmp = (List *)mylist;
	
	if(NULL == tmp)
	{
		return;
	}
	
	Node * cur = tmp->header->next;
	Node * del = NULL;
	
	while(cur != NULL)
	{
		del = cur;
		cur = cur->next;
		free(del);
	}
	
	free(tmp);
	*mylist == NULL;
}