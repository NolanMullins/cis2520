#ifndef __IO_MULLINSN__
#define __IO_MULLINSN__

#include "linkedList.h"

//read a line (returns 1 if error)
int readLine (FILE* file, char* line);

//removes the \n
void rmNewLine(char* dest, char* src);

//loads the linked lists
Car* loadList(char* filepath, Car** list1, Car** list2, Car** list3);

//saves the linked lists
void saveList(char* filepath, Car* list1, Car* list2, Car* list3);

//checks if a number is valid
int checkNum(char* string);

#endif