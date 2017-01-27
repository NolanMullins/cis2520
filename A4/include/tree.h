#ifndef __MULLINSN__TREE__
#define	__MULLINSN__TREE__

typedef struct tree
{
	struct tree* right;
	struct tree* left;
	char* value;
	int freq;
	int height;
}Tree;

//will print all keys with frequency above freq
void printAbove(Tree* node, int freq);

//returns 1 if leaf
int isLeaf(Tree* node);

//will delete a node from a tree with key = value
Tree* delNode(Tree* head, char* value);

//will read in a file and apppend it to head
Tree* readFile(Tree* head, char* file);

//will create a new node with key = value
Tree* createNode(char* value);

//will insert value into the tree
Tree* insert(Tree* head, char* value);

//will balance the passed in tree
Tree* balance(Tree* head);

//left rotation
Tree* left(Tree* node);

//right rotation
Tree* right(Tree* node);

//will recalc the height factors of all nodes
void reCalcHeight(Tree* head);

//will return the greater height of the 2 nodes
int getMax(Tree* node1, Tree* node2);

//will get the height of a node (was to lazy to write head->left-height every time)
int getHeight(Tree* node);

//will return the balnace factor of the node
int balanceFactor(Tree* node);

//will return the node with key = value
Tree* find(Tree* head, char* value);

//returns the size of the tree
int getSize(Tree* head);

//prints the tree out
void printTree(Tree* head);

//returns the height of the tree
int height(Tree* node);

//will use fancyPrint2 to print out the tree to the terminal
void fancyPrint(Tree* head);

//prints out a layer of a tree
void fancyPrint2 (Tree* head, int a, int sizeBuff, int tmp);

//deletes and frees a tree
void delTree (Tree* head);

#endif