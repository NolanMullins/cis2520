#include <stdlib.h>
#include "linkedList.h"

Car* swap(int a, int b, Car* list)
{
	Car* x = get(a, list);
	Car* y = get(b, list);
	//if head is being swapped
	if (a == 0)
	{
		list = y;
		x->next = y->next;
		y->next = x;
	}
	else
	{
		Car* prev = get(a-1, list);
		prev->next = y;
		x->next = y->next;
		y->next = x;
	}
	return list;
}

Car* sortRented(Car* rented)
{
	if (rented == NULL)
		return NULL;

	//bubble sort on rented list 
	int l = length(rented);
	int flag = 1;

	while (flag == 1)
	{
		flag = 0;
		for (int a = 0; a < l-1; a++)
		{
			//sort by time
			if (get(a, rented)->time > get(a+1, rented)->time)
			{
				rented = swap(a,a+1, rented);
				flag = 1;
			}
		} 
	}
	return rented;
}

Car* sortAvailable(Car* available)
{
	if (available == NULL)
		return NULL;

	//bubble sort on available list
	int l = length(available);
	int flag = 1;

	while (flag == 1)
	{
		flag = 0;
		for (int a = 0; a < l-1; a++)
		{
			//sort by mileage
			if (get(a, available)->mileage > get(a+1, available)->mileage)
			{
				available = swap(a,a+1, available);
				flag = 1;
			}
		} 
	}
	return available;
}
