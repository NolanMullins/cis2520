#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "io.h"

void exitWithError(char* line, FILE* f)
{
	printf("%s\n", line);
	fclose(f);
	exit(0);
}

void parseFile(char arr[20][10][3])
{
	FILE* f = fopen("data/f.dat", "r");
	for (int a = 0; a < 20; a++)
	{
		//read line
		char line[256];
		int tmp = readLine(f, line);
		if (tmp==1)
			exitWithError("Error with file", f);
		int length = strlen(line);
		int index = 0;
		//loop through line and read in values
		for (int b = 0; b < length; b++)
		{
			//get rid of spaces
			while(line[b]==' ')
				b++;
			//check for end of line
			if (line[b] == '\n' || line[b] == '\0')
				break;
			if (isdigit(line[b])==0||isdigit(line[b++])==0)
				exitWithError("Error with file, non number found", f);
			arr[a][index][0]=line[b-1];
			arr[a][index][1]=line[b++];
			arr[a][index++][2]='\0';
		}
		if (index != 10)
			exitWithError("Incorrect format found in file", f);
	}
	fclose(f);
}

void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void downHeap(int arr[20])
{
	for (int a = 1; a <= 10; a++)
	{
		int p = a-1, c = 2*a-1;
		//check for smaller child
		if (arr[c]>arr[c+1])
			c++;
		//check parent against smaller child
		if (arr[p]>arr[c])
		{
			swap(&arr[p], &arr[c]);
			downHeap(arr);
			return;
		}
	}
}

int getKey(char arr[20][10][3], int i)
{
	//check if lines been used
	if(arr[i][0][0]=='x')
		return -1;
	return atoi(arr[i][0])+atoi(arr[i][1])+atoi(arr[i][2]);
}

void printKey(int key, char arr[20][10][3])
{
	for (int a = 0; a < 20; a++)
		//if key matches print the line
		if (key == getKey(arr, a))
		{
			for (int b = 0; b < 10; b++)
				printf("%s ", arr[a][b]);
			printf("\n");
			arr[a][0][0]='x';
		}
}
