#include <stdio.h>
#include <stdlib.h>

# define LISTSIZE 20

const int countArraySize = 6; // Stub the returns max element of array

int main()
{
	unsigned int inputArray[LISTSIZE];
	unsigned int outputArray[LISTSIZE];
	unsigned int countArray[countArraySize];

	int getInput(unsigned int []);
	void printList(unsigned int [], unsigned int);

	if (!getInput(inputArray))
	{
		printf("Unable to build array\n");
		return 0;
	}

	// Initialize count array
	for (int i=0;i<countArraySize;i++)
	{
		countArray[i] = 0;
	}

	// Count the number of ocurrances of each element
	for (int i=0;i<LISTSIZE;i++)
	{
		countArray[inputArray[i]-1]++;
	}

	unsigned int outputArrayIndex = 0;

	
	for (unsigned int countArrayIndex=0;countArrayIndex<countArraySize;countArrayIndex++)
	{
		if (outputArrayIndex >= LISTSIZE)
		{
			return 0;
		}

		// populate the output array in sorted order
		for (int j=1;j<=countArray[countArrayIndex];j++)
		{
			outputArray[outputArrayIndex++] = countArrayIndex+1;
		}
	} 

	printList(inputArray,LISTSIZE);

	printList(countArray,countArraySize);

	printList(outputArray,LISTSIZE);

	return 1;
}


// A function to get input
int getInput(unsigned int inputArray[])
{
	if (LISTSIZE <=0)
	{
		return 0;
	}

	for (int i=0;i<LISTSIZE;i++)
	{
		inputArray[i] = rand() % countArraySize + 1;
	}

	return 1;
}

// function to print the array list
// Takes array and array size as input
void printList(unsigned int inputArray[], unsigned int arrayLength)
{
	for (int i=0;i<arrayLength;i++)
	{
		printf("%u ",inputArray[i]);
	}

	printf("\n");
}
