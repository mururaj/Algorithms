#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define NUM_ELEMENTS 100

void swapElements(int *listVal1, int *listVal2);

int main()
{
	int inputList[MAX_SIZE], lowerIndex = 0;
	void generateElements(int inputList[]);
	void printElements(int inputList[]);
	int quickSort(int inputList[],int listSize,int lowerIndex);
	

	generateElements(inputList);
	quickSort(inputList,NUM_ELEMENTS,lowerIndex);
	printElements(inputList);
	
	return 1;
}

void generateElements(int inputList[])
{
	for (int i=0;i<NUM_ELEMENTS;i++)
	{
		inputList[i] = rand() % 100 + 1;
	}
}

void printElements(int inputList[])
{
	for (int i=0;i<NUM_ELEMENTS;i++)
	{
		printf("%d ",inputList[i]);
	}

	printf("\n");
}

int quickSort(int inputList[],int listSize, int lowerIndex)
{
	int pivotElement, upperIndex;


	printf("%d listSize \n",listSize);

	if (listSize < 2)
	{
		return 1;
	}

	pivotElement = inputList[ rand() % listSize];

	lowerIndex = 0;
	upperIndex = listSize -1;

	printf("Pivot value is %d\n",pivotElement);
	while (lowerIndex < upperIndex)
	{
		while (inputList[lowerIndex] <= pivotElement)
		{
			lowerIndex++;
		}
	
		// printf("Exit loop1\n");
		while (inputList[upperIndex] >= pivotElement)
		{
			upperIndex--;
		}

		//printf("Exit loop2\n");

		printf("Before swap lowerIndex val= %d upperIndex val = %d\n",inputList[lowerIndex],inputList[upperIndex]);
		swapElements(&inputList[lowerIndex],&inputList[upperIndex]);
		printf("After swap lowerIndex val= %d upperIndex val = %d\n",inputList[lowerIndex],inputList[upperIndex]);
	}

	printf("Exit loop3\n");
	
	quickSort(inputList,lowerIndex,0);
	quickSort(&inputList[lowerIndex+1],listSize - lowerIndex -1,0);
}

void swapElements(int *listVal1, int *listVal2)
{
	int temp;
	temp = *listVal1;
	*listVal1 = *listVal2;
	*listVal2 = temp;
}
