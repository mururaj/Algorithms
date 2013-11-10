#include <stdio.h>
#include <stdlib.h>

#define MAXELEMENTS 25

// BST node structure 
typedef struct node
{
	int data;
	struct node *leftChild;
	struct node *rightChild;	
}Node;

// Stack element structure
typedef struct stackElement
{
	Node *treeElement;
	struct stackElement *next;
}Stack;

// Queue element structure
typedef struct queueElement
{
	int data;
	struct queueElement *next;
}Queue;

int main()
{
	// Initialize the root 
	Node *root = NULL;

	int insertElements(Node **root,int data);
	int printElements(Node *root);
	int getMaxDepth(Node *root,int parentLevel);
	int getNodeCount(Node *root);
	int hasPathSum(Node *root,int sumValue,int parentSumVal);
	int printPath(Node *root);

	int numElements;

	printf("Please enter the number of elements to be inserted\n");
	scanf("%d",&numElements);

	if (numElements > MAXELEMENTS)
	{
		printf("Exceeded total num of elements allowed\n");
		return 0;
	}

	// Input elements into BST
	for (int i=1;i<=numElements;i++)
	{
		int data;
		printf("Enter node data \n");
		scanf("%d",&data);
		if (!insertElements(&root,data))
		{
			printf("Unable to insert element\n");
			return 0;
		}
	}

	// print BST elements
	if (!printElements(root))
	{
		printf("Unable to print elements\n");
		return 0;
	}

	printf("The max depth of the tree %d \n",getMaxDepth(root,100));
	printf("Number of nodes in the tree %d \n",getNodeCount(root));

	int sumVal;
	printf("Enter the sum value \n");
	scanf("%d",&sumVal);

	if (hasPathSum(root,sumVal,100))
	{
		printf("sum of at least one of the path is %d\n",sumVal);
	} else
	{
		printf("There is no path with sum %d\n",sumVal);
	}

	return 1;
}

int insertElements(Node **root,int data)
{
	// Allocate a new element
	Node *newElement = (Node *) malloc(sizeof(Node));

	if (!newElement)
	{
		return 0;
	}
	newElement->leftChild = NULL;
	newElement->rightChild = NULL;
	newElement->data = data;
	
	// If no root, declare this as root
	if (!*root)
	{
		*root = newElement;
		return 1;
	}

	// Non-recursive insertion
	Node *currentNode = *root;

	// Traverse the tree till you find right position
	while (currentNode)
	{
		// Check if the new node must be inserted at left
		if (data <=currentNode->data)
		{
			//  If current node has no leftchild, insert here
			if (!currentNode->leftChild)
			{
				currentNode->leftChild = newElement;
				return 1;
			} else
			{
				// else traverse left
				currentNode = currentNode->leftChild;
			}
		} else
		{
			// If current node has no rightchild, insert here
			if (!currentNode->rightChild)
			{
				currentNode->rightChild = newElement;
				return 1;
			} else
			{
				// else traverse right
				currentNode = currentNode->rightChild;
			}
		}
	}

	// at this position probably error
	return 0;
}

int push(Node *newElement,Stack **stackHead)
{
	// Constrcut the stack element
	Stack *newStackElement = (Stack *) malloc(sizeof(Stack));

	if (!newStackElement)
	{
		//unable to allocate memory for stack
		printf("Unable to allocate stack memory\n");
		return 0;
	}

	// Initialize the stack members
	newStackElement->treeElement = newElement;
		
	// Insert the node at head position
	newStackElement->next = *stackHead;

	*stackHead = newStackElement;

	return 1;
}

Node* pop(Stack **stackHead)
{
	Node *treeNode = NULL;

	// Check for null condition
	if (!*stackHead)
	{
		return NULL;
	}

	// Store current head
	Stack *tmpElement = *stackHead;

	// Move head to next element
	*stackHead = (*stackHead)->next;
	
	treeNode = tmpElement->treeElement;
	free(tmpElement);
	tmpElement= NULL;

	return treeNode;
}

int printElements(Node *root)
{
	Stack *stackHead = NULL;
	
	// If no root return
	if (!root)
	{
		printf("Empty tree\n");
		return 1;
	}

	// First push root node into stack
	if (!push(root,&stackHead))
	{	
		#ifdef DEBUG
		printf("Push on stack failed\n");
		#endif

		return 0;
	}

	Node *currentNode= NULL;

	while ((currentNode = pop(&stackHead)))
	{
		printf("%d ->", currentNode->data);

		// push right child of node into stack
		if (currentNode->rightChild)
		{
			if (!push(currentNode->rightChild,&stackHead))
			{
				#ifdef DEBUG
				printf("Push on stack failed\n");
				#endif

				return 0;
			}
		}

		// push left child of node into stack 
		if (currentNode->leftChild)
		{
			if (!push(currentNode->leftChild,&stackHead))
			{
				#ifdef DEBUG
				printf("Push on stack failed\n");
				#endif

				return 0;
			}
		}
	}

	printf("\n");

	return 1;
}

int getMaxDepth(Node *root,int currentDepth)
{
	static char firstCall = 'Y';

	// Set currentPath to 0 for first call
	if (firstCall == 'Y')
	{
		currentDepth = 0;
		firstCall = 'N';
	}

	// If no root, depth 0
	if (!root)
	{
		return currentDepth;
	}
	

	// Increment the depth by 1
	++currentDepth;

	// Initialize the left & right child depth to current depth
	int leftChildDepth = currentDepth;
	int rightChildDepth = currentDepth;

	if (root->leftChild)
	{
		leftChildDepth = getMaxDepth(root->leftChild, currentDepth);
	}

	if (root->rightChild)
	{
		rightChildDepth = getMaxDepth(root->rightChild, currentDepth);
	}

	// return the max of the child depth
	return (leftChildDepth>rightChildDepth? leftChildDepth:rightChildDepth);
}

int getNodeCount(Node *root)
{
	static int nodeCount = 0;

	if (root)
	{
		++nodeCount;

		if (root->leftChild)
		{
			getNodeCount(root->leftChild);
		}

		if (root->rightChild)
		{
			getNodeCount(root->rightChild);
		}
	}

	return nodeCount;
}

int hasPathSum(Node *root,int sumValue,int parentSumVal)
{
	static char firstCall = 'Y';

	// Set parentSumval to 0 for first time call
	if (firstCall == 'Y')
	{
		parentSumVal = 0;
		firstCall = 'N';
	}
	// Sum false if no root
	if (!root)
	{
		return 0;
	}

	// Compute the sum of current path including this node
	int currentPathSum = root->data + parentSumVal;

	// if sum value matching return true
	if ( !root->leftChild && !root->rightChild &&
		currentPathSum == sumValue)
	{
		return 1;
	}

	return (
		(hasPathSum(root->leftChild,sumValue,currentPathSum)) 
			|| 
		(hasPathSum(root->rightChild,sumValue,currentPathSum))
		);
}

