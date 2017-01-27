#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STRING_MAX 256

int readLine (FILE* file, char* line)
{
	if (fgets(line, 255, file) != NULL && strlen(line) > 0)
	{
		return 0;
	}
	return 1;
}

void rmNewLine(char* dest, char* src)
{
	strcpy(dest, src);
	dest[strlen(dest)-1] = '\0';
}

int checkNum(char* string)
{
	if (string == NULL)
		return -1;
	//loop through and look for none digits
	for (int a = 0; a < strlen(string); a++)
		if (isdigit(string[a]) == 0 && string[a] != '.')
			return -1;
	return atoi(string);
}
