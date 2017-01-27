#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "linkedList.h"

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

Car* loadList(char* filepath, Car** list1, Car** list2, Car** list3)
{
	//INIT
	char r = 'r';
	FILE* file = fopen(filepath, &r);
	if (file == NULL)
		return NULL;
	Car* list = NULL;
	char line[STRING_MAX];

	//loop through file and read the records
	for (int a = 0; a < 3; a++)
	{
		while (readLine(file, line) == 0 && strcmp(line, "--") != 0 && strcmp(line, "--\n") != 0)
		{
			//Name
			char name[STRING_MAX];
			rmNewLine(name, line);
			//plate
			if (readLine(file, line) == 1)
			{
				printf("File Error - plate\n");
				exit(0);
			}
			char plate[STRING_MAX];
			rmNewLine(plate, line);
			//mileage
			if (readLine(file, line)==1)
			{
				printf("File Error - mileage\n");
				exit(0);
			}
			char mileString[STRING_MAX];
			rmNewLine(mileString, line);
			int mileage = atoi(mileString);
			//time
			if (readLine(file, line)==1)
			{
				printf("File Error - time\n");
				exit(0);
			}
			char timeString[STRING_MAX];
			rmNewLine(timeString, line);
			int time = atoi(timeString);

			//printf("Name: %s, Plate: %s, Milage: %d, Time: %d\n", name, plate, mileage, time);
			if (a==0)
			{
				//build node
				if (*list1 == NULL)
					*list1 = createRecord(name, plate, mileage, time);
				else
					*list1 = addToBack(*list1, createRecord(name, plate, mileage, time));
			}
			else if (a==1)
			{
				//build node
				if (*list2 == NULL)
					*list2 = createRecord(name, plate, mileage, time);
				else
					*list2 = addToBack(*list2, createRecord(name, plate, mileage, time));
			}
			else
			{
				//build node
				if (*list3 == NULL)
					*list3 = createRecord(name, plate, mileage, time);
				else
					*list3 = addToBack(*list3, createRecord(name, plate, mileage, time));
			}
			
			
		}
	}
	
	fclose(file);
	return list;
}

void saveList(char* filepath, Car* list1, Car* list2, Car* list3)
{
	char w = 'w';
	FILE* file = fopen(filepath, &w);
	//int l = length(listToSave);
	
	for (int a = 0; a < 3; a++)
	{
		int l = 0;
		//get length of list a
		switch (a)
		{
			case 0:
				l = length(list1);
				break;
			case 1:
				l = length(list2);
				break;
			case 2:
				l = length(list3);
				break;
		}
		for (int b = 0; b < l; b++)
		{
			Car* temp = NULL;
			//get index of list a
			switch (a)
			{
				case 0:
					temp = get(b, list1);
					break;
				case 1:
					temp = get(b, list2);
					break;
				case 2:
					temp = get(b, list3);
					break;
			}
			//Name
			fprintf(file, "%s\n", temp->name);
			//Plate
			fprintf(file, "%s\n", temp->plate);
			//Milage
			fprintf(file, "%d\n", temp->mileage);
			//time
			fprintf(file, "%d\n", temp->time);
		}
		fprintf(file, "--\n");
	}
	fclose(file);
}

int checkNum(char* string)
{
	if (string == NULL)
		return -1;
	for (int a = 0; a < strlen(string); a++)
		if (isdigit(string[a]) == 0)
			return -1;
	return atoi(string);
}
