#include <iostream>

using namespace std;

// Table size is fixed now. Need to work on dynamic sizing
#define TABLESIZE 10

/*
hashTable class to model hash table. 
tablesize -> represents the size of the hash table
computeHashKey -> computes the hash key for the given value
*/
template <class T>
class hashTable
{
	public:
		typedef struct node
		{
			T value; // item value
			struct node *next; // next pointer
		}Node;

		hashTable(): tableSize(TABLESIZE)
		{
			// initializing table entries	
			for (int i=0;i<tableSize;i++)
			{
				tableEntries[i] = NULL;
			}
									 
		}

		bool insertValue(T value); 

		bool isContain(T value);
		
		bool deleteValue(T value);

		int computeHashKey(T value);

		~hashTable()
		{
			// free up all the entries and list
			for (int i=0;i<tableSize;i++)
			{
				// For each table entry
				if (tableEntries[i])
				{
					//Traverse the list & delete each element
					while(tableEntries[i])
					{
						Node *tmpNode = tableEntries[i];
						tableEntries[i] = tableEntries[i]->next;
						delete tmpNode;
					}					
				}				
			}

		}
		
	private:
		const int tableSize; // size of hashTable		
		Node *tableEntries[TABLESIZE]; 
};

/*
Func: insertValue to insert given value into hash table
Args: value of type T (T could be int or float)
return true on success and false on failure
*/
template <class T>
bool hashTable<T>::insertValue(T value)
{
	// Check if value already inserted
	if (isContain(value))
	{
		return true;
	}

	// compute hash key
	int hashKey = computeHashKey(value);

	// Create a new element
	Node *newElement = new Node();

	if (!newElement)
	{
		// insertion failed
		printf("no space. insertion failed\n");
		return false;
	}
	newElement->value = value;

	// Insert at head position
	newElement->next = tableEntries[hashKey];
	tableEntries[hashKey] = newElement;

	// return success
	return true;
}

/*
Func: isContain to check if the hash table contains the value
Args: value of type T (T could be int or float)
return true if found and false if not found
*/
template <class T>
bool hashTable<T>::isContain(T value)
{
	// compute hash key
	int hashKey = computeHashKey(value);

	Node *currentNode = tableEntries[hashKey];

	while (currentNode)
	{
		// Check if the list already has this value
		if (currentNode->value == value)
		{
			return true;
		}
		
		currentNode = currentNode->next;
	}

	//no matching value
	return false;
}

/*
Func: computeHashKey hash function used in this implementation
Args: value of type T (T could be int or float)
return the computed hash key of type int
*/
template <class T>
int hashTable<T>::computeHashKey(T value)
{
	// typecast value to integer
	int myValue = int(value);

	// apply value modulo tablesize
	return myValue % tableSize;
}


/*
Func: deleteValue used to delete value in hash table
Args: value of type T (T could be int or float)
return if item found and deleted or else false
*/
template <class T>
bool hashTable<T>::deleteValue(T value)
{
	// compute hash key
	int hashKey = computeHashKey(value);

	
	if (!tableEntries[hashKey])
	{
		cout<<"Entry not found\n";
		return false;
	}

	Node *currentNode = tableEntries[hashKey];

	// Check if the node is head node
	if (tableEntries[hashKey]->value == value)
	{
		tableEntries[hashKey] = tableEntries[hashKey]->next;
		delete currentNode;
		return true;
	}

	Node *prevNode = currentNode;

	// Find the node and delete if found
	while (currentNode)
	{
		if (currentNode->value == value)
		{
			prevNode->next = currentNode->next;
			delete currentNode;
			return true;
		}
		prevNode = currentNode;
		currentNode = currentNode->next;
	}

	cout<<"Entry not found\n";
	return false;

}


int main()
{
	hashTable<float> table1;
	float value; // value can be int or float

	//Store values in hash table
	for (int i=0;i<5;i++)
	{
		
		cout<<"Please enter the value";
		cin>>value;

		if (!table1.insertValue(value))
		{
			cout<<"Insertion failed\n";
			return 0;
		}

	}

	// Searching for values
	char usrOption;

	cout<<"Enter Y/N for searching\n";
	cin>>usrOption;
	while (usrOption == 'Y')
	{
		cout<<"Enter the search value\n";
		cin>>value;

		if (!table1.isContain(value))
		{
			cout<<"This value not found\n";
		} else
		{
			cout<<"This value is found\n";
		}

		cout<<"Enter the value to delete\n";
		cin>>value;

		if (!table1.deleteValue(value))
		{
			cout<<"No deletion\n";
		} else
		{
			cout<<"Element deleted\n";
		}

		cout<<"Enter Y/N for searching\n";
		cin>>usrOption;
	}
	

	return 1;
}
