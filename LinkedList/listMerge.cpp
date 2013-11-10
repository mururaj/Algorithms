#include <stdio.h>
#include <stdlib.h>

#define MAXLISTLENGTH 3
typedef struct node
{
	int data;
	node *next;
}Node;

int main()
{
	Node *list1Head = NULL, *list2Head = NULL;
	Node *mergeListHead = NULL;
	int numElements;
	int getInput(Node **listHead);
	void printList(Node *listHead);
	Node *mergeList(Node *list1Head,Node *list2Head);
	
	printf("enter total num of elements for list1\n");
	scanf("%d",&numElements);

	if (numElements > MAXLISTLENGTH)
	{
		printf("Only %d elements permitted\n", MAXLISTLENGTH);
		return 0;
	}

	for (int i=1;i<=numElements;i++)
	{
		if (!getInput(&list1Head))
			{
				return 0;
			}
	}

	printf("enter total num of elements for list2\n");
	scanf("%d",&numElements);

	if (numElements > MAXLISTLENGTH)
	{
		printf("Only %d elements permitted\n", MAXLISTLENGTH);
		return 0;
	}
	
	for (int i=1;i<=numElements;i++)
	{
		if (!getInput(&list2Head))
			{
				return 0;
			}
	}	
	
	printList(list1Head);
	printList(list2Head);

	mergeListHead = mergeList(list1Head,list2Head);

	printList(mergeListHead);

	return 0;
}

int getInput(Node **listHead)
{
	
	Node *tmpNode = (Node *)malloc(sizeof(Node));

	if (!tmpNode)
	{
		printf("Unable to get memeory for new node\n");
		return 0;
	}

	printf("Enter data\n");
	scanf("%d",&tmpNode->data);
	
	tmpNode->next = *listHead;
	*listHead = tmpNode;

	return 1;
}

void printList(Node *listHead)
{
	while (listHead)
	{
		printf("%d ->",listHead->data);
		listHead = listHead->next;
	}
	printf("\n");
}

// Merge both the list by alternatively linking the nodes
Node *mergeList(Node *list1Head,Node *list2Head)
{
	Node *mergeListHead;
	if (!list1Head)
	{
		return list2Head;
	}

	if (!list2Head)
	{
		return list1Head;
	}

	mergeListHead = list1Head;

	Node *list1Next, *list2Next;
	while (list1Head && list2Head)
	{
		list1Next = list1Head->next;
		list2Next = list2Head->next;
		if (list2Head)
		{
			list1Head->next = list2Head;
		}		
		list1Head = list1Next;

		if (list1Head)
		{
			list2Head->next = list1Head;
		}		
		list2Head = list2Next;
	}

	// Return the merged list head
	return mergeListHead;

}

