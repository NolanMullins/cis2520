#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nameThisLater.h"

int main (int argc, char* argvp[])
{
	char arr[20][10][3];
	//parse f.dat
	parseFile(arr);

	int heap[20];
	//load keys into heap
	for (int a = 0; a < 20; a++)
	{
		heap[a] = getKey(arr, a);
	}
	//perform downheap
	downHeap(heap);
	//print out data in heap order
	for(int a = 0; a < 20; a++)
		printKey(heap[a], arr);		
}