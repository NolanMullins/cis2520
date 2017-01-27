#ifndef __MULLINSN__QUEUE__
#define __MULLINSN__QUEUE__

#include "tree.h"

typedef struct queue
{
	struct queue* next;
	Tree* node;
} Queue;

Queue* createQ(Tree* node);
Queue* push(Queue* head, Queue* add);
Queue* pop(Queue* head);
Queue* getLast(Queue* head);
void destroy(Queue* node);
void destroyList(Queue* head);
int qLength(Queue* node);

#endif