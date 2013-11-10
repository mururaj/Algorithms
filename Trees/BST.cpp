/*
Author: Muruganantham Raju
Program to perform operations on BST
*/
#include <stdio.h>
#include <stdlib.h>

// A node in BST
typedef struct node
{
	int data;
	struct node *leftChild;
	struct node *rightChild;
}NodeT;

class Queue
{
	private:
		typedef struct node
		{
			void *data;
			node *next;
		}qNode;
		qNode *head;
		qNode *tail;
	public:
		int append(void *data);
		void *remove();
		Queue() 
		 { 	
			head = NULL;
        	tail = NULL;
		 }
};

int Queue::append(void *data)
{
	qNode *tmpNode = (qNode *)malloc(sizeof(qNode));
	if (!tmpNode)
	{
		return 0;
	}
	tmpNode->data = data;

	if (!head && !tail)
	{
		head = tmpNode;
		tail = tmpNode;
		tmpNode->next = NULL;
		return 1;
	}

	if ((head && !tail) || (!head && tail))
	{
		// possible error
		return 0;
	}

	tail->next = tmpNode;
	tail= tail->next;
	tail->next = NULL;
	return 1;
}

void* Queue::remove()
{
	qNode *headNode;
	if (!head && !tail)
	{
		return NULL;
	}

	if (head == tail)
	{
		headNode = head;
		head = NULL;
		tail = NULL;
		return headNode->data;
	}

	if ((head && !tail) || (!head && tail))
	{
		// possible error
		return NULL;
	}
	
	headNode = head;
	head = head->next;
	return headNode->data;
}

int main()
{
	int choice,searchData;
	void printMenu();
	int insertElement(NodeT **root);
	void preOrderTraverse(NodeT *root);
	void inOrderTraverse(NodeT *root);
	void postOrderTraverse(NodeT *root);
	void depthFirstTraversal(NodeT *root);
	void breathFirstTraversal(NodeT *root,Queue *bfsQueue);
	int removeNode(NodeT **root,int data, NodeT *parentNode);
	NodeT *findNode(NodeT *root, int data);
	NodeT *searchNode;

	// Initialize root node of tree
	NodeT *root = NULL;
	Queue bfsQueue;

	printMenu();
	do
	{
		printMenu();
		printf("Please enter your choice\n");
		scanf("%d",&choice);
		switch (choice)
		{
		case 1:
			if (!insertElement(&root))
			{
				printf("Insertion failed\n");
			}
			break;
		case 2:
			preOrderTraverse(root);
			break;
		case 3:
			postOrderTraverse(root);
			break;
		case 4:
			inOrderTraverse(root);
			break;
		case 5:
			printf("Enter the search data\n");
			scanf("%d",&searchData);
			if (!(searchNode = findNode(root,searchData)))
			{
				printf("Unable to Find the node\n");
			} 
			else if (searchNode->data == searchData)
			{
				printf("Matching node found\n");
			} else
			{
				printf("Unable to find the node\n");
			}
			break;
		case 6:
			printf("Enter the element to remove\n");
			scanf("%d",&searchData);
			if (!removeNode(&root,searchData,NULL))
			{
				printf("Unable to Find the node\n");
			} 
			else
			{
				printf("Node removed\n");
			}
			break;
		case 7:
			depthFirstTraversal(root);
			break;
		case 8:
			breathFirstTraversal(root,&bfsQueue);
			break;
		default:
			printf("You entered invalid choice or Exit\n");
		}
	}
	while (choice!=9);
	return 0;
}

/*
Func printMenu: lists choices to perform different
operations on BST
*/
void printMenu()
{
	printf("\n");
	printf("1.Enter an element into BST\n");
	printf("2.Pre-order traversal\n");
	printf("3.Post-order traversal\n");
	printf("4.In-order traversal\n");
	printf("5.Search an element\n");
	printf("6.Remove an element\n");
	printf("7.Depth First Traversal \n");
	printf("8.Breath First Traversal \n");
	printf("9.Exit\n");
}


/*
Func insertElement: insert a node into BST
Args: 
"**root" pointer to BST root pointer
Algorithm:
1. Create a new node
2. If no root, assign root to new node & return success
3. Starting from root traverse the tree to find right
position to insert the new node
 - If the new node data <= current tmpnode data, 
   (a) if tmpnode has no left child, then insert new node
       as its left child & return success
	   else traverse left branch of the tree
  - If the new node data > current tmpnode data,
   (b) if tmpnode has no right child, then insert new node
       as its right child & return success
	   else traverse right branch of the tree
*/
int insertElement(NodeT **root)
{
	NodeT *newElement,*tmpElement;
	newElement= (NodeT *)malloc(sizeof(NodeT));

	// Check NULL condition for newElement
	if (!newElement)
	{
		printf("Unable to get memory for new element\n");
		return 0;
	}
	
	printf("Please enter the data\n");
	scanf("%d",&newElement->data);
	newElement->leftChild = NULL;
	newElement->rightChild = NULL;

	// If no root, then set root to newElement
	if (!*root)
	{
		*root = newElement;
		return 1;
	}

	// temporary pointer starting at root
	tmpElement = *root;

	while (tmpElement)
	{
		
		if (newElement->data <= tmpElement->data)
		{
			// If no leftchild, then newElement is leftchild
			if (!tmpElement->leftChild)
			{
				tmpElement->leftChild = newElement;
				return 1;
			}
			tmpElement = tmpElement->leftChild;			
		} 
		else if (newElement->data > tmpElement->data)
		{
			// If no rightchild, then newElement is rightchild
			if (!tmpElement->rightChild)
			{
				tmpElement->rightChild = newElement;
				return 1;
			}
			tmpElement = tmpElement->rightChild;
		}
	}

	// At this point probably error
	return 0;
}

/*
Func preordertraverse: Visits the node of BST in 
root,left and right order
Args:
"*root" -> current root pointer of the tree
*/
void preOrderTraverse(NodeT *root)
{
	if (root)
	{
		printf("%d ",root->data);
		preOrderTraverse(root->leftChild);
		preOrderTraverse(root->rightChild);
	}
}

/*
Func inordertraverse: Visits the node of BST in 
left,root and right order
Args:
"*root" -> current root pointer of the tree
*/
void inOrderTraverse(NodeT *root)
{
	if (root)
	{
		inOrderTraverse(root->leftChild);
		printf("%d ",root->data);
		inOrderTraverse(root->rightChild);
	}
}

/*
Func postordertraverse: Visits the node of BST in 
left,right and root order
Args:
"*root" -> current root pointer of the tree
*/
void postOrderTraverse(NodeT *root)
{
	if (root)
	{
		postOrderTraverse(root->leftChild);
		postOrderTraverse(root->rightChild);
		printf("%d ",root->data);
	}
}

/*
Func findNode: A recursive funtion to return 
the node that matches given data 
Args:
"NodeT *root" -> current root pointer of the tree
"int data" -> Data of the node to be found
Algorithm:
1. If passed *root is NULL, return NULL
2. If the current root node data matches search
node data, then return root node
3. If search node data < current root node data, then
make recursive call to findNode with leftChild as root
4. If search node data > current root node data, then
make recursive call to findNode with rightChild as root
*/
NodeT *findNode(NodeT *root, int data)
{
	// If no root, return NULL
	if (!root)
	{
		return NULL;
	}

	// If data matches root data, return root node
	if (root->data == data)
	{
		return root;
	}

	// node may be available only at left branch of tree
	if (data < root->data)
	{
		return findNode(root->leftChild,data);
	}

	// node may be available only at right branch of tree
	if (data > root->data)
	{
		return findNode(root->rightChild,data);
	}

	// At this point, return NULL
	return NULL;
}

/*
Func removeNode: Remove a node from BST
Args:
"**root" -> Pointer to root pointer of tree
"data" -> data of the node to be removed
"*parentNode" -> Pointer of parentNode of removal node
Algorithm:
1. If no root, return error
2. If node to be removed is current node
  (a) If current node has no left and right child
	- if current node has no parent, then tree has only one root
	 free the root and return success
	- if current node is left child of parent, mark parent's left
	child to NULL, free current node and return success
	- if current node is right child of parent, mark parent's right
	child to NULL, free current node and return success
	- If none matches, return error
  (b) If current node has no right child
    - if current node is left child of parent, set parent's left
	child to left child of current node, free current node and 
	return success
	- if current node is right child of parent, set parent's right
	child to left child of current node, free current node and 
	return success
  (c) If current node has no left child
    - if current node is left child of parent, set parent's left
	child to right child of current node, free current node and 
	return success
	- if current node is right child of parent, set parent's right
	child to right child of current node, free current node and 
	return success
  (d) If not a to c, then node to be removed has both right & left child
    - Find the largest node from the left branch of the removal node
	- Set the data of largest node to removal node data
	- Recursive call to removeNode with root set to largest node, data to
	largest node data and parent to parent of largest node
3. If node to be removed < current node data
    - make recursive call to removeNode with root set to leftChild of 
	current node and parent set to current node
4. If node to be removed > current node data
    - make recursive call to removeNode with root set to rightChild of
	current node and parent set to current node
*/
int removeNode(NodeT **root,int data,NodeT *parentNode)
{
	NodeT *tmpNode = *root;
	NodeT *largeNode;

	// If no root, return error
	if (!tmpNode)
	{
		return 0;
	}

	if (tmpNode->data == data)
	{
		
		// Check if removal node has no children 
		if (!tmpNode->leftChild && !tmpNode->rightChild)
		{
			if (!parentNode)
			{
				free(*root);
				*root = NULL;
				return 1;
			}

			if (parentNode->leftChild == tmpNode)
			{
				parentNode->leftChild = NULL;
				free(tmpNode);
				tmpNode = NULL;
				return 1;
			} 
			if (parentNode->rightChild == tmpNode)
			{
				parentNode->rightChild = NULL;
				free(tmpNode);
				tmpNode = NULL;
				return 1;
			}

			return 0;
		} 

		// check if removal node has only right child
		if (!tmpNode->leftChild && tmpNode->rightChild)
		{
			if (parentNode->leftChild == tmpNode)
			{
				parentNode->leftChild = tmpNode->rightChild;
			}
			else if (parentNode->rightChild == tmpNode)
			{
				parentNode->rightChild = tmpNode->rightChild;
			}
			free(tmpNode);
			tmpNode = NULL;
			return 1;
		}

		// check if removal node has only left child
		if (tmpNode->leftChild && !tmpNode->rightChild)
		{
			if (parentNode->leftChild == tmpNode)
			{
				parentNode->leftChild = tmpNode->leftChild;
			}
			else if (parentNode->rightChild == tmpNode)
			{
				parentNode->rightChild = tmpNode->leftChild;
			}
			free(tmpNode);
			tmpNode = NULL;
			return 1;
		}

		// at this stage removal node has both children
		// find largest node from leftbranch of removal node
		largeNode = tmpNode->leftChild;
		parentNode = tmpNode;

		while (largeNode->rightChild)
		{
			parentNode = largeNode;
			largeNode = largeNode->rightChild;
		}

		// set largest node data to removal node data
		tmpNode->data = largeNode->data;

		// now instead removing the tmpNode, call removal of 
		// largest node
		return removeNode(&largeNode,largeNode->data,parentNode);

	}

	// node to be removed is in left branch of tree
	if (data < tmpNode->data)
	{
		return removeNode(&tmpNode->leftChild,data,tmpNode);
	}

	// node to be removed is in right branch of tree
	if (data > tmpNode->data)
	{
		return removeNode(&tmpNode->rightChild,data,tmpNode);
	}

}


void depthFirstTraversal(NodeT *root)
{
	if (root)
	{
		printf("%d ",root->data);
		
		if (root->leftChild)
		{
			depthFirstTraversal(root->leftChild);
		}

		if (root->rightChild)
		{
			depthFirstTraversal(root->rightChild);
		}

	}
}


int breathFirstTraversal(NodeT *root,Queue *bfsQueue)
{
	NodeT *tmpNode;
	if (!root || !bfsQueue)
	{
		return 0;
	}

	{
		printf("%d ", root->data);
		if (root->leftChild)
		{
			bfsQueue->append((void *)root->leftChild);
		}
		if (root->rightChild)
		{
			bfsQueue->append((void *)root->rightChild);
		}
	}

	while ( (tmpNode = (NodeT *)bfsQueue->remove()) != NULL)
	{
		printf("%d ",tmpNode->data);
		if (tmpNode->leftChild)
		{
			bfsQueue->append((void *)tmpNode->leftChild);
		}
		if (tmpNode->rightChild)
		{
			bfsQueue->append((void *)tmpNode->rightChild);
		}
	}

	return 1;
}


