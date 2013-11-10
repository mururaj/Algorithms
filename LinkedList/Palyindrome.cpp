/*
Author: Muruganantham Raju
A program to check if elements of a linked list form a palindrome
*/

#include <stdio.h>
#include <stdlib.h>

// Linked list node structure
typedef struct node 
{
    char data;
	node *next;
}Node;

int listLength;

int main()
{
	Node *listHead = NULL;
	int getInput(Node **listHead);
	void printList(Node *listHead);
	bool isPalindrome(Node *listHead);

	if(!getInput(&listHead))
	{
		printf("Unable to build list \n");
		return 0;
	}

	printList(listHead);

	if (isPalindrome(listHead))
	{
		printf("The list is Palindrome\n");
	} else
	{
		printf("The list is not a Palindrome\n");
	}

	return 1;
}

/*
Func: getInput to get user data and store into list
Args: 
"Node **listHead" Pointer to list head pointer
Algorithm:
1) get user input char until char 1 is typed
2) For each received char create a new node and store 
- the character in data portion of node
*/
int getInput(Node **listHead)
{
	Node *tmpNode;
	char tmpChar;
	printf("Please enter char. To exit enter 1 \n");

	
	while ((tmpChar = getchar()) != '1')
	{
		tmpNode = (Node *) malloc(sizeof(Node));

		// Check if memory not allocated
		if (!tmpNode)
		{
			return 0;
		}
		tmpNode->data = tmpChar;
	
		// if no head
		if (!*listHead)
		{
			*listHead = tmpNode;
			(*listHead)->next = NULL;
		} else
		{
			tmpNode->next = *listHead;
			*listHead = tmpNode;
		}
		
		// compute list length
		listLength++;
	}

	return 1;
	
}

/*
Func: print the elements of the linked list
Args: 
"Node *listHead" -> headpointer of linked list
*/
void printList(Node *listHead)
{
	if (!listHead)
	{
		printf("List is empty\n");
	}
	// Print all the elements of the list
	while(listHead)
	{
		printf("%c ->",listHead->data);
		listHead = listHead->next;
	}
}

/*
Func: Check if the list elements form palindrome
Args:
"Node *listHead" -> head pointer of linked list
Algorithm:
1) Find the middle element of the list
2) Reverse the list from middle to end
3) Compare chars from beginning of list with mid of list
4) Keep moving to next element from both sides
5) Return false if any one char is miss matching, otherwise true
*/
bool isPalindrome(Node *listHead)
{
	int i=1,midPosition =listLength/2+listLength%2;
	Node *midNode = listHead;
	Node *currentNode=NULL, *nextNode =NULL,*first=NULL;

	if (!listHead)
	{
		printf("List is empty\n");
		return false;
	}

	// Find the middle node
	while (i<midPosition)
	{
		midNode = midNode->next;
		i++;
	}
	
	// Reverse the list starting at currentNode
	// Including currentNode
	currentNode = midNode->next;
	
	// Logic to reverse the list from mid position
	while (currentNode)
	{
		nextNode = currentNode->next;

		currentNode->next = first;

		first = currentNode;

		currentNode = nextNode;
	}

	// Attach the reversed half of list
	midNode->next = first;

	
	i=1;

	// Compare leftmost and mid position and
	// keep moving
	while (i<=listLength/2)
	{
		if (!listHead || !first)
		{
			return false;
		}
		if (listHead->data != first->data)
		{
			return false;
		}
		listHead = listHead->next;
		first = first->next;
		i++;
	}
	
	return true;
}
