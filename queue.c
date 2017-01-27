#include <stdio.h>
#include <stdlib.h>

#include "extra.h"
#include "queue.h"

Queue* createQ(Tree* node)
{
	Queue* new = malloc(sizeof(Queue));
	if (new==NULL)
		exitWithError("Memory error");
	new->node = node;
	return new;
}

Queue* push(Queue* head, Queue* add)
{
	add->next = head;
	return add;
}

Queue* pop(Queue* head)
{
	if (head == NULL)
		return NULL;
	if (head->next==NULL)
		return NULL;
	Queue* temp;
	while (temp->next->next!=NULL)
		temp = temp->next;
	temp->next = NULL;
	return head;
}

Queue* getLast(Queue* head)
{
	if (head==NULL)
		return NULL;
	if (head->next==NULL)
		return head;
	return getLast(head->next);
}

int qLength(Queue* node)
{
	if(node==NULL)
		return 0;
	if (node->next == NULL)
		return 1;
	return 1+qLength(node->next);
}

void destroy(Queue* node)
{
	free(node);
}

void destroyList(Queue* head)
{
	if (head == NULL)
		return;
	Queue* next = head->next;
	free(head);
	destroyList(next);
}
/*
void traverse(Tree* head)
{
	Queue* q = createQ(head);
	//char arr[possibleLeaves][256];
	while (qLength(q)!=0)
	{
		Queue* top = getLast(q);
		q = pop(q);

		if (top->node->left != NULL)
		{
			q = push(q, createQ(top->node->left));
		}
		if (top->node->right != NULL)
		{
			q = push(q, createQ(top->node->right));
		}
		printf("%s\n", top->node->value);
		//strcpy(arr[index++], top->node->value);
		destroy(top);
	}
}*/
