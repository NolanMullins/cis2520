#include <stdio.h>
#include <string.h>
#include "extra.h"
#include "io.h"
#include "tree.h"

int main(int argc, char* argv[])
{
	if (argc != 2)
		exitWithError("incorrect lines entered");

	//check if # of ( == # of )
	if (checkBrackets(argv[1])!=0)
		exitWithError("Incorrect number of brackets");

	//read in eqn
	Tree* head = parseLine(argv[1]);

	int input = 0;
	//command loop
	do
	{
		char userInput[256];
		printf("***************************\n"
				"Enter a number\n"
				"1. Display\n"
				"2. Preorder\n"
				"3. Inorder\n"
				"4. Postorder\n"
				"5. Update\n"
				"6. Calculate\n"
				"7. Exit\n"
				"***************************\n");
		fgets(userInput, 255, stdin);
		userInput[strlen(userInput)-1] = '\0';
		input = checkNum(userInput);

		switch (input)
		{
			//check user input
			case 1:
				fancyPrint(head);
				printf("\n");
				break;
			case 2:
				preOrder(head);
				printf("\n");
				break;
			case 3:
				inOrder(head);
				printf("\n");
				break;
			case 4:
				postOrder(head);
				printf("\n");
				break;
			case 5:
				printf("Enter a key and a number in the format Key,Number\n");
				char line[256];
				if (fgets(line, 255, stdin) == NULL)
				{
					exitWithError("Invalid input");
				}
				for (int a = 0; a < strlen(line); a++)
					if (line[a] == '\n')
						line[a] = '\0';
				update(head, line);
				break;
			case 6:
				printf("%.3f\n",calc(head));
				break;
			case 7:
				printf("Exiting\n");
				break;
			default:
				printf("Invalid option\n");
		}

	} while (input != 7);
	//free memory
	delTree(head);
}
