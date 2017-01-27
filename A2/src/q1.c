#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedList.h"
#include "io.h"
#include "functions.h"
#include "sort.h"

int main(int argc, char* argv[])
{
	Car* available = NULL;
	Car* rented = NULL;
	Car* inRepair = NULL;

	//load
	loadList("data/data.txt", &available, &rented, &inRepair);

	float income = 0;

	//sort
	available = sortAvailable(available);
	rented = sortRented(rented);

	//run
	int input = -1;
	while (input != 7)
	{
		printf("Please enter 1-7\n");
		char line[256];
		if (fgets(line, 255, stdin) == NULL)
		{
			printf("Error");
		}
		line[strlen(line)-1] = '\0';
		input = checkNum(line);

		run(&available, &rented, &inRepair, input, &income);
	}
	
	printf("\n***********************************\n");
	printf("Total income: $%.2f\n", income);
	printf("***********************************\n\n");

	printf("Saving\n");

	//save
	saveList("data/data.txt", available, rented, inRepair);

	//free memory
	destroyList(available);
	destroyList(rented);
	destroyList(inRepair);

}