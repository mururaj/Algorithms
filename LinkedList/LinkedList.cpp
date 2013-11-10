/*
Author: Muruganantham Raju
Date: 01/13/2013
A singly linked list with head and tail pointers
*/
#include <stdio.h>
#include <stdlib.h>

// Declaration of node
typedef struct node
	{
		int data;
		struct node *next;
	}Node;

int main()
{
	int	insertElement(Node **head,Node **tail,Node *element);
	int removeElement(Node **head,Node **tail,Node *element);
	int updateElement(Node *head,int position);
	int traverseList(Node *node);
	void swapList(Node **root);
	Node * getInsertElement(Node *head,int position);
	Node * getElementToDelete(Node *head,int position);
	void printMenu();
	int choice,position;
	
	Node *prevElement,*toDelete;
	Node *head = NULL;
	Node *tail = NULL;

	printMenu();
	scanf("%d",&choice);

	while (choice !=6 )
	{	
		switch(choice)
		{
		case 1:
			if (!head)
			{
				position=1;
				prevElement = getInsertElement(head,position);
			} else {
				printf("Please enter the position to insert\n");
				scanf("%d",&position);
				prevElement = getInsertElement(head,position);
			}
			if ((!prevElement && head && position != 1)|| position<=0)
			{
				printf("Invalid position entered\n");
			} else
			{
				insertElement(&head,&tail,prevElement);
			}
			break;
		case 2:
			printf("Please enter the position to be deleted\n");
			scanf("%d",&position);
			if (position <=0)
			{
				printf("Invalid position entered\n");
				break;
			}
			toDelete = getElementToDelete(head,position);
			if (!toDelete)
			{
				printf("Invalid position entered\n");
				break;
			}
			removeElement(&head,&tail,toDelete);
			break;
		case 3:
			printf("Please enter the position to update\n");
			scanf("%d",&position);
			updateElement(head,position);
			break;
		case 4:
			traverseList(head);
			break;
		case 5:
			swapList(&head);
			break;
		default:
			printf("You entered wrong choice\n");
		}
		printMenu();
		scanf("%d",&choice);
	}	
	
	return 1;
}

void printMenu()
{
printf("Menu for linked list\n");
printf("1. Insert an element\n");
printf("2. Remove an element\n");
printf("3. Update an element\n");
printf("4. Traverse the list\n");
printf("5. Swap the list\n");
printf("6. Exit\n");
printf("Please enter your choice\n");
}

/*
Func getInsertElement: returns the previous element
- of the insertion point
Args:
"position" Position to insert a new element
*/
Node * getInsertElement(Node *head,int position)
{
	int i=0;
	
	// if head is NULL, build a new list
	if (!head)
	{
		printf("Building new list\n");
		return head;
	}

	// To insert at head, return prev of head (NULL)
	if (position == 1)
	{
		return NULL;
	}

	// move till prev element of insertion point	
	while (head && i< position-2)
	{
		head = head->next;
		i++;
	}
	
	// Return the previous element of insertion point
	return head;
}

/*
Func insertElement: Insert an element next to element
- passed in argument
Args:
"**head" Pointer to list head pointer
"**tail" Pointer to list tail pointer
"*element" Previous element of insertion point
*/
int	insertElement(Node **head,Node **tail,Node *element)
{
	// Create a new element
	Node *newElement;
	newElement = (Node *) malloc(sizeof(newElement));
	Node *tmpElement = *head;
	

	if (!newElement)
	{
		 printf("Memeory allocation failed\n");
		 return 0;
	}

	printf("please enter data\n");	
	scanf("%d",&newElement->data);
	
	// If list is empty, head, tail points to newElement
	if (!*head && !*tail && !element)
	{
		*head = newElement;
		*tail = newElement;
		newElement->next = NULL;
		return 1;
	}

	// Inserting at begining of list. Move head to newElement
	if (*head && *tail && !element)
	{
		newElement->next = *head;
		*head = newElement;
		return 1;
	}

	// If no head, tail at this position; probably an error
	if (!*head && !*tail)
	{
		return 0;
	}

	// Traverse till list end or prev element position
	while (tmpElement)
	{
		if (tmpElement == element)
		{
			// If insertion point is last, update tail
			if (!tmpElement->next)
			{
				newElement->next = tmpElement->next;
				tmpElement->next = newElement;
				*tail = newElement;
			} else
			{
				newElement->next = tmpElement->next;
				tmpElement->next = newElement;
			}
			return 1;			
		}
		tmpElement = tmpElement->next;
	}

	//At this point no way to insert, return error
	return 0;

}

/*
Func getElementToDelete: Returns the element to be deleted
Args:
"*head" value of head pointer
"position" Position of element to be deleted
*/
Node * getElementToDelete(Node *head,int position)
{
	int i=1;

	// Traverse till list end
	while (head)
	{
		// If element to delete found, return
		if (i==position)
		{
			return head;
		}	
		head = head->next;
		i++;
	}
	
	// At this point, no element found
	return NULL;
}

/*
Func traverseList: Traverse list and print each node
Args:
"*head" value of head pointer
*/
int traverseList(Node *head)
{
	if (!head)
	{
		printf("List is empty\n");
		return 0;
	}

	// Traverse till list end
	while (head)
	{
		printf("%d ->", head->data);
		head = head -> next;
	}

	return 1;
}

/*
Func removeElement: Delete the element from list
Args:
"**head" pointer to head pointer
"**tail" pointer to tail pointer
"*element" Element to be deleted
*/
int removeElement(Node **head,Node **tail,Node *element)
{
	
	Node *tmpElement = *head;

	// if any of the pointer is empty, return error
	if (!*head || !*tail || !element)
	{
		printf("No such elements\n");
		return 0;
	}

	// If only only element in list, head & tail set to NULL
	if (*head == *tail && element == *head)
	{
		free(element);
		element = NULL;
		*head = NULL;
		*tail = NULL;
		return 1;
	}

	// If head element to be removed, move head
	if (element == *head)
	{
		*head = (*head)->next;
		free(element);
		element = NULL;
		return 1;
	}

	// Traverse till end of the list
	while (tmpElement)
	{
		// Find previous element of delete position
		if (tmpElement->next == element)
		{
			tmpElement->next = element->next;
			// If tail to be removed, update tail
			if (element == *tail)
			{
				*tail = tmpElement;
			}
			free(element);
			element = NULL;
			return 1;
		}
		tmpElement = tmpElement->next;
	}
	
	// At this position, nothing to remove hence error
	return 0;
}

/*
Func updateElement: Add an integer value to specific element
Args:
"*head" value of head pointer
"position" Location of element to update
*/
int updateElement(Node *head,int position)
{
	int i=1;
	int data;

	// If no element, return error
	if (!head)
	{
		printf("List is empty\n");
		return 0;
	}

	// If position 0 or -ve, return error
	if (position <=0 )
	{
		printf("Invalid position");
		return 0;
	}

	// Traverse till end of the list
	while (head)
	{
		// Update element at given position
		if (i==position)
		{
			printf("Please enter the data to add\n");
			scanf("%d",&data);
			head->data = head->data + data;
			return 1;
		}
		head = head->next;
		i++;
	}

	// At this point, nothing to update hence error
	return  0;

}

int swapList(Node **root)
{
	Node *currentNode = *root;
	
	if (!currentNode || !currentNode->next)
	{
		return 1;
	}

	*root = (*root)->next;

	while (currentNode)
	{
		if (!currentNode->next)
		{
			return 1;
		}

		Node *tmpNode = (currentNode->next)->next;
		(currentNode->next)->next = currentNode;

		if (tmpNode)
		{
			if (tmpNode->next)
			{
				currentNode->next = tmpNode->next;
			} else
			{
				currentNode->next = tmpNode;
			}
		} else
		{
			currentNode->next = NULL;
		}

		currentNode = tmpNode;
	}

	return 1;

}

