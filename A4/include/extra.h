#ifndef __MULLINSN__EXTRA__
#define __MULLINSN__EXTRA__

//will display error msg and exit the program
void exitWithError(char* msg);
//copy contents from start to end from src into dest
void substring(char* dest, char* src, int start, int end);
//returns abs of a number
int absl(int n);

#endif