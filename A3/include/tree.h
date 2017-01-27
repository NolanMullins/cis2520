#ifndef __MULLINSN__TREE__
#define __MULLINSN__TREE__

typedef struct tree
{
	struct tree* right;
	struct tree* left;
	char* value;
}Tree;

//crete a node for the tree
Tree* create(char* value);
//stores the location of the outer most brackts in left and right
void getLR (char* line, int* left, int* right);
//will use fancyPrint2 to print out the tree to the terminal
void fancyPrint(Tree* head);
//prints out a layer of a tree
void fancyPrint2 (Tree* head, int a, int sizeBuff, int tmp);
//if the number of ( matchs the number of ) it will return 0
int checkBrackets (char* line);
//parses an eqn line
Tree* parseLine (char* line);
//will create a node given a section of an equation
Tree* createNode(char* line, int left, int right);
//calculates and returns the answer to the eqn
float calc(Tree* head);
//updates a variable in the tree
void update (Tree* head, char* line);
//replaces a variable in the tree with val
void updateTree (Tree* head, char* exp, char* val);
//prints out in order
void inOrder (Tree* head);
//prints out in preOrder
void preOrder (Tree* head);
//prints out in post order
void postOrder (Tree* head);
//deletes and frees a tree
void delTree (Tree* head);

#endif