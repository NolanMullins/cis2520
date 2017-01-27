#ifndef __LINKEDLIST_MULLINSN__
#define __LINKEDLIST_MULLINSN__
//#include "linkedList.h"

/**
 * Car_List Struct
 */
struct Car{
	char* name;
	char* plate;
	int mileage;
	int time;
	struct Car* next;
};

typedef struct Car Car;

//create a Car* node
Car * createRecord(char * name, char * plate, int milage, int time);

//prints a given node
char * printRecord(Car * toPrint);

//REKT'd
void destroyRecord(Car * toDie);

//adds a node to the front
Car * addToFront(Car * theList, Car * toBeAdded);

//adds a node to the back
Car * addToBack(Car * theList, Car * toBeAdded);

//removes the first node
Car * removeFromFront(Car * theList);

//removes the last node
Car * removeFromBack(Car * theList);

//gets the last node
Car * getLastItem(Car * theList);

//gets the first node
Car * getFirstItem(Car * theList);

//prints the list
void printList(Car * theList);

//when where u when list is kill?
void destroyList(Car * theList);

//gets index x from list
Car* get(int x, Car* list);

//gets the length of a list
int length(Car* list);

//DONT USE
int getLength(int x, Car* list);

//insert a node at pos
Car* insert(Car* head, Car* toAdd, int pos);

//removes an index (DOESNT FREE IT)
Car* removeIndex(Car* head, int index);

#endif