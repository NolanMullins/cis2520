#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "tree.h"
#include "extra.h"
#include "io.h"

Tree* create (char* value)
{
	if (value == NULL)
		return NULL;
	Tree* new = malloc(sizeof(Tree));
	if (new == NULL)
		return NULL;
	//copy old vars into new ones and return new struct
	char* newVal = malloc(sizeof(char)*strlen(value)+1);
	strcpy(newVal, value);
	new->value = newVal;
	new->left = NULL;
	new->right = NULL;
	return new;
}

void printSection(char* line, int start, int end)
{
	for (int a = start; a <= end; a++)
		printf("%c", line[a]);
	printf("\n");
}

int isSymbol(char* line, int index)
{
	if (line[index] == '+' || line[index] == '-' || line[index] == '*' || line[index] == '/')
		return 1;
	return 0;
}

void getLR (char* line, int* left, int* right)
{
	int start = *left, end = *right;
	*left = -1;
	*right = -1;
	int brk=0;
	//loop through section and locate left most and its coresponding right most bracket
	for (int a = start; a <= end; a++)
	{
		if (line[a] == '(' && *left == -1)
			*left = a;
		else if (line[a]=='(')
			brk++;
		if (line[a]==')' && brk > 0)
			brk--;
		else if (line[a]==')')
		{
			*right = a;
			break;
		}
	}
	if (*left+1==*right)
		exitWithError("Why u put empty brackets :(");
}

Tree* parseLine (char* line)
{	
	//assumed () are first and last
	int left=0,right=strlen(line);
	getLR(line, &left, &right);

	return createNode(line, left, right);
}

Tree* createNode(char* line, int left, int right)
{
	int symbol = -1;
	int brk=0;
	int start = left+1, end = right-1;
	//look symbol outside of inner scope
	for (int a = start; a <= end; a++)
	{
		if (isSymbol(line, a)==1 && brk == 0)
			symbol = a;
		if (line[a]=='(')
			brk++;
		else if (line[a]==')')
			brk--;
	}
	//no symbol found at content
	if (symbol == -1)
	{
		int l=left,r=right;
		getLR(line, &l, &r);
		//is there a set of brackets
		if (l==-1 || r==-1)//no? store value in new node
		{
			char val[256];
			substring(val, line, left, right);
			return create(val);
		}
		//yes? parse the inside of it
		return createNode(line, l+1, r-1);
	}
	//store symbol
	Tree* node = malloc(sizeof(Tree));
	char* newVal = malloc(sizeof(char)*2);
	newVal[0] = line[symbol];
	newVal[1] = '\0';
	node->value = newVal;

	//parse left
	node->left = createNode(line, left+1, symbol-1);
	//parse right
	node->right = createNode(line, symbol+1, right-1);
	return node;
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

int checkBrackets (char* line)
{
	int a = 0;
	int brk = 0;
	//loop through and count (vs) difference
	while(line[a]!='\0')
	{
		if (line[a]=='(')
			brk++;
		else if (line[a]==')')
			brk--;
		a++;
	}
	return brk;
}

void update (Tree* head, char* line)
{
	int i = -1;
	//loop through and look for seperator
	for (int a = 0; a < strlen(line); a++)
		if (line[a]==',')
		{
			i = a;
			break;
		}
	if (i < 0)
	{
		printf("Error with format\n");
	}
	char exp[256], val[256];
	substring(exp, line, 0, i-1);
	//check if this variable is a number
	if (isdigit(exp[0])!=0)
		printf("%s is not a variable\n", exp);
	int tmp = 0;
	if (line[i+1]==' ')
		tmp=1;
	substring(val, line, i+1+tmp, strlen(line));
	//check if the number after the , is actaully a number
	if (checkNum(val)>=0)
		updateTree(head, exp, val);
	else
		printf("%s is not a number\n", val);
}

void updateTree (Tree* head, char* exp, char* val)
{
	if (head==NULL)
		return;
	//if this node is the variable check
	if (strcmp(head->value, exp)==0)
	{
		free(head->value);
		char* new = malloc(sizeof(char)*strlen(val)+1);
		strcpy(new, val);
		head->value = new;
	}
	if (head->left != NULL)
		updateTree(head->left, exp, val);
	if (head->right != NULL)
		updateTree(head->right, exp, val);
}


float calc(Tree* head)
{
	if (head == NULL)
		return 0;
	//if this is a number return it
	int test = checkNum(head->value);
	if (test !=-1)
		return atof(head->value);
	//check the operator and perform the action
	if (strcmp("*", head->value)==0)		
		return calc(head->left)*calc(head->right);
	else if (strcmp("/", head->value)==0)
		return calc(head->left)/calc(head->right);
	else if (strcmp("+", head->value)==0)
		return calc(head->left)+calc(head->right);
	else if (strcmp("-", head->value)==0)
		return calc(head->left)-calc(head->right);
	return 0;
}

void inOrder (Tree* head)
{
	if (head==NULL)
		return;
	//print left child then head and then right child
	if (head->left != NULL)
	{
		printf(" (");
		inOrder(head->left);
	}
	printf("%s ", head->value);
	if (head->right != NULL)
	{
		inOrder(head->right);
		printf(") ");
	}
}

void preOrder (Tree* head)
{
	if (head==NULL)
		return;
	//print head left than right
	printf("%s ", head->value);
	if (head->left != NULL)
		preOrder(head->left);
	if (head->right != NULL)
		preOrder(head->right);
}

void postOrder (Tree* head)
{
	if (head==NULL)
		return;
	//print left right than head
	if (head->left != NULL)
		postOrder(head->left);
	if (head->right != NULL)
		postOrder(head->right);
	printf("%s ", head->value);
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
