#pragma once
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class LinkedList {
public:
	// Default Constructor
	LinkedList()
	{
		_nodeCounter = 0;
		head = nullptr;
		tail = nullptr;
	}

	// Node Nested Class
	class Node 
	{
	public:
		Node* next;
		Node* prev;
		T data;

	};

	// Iterator Pointer
	Node * createIterator()
	{
		iterator = Head();

		return iterator;
	}

	// ========= Insertion ========= //

	void AddNodesHead(const T *data, unsigned int count)
	{
		int invertIndex = (int) count - 1;
		// Call AddHead from bottom of the array in a for loop
		for (int i = invertIndex; i >= 0 ; i--)
		{
			AddHead(data[i]);
		}
	}

	void AddNodesTail(const T *data, unsigned int count)
	{
		// Call AddTail from top of the array in a for loop
		for (unsigned int i = 0; i < count; i++)
		{
			AddTail(data[i]);
		}

	}

	// ========= Mutators ========== //

	// Insertion Function

	void InsertAt(const T &data, unsigned int index)
	{
		if (index > _nodeCounter)
		{
			throw "Incorrect Index";
		}
		else if (index == _nodeCounter)
		{
			// Handles the end of list index
			Node * newNode = new Node();
			newNode->data = data;
			tail->next = newNode;
			newNode->prev = tail;
			newNode->next = nullptr;
			tail = newNode;

			_nodeCounter++;
		}
		else
		{
			Node * newNode = new Node();
			unsigned int count = 0;
			newNode->data = data;

			iterator = createIterator();
			// Iterate through nodes in the list till index
			while (count != index)
			{
				iterator = iterator->next;
				count++;
			}
			// Update the new node's attributes
			newNode->prev = iterator->prev;
			newNode->next = iterator;

			//Update the adjacent Nodes
			if (iterator->prev != nullptr)
			{
				iterator->prev->next = newNode;
			}
			else
			{
				head = newNode;
			}

			// Update the old node at i'th position
			iterator->prev = newNode;

			_nodeCounter++;
		}
		
	}

	void InsertAfter(Node *node, const T &data)
	{
		// Create a new Node with data
		Node * newNode = new Node();
		newNode->data = data;
		newNode->prev = node;
		newNode->next = node->next;

		// Update the node attributes
		node->next->prev = newNode;
		node->next = newNode;
		_nodeCounter++;

	}

	void InsertBefore(Node *node, const T &data)
	{
		// Create a new Node with data
		Node * newNode = new Node();
		newNode->data = data;
		newNode->next = node;
		newNode->prev = node->prev;

		// Update the node attributes
		node->prev->next = newNode;
		node->prev = newNode;
		_nodeCounter++;
	}

	// Removal Functions

	void Clear()
	{
		Node * ptr = Head();
		Node * temp;

		while (ptr != nullptr)
		{
			temp = ptr->next;
			delete ptr;
			ptr = temp;
		}

		head = nullptr;
		tail = nullptr;
		_nodeCounter = 0;
	}

	bool RemoveHead()
	{
		// Check if List is empty
		if (head == nullptr)
		{
			return false;
		}
		// Check if only one element is remaining
		else if (head->next == nullptr)
		{
			head = nullptr;
			tail = nullptr;
			_nodeCounter--;
			return true;
		}
		else
		{
			head->next->prev = nullptr;
			head = head->next;
			_nodeCounter--;
			return true;
		}
		
	}

	bool RemoveTail()
	{
		// Check if List is empty
		if (tail == nullptr)
		{
			return false;
		}
		// Check if list has a single element
		else if (tail->prev == nullptr)
		{
			tail = nullptr;
			head = nullptr;
			_nodeCounter--;
			return true;
		}
		else
		{
			tail->prev->next = nullptr;
			tail = tail->prev;
			_nodeCounter--;
			return true;
		}
		
	}

	bool RemoveAt(unsigned int index)
	{
		if (index > _nodeCounter)
		{
			return false;
		}
		else
		{
			iterator = createIterator();
			unsigned int indexCounter = 0;

			while (indexCounter != index)
			{
				iterator = iterator->next;
				indexCounter++;
			}

			// If iterator is at Head
			if (iterator->prev == nullptr)
			{
				iterator->next->prev = nullptr;
			}
			// If iterator is at the Tail
			else if (iterator->next == nullptr)
			{
				iterator->prev->next = nullptr;
			}
			// If in the middle of List
			else
			{
				iterator->prev->next = iterator->next;
				iterator->next->prev = iterator->prev;
			}

			_nodeCounter--;
			iterator = nullptr;

			return true;
		}
		
	}

	unsigned int Remove(const T &data)
	{
		unsigned int elementsRemoved = 0;
		Node * iterator = head;
		Node* temp;
		
		while (iterator != nullptr)
		{
			temp = iterator->next;
			if (iterator->data == data)
			{
				// If iterator is at Head
				if (iterator->prev == nullptr)
				{
					iterator->next->prev = nullptr;
				}
				// If iterator is at the Tail
				else if (iterator->next == nullptr)
				{
					iterator->prev->next = nullptr;
				}
				// If in the middle of List
				else
				{
					iterator->prev->next = iterator->next;
					iterator->next->prev = iterator->prev;
				}
				delete iterator;
				elementsRemoved++;
			}
			iterator = temp;
		}
		// Update the nodeCounter
		_nodeCounter -= elementsRemoved;
		return elementsRemoved;
	}

	// AddHead
	void AddHead(const T &data)
	{
		// Create a temp node
		Node* temp = new Node();
		temp->data = data;
		temp->next = nullptr;
		temp->prev = nullptr;

		if (head == nullptr)
		{
			head = temp;
			tail = temp;
			head->next = nullptr;
			head->prev = nullptr;
		}
		else
		{
			head->prev = temp;
			if (_nodeCounter == 1)
				tail->prev = temp;
			temp->next = head;
			head = temp;
		}
		_nodeCounter++;
	}

	// AddTail
	void AddTail(const T &data)
	{
		// Create a temp node
		temp = new Node();
		temp->data = data;
		temp->next = nullptr;
		temp->prev = nullptr;

		if (tail == nullptr)
		{
			head = temp;
			tail = temp;
			tail->next = nullptr;
			tail->prev = nullptr;
		}
		else
		{
			tail->next = temp;
			if (_nodeCounter == 1)
				head->next = temp;
			temp->prev = tail;
			temp->next = nullptr;
			tail = temp;
			temp = nullptr;
		}
		_nodeCounter++;
	}


	// ========= Accessors ========== //

	// Finders

	void FindAll(vector<Node *> &outData, const T&value) const
	{
		// Iterate through the List
		Node * iterator = head;

		for  (unsigned int i = 0; i < _nodeCounter; i++)
		{
			// Check if data matches value passed
			if (iterator->data == value)
			{
				Node * tempPtr = new Node();
				tempPtr = iterator;
				// Push matched nodes in outData vector
				outData.push_back(tempPtr);
				tempPtr = nullptr;
			}
			iterator = iterator->next;
			
		}

		iterator = nullptr;
		
		
	}

	Node *Find(const T &data)
	{
		bool nodeFound = false;
		iterator = createIterator();

		while (!nodeFound && iterator->next != nullptr)
		{
			if (iterator->data == data)
			{
				nodeFound = true;
			}
			iterator = iterator->next;
		}
		if (nodeFound)
		{
			return iterator->prev;
		}
		else
		{
			return nullptr;
		}
		
	}

	const Node *Find(const T &data) const
	{
		bool nodeFound = false;
		iterator = createIterator();

		while (!nodeFound && iterator->next != nullptr)
		{
			if (iterator->data == data)
			{
				nodeFound = true;
			}
			iterator = iterator->next;
		}
		if (nodeFound)
		{
			return iterator->previous;
		}
		else
		{
			return nullptr;
		}
	}

	Node *Tail()
	{
		return tail;
	}
	const Node *Tail() const
	{
		return tail;
	}

	Node *Head()
	{
		return head;
	}
	const Node *Head() const
	{
		return head;
	}

	const Node * GetNode(unsigned int index) const
	{
		if (index > _nodeCounter)
		{
			throw "Incorrect index";
		}
		else
		{
			unsigned int indexCount = 0;

			Node * iterator = head;
		
			while (indexCount != index)
			{
				iterator = iterator->next;
				indexCount++;
			}

			return iterator;
		}
		
	}

	Node * GetNode(unsigned int index)
	{
		if (index > _nodeCounter)
		{
			throw "Incorrect index";
		}
		else
		{
			unsigned int indexCount = 0;

			Node* iterator = head;

			while (indexCount != index)
			{
				iterator = iterator->next;
				indexCount++;
			}

			return iterator;
		}

	}

	// Print all nodes in forward direction
	void PrintForward() const
	{
		// Create an iterator
		Node * iterator = head;
		
		while (iterator != nullptr)
		{
			cout << iterator->data << endl;
			iterator = iterator->next;
		}
	}

	// Print all nodes from back to front
	void PrintReverse() const
	{
		// Create an iterator
		Node * iterator = tail;
		
		while (iterator != nullptr)
		{
			cout << iterator->data << endl;
			iterator = iterator->prev;
		}
	}

	// Get Node Count
	unsigned int NodeCount() const
	{
		return _nodeCounter;
	}

	/*===== Operators =====*/
	const T &operator[] (unsigned int index) const
	{
		// Return the node at given index
		if (index > _nodeCounter)
		{
			throw "Incorrect index";
		}
		else
		{
			unsigned int indexCount = 0;

			Node* iterator = head;

			while (indexCount != index)
			{
				iterator = iterator->next;
				indexCount++;
			}

			return iterator->data;
		}
	}

	T &operator[] (unsigned int index)
	{
		// Return the node at given index
		if (index > _nodeCounter)
		{
			throw "Incorrect index";
		}
		else
		{
			unsigned int indexCount = 0;

			Node* iterator = head;


			while (indexCount != index)
			{
				iterator = iterator->next;
				indexCount++;
			}

			return iterator->data;
		}
	}

	/*===== The Big Three =====*/

	LinkedList(const LinkedList<T> &list)
	{
		_nodeCounter = list._nodeCounter;

		for (unsigned int i = 0; i < _nodeCounter; i++)
		{
			Node * newNode = new Node();
			newNode = list.GetNode(i);
			AddTail(newNode);
		}

		head = list.Head();
		tail = list.Tail();
	}

	LinkedList<T> & operator= (const LinkedList<T> &rhs)
	{
		_nodeCounter = rhs._nodeCounter;
		head = rhs.Head();
		tail = rhs.Tail();

		for (unsigned int i = 0; i < _nodeCounter; i++)
		{
			AddTail(rhs.GetNode(i));
		}

		return *this;
	}

	~LinkedList()
	{
		Clear();
		/*if (iterator != nullptr)
		{
			delete iterator;
		}
		if (head != nullptr)
		{
			delete head;
		}
		if (tail != nullptr)
		{
			delete tail;
		}*/
	}



private:
	unsigned int _nodeCounter;
	Node* next;
	Node* prev;
	Node* head;
	Node* tail;
	Node * iterator;
	Node* temp;

};