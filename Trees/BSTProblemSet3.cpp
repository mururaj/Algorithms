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
	Node *root1 = NULL;
	Node *root2 = NULL;
	int insertElements(Node **root,int data);
	int printAllPaths(Node *root);
	int isSame(Node *root1,Node *root2);
	
	
	
	int numElements1;

	printf("Please enter the number of elements to be inserted\n");
	scanf("%d",&numElements1);

	if (numElements1 > MAXELEMENTS)
	{
		printf("Exceeded total num of elements allowed\n");
		return 0;
	}

	// Input elements into BST
	for (int i=1;i<=numElements1;i++)
	{
		int data;
		printf("Enter node data \n");
		scanf("%d",&data);
		if (!insertElements(&root1,data))
		{
			printf("Unable to insert element\n");
			return 0;
		}
	}
	
	int numElements2;
	printf("Please enter the number of elements to be inserted\n");
	scanf("%d",&numElements2);

	if (numElements2 > MAXELEMENTS)
	{
		printf("Exceeded total num of elements allowed\n");
		return 0;
	}

	// Input elements into BST
	for (int i=1;i<=numElements2;i++)
	{
		int data;
		printf("Enter node data \n");
		scanf("%d",&data);
		if (!insertElements(&root2,data))
		{
			printf("Unable to insert element\n");
			return 0;
		}
	}

	
	// print BST elements
	printf("\nPrinting tree1 elements\n");
	if (!printElements(root1))
	{
		printf("Unable to print elements\n");
		return 0;
	}

		// print BST elements
	printf("\nPrinting tree2 elements\n");
	if (!printElements(root2))
	{
		printf("Unable to print elements\n");
		return 0;
	}

	if (!isSame(root1,root2))
	{
		printf("\nTrees are not identical\n");
	} else
	{	
		printf("\nTrees are identical\n");
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

int isSame(Node *root1,Node *root2)
{
	int leftBranchRetVal1 = 1;
	int rightBranchRetVal2 = 1;

	// If any one of the node empty, return false
	if (!root1 || !root2)
	{
		return 0;
	}

	// If data not matching, return false
	if (root1->data != root2->data)
	{
		return 0;
	}

	// If left branches not matching, return false
	if (!((root1->leftChild && root2->leftChild) ||
		(!root1->leftChild && !root2->leftChild)))
	{
		return 0;
	} 

	// If right branches not matching, return false
	if (!((root1->rightChild && root2->rightChild) ||
		(!root1->rightChild && !root2->rightChild)))
	{
		return 0;
	}

	// Validate left branch
	if (root1->leftChild)
	{
		leftBranchRetVal1 = isSame(root1->leftChild,
			root2->leftChild);
	}

	// Validate right branch
	if (root1->rightChild)
	{
		rightBranchRetVal2 = isSame(root1->rightChild,
			root2->rightChild);
	}

	return leftBranchRetVal1 && rightBranchRetVal2;
	
}



