#include <stdio.h>
#include <stdlib.h>
#define MAXHEAPSIZE 50
#define ER_INVALIDSIZE 1
#define ER_MEM 2
#define ER_INSERT 3
#define ER_DELETE 4

int getParentIndex(int);
int getMaxChildIndex(int *,int,int);

int main()
{
	int heapSize;
	int *heapArray;
	int currentLength;
	int insertElements(int *,int,int,int);
	int deleteElement(int *,int);
	int printHeap(int *,int);	
	int lpCount,data;
	int maxElement;

	printf("Enter the size of heap\n");
	scanf("%d",&heapSize);

	
	// check for heap size error
	if (heapSize <= 0 || heapSize > MAXHEAPSIZE)
	{
		printf("Invalid heap size \n");
		return ER_INVALIDSIZE;
	}

	// Allocate memory to heap array
	heapArray = (int *) malloc(sizeof(int) * heapSize);

	if (!heapArray)
	{
		printf("Unable to allocate memory for heap array \n");
		return ER_MEM;
	}

	// Build the heap
	printf("Please enter total of %d data\n",heapSize);

	for (lpCount=0;lpCount<heapSize;lpCount++)
	{
		scanf("%d",&data);
		if (!insertElements(heapArray,heapSize,
							lpCount,data))
		{
			printf("Insertion failed\n");
			return ER_INSERT;
		}
	}

	currentLength = lpCount;

	
	printHeap(heapArray,heapSize);

	maxElement = deleteElement(heapArray,currentLength);

	if (maxElement == -1)
	{
		printf("Removal of heap element failed\n");
		return ER_DELETE;
	} else
	{
		printf("The removed max element is %d \n",maxElement);
		// update current length
		-- currentLength;
	}

	printHeap(heapArray,heapSize);

	maxElement = deleteElement(heapArray,currentLength);

	if (maxElement == -1)
	{
		printf("Removal of heap element failed\n");
		return ER_DELETE;
	} else
	{
		printf("The removed max element is %d \n",maxElement);
		// update current length
		-- currentLength;
	}

	printHeap(heapArray,heapSize);

	return 1;
}

int insertElements(int *heapArray,int heapSize,
					int currentLength,int data)
{
	
	int currentIndex = currentLength;
	char insertionDone = 'F';
	int myParentIndex;
	int tmpElement;

	// Check null condition
	if (!heapArray)
	{
		printf("Heap array doesn't exist\n");		
		return 0;
	}
	
	// If this is first element, insert and return
	if (currentLength == 0)
	{
		heapArray[0] = data;
		insertionDone = 'T';
		return 1;
	}

	// Assign data into heap array
	heapArray[currentIndex] = data;

	while (insertionDone == 'F')
	{
		myParentIndex = getParentIndex(currentIndex);
		if (myParentIndex == -1)
		{
			#ifdef DEBUG
			printf("No need to get root parent\n");
			#endif

			insertionDone = 'T';
			return 1;
		}

		// Compare and swap
		if (heapArray[currentIndex] > heapArray[myParentIndex])
		{
			tmpElement = heapArray[currentIndex];
			heapArray[currentIndex] = heapArray[myParentIndex];
			heapArray[myParentIndex] = tmpElement;

			currentIndex = myParentIndex;
		} else
		{
			insertionDone = 'T';
			return 1;
		}
	}
	
}


int getParentIndex(int childIndex)
{
	//check for error condition
	if (childIndex == 0)
	{
		#ifdef DEBUG
		printf("Error: No parent for root\n");
		#endif

		return -1;
	}

	//compute parent Index
	return (childIndex - 1)/2;
}

void printHeap(int *heapArray,int heapSize)
{
	int lpCnt;

	for (lpCnt = 0;lpCnt<heapSize;lpCnt++)
	{
		printf("%d ",heapArray[lpCnt]);
	}
	
	printf("\n");
	return;
}

int deleteElement(int *heapArray,int currentLength)
{
	int maxElement,tmpElement;
	char deletionDone = 'F';
	int currentParentIndex,maxChildIndex;

	//Check for null error
	if (!heapArray)
	{
		printf("Heap array doesn't exist \n");
		return -1;
	}

	if (currentLength == 0)
	{
		printf("Heap array is empty \n");
		return -1;
	}
	
	// Always first element is max element in maxHeap
	maxElement = heapArray[0];

	// Check if only one element in heap
	if (currentLength == 1)
	{
		// empty the heap
		heapArray[0] = 0;
		deletionDone = 'T';
		return maxElement;
	}

	// Assign last child to root
	heapArray[0] = heapArray[currentLength-1];
	heapArray[currentLength-1] = 0;

	// As one element deleted, update current length
	--currentLength;

	// Starting from new root element
	currentParentIndex = 0;

	while (deletionDone == 'F')
	{
		maxChildIndex = getMaxChildIndex(heapArray,currentParentIndex,currentLength);
		if (maxChildIndex == -1)
		{
			printf("get max child returned an error\n");
			return -1;
		} else if (maxChildIndex == -2)
		{
			deletionDone = 'T';
			return maxElement;
		}

		// Compare with child and swap
		if (heapArray[currentParentIndex] < heapArray[maxChildIndex])
		{
			tmpElement = heapArray[currentParentIndex];
			heapArray[currentParentIndex] = heapArray[maxChildIndex];
			heapArray[maxChildIndex] = tmpElement;

			// Update max child as new parent
			currentParentIndex = maxChildIndex;
		} else
		{
			deletionDone = 'T';
			return maxElement;
		}
	}

}


int getMaxChildIndex(int *heapArray,int currentParentIndex,int currentLength)
{
	int maxChildIndex;

	// parent Index can't be larger than total elements
	if (currentParentIndex >= currentLength || currentParentIndex < 0)
	{
		printf("Error: Invalid parent index exceeded heap size or -ve \n");
		return -1;
	}

	// Check if this parent has any children
	if ( (2*currentParentIndex + 1) >= currentLength)
	{
		#ifdef DEBUG
			printf("No children to compare \n");
		#endif
		return -2;		
	}

	// Check if this parent has only one children
	if ((2*currentParentIndex + 2) >= currentLength)
	{
		// return the left child index
		return (2*currentParentIndex + 1);
	}

	// Now this parent has both children
	// Return index of max child
	return  heapArray[2*currentParentIndex+1]
		    >heapArray[2*currentParentIndex+2]?
			2*currentParentIndex+1:2*currentParentIndex+2;

}
