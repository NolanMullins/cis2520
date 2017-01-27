#ifndef __FUNCTIONS_MULLINSN__
#define __FUNCTIONS_MULLINSN__

#include "linkedList.h"

//return 1 if plate is unique else returns -index
int checkPlate(Car* list, char* plate);

//will ask the user for a new plate (returns input)
char* askForPlate(Car* available, Car* rented, Car* inRepair);

//will run the users selected choice
void run(Car** available, Car** rented, Car** inRepair, int input, float* income);

//adds a new car to available list
Car* addNewCar(Car* available, Car* rented, Car* inRepair);

//moves a car as defined by its plate from 'from' to 'to'
Car* moveCarfromList(Car* from, Car* to, char* plate);

//user will return a car to the available list
void returnCar (Car** rented, Car** available, float* income);

//user f***'d the car up
void carIsKill(Car** rented, Car** inRepair, float* income);

//move a car from available to rented
void rentCar(Car** available, Car** rented);

//move car from inRepair to available
void fixCar(Car** inRepair, Car** available);

//get a mileage number from the user
int askForMileage();

//complate a $$$ transaction
void transaction(int prevDist, int newDist, float* income, char* from, char* to, char* car, char* plate);

#endif