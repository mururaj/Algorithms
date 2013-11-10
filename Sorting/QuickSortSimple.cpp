/*
Author: Muruganantham Raju
Implementation of simple Quick Sort algorithm
*/

#include <stdio.h>
#include <stdlib.h>

#define NUM_ELEMENTS 1000

// List of integers to hold input ints and sorted ints
int inputList[NUM_ELEMENTS];

int main()
{
	void generateElements();
	void printElements(int integerList[],int listSize);
	int quickSort(int integerList[], int listSize, int beginIndex);

	generateElements();

	printElements(inputList,NUM_ELEMENTS);

	// beginIndex is 0 
	quickSort(inputList,NUM_ELEMENTS,0);

	printElements(inputList,NUM_ELEMENTS);
}

/* 
Func generateElements: generate input integers in the 
range 1 to NUM_ELEMENTS using random number generator
*/
void generateElements()
{
	for (int i=0;i<NUM_ELEMENTS;i++)
	{
		inputList[i] = rand() % NUM_ELEMENTS + 1;
	}
}

/*
Func printElements: print the elements of integer array
Args:
"integerList[]" an array of integers
"listSize" size that corresponds to size of the int array
*/

void printElements(int integerList[],int listSize)
{
	for (int i=0;i<listSize;i++)
	{
		printf("%d ",integerList[i]);
	}

	printf("\n");
}

/*
Func quickSort: sort the input list of integers using quick-
sort algorithm
Args:
"integerList[]" an array of integer containing full/partial list
- of numbers to be sorted
"listSize" size of the input list
"beginIndex" the begining position of the partitioned array 
- corresponds to original array 
algorithm:
	1. if listSize <=1 return 
	2. Select a pivot element (randomly) from the integerList
	3. Move all the elements less than pivot to smallerIntegerList
	   Rest of the elements to largerIntegerList. Note that the 
	   choosen pivot element to be excluded from comparison
	4. Assign the current pivot element to final sorted list
	5. Call quickSort on smallerIntegerList & largerIntegerList
*/

int quickSort(int integerList[], int listSize, int beginIndex)
{
	int pivotElement,smallListIndex=0,largeListIndex=0;
	int pivotElementIndex;
	int smallerIntegerList[NUM_ELEMENTS];
	int largerIntegerList[NUM_ELEMENTS];

	if (listSize <= 1)
	{
		inputList[beginIndex] = integerList[0];
		return 1;
	}

	pivotElementIndex = rand() % listSize;
	pivotElement = integerList[ pivotElementIndex ];

	for (int inputListIndex=0;inputListIndex<listSize;inputListIndex++)
	{
		// Exclude pivotelement from comparison
		if ( inputListIndex != pivotElementIndex)
		{
			if (integerList[inputListIndex] < pivotElement)
			{
				smallerIntegerList[smallListIndex++] = integerList[inputListIndex];
			} else
			{
				largerIntegerList[largeListIndex++] = integerList[inputListIndex];
			}
		}
	}

	// pivotElement to be inserted at position corresponds
	// to number of elements in smallerlist so far
	inputList[beginIndex+smallListIndex] = pivotElement;

	// if there is no element in smallerlist, no need to sort
	if (smallListIndex != 0)
	{
		quickSort(smallerIntegerList,smallListIndex,beginIndex);
	}

	// if there is no element in largerlist, no need to sort
	if (largeListIndex != 0)
	{
		// Note that the thir arg is the begnining index of paritioned array
		// corresponds to orignial array size
		quickSort(largerIntegerList,largeListIndex,beginIndex+smallListIndex+1);
	}	

}
