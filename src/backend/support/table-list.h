#ifndef TABLELIST_H
#define TABLELIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct Node{
    char * player;
    struct Node * next;
}Node;


typedef struct Table{
    Node * team;
}Table;



Table * initTableList();
// bool listFind(Table *list, const char *data);
void listInsert(Table *list, const char *data);
//void listDelete(Table *list, const char *data);
int countList(Table * list);
void freeTableList(Table *list);
char * indexList(Table * list, int idx);
// void printList(Table *list);

#endif  // CHARLIST_H