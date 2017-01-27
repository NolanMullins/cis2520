#ifndef __MULLINSN__TODO__
#define __MULLINSN__TODO__

//will close the file, print an error msg and then exit
void exitWithError(char* line, FILE* f);
//parse through the file and load the ints into an array
void parseFile(char arr[20][10][3]);
//swap a with b
void swap(int* a, int* b);
//perform downheap on an array based heap
void downHeap(int arr[20]);
//gets the key of a given line
int getKey(char arr[20][10][3], int i);
//prints a line given a key
void printKey(int key, char arr[20][10][3]);
#endif