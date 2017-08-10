#ifndef _LIST_H_
#define _LIST_H_

typedef struct Node
{
	char * data;
	struct Node * next;
}Node;

typedef struct List
{
	int size;
	struct Node header;
}List;

typedef void * MyList;

void initList(MyList * mylist);

void push_backList(MyList mylist);

void destroy(MyList * mylist);

#endif