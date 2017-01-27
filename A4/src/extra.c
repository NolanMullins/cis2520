#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void exitWithError(char* msg)
{
	printf("%s\n", msg);
	exit(0);
}

void substring(char* dest, char* src, int start, int end)
{
	int size = end - start;
	if (size < 0)
		exitWithError("Invalid variable");
	int a = 0;
	//copy contents over
	for (int b = start; b <= end; b++)
	{
		dest[a] = src[b];
		a++;
	}
	dest[a]='\0';
}

int absl(int n)
{
	if (n<0)
		return n*-1;
	return n;
}
