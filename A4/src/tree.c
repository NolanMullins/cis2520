#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "tree.h"
#include "extra.h"

Tree* readFile(Tree* head, char* file)
{
	if (access(file, F_OK))
	{
		printf("FILE NOT FOUND\n");
		return head;
	}
	char string[256];
	FILE* f = fopen(file, "r");
	while (fscanf(f, "%s", string) > 0)
	{
		//printf("%s\n", string);
		head = insert(head, string);
	}
	fclose(f);
	return head; 
}

Tree* createNode(char* value)
{
	if (value==NULL)
		printf("Null value in tree\n");

	Tree* node = malloc(sizeof(Tree));
	char* string = malloc(sizeof(char)*strlen(value)+1);
	strcpy(string, value);
	
	//copy data
	node->freq = 1;
	node->height = 1;
	node->value = string;
	node->left = NULL;
	node->right = NULL;
	return node;
}

Tree* insert(Tree* head, char* value)
{
	if (head == NULL)
		return createNode(value);
	if (strcmp(head->value, value)==0)
	{
		head->freq++;
		return head;
	}
	if (strcmp(head->value, value) < 0)				//val > node == insert right
		head->right = insert(head->right, value);
	else
		head->left = insert(head->left, value);
	//re calc the height vars of the lower tree
	reCalcHeight(head);
	//balance tree
	if (absl(balanceFactor(head))>1)
		head = balance(head);
	return head;
}

int isLeaf(Tree* node)
{
	if (node==NULL)
		return 0;
	if (node->left==NULL&&node->right==NULL)
		return 1;
	return 0;
}

Tree* delNode(Tree* head, char* value)
{
	if (head==NULL)
		return NULL;

	if (strcmp(head->value, value) < 0) //val > node == right
	{
		head->right = delNode(head->right, value);
	} 
	else if (strcmp(head->value, value) > 0) //val < node == left
	{
		head->left = delNode(head->left, value);
	}
	else
	{
		if (--head->freq>0)
			return head;
		Tree* tmp=NULL;
		//single child cases
		if (head->right==NULL)
		{
			printf("Test2\n");
			tmp = head->left;
			free(head->value);
			free(head);
			return tmp;
		}
		if (head->left==NULL)
		{
			tmp = head->right;
			free(head->value);
			free(head);
			return tmp;
		}

		//find replacement
		tmp = head->right;
		while (tmp->left->left != NULL)
			tmp=tmp->left;

		//create new tree head
		Tree* newHead = createNode(tmp->left->value);
		newHead->freq = tmp->left->freq;
		newHead->left = head->left;
		newHead->right = head->right;

		//delete node
		Tree* del = tmp->left;
		tmp->left=tmp->left->right;
		free(del->value);
		free(del);
		free(head->value);
		free(head);
		return newHead;
	}

	reCalcHeight(head);
	if (absl(balanceFactor(head))>1)
		head = balance(head);
	return head;
}

int getHeight(Tree* node)
{
	if (node==NULL)
		return 0;
	return node->height;
}

int getMax(Tree* node1, Tree* node2)
{
	if (node1==NULL)
	{
		if (node2==NULL)
			return 0;
		else
			return node2->height;
	}
		
	if (node2==NULL)
		return node1->height;
	return (node1->height>node2->height)? node1->height: node2->height;
}

void reCalcHeight(Tree* head)
{
	if (head==NULL)
		return;
	if (isLeaf(head)==1)
	{
		head->height=1;
	}
	{
		reCalcHeight(head->left);
		reCalcHeight(head->right);
		head->height = getMax(head->left,head->right)+1;
	}
	
}

void delTree (Tree* head)
{
	if (head == NULL)
		return;
	if (head->left!=NULL)
		delTree(head->left);
	if (head->right!=NULL)
		delTree(head->right);
	free(head->value);
	free(head);
}

int balanceFactor(Tree* node)
{
	return getHeight(node->left)-getHeight(node->right);
}

Tree* balance(Tree* head)
{
	Tree* newHead = head;
	if (balanceFactor(newHead)>0)	//left heavy
	{
		if (balanceFactor(newHead->left)<0)
			newHead->left = left(newHead->left);
		return right(newHead);
	}
	else							//right heavy
	{
		if (balanceFactor(newHead->right)>0)
			newHead->right = right(newHead->right);
		return left(newHead);
	}
	return newHead;
}

Tree* left(Tree* node)
{
	Tree* newHead = node->right;
	node->right = newHead->left;
	newHead->left = node;
	return newHead;
}

Tree* right(Tree* node)
{
	Tree* newHead = node->left;
	node->left = newHead->right;
	newHead->right = node;
	return newHead;
}

Tree* find(Tree* head, char* value)
{
	if (head==NULL)
		return NULL;
	if (strcmp(head->value,value)==0)
		return head;
	if (strcmp(head->value, value) < 0)				//val > node == insert right
		return find(head->right, value);
	else
		return find(head->left, value);
}	

int getSize(Tree* head)
{
	if (head==NULL)
		return 0;
	int size  = 1;//head->freq;
	if (head->left != NULL)
		size+=getSize(head->left);
	if (head->right != NULL)
		size+=getSize(head->right);
	return size;
}

void printTree(Tree* head)
{
	if (head==NULL)
		return;
	printf("Key: %s, Freq: %d\n", head->value, head->freq);
	printTree(head->left);
	printTree(head->right);
}

void printAbove(Tree* node, int freq)
{
	if (node==NULL)
		return;
	//is this node above the req freq
	if (node->freq > freq)
		printf("%s: freq: %d\n", node->value, node->freq);
	if (node->left != NULL)
		printAbove(node->left, freq);
	if (node->right != NULL)
		printAbove(node->right, freq);
}

int height(Tree* node)
{
	if (node==NULL)
		return 0;
	if (node->left==NULL && node->right==NULL)
		return 1;
	//get height of subtrees
	int l = height(node->left);
	int r = height(node->right);
	int max=0;
	//check which subtree is bigger
	if (l>r)
		max = l;
	else
		max = r;
	return max+1;
}

void fancyPrint(Tree* head)
{
	printf("\n");
	int h = height(head);
	int buff = 2<<(h+1);
	//loop through tree levels
	for (int a = 0; a < h; a++)
	{
		fancyPrint2(head, a, buff/(2<<a), 0);
		//if i want to add lines recall fancyprint2 but print out - instead
		printf("\n");
	}
}

void fancyPrint2 (Tree* head, int a, int sizeBuff, int tmp)
{
	//if this is the print height and there is no head
	if (a==0 && head == NULL)
	{
		printf("%*s%c%*s", sizeBuff-tmp, "", ' ' , sizeBuff-tmp, "");
		return;
	}
	//print ghost subtree
	else if (a>0 && head == NULL)
	{
		fancyPrint2(NULL, a-1, sizeBuff, 1);
		fancyPrint2(NULL, a-1, sizeBuff, 0);
		return;
	}
	//print real tree
	if (a==0)
	{
		int size = (int)(strlen(head->value)/2);
		printf("%*s%s%*s", sizeBuff-size-tmp, "",head->value, sizeBuff-size-tmp, "");
	}
	if (head->left != NULL)
		fancyPrint2(head->left, a-1, sizeBuff, 1);
	else if (a>0)
		fancyPrint2(NULL, a-1, sizeBuff, 1);
	if (head->right != NULL)
		fancyPrint2(head->right, a-1, sizeBuff, 0);
	else if (a>0)
		fancyPrint2(NULL, a-1, sizeBuff, 0);
}