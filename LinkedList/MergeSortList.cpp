#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10

typedef struct node
{
	int data;
	struct node *next;
}Node;

int merge(Node **firstListHead,unsigned int,
		 Node **secondListHead, unsigned int);
int printList(Node *head);

int main(int argc, char *argv[])
{
	Node *head = NULL;
	int insertElements(Node **head);
	int mergeSort(Node **head,int listSize);
	
	if (!insertElements(&head))
	{
		printf("Insertion failed\n");
		return 0;
	}

	printList(head);

	if (!mergeSort(&head,MAXSIZE))
	{
		printf("Merge operation failed\n");
		printList(head);
		return 0;
	}

	printList(head);
	return 1;
}

int insertElements(Node **listHead)
{
	
	for (int i=1;i<=MAXSIZE;i++)
	{
		Node *newNode = (Node *) malloc(sizeof(Node));

		if (!newNode)
		{
			return 0;
		}

		newNode->data = rand();
		newNode->next = NULL;
		
		if (i==1)
		{
			*listHead = newNode;
		} else
		{
			newNode->next = *listHead;
			*listHead = newNode;
		}

	}

	return 1;

}

int printList(Node *listHead)
{
	while (listHead)
	{
		printf("%d ->",listHead->data);
		listHead = listHead->next;
	}

	printf("\n");
	return 1;
}


int mergeSort(Node **listHead,int listSize)
{
	if (!*listHead)
	{
		return 0;
	}

	if (listSize <= 0 || listSize > MAXSIZE)
	{
		return 0;
	}

	if (listSize == 1)
	{
		// split the list into distinct nodes
		(*listHead)->next = NULL;
		return 1;
	}

	Node *firstListHead = *listHead;
	Node *secondListHead = *listHead;
	unsigned int firstListSize = listSize/2+listSize%2;
	unsigned int secondListSize = listSize/2;

	// Get the starting position of second list
	for (int i=1;i<=firstListSize;i++)
	{
		if (!secondListHead)
		{
			return 0;
		}
		secondListHead = secondListHead->next;
	}

	if (!mergeSort(&firstListHead,firstListSize))
	{
		return 0;
	}
	
	printf("Printing first list \n");
	printList(firstListHead);

	if (!mergeSort(&secondListHead,secondListSize))
	{
		
		return 0;
	}

	printf("Printing second list \n");
	printList(secondListHead);
	
	if (!merge(&firstListHead,firstListSize,&secondListHead,secondListSize))
	{
		return 0;
	}	

	printf("Printing merged list \n");
	*listHead = firstListHead;
	printList(*listHead);
	return 1;
}


int merge(Node **firstListHead,unsigned int firstListSize,
			 Node **secondListHead,unsigned int secondListSize)
{
	if (!*firstListHead)
	{
		return 1;
	}

	if (!*secondListHead)
	{
		return 1;
	}

	if (!*firstListHead && !*secondListHead)
	{
		printf("Both heads are empty\n");
		return 0;
	}

	if (firstListSize <=0 || firstListSize > MAXSIZE
		|| secondListSize <=0 || secondListSize > MAXSIZE)
	{
		printf("List size check failed\n");
		return 0;
	}

	Node *firstListCurNode = *firstListHead;
	Node *secondListCurNode = *secondListHead;
	Node *mergeListHead = NULL;
	Node *mergeListCurNode = NULL;
	unsigned int firstListCurPosition = 1;
	unsigned int secondListCurPosition =1;

	while ( firstListCurPosition <= firstListSize
		&& secondListCurPosition <= secondListSize)
	{	
		if (!firstListCurNode || !secondListCurNode)
		{
			printf("One of list cur node empty\n");
			return 0;
		}

		if (firstListCurNode->data < secondListCurNode->data)
		{
			if (!mergeListHead)
			{
				mergeListHead = firstListCurNode;
				mergeListCurNode = mergeListHead;
			} else
			{
				mergeListCurNode->next = firstListCurNode;
				mergeListCurNode = mergeListCurNode->next;
			}
			firstListCurNode = firstListCurNode->next;
			firstListCurPosition++;
			mergeListCurNode->next = NULL;
		} else
		{	
			if (!mergeListHead)
			{
				mergeListHead = secondListCurNode;
				mergeListCurNode = mergeListHead;
			} else
			{
				mergeListCurNode->next = secondListCurNode;
				mergeListCurNode = mergeListCurNode->next;
			}
			secondListCurNode = secondListCurNode->next;
			secondListCurPosition++;
			mergeListCurNode->next = NULL;			
		}
	}

	if (!firstListCurNode && !secondListCurNode)
	{
		*firstListHead = mergeListHead;
		*secondListHead = mergeListHead;
		return 1;
	}

	if (firstListCurPosition <= firstListSize)
	{
		mergeListCurNode->next = firstListCurNode;
		*firstListHead = mergeListHead;
		*secondListHead = mergeListHead;
		return 1;
	} 

	if (secondListCurPosition <= secondListSize)
	{
		mergeListCurNode->next = secondListCurNode;
		*firstListHead = mergeListHead;
		*secondListHead = mergeListHead;
		return 1;
	}

	printf("Possible error here\n");
	return 0;
}
