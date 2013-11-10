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

int getMaxDepth(Node *root,int parentLevel);
int printElements(Node *root);

int main()
{
	// Initialize the root 
	Node *root = NULL;

	int insertElements(Node **root,int data);
	int printAllPaths(Node *root);
	Node* mirrorTree(Node *root);
	Node* duplicateTree(Node *root);
	Node* duplicateRoot = NULL;
	Node* mirrorRoot = NULL;
	
	
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
	printf("Printing tree elements\n");
	if (!printElements(root))
	{
		printf("Unable to print elements\n");
		return 0;
	}

	printf("\nThe max depth of the tree %d \n",getMaxDepth(root,0));

	// Print the paths
	printf("Printing all the paths\n");
	if (!printAllPaths(root))
	{
		printf("Unable to print the paths\n");
		return 0;
	}
	
	mirrorRoot = mirrorTree(root);

	printf("Mirror tree path\n");
	// Print mirror tree elements
	if (!printElements(mirrorRoot))
	{
		printf("Unable to print elements\n");
		return 0;
	}

	duplicateRoot = duplicateTree(root);

	printf("\nDuplicate tree path\n");
	//print elements of duplicate tree
	if (!printElements(duplicateRoot))
	{
		printf("Unable to print duplicate tree\n");
		return 0;
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

int printElements(Node *root)
{
	// Check for null condition
	if (root)
	{
		printf("%d ->",root->data);
		printElements(root->leftChild);
		printElements(root->rightChild);
	}
	return 1;
}

int printAllPaths(Node *root)
{
	// Initialize the required data structures
	const int arraySize = getMaxDepth(root,0);
	static int *a = (int *) malloc(sizeof(int) * arraySize);
	static int currentLength = 0;

	// if no root, return error
	if (!root)
	{
		#ifdef DEBUG
			printf("Empty tree\n");
		#endif
		
		return 0;
	}

	// Get myindex
	int myIndex = currentLength;

	//Add myself into stack
	a[myIndex] = root->data;

	currentLength++;

	//Check if leaf node
	if (!root->leftChild && !root->rightChild)
	{
		// Call printpath
		for (int i=0;i<currentLength;i++)
		{
			printf("%d ->",*(a + i));
		}

		printf("\n");

		// Remove myself
		a[myIndex] = -1;
		
		currentLength--;

		return 1;
	}

	if (root->leftChild)
	{
		printAllPaths(root->leftChild);
	}

	if (root->rightChild)
	{
		printAllPaths(root->rightChild);
	}

	// Remove myself
	a[myIndex] = -1;

	currentLength--;

	// Free the dynamic data structure
	if (currentLength == 0)
	{
		free(a);
	}
	
	return 1;
}

Node* mirrorTree(Node *root)
{
	// Check for no root
	if (!root)
	{
		#ifdef DEBUG
			printf("Tree is empty!\n");
		#endif
		return NULL;
	}

	// Check if I am the only node
	if (!root->leftChild && !root->rightChild)
	{
		// Return myself. nothing to reverse underneath
		return root;
	}

	// Check if I have only a left child
	if (root->leftChild && !root->rightChild)
	{
		root->rightChild = mirrorTree(root->leftChild);
		root->leftChild = NULL;

		if (!root->rightChild)
		{
			#ifdef DEBUG
				printf("Something corrupted\n");
			#endif
			return NULL;
		}
	}  //Check if I have only a right child
	else if (root->rightChild && !root->leftChild)
	{	
		root->leftChild = mirrorTree(root->rightChild);
		root->rightChild = NULL;

		if (!root->leftChild)
		{
			#ifdef DEBUG
				printf("Something corrupted\n");
			#endif
			return NULL;
		}

	} // check if I have both the children
	else if (root->rightChild && root->leftChild)
	{
		// mirror the childs
		Node *tmpLeft = mirrorTree(root->leftChild);
		Node *tmpRight = mirrorTree(root->rightChild);
		
		if (!tmpLeft || !tmpRight)
		{
			#ifdef DEBUG
				printf("Something corrupted\n");
			#endif
			return NULL;
		}

		// Shift the children
		root->rightChild = tmpLeft;
		root->leftChild = tmpRight;
	} else
	{
		// Control shouldn't reach here
		#ifdef DEBUG
			printf("Something corrupted\n");
		#endif
		return NULL;
	}

	// return myself
	return root;

}

Node* duplicateTree(Node *root)
{
	Node *tmpLeft = NULL;
	Node *tmpRight = NULL;
	Node *newNode = NULL;

	// if no root, return NULL
	if (!root)
	{
		return NULL;
	}

	// Duplicate the children first
	tmpLeft = duplicateTree(root->leftChild);
	tmpRight = duplicateTree(root->rightChild);

	// Create a new Node
	newNode = (Node *)malloc(sizeof(Node));

	if (!newNode)
	{
		printf("Unable to allocate memory \n");
		exit;
	}
	newNode->data = root->data;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;
	
	// Duplicate myself
	root->leftChild = newNode;

	
	newNode->leftChild = tmpLeft;
	root->rightChild = tmpRight;

	// printf("Inside duplicate\n");
	//printElements(root);

	return root;
}

