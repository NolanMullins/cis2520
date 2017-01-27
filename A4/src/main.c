#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "tree.h"
#include "io.h"
#include "extra.h"

//TODO
//read file
//rest of functions

int main (int argc, char* argv[])
{

	Tree* head = NULL;
	//cmd loop
	int input = 0;
	do
	{
		char userInput[256];
		printf("***************************\n"
				"Enter a number\n"
				"1. Initialization\n"
				"2. Find\n"
				"3. Insert\n"
				"4. Remove\n"
				"5. Check Height and Size\n"
				"6. Find All\n"
				"7. Exit\n"
				"***************************\n"
				"avl/> ");
		//grab user choice
		fgets(userInput, 255, stdin);
		userInput[strlen(userInput)-1] = '\0';
		input = checkNum(userInput);

		switch (input)
		{
			//check user input
			case 1: //init
				printf("Filepath: ");
				char file[256];
				fgets(file, 255, stdin);
				file[strlen(file)-1] = '\0';
				head = readFile(head, file);
				break;
			case 2: //find
				printf("Find Key: ");
				char key[256];
				fgets(key, 255, stdin);
				key[strlen(key)-1] = '\0';
					if (find(head, key)!=NULL)
						printf("Value: %s, freq: %d\n", key, find(head, key)->freq);
					else
						printf("Key_not_found\n");
				break;
			case 3: //insert
				printf("Insert Key: ");
				char keyI[256];
				fgets(keyI, 255, stdin);
				keyI[strlen(keyI)-1] = '\0';
				head = insert(head, keyI);
				break;
			case 4:
				printf("Remove Key: ");
				char del[256];
				fgets(del, 255, stdin);
				del[strlen(del)-1] = '\0';
				if (find(head, del)!=NULL)
					head = delNode(head, del);
				else
					printf("Key_not_found\n");
				break;
			case 5: //check height and size
				if (head==NULL)
					printf("EMPTY\n");
				else
					printf("Height: %d, Size: %d\n", getHeight(head)-1, getSize(head));
				break;
			case 6:	//find all-
				printf("Frequency: ");
				char keyF[256];
				fgets(keyF, 255, stdin);
				keyF[strlen(keyF)-1] = '\0';
				if (checkNum(keyF)<0)
					printf("Not a number entered\n");
				else
					printAbove(head, atoi(keyF));
				break;
			case 7:
				printf("Exiting\n");
				break;
			default:
				printf("Invalid option\n");
		}
		//if (head != NULL)
		//	fancyPrint(head);

	} while (input != 7);

	//free memory
	delTree(head);
	return 1;
}
