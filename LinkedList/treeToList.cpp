#include <stdio.h>
#include <stdlib.h>

/* Tree has left & right child
   Each node has data */
typedef struct node
{
	unsigned int data;
	node *rightChild;
	node *leftChild;
}NodeT;

int main()
{
	int insertElement(NodeT **root);
	int numElements,i;
	void printTree(NodeT *root);
	void printList(NodeT *listHead);
	NodeT* treeToList(NodeT **root,NodeT *parentNode = NULL);
	NodeT *root = NULL;
	NodeT *listHead = NULL;

	printf("Enter total number of elementsn");
	scanf("%d",&numElements);

	for (i=1;i<=numElements;i++)
	{
		if (!insertElement(&root))
		{
			return 0;
		}
	}

	printTree(root);

	listHead = treeToList(&root);

	printList(listHead);

	return 1;
}

/*
Func insertElement: insert an element to tail of the list
Args:
"Node **head" pointer to list head pointer
*/
int insertElement(NodeT **root)
{
	NodeT *tmpNode = (NodeT *)malloc(sizeof(NodeT));
	NodeT *currentNode = *root;
	if (!tmpNode)
	{
		return 0;
	}
	tmpNode->leftChild = NULL;
	tmpNode->rightChild = NULL;
	printf("Enter a non-negative integer\n");
	scanf("%u",&tmpNode->data);
	
	if (!currentNode)
	{
		*root = tmpNode;
		return 1;
	}

	while (currentNode)
	{
		if (tmpNode->data <= currentNode->data)
		{
			if (!currentNode->leftChild)
			{
				currentNode->leftChild = tmpNode;
				return 1;
			} 

			currentNode = currentNode->leftChild;
		} else
		{
			if (!currentNode->rightChild)
			{
				currentNode->rightChild = tmpNode;
				return 1;
			}
			
			currentNode = currentNode->rightChild;
		}
	}

	// Possibly error at this point
	return 0;

}

/*
Func printTree: print all elements of the tree
Args:
"*root" pointer to root of tree
*/
void printTree(NodeT *root)
{
	if (root)
	{
		printf("%d ", root->data);
		printTree(root->leftChild);
		printTree(root->rightChild);
	}
}


NodeT* treeToList(NodeT **root,NodeT *parentNode = NULL)
{
	NodeT *myLeft = NULL, *myRight = NULL;
	NodeT *rootNode = *root;
	static NodeT *headNode = NULL;
	if (rootNode)
	{
		// Get my left and right children
		myLeft = treeToList(&rootNode->leftChild,rootNode);
		myRight = treeToList(&rootNode->rightChild,rootNode);

		// I don't have children
		if (!myLeft && !myRight)
		{
			if (!headNode)
			{
				headNode = rootNode;
			}
			return rootNode;
		}

		// I have left children
		if (myLeft)
		{
			myLeft->leftChild = rootNode;
			
			if (rootNode == headNode && headNode )
			{
				headNode = myLeft;
			}
		}

		// I have right children
		if (myRight)
		{
			rootNode->leftChild = myRight;
			
			if (myRight == headNode && headNode )
			{
				headNode = rootNode;
			}
		} else
		{
			rootNode->leftChild = NULL;
		}

		// right child must be reset
		rootNode->rightChild = NULL;

		if (!parentNode)
		{
			return headNode;
		}

		// return appropriate pointer based on left/right branch of parent
		if (parentNode->leftChild == rootNode)
		{
			if (myRight)
			{
				return myRight;
			} else
			{
				return rootNode;
			}
		} else if (parentNode->rightChild == rootNode)
		{
			if (myLeft)
			{
				return myLeft;
			} else
			{
				return rootNode;
			}

		}
	} else
	{
		return NULL;
	}
}

/*
Func printList: prints the converted list
- traversing leftchild
*/
void printList(NodeT *listHead)
{
	while(listHead)
	{
		printf("%u ", listHead->data);
		listHead = listHead->leftChild;
	}
}
