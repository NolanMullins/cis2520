#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedList.h"

Car * createRecord(char * name, char * plate, int mileage, int time)
{

  //memory test
  if (name == NULL)
    return NULL;

  //value test
  if (strlen(name) >= 255 || strlen(plate) > 9 || mileage < 0)
  {
    return NULL;
  }

  Car* newCar;
  newCar = malloc(sizeof(Car));
  if (newCar == NULL)
    return NULL;
  //name
  newCar->name = malloc(sizeof(char)*256);
  if (newCar->name == NULL)
  {
    free(newCar);
    return NULL;
  }
  //plate
  newCar->plate = malloc(sizeof(char)*10);
  if (newCar->plate == NULL)
  {
    free(newCar->name);
    free(newCar);
    return NULL;
  }
  strcpy(newCar->name, name);
  //free(name);

  strcpy(newCar->plate, plate);
  //free(group);

  newCar->next = NULL;
  newCar->mileage = mileage;
  newCar->time = time;

  return newCar;
}

char * printRecord(Car * toPrint)
{
  if (toPrint == NULL)
  {
    return NULL;
  }
  //generate and return line
  char* line = malloc(sizeof(char)*256);
  sprintf(line, "%s   Plate:%s   Mileage:%d   Time:%d", toPrint->name, toPrint->plate, toPrint->mileage, toPrint->time);
  return line;
}

Car* get(int x, Car* list)
{
  if (x==0)
    return list;
  if (list->next == NULL)
    return NULL;
  return get(--x, list->next);
}

int length(Car* list)
{
  if (list == NULL)
    return 0;
  return getLength(1, list);
}

int getLength(int x, Car* list)
{
  if (list->next == NULL)
    return x;
  return getLength(++x, list->next);
}

Car* insert(Car* head, Car* toAdd, int pos)
{
  Car* instertAfter = get(pos-1, head);
  toAdd->next = instertAfter->next;
  instertAfter->next = toAdd;
  return head;
}

Car* removeIndex(Car* head, int index)
{
  if (index == 0)
  {
    Car* newHead = head->next;
    return newHead;
  }
  Car* before = get(index-1, head);
  Car* destroyMe = before->next;
  if (destroyMe == NULL)
    return head;
  before->next = destroyMe->next;
  return head;
}

void destroyRecord(Car * toDie)
{
  if (toDie != NULL)
  {
    if (toDie->name != NULL)
    {
      free(toDie->name);
    }
    if (toDie->plate != NULL)
    {
      free(toDie->plate);
    }
    free(toDie);
  }
}

Car * addToFront(Car * theList, Car * toBeAdded)
{
  if (toBeAdded == NULL)
    return theList;
  toBeAdded->next = theList;
  return toBeAdded;
}

Car * addToBack(Car * theList, Car * toBeAdded)
{
  if (theList != NULL)
  {
    getLastItem(theList)->next = toBeAdded;
    toBeAdded->next = NULL;
    return theList;
  }
  return toBeAdded;
}

Car * removeFromFront(Car * theList)
{
  if (theList != NULL)
  return theList->next;
  return NULL;
}

Car * removeFromBack(Car * theList)
{
  if (theList != NULL && theList->next != NULL)
  {
    Car* head = theList;
    while (theList->next->next != NULL)
    {
      theList = theList->next;
    }
    theList->next = NULL;
    return head;
  }
  return NULL;
}

Car * getLastItem(Car * theList)
{
  if (theList != NULL)
  {
    if (theList->next == NULL)
    {
      return theList;
    }
    else
    {
      return getLastItem(theList->next);
    }
  }
  return NULL;
}

Car * getFirstItem(Car * theList)
{
  return theList;
}

int isEmpty(Car * theList)
{
  if (theList == NULL)
  {
    return 1;
  }
  return 0;
}

void printList(Car * theList)
{
  if (theList != NULL)
  {
    char* line = printRecord(theList);
    printf("%s\n", line);
    free(line);
    printList(theList->next);
  }
}

void destroyList(Car * theList)
{
  if (theList != NULL)
  {
    if (theList->next != NULL)
    {
      destroyList(theList->next); 
    }
    destroyRecord(theList);
  }
}
