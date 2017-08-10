#ifndef _MENU_H_
#define _MENU_H_

#include "graph.h"

#define ROWSPACES 1
#define MAXLEN 40

void printChars(int len, char c);

void printRowSpaceLines(int len);

void printStrLine(const char * str);

void titleTemplate(const char * str);

int menuOne();

int menuFrom(ALGraph * G, const char * method);

int menuTo(ALGraph * G, const char * method, int to);

int way(ALGraph * G, const char * method, int from, int to);

void result(ALGraph * G, const char * method, int from, int to, int whichMin, int transport);

int getSelect();
#endif // !_MENU_H_
