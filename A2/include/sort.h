#ifndef __SORT_MULLINSN__
#define __SORT_MULLINSN__
#include "linkedList.h"

//sorts a rented list
Car* sortRented(Car* rented);

//sorts an available list
Car* sortAvailable(Car* available);

//will swap 2 elements in a list
Car* swap(int a, int b, Car* list);

#endif