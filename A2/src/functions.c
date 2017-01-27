#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
#include "linkedList.h"
#include "sort.h"
#include "functions.h"

#define STRING_MAX 256

int checkPlate(Car* list, char* plate)
{
	//loop through cars in the list and look for a duplicate
	int l = length(list);
	for (int a = 0; a < l; a++)
		if (strcmp(get(a,list)->plate, plate) == 0)
			return -a;
	return 1;
}

char* askForPlate(Car* available, Car* rented, Car* inRepair)
{
	char* plate = malloc(sizeof(char)*STRING_MAX);
	printf("Enter a plate\n");
	if (fgets(plate, 255, stdin) == NULL)
	{
		printf("Invalid input\n");
		free(plate);
		return NULL;
	}
	int test = strlen(plate);
	for (int a = 0; a < test; a++)
		if (plate[a] == '\n')
			plate[a] = '\0';
	if (checkPlate(available, plate) < 0 || checkPlate(rented, plate) < 0 || checkPlate(inRepair, plate) < 0 || strlen(plate) > 9 || strlen(plate) < 6)
	{
		printf("Plate: 5 < L < 10 and cant already exist\n");
		free(plate);
		return NULL;
	}
	return plate;
}

int askForMileage()
{
	char input[STRING_MAX];
	printf("Enter the cars mileage:\n");
	if (fgets(input, 255, stdin) == NULL )//|| checkNum(input) == -1)
	{
		printf("Invalid input\n");
		return -1;
	}
	int test = strlen(input);
	for (int a = 0; a < test; a++)
		if (input[a] == '\n')
			input[a] = '\0';
	if (checkNum(input)==-1)
	{
		printf("Not a valid number\n");
		return -1;
	}
	return checkNum(input);
}

Car* addNewCar(Car* available, Car* rented, Car* inRepair)
{
	//name
	char name[STRING_MAX];
	printf("Enter a name\n");
	if (fgets(name, 255, stdin) == NULL || strcmp(name, "--\n")==0 || strcmp(name, "--")==0)
	{
		printf("Invalid input\n");
		return available;
	}
	//remove newline char
	int test = strlen(name);
	for (int a = 0; a < test; a++)
		if (name[a] == '\n')
			name[a] = '\0';
	//plate
	char* plate = askForPlate(available, rented, inRepair);
	if (plate == NULL)
	{
		return available;
	}

	//mileage
	int mileage = askForMileage();
	if (mileage < 0)
	{
		free(plate);
		return available;
	}

	//create car
	Car* newCar = createRecord(name, plate, mileage, 0);
	if (newCar == NULL)
		printf("Error adding new car\n");
	//transaction
	printf("\n***********************************\n");
	printf("Car: %s\nPlate: %s\n", newCar->name, newCar->plate);
	printf("To: %s\n","Available");
	printf("***********************************\n\n");
	//add it to the list and sort the list
	available = addToBack(available, newCar);
	available = sortAvailable(available);
	free(plate);
	return available;
}

void returnCar (Car** rented, Car** available, float* income)
{
	char plate[STRING_MAX];
	printf("enter plate of car to return\n");
	if (fgets(plate, 255, stdin) == NULL)
	{
		printf("Invalid input\n");
		return;
	}
	//remove newline char
	int test = strlen(plate);
	for (int a = 0; a < test; a++)
		if (plate[a] == '\n')
			plate[a] = '\0';
	//check if plate lenght is correct
	if (strlen(plate) > 9 || strlen(plate) < 6)
	{
		printf("Invalid input\n");
		return;
	}
	//look for car entered
	int index = -checkPlate(*rented, plate);
	if (index >= 0)
	{
		Car* temp = get(index, *rented);
		//complete transaction
		int newMileage = askForMileage();
		if (newMileage < temp->mileage)
		{
			printf("Mileage cant be less than when it left\n");
			return;
		}
		transaction(temp->mileage, newMileage, income, "Rented", "Available", temp->name, temp->plate);
		temp->mileage = newMileage;
		//correct lists
		*rented = moveCarfromList(*rented, *available, temp->plate);
		*available = sortAvailable(*available);
	}
	else
	{
		printf("Car not found\n");
	}
}

void carIsKill(Car** rented, Car** inRepair, float* income)
{
	char plate[STRING_MAX];
	printf("Enter rented cars plate to repair\n");
	if (fgets(plate, 255, stdin) == NULL)
	{
		printf("Invalid input\n");
		return;
	}
	int test = strlen(plate);
	for (int a = 0; a < test; a++)
		if (plate[a] == '\n')
			plate[a] = '\0';
	if (strlen(plate) > 9 || strlen(plate) < 6)
	{
		printf("Invalid input\n");
		return;
	}
	int index = -checkPlate(*rented, plate);
	if (index >= 0)
	{
		Car* temp = get(index, *rented);
		//Complete transaction
		int newMileage = askForMileage();
		if (newMileage < temp->mileage)
		{
			printf("Mileage cant be less than when it left\n");
			return;
		}
		transaction(temp->mileage, newMileage, income, "Rented", "inRepair", temp->name, temp->plate);
		temp->mileage = newMileage;
		//add car to repair list
		*rented = moveCarfromList(*rented, *inRepair, temp->plate);
	}
	else
	{
		printf("Car not found\n");
	}
}

void fixCar(Car** inRepair, Car** available)
{
	char plate[STRING_MAX];
	printf("Enter rented cars plate to repair\n");
	if (fgets(plate, 255, stdin) == NULL)
	{
		printf("Invalid input\n");
		return;
	}
	//remove newline char
	int test = strlen(plate);
	for (int a = 0; a < test; a++)
		if (plate[a] == '\n')
			plate[a] = '\0';
	if (strlen(plate) > 9 || strlen(plate) < 6)
	{
		printf("Invalid input\n");
		return;
	}
	//look for car in list
	int index = -checkPlate(*inRepair, plate);
	if (index >= 0)
	{
		Car* temp = get(index, *inRepair);
		//output data to user
		printf("\n***********************************\n");
		printf("Car: %s\nPlate: %s\n", temp->name, temp->plate);
		printf("From: %s\nTo: %s\n", "inRepair", "Available");
		printf("***********************************\n\n");
		//correct lists
		*inRepair = moveCarfromList(*inRepair, *available, temp->plate);
		*available = sortAvailable(*available);
	}
	else
	{
		printf("Car not found\n");
	}
}

void rentCar(Car** available, Car** rented)
{
	char charTime[STRING_MAX];
	int time;
	printf("Enter the expected return date\n");
	if (fgets(charTime, 255, stdin) == NULL)
	{
		printf("Invalid input\n");
		return;
	}
	//remove newline char
	int test = strlen(charTime);
	for (int a = 0; a < test; a++)
		if (charTime[a] == '\n')
			charTime[a] = '\0';
	time = checkNum(charTime);
	//check for reasonable number
	if (time < 20160000 || time > 21110000)
	{
		printf("Invalid input\n");
		return;
	}
	//int time = 20160718;
	Car* toRent = get(0, *available);
	toRent->time = time;
	//output data to user
	printf("\n***********************************\n");
	printf("Car: %s\nPlate: %s\n", toRent->name, toRent->plate);
	printf("From: %s\nTo: %s\n", "Available", "Rented");
	printf("***********************************\n\n");
	//correct lists
	*available = moveCarfromList(*available, *rented, toRent->plate);
	*rented = sortRented(*rented);
}

Car* moveCarfromList(Car* from, Car* to, char* plate)
{
	//look for car
	int index = checkPlate(from, plate);
	if (index < 1)
	{
		//move car from 'from' to 'to'
		Car* temp = get(-index, from);
		from = removeIndex(from, -index);
		addToBack(to, temp);
	} 
	else
	{
		printf("Car not found in list\n");
	}
	return from;
}

void transaction(int prevDist, int newDist, float* income, char* from, char* to, char* car, char* plate)
{
	int dist = newDist - prevDist;
	float cost = 40;
	if (dist > 100)
		cost += (dist-100)*0.15;
	printf("\n***********************************\n");
	printf("Car: %s\nPlate: %s\n", car, plate);
	printf("From: %s\nTo: %s\n", from, to);
	printf("Distance travleld: %d\nTotal cost: $%.2f\n", dist, cost);
	printf("***********************************\n");
	*income += cost;
}

void run(Car** available, Car** rented, Car** inRepair, int input, float* income)
{
	switch (input)
	{
		case 1:
			*available = addNewCar(*available, *rented, *inRepair);
			break;
		case 2:
			returnCar(rented, available, income);
			break;
		case 3:
			carIsKill(rented, inRepair, income);
			break;
		case 4:
			fixCar(inRepair, available);
			break;
		case 5:
			rentCar(available, rented);
			break;
		case 6:
			printf("\nAvailable\n");
			printList(*available);
			printf("\nRented\n");
			printList(*rented);
			printf("\nIn Repair\n");
			printList(*inRepair);
			break;
		case 7:
			printf("Exit\n");
			break;
		default:
			printf("Invalid number\n");
	}
}
