#pragma once
#pragma once
#include "Pokemon.h"

//a node represents one element in a sorted linked list, 
//for instance in the linked list 3-4-6, 3 would be one node
class Node
{
private:
	Node* next;
	Node* last;
	Pokemon* poke;

public:
	//constructor that sets up the basics of a node
	Node(Pokemon* p)
	{
		poke = p;
		Node* next = nullptr;
		Node* last = nullptr;
	}

	//getters for each field
	Node* getNext()
	{
		return this->next;
	}
	Node* getLast()
	{
		return this->last;
	}
	Pokemon* getPoke()
	{
		return this->poke;
	}

	//setters for each field
	void setNext(Node* n)
	{
		this->next = n;
	}
	void setLast(Node* n)
	{
		this->last = n;
	}
	void setPoke(Pokemon* p)
	{
		this->poke = p;
	}
};


//a sorted list is used to sort the elements in a singular
//block of a B Tree, this is in order to track the max and min
//of a block accurately in order to navigate in a binary tree esque fashion
class sortedList
{
private:
	Node* first;
	Node* last;
	int size;

public:
	//basic constructor to set values to null
	sortedList()
	{
		first = nullptr;
		last = nullptr;
		size = 0;
	}

	//the insert function allows a singular element (Pokemon pointer) to be inserted into a linked list
	void insert(Pokemon* p)
	{
		Node* n = new Node(p);
		size++;

		//if there is no first element in the linked list, that means it is empty and this element
		//is now the first element
		if (first == nullptr)
		{
			first = n;
			last = n;
			return;
		}

		Node* current = first;
		int nn;
		int cc;
		nn = n->getPoke()->getSearchedValue();

		//indefinite loop until a place is found either along the way or at the end of the linked list
		while (true)
		{
			//nn and cc represent the current nodes searched value of the node we are trying to insert
			cc = current->getPoke()->getSearchedValue();

			//if the node is smaller than the current node, it should go in front of it
			if (nn <= cc)
			{
				if (current == first)
				{
					first = n;
				}
				if (current->getLast() != nullptr)
				{
					n->setLast(current->getLast());
					current->getLast()->setNext(n);

				}
				n->setNext(current);
				current->setLast(n);
				return;
			}

			//if the nodes are equal in value, insert after if there arent nodes after the current one
			//if there are nodes after the current one, the loop will continue and put the new node at the end of
			//a string of same indices ie. if you insert 5 into 12556 it would go before the 6
			if ((nn == cc) && (current->getNext() != nullptr))
			{
				n->setNext(current->getNext());
				n->setLast(current);
				n->getNext()->setLast(n);
				current->setNext(n);
			}
			if (current->getNext() != nullptr)
				current = current->getNext();
			else
				break;
		}
		current->setNext(n);
		n->setLast(current);
		last = n;
	}

	//returns a vector representing the pokemon in the list
	vector<Pokemon*> getVector()
	{
		Node* current = first;
		vector<Pokemon*> vec;
		while (current != nullptr)
		{
			vec.push_back(current->getPoke());
			current = current->getNext();
		}
		return vec;
	}

	//begins a recursive method of a similar name in order to return all pokemon that match certain values
	void returnPokemon(int indexTop, int indexBot, int count, vector<Pokemon*>& results)
	{
		Node* n = first;
		returnPokemonRecursive(indexTop, indexBot, count, n, results);
	}

	//recursively iterates through the linked list, finding every pokemon that matches the search criteria and adding them to a vector
	void returnPokemonRecursive(int indexTop, int indexBot, int count, Node* n, vector<Pokemon*>& results)
	{
		if (n->getPoke()->getSearchedValue() <= indexTop && n->getPoke()->getSearchedValue() >= indexBot)
		{
			results.push_back(n->getPoke());
			if (results.size() == count)
				return;
		}
		if (n->getNext())
			returnPokemonRecursive(indexTop, indexBot, count, n->getNext(), results);
	}

	//getters for the fields
	Node* getFirst()
	{
		return this->first;
	}
	Node* getLast()
	{
		return this->last;
	}
	int getSize()
	{
		return this->size;
	}

	//setters for the fields
	void setFirst(Node* n)
	{
		this->first = n;
	}
	void setLast(Node* n)
	{
		this->last = n;
	}
	void setSize(int i)
	{
		this->size = i;
	}
};