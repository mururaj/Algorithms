/*
Author: Muruganantham Raju
Implementation of Merge Sort algorithm
*/

#include <stdio.h>
#include <stdlib.h>

# define MAX_SIZE 1000
# define MIN_SIZE 1

# define NUM_ELEMENTS 1000

void copyMergeList(int partialMergeList[],int listSize);
int merge(int partialMergeList1[],int list_1_Size,int partialMergeList2[],int list_2_Size);
void printMergeList(int size);


// Global mergeList into which the sorted merged values 
// are stored. 
int mergeList[MAX_SIZE];

int main()
{
	int inputElements[MAX_SIZE];
	int numElements;
	const int beginIndex = 0;
	void getElements(int inputElements[], int numElements);
	void generateInput(int inputElements[]);
	int mergeSort(int inputElements[], int numElements, int beginIndex);

	numElements = NUM_ELEMENTS;
	
	/*
	printf("Enter number of elements\n");
	scanf("%d",&numElements);
	*/
	
	if (numElements > MAX_SIZE && numElements < MIN_SIZE)
	{
		printf("Number of elements must be within range of %d to %d",MAX_SIZE,MIN_SIZE);
		return 1;
	}

	/* Function to get user input instead auto generation
	getElements(inputElements,numElements);
	*/

	generateInput(inputElements);

	mergeSort(inputElements,numElements,beginIndex);

	printMergeList(numElements);
	
	return 0;
}

/*
Func getElements: get the input integers from the user
Args:
"inputElements[]" array to store the input values
"numElements" number of input value
*/
void getElements(int inputElements[],int numElements) 
{
	printf("Enter input integers");
	for(int i=0;i<numElements;i++)
	{
		scanf("%d",&inputElements[i]);	
	}
}


/*
Func mergeSort: performs the merge sorting of input integer array
	1. Split the array into two partialMergeList
    2. Call merge sort on each partialMergeList
	3. Merge the partially sorted list into One

Args:
"inputElements[]" array of input integers
"numElements" number of elements in the input array
"beginIndex" the beginning index position within inputElements[] array
*/
int mergeSort(int inputElements[],int numElements, int beginIndex)
{
	int k=0, i=beginIndex,list_1_Size,list_2_Size;
	int partialMergeList1[MAX_SIZE], partialMergeList2[MAX_SIZE];


	// if number of elements is 1, then assign that element to merge
	// list and return
	if (numElements == 1)
	{
		mergeList[k] = inputElements[i];
		return 1;
	}

	// Divide the list into two partialList
	list_1_Size = numElements/2;
	list_2_Size = numElements/2+numElements%2;

	// MergeSort the partialList1
	mergeSort(inputElements,list_1_Size,i);

	#ifdef DEBUG
	printf("PartialList1 Merge\n");
	printMergeList(list_1_Size);
	#endif

    // Partially sorted list is store in mergeList global array
	// Copy the partially sorted list from gloabl array to partial
	// MergeList1
	copyMergeList(partialMergeList1,list_1_Size);

	// MergeSort the partialList2
	mergeSort(inputElements,list_2_Size,i+list_1_Size);

	#ifdef DEBUG
	printf("PartialList2 Merge\n");
	printMergeList(list_2_Size);
	#endif

	copyMergeList(partialMergeList2,list_2_Size);

    // Partially sorted list is store in mergeList global array
    // Copy the partially sorted list from gloabl array to partial
	// MergeList2
	merge(partialMergeList1,list_1_Size,partialMergeList2,list_2_Size);

	#ifdef DEBUG
	printf("After Merge\n");
	printMergeList(numElements);
	#endif 

	return 1;
}

/*
Func copyMergeList: Copy paritally sorted values from 
global mergeList to partialList
Args:
"partialMergeList[]" array to store partially sorted integers
"listSize" size of the partially sorted array
*/

void copyMergeList(int partialMergeList[],int listSize)
{
	for (int i=0;i<listSize;i++)
	{
		partialMergeList[i]= mergeList[i];
	}	
	
}

/*
Func merge: Merge two partially sorted list into
single sorted list and store it on global mergeList
Args:
"partialMergeList1[]" array of integers containing first
half of sorted values
"list_1_Size" size of the partially sorted array partialMergeList1
"partialMergeList2[]" array of integers containing second
half of sorted values
"list_2_Size" size of the partially sorted array partialMergeList2
*/

int merge(int partialMergeList1[],int list_1_Size,int partialMergeList2[],int list_2_Size)
{
	int list_1_Index=0,list_2_Index=0,mergeListIndex=0;

	while (mergeListIndex<list_1_Size+list_2_Size)
	{
		if (list_1_Index>=list_1_Size || list_2_Index>=list_2_Size)
		{
			// break if all values of any one of array has been compared
			break;
		}
		
		// Move list_1_index when its value is lesser than partialMergeList2
		if (partialMergeList1[list_1_Index] < partialMergeList2[list_2_Index])
		{
			mergeList[mergeListIndex++] = partialMergeList1[list_1_Index++];
		} 
		else 
		{
			// Move list_2_index when its value is lesser than partialMergeList1
			mergeList[mergeListIndex++] = partialMergeList2[list_2_Index++];
		}
	}

	
	// Copy remaining elements if any into global mergeList
	while (list_1_Index < list_1_Size)
	{
		mergeList[mergeListIndex++] = partialMergeList1[list_1_Index++];
	}

	while (list_2_Index < list_2_Size)
	{
		mergeList[mergeListIndex++] = partialMergeList2[list_2_Index++];
	}

	return 1;

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
Func printMergeList: print the elements of the merged array
Args:
"size" size that corresponds to total num of elements stored
in global mergeList at this moment of operation
*/

void printMergeList(int size)
{
	for (int i=0;i<size;i++)
	{
		printf("%d ",mergeList[i]);
	}
	printf("\n");
}


