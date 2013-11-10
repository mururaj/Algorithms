/*
Author: Muruganantham Raju
Implementation of Bubble Sort algorithm
*/
#include <stdio.h>
#include <stdlib.h>

# define MAX_SIZE 10000
# define NUM_ELEMENTS 10000
# define FALSE 0
# define TRUE 1


int main()
{
	int inputElements[MAX_SIZE];
	void generateInput(int inputElements[]);
	void printElements(int inputElements[]);
	void bubbleSort(int inputElements[]);

	generateInput(inputElements);

	printf("Unsorted list\n");

	printElements(inputElements);

	bubbleSort(inputElements);

	printf("Sorted list\n");

	printElements(inputElements);

}

/* 
Func generateInput: generate input integers in the 
range 1 to 100 using random number generator
Args:
"inputElements[]" array to store generated values
*/

void generateInput(int inputElements[])
{
	for (int i=0;i<NUM_ELEMENTS;i++)
	{
		inputElements[i] = rand() % 100 + 1;
	}	
}

/*
Func printElements: print the elements of the array
Args:
"inputElements[]" array to be printed
*/

void printElements(int inputElements[])
{
	for (int i=0;i<NUM_ELEMENTS;i++)
	{
		printf("%d ",inputElements[i]);
	}

	printf("\n");
}

/*
Func bubbleSort: Implements bubble sort algorithm
and produce sorted list of integers
Args:
"inputElements[]" input integer array to be sorted
Algorithm:
1. Initially SWAP to FALSE for every iteration
2. Compare adjascent elements and swap them if 
- lower index has element > higher index element
3. End of each iteration of outer loop, at least
- one higher element get placed at sorted position
4. The lower value elements bubble up to front of 
- array.
5. If no SWAP has been performed for any iteration,
- it signifies the list is already sorted. Thus the
- best case performance of bubbleSort is O(n) for 
- a sorted array.
*/
void bubbleSort(int inputElements[])
{
	int temp;
	bool SWAP = FALSE; 

	for (int j=0;j<NUM_ELEMENTS;j++)
	{
		// Reinitialize SWAP to FALSE
		SWAP = FALSE;

		for (int i=0;i<NUM_ELEMENTS-1-j;i++)
			{
				// Compare and swap if necessary
				if (inputElements[i] > inputElements[i+1])
				{
					temp = inputElements[i+1];
					inputElements[i+1] = inputElements[i];
					inputElements[i] = temp;
					SWAP = TRUE;
				}
			}
		
		// if no swap, array is sorted
		if (!SWAP)
		{
			break;
		}
	}
	
}

