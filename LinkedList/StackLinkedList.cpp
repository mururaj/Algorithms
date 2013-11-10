/*
Author: Muruganantham Raju
Date: 01/12/2013
*/

#include <stdio.h>
#include <stdlib.h>

// Declaration of a node
typedef struct node
{
	void *data;
	struct node *next;
}Node;

int main(int argc, char *argv[])
{
	int push(Node **stack,void *data);
	int pop(Node **stack,void **data);
	int createStack(Node **stack);
	int deleteStack(Node **stack);
	void printStack(Node *stack);

	void  *data;

	//Create stack
	Node *stack;

	if (createStack(&stack))
	{
		printf("A new stack is initialized\n");
	} else {
		printf("Stack creation failued\n");
	    return 0;
	}

	if (!push(&stack,(void *) 10))
	{
		printf("Push failed\n");
	}

	if (!push(&stack,(void *) 20))
	{
		printf("Push failed\n");
	}
	
	printStack(stack);

	if (!pop(&stack,&data))
	{
		printf("Stack is empty\n");
	} else
	{
		printf("The popped element is %d\n",(int *)data);
	}

	printStack(stack);

	if (!push(&stack,(void *) 30))
	{
		printf("Push failed\n");
	}

	printStack(stack);

	if (!pop(&stack,&data))
	{
		printf("Stack is empty\n");
	} else
	{
		printf("The popped element is %d\n",(int *)data);
	}

	printStack(stack);

	if (!pop(&stack,&data))
	{
		printf("Stack is empty\n");
	} else
	{
		printf("The popped element is %d\n",(int *)data);
	}


	printStack(stack);

	if (!pop(&stack,&data))
	{
		printf("Stack is empty\n");
	} else
	{
		printf("The popped element is %d\n",(int *)data);
	}

	printStack(stack);


	if (!push(&stack,(void *) 100))
	{
		printf("Push failed\n");
	}

	if (!push(&stack,(void *) 200))
	{
		printf("Push failed\n");
	}

	if (!push(&stack,(void *) 300))
	{
		printf("Push failed\n");
	}

	if (!push(&stack,(void *) 400))
	{
		printf("Push failed\n");
	}

	printStack(stack);

	deleteStack(&stack);

	printStack(stack);
	

}
/*
Func createStack: Initializes stack to NULL
Args:
"**stack" Pointer to stack's head pointer
*/
int createStack(Node **stack)
{
	// Initialize to NULL
	*stack = NULL;

	return 1;
}

/*
Func push: Push an elment into the stack
Args:
"**stack" Pointer to stack's head pointer
"*data" data to be stored
Algorithm:
1. Create a new Node element
2. if this is first element of stack, assign
- stack's head pointer to this element & return
3. Otherwise, new element to point to current 
- head and stack's head pointer to new element
*/
int push(Node **stack,void *data)
{
	Node *newElement;

	newElement = (Node *) malloc(sizeof(Node));

	if (!newElement)
	{
		printf("Unable to get memory for new element\n");
		return 0;
	}

	newElement->data = data;

	// if this is the first element
	if (!*stack)
	{
		newElement->next = NULL;
		// stack's head point to this element
		*stack = newElement;
		return 1;
	}

	newElement->next = *stack;
	// stack's head point to this element
	*stack = newElement;

	return 1;
}

/*
Func pop: Remove an element from top
Return 0 if empty otherwise 1
Args:
"**stack" Pointer to stack's head pointer
"**data" to hold the removed data item
Algorithm:
1. If stack is empty, return error code 0
2. If stack has only one element, remove -
the element and reinitialize stack to NULL.
- Store the data item on *data.
3. Otherwise, Store top element into *data 
- Move stack head to next element and freeup
- the element.
*/

int pop(Node **stack,void **data)
{
	// Check for empty stack
	if (!*stack)
	{
		printf("Stack is empty \n");
		*data = (void *) -1;
		return 0;
	}

	Node *tempElement;

	// if only one element in stack
	if (!(*stack)->next)
	{
		tempElement = *stack;
		*data = tempElement->data;
		free(tempElement);
		tempElement = NULL;
		// empty the stack
		*stack = NULL;
		return 1;
	}

	tempElement = *stack;
	*stack = (*stack)->next;
	*data = tempElement->data;
	free(tempElement);
	tempElement = NULL;
	return 1;
}

/*
Func deleteStack: Freeup the stack
Args:
"**stack" pointer to stack's head pointer
*/
int deleteStack(Node **stack)
{
	Node *tempElement;

	while (*stack)
	{
		tempElement = *stack;
		*stack = (*stack)->next;
		free(tempElement);
		tempElement = NULL;
	}

	return 1;
}

/*
Func printStack: print the stack elements
Args:
"*stack" stack's head pointer
*/
void printStack(Node *stack)
{
	while(stack)
	{
		printf("%d \n",(int *)stack->data);
		stack = stack->next;
	}
}
