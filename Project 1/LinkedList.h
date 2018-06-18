#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
public:
	// Default Constructor
	LinkedList()
	{
		_nodeCounter = 0;
		Node* head = nullptr;
		Node* tail = nullptr;
	}

	// Node Nested Class
	class Node 
	{
	public:
		Node* next;
		Node* previous;
		T _data;
	};

	// ========= Mutators ========== //


	// AddHead
	void AddHead(const T &data)
	{
		// Create a temp node
		Node* temp = new Node();
		temp->_data = data;
		temp->next = nullptr;
		temp->previous = nullptr;

		if (head == nullptr)
		{
			head = temp;
			tail = temp;
			head->next = nullptr;
			head->previous = nullptr;
		}
		else
		{
			head->next = temp;
			if (_nodeCounter == 1)
				tail->next = temp;
			temp->previous = head;
			head = temp;
			temp = nullptr;
		}
		_nodeCounter++;
	}


	// ========= Accessors ========== //

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

	const Node * GetNode(unsigned int index)
	{
		if (index > _nodeCounter)
		{
			throw "Incorrect index";
		}
		else
		{
			unsigned int indexCount = 0;

			Node * iterator = new Node();
			iterator->_data = Tail()->_data;
			iterator->next = Tail()->next;

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
		Node * iterator = new Node();
		iterator->_data = Tail()->_data;
		iterator->next = Tail()->next;
		
		while (iterator != nullptr)
		{
			cout << iterator->_data << endl;
			iterator = iterator->next;
		}

		delete iterator;
	}

	// Print all nodes from back to front
	void PrintReverse() const
	{
		// Create an iterator
		Node * iterator = new Node();
		iterator->_data = Head()->_data;
		iterator->previous = Head()->previous;

		while (iterator != nullptr)
		{
			cout << iterator->_data << endl;
			iterator = iterator->previous;
		}

		delete iterator;
	}

	// Get Node Count
	unsigned int NodeCount() const
	{
		return _nodeCounter;
	}

private:
	unsigned int _nodeCounter;
	Node* next;
	Node* previous;
	Node* head;
	Node* tail;

};