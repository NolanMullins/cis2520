#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//push value onto stack
char** push(char** stack, char* line);
//pop off top value of stack
char* pop(char** stack);

int main(int argc, char* argv[])
{
	//allocate memory for the stack
	char** stack = malloc(sizeof(char*)*100);
	//check for the function entered
	if (argc != 2)
	{
		printf("Enter a single cmd line arg\n");
		free(stack);
		exit(0);
	}
	int length = strlen(argv[1]);
	//loop through string
	for (int a = 0; a < length; a++)
	{	
		if (isdigit(argv[1][a])!=0)
		{
			//if digit push it to the stack 
			char c[2];
			c[0]=argv[1][a];
			c[1]='\0';
			push(stack,c);
		}
		else
		{
			//pop 2 digits off the stack
			char* top = pop(stack);
			float f1 = atof(top);
			free(top);
			top = pop(stack);
			if (top == NULL)
			{
				printf("Invalid equation\n");
				exit(0);
			}
			float f2 = atof(top);
			free(top);
			float result;
			//depending on the symbol perform the operation
			switch (argv[1][a])
			{
				case '-':
					result = f2-f1;
					break;
				case '+':
					result = f2+f1;
					break;
				case '*':
					result = f2*f1;
					break;
				case '/':
					result = f2/f1;
					break;
			}
			//push the result to the stack
			char resultString[100];
			sprintf(resultString, "%.2f", result);
			push(stack ,resultString);
		}
	}
	//print the result
	char* line = pop(stack);
	printf("%s\n", line);

	free(line);
	free(stack);
}

char** push(char** stack, char* line)
{
	int a = 0;
	while (stack[a] != NULL)
		a++;
	stack[a] = malloc(sizeof(char)*strlen(line)+1);
	strcpy(stack[a], line);
	return stack;
}

char* pop(char** stack)
{
	if (stack[0]==NULL)
		return NULL;
	int a = 0;
	while (stack[a+1]!=NULL)
		a++;
	char* line = malloc(sizeof(char)*strlen(stack[a])+1);
	strcpy(line, stack[a]);
	free(stack[a]);
	stack[a] = NULL;
	return line;
}
