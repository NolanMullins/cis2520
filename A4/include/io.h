#ifndef __MULLINSN__IO__
#define __MULLINSN__IO__

//read a line (returns 1 if error)
int readLine (FILE* file, char* line);

//removes the \n
void rmNewLine(char* dest, char* src);

//checks if a number is valid
int checkNum(char* string);

#endif