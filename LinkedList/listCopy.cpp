/*
Author: Muruganantham Raju
Program to copy a linked list with given structure & duplicate the list
*/
#include <stdio.h>
#include <stdlib.h>
#include <tr1/unordered_map>
#include <iostream>
using namespace std::tr1;

#define LENGTH 5

// Each node has next and random pointers
typedef struct node 
{
	node *next;    //   points to next element of list
	node *random;  // points to any random element of list including itself
	int data;
}Node;

int main()
{
	Node *head = NULL;
	Node *duplicateList = NULL;
	int numNodes,position=-1;
	int insertElement(Node **head);
	void printList(Node *head);
	int fillupRandom(Node *head,int nodePosition,int randPosition);
	Node *listCopy(Node *head);

	// Create list1
	for (int i=0;i<LENGTH;i++)
	{
		if (!insertElement(&head))
		{
			return 0;
		}
	}

	printList(head);
	
	// Determine random pointers for list1
	for (int i=0;i<LENGTH;i++)
	{
		printf("Enter the position of element that rand must point to\n");
		scanf("%d",&position);

		if( position < 0 || position >= LENGTH)
		{
			printf("You entered wrong position\n");
			printf("This node will be linked to itself\n");
			if (!fillupRandom(head,i,i))
			{
				printf("Unable to set random pointer. Exiting\n");
				return 0;
			}
		} else
		{
			if (!fillupRandom(head,i,position))
			{
				printf("Unable to set random pointer. Exiting\n");
				return 0;
			}
		}
		
	}

	printList(head);
	
	// Create a new copy of list1
	duplicateList = listCopy(head);

	printList(duplicateList);
	return 1;
}

/*
Func insertElement: insert an element to tail of the list
Args:
"Node **head" pointer to list head pointer
*/

int insertElement(Node **head)
{
	
	// create a new node
	Node *tmpNode = (Node *) malloc(sizeof(Node));

	if (!tmpNode)
	{
		return 0;
	}
	tmpNode->next = NULL;
	tmpNode->random = NULL;

	printf("Enter data for your node\n");
	scanf("%d",&tmpNode->data);

	// if no head, set head
	if (!*head)
	{
		*head = tmpNode;
		return 1;
	}

	Node *currentNode = *head;

	// every call move till end of list (insertion point)
	while (currentNode->next)
	{
		currentNode = currentNode->next;
	}

	// insert the new node into tail of the list
	currentNode->next = tmpNode;
	
	return 1;
}


/*
Func printList: print the entire list
Args:
"Node *head" -> head of the list 
*/
void printList(Node *head)
{
	if (!head)
	{
		printf("Head is empty\n");
	}
	while (head)
	{
		printf("Node Data %d ->", head->data);
		// also print data of random node 
		if (head->random)
		{
			printf("Random Node Data %d->", head->random->data);
		}
		head = head->next;
		printf("\n");
	}
}

/*
Func fillupRandom: to link current node to chosen random node of the list
Args:
"Node *head" -> head of the linked list
"int nodePosition" -> Position of node from head (starts with 0) of the list
"int nodePosition" -> Position of random node to be pointed
*/
int fillupRandom(Node *head,int nodePosition,int randPosition)
{
	Node *currentNode = NULL, *randNode = NULL;
	int listIterator = 0;

	while (listIterator < LENGTH)
	{
		if (!head)
		{
			return 0;
		}

		// find node at nodePosition
		if (listIterator == nodePosition)
		{
			currentNode = head;
		}

		// find node at randPosition
		if (listIterator == randPosition)
		{
			randNode = head;
		}

		// link randNode to current node
		if (currentNode && randNode)
		{
			currentNode->random = randNode;
			return 1;
		}

		head = head->next;
		listIterator ++;
	}

	// At this point possible error
	return 0;
}

/*
Func listCopy: Create a copy of a list
Args:
"Node *head" -> head of the list to be recreated
Algorithm:
1. Create a hashmap of list1Node, list2Node
2. For every list1Node, create a new list2Node & add
- into hash as key, value pairs
3. Before building any new node, confirm whether the 
- node is already created by checking hashmap with key
4. If a node is already added to hash, then no need to
- create a new node
5. Set next pointer and move node by node in passed list
*/
Node *listCopy(Node *head)
{
	Node *newNode =NULL, *randomNode = NULL;
	Node *newListHead = NULL;
	unordered_map <Node *,Node *> hashSet;
	Node *currentNode = head;
	Node *prevNode = NULL;

	while (currentNode)
	{
		
		if (!hashSet[currentNode])
		{
			newNode = (Node *) malloc(sizeof(Node));

			if (!newNode)
				{
					return NULL;
				}			
	
			newNode->next = NULL;
			newNode->random = NULL;
			newNode->data = currentNode->data;
			// Add to hash <currentNode, newNode>
			hashSet[currentNode] = newNode;
		}

		if (!hashSet[currentNode->random])
		{
			randomNode = (Node *) malloc(sizeof(Node));

			if (!randomNode)
			{
				return NULL;
			}

			randomNode->next = NULL;
			randomNode->random = NULL;
			randomNode->data = currentNode->random->data;
			// Add to hash <currentNode->random, randomNode
			hashSet[currentNode->random] = randomNode;
		}

		newNode = hashSet[currentNode];
		randomNode = hashSet[currentNode->random];
		newNode->random = randomNode;

		if (!prevNode)
		{
			newListHead = newNode;
		} else
		{
			// Set next pointer of new list
			prevNode->next = newNode;
		}

		prevNode = newNode;

		// Move to next element of given list
		currentNode = currentNode->next;

		// it is better to reset these nodes to NULL
		newNode = NULL;
		randomNode = NULL;
	}
	
	// Return head of newly created node
	return newListHead;
}
