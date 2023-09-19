#include "LinkedList.h"

//The block represents the linked list of values in a B Tree block,
//however it carries the additional functionality of holding pointers
//to its children and being able to split when necessary as well as being
//able to tell whether or not it is a root
class Block
{
private:
	//holds a sorted list of pokemon
	sortedList* pokeList;

	//L and N are changable, however in this implementation, N will always be 3 and L will always be 5
	int L;
	int N;

	//holds pointers to each of its children
	Block* leftChild;
	Block* middleChild;
	Block* rightChild;

	//buffer child represents a 4th child which is created just before
	//a split must be made, it is used to represent an extra middle child
	Block* bufferChild;

	//holds a pointer to the parent block
	Block* parent;

	//holds values pertaining to the highest and lowest value index as well as the index in the center
	int max;
	int min;
	int mid;

	//holds values for whether the block is a leaf, root, or neither
	bool isLeaf;
	bool isRoot;

public:
	//consstructor that initialized all nullpointers, creates a pokemon linked list, and initialized its booleans
	Block(bool il, bool ir)
	{
		L = 5;
		N = 3;
		isLeaf = il;
		isRoot = ir;
		pokeList = new sortedList();

		parent = nullptr;
		leftChild = nullptr;
		middleChild = nullptr;
		rightChild = nullptr;
		bufferChild = nullptr;
	}

	//inserts a pokemon into the block, and the linked list by extension
	Block* insert(Pokemon* p, bool isCurrentlySplitting)
	{
		//in the case of a split b represents the newly made block
		//this is returned incase this block needs to be made the new root of the tree
		Block* b = nullptr;

		//this if statment essentially navigates the tree in a RLMN (right left middle node) fashion recursively
		//if we are splitting and currently inserting into a new block, we dont need to have the block navigate anywhere
		//this is why isCurrentlySplitting is used
		//there is also downward navigation when you arent yet at a leaf node
		if (!isLeaf && !isCurrentlySplitting)
		{
			if (p->getSearchedValue() > max)
				b = rightChild->insert(p, false);
			else if (p->getSearchedValue() < min)
				b = leftChild->insert(p, false);
			else
			{
				if (middleChild)
					b = middleChild->insert(p, false);
				else if (p->getSearchedValue() == min)
					b = leftChild->insert(p, false);
				else if (p->getSearchedValue() == max)
					b = rightChild->insert(p, false);
			}
			return b;
		}

		//if we do not need to navigate downward in the tree, we can insert into the block
		pokeList->insert(p);

		//if there are too many pokemon in the block we must split
		if (pokeList->getSize() >= L)
		{
			b = split();
			return b;
		}

		//update the max and min of the block incase of a change
		max = pokeList->getLast()->getPoke()->getSearchedValue();
		min = pokeList->getFirst()->getPoke()->getSearchedValue();

		//if we split we do not need to delete an old block, we can return nullptr
		return nullptr;
	}

private:
	//splits a block into three new ones, parent, leftchild, rightchild
	Block* split()
	{
		int splitIndex = pokeList->getSize() - (pokeList->getSize() / 2) - 1;
		vector<Pokemon*> vec = pokeList->getVector();
		Pokemon* p = vec.at(splitIndex);

		bool newRoot = false;

		bool ir = false;
		bool il = false;
		if (isLeaf)
			il = true;
		if (isRoot)
			ir = true;

		if (parent == nullptr)
		{
			newRoot = true;
			parent = new Block(false, ir);
			parent->insert(p, true);
		}
		else
		{
			parent->insert(p, true);
		}

		ir = false;

		Block* lc = new Block(il, ir);
		Block* rc = new Block(il, ir);
		lc->parent = parent;
		rc->parent = parent;

		for (int i = 0; i < splitIndex; i++)
		{
			if (vec.size() == i)
				break;
			lc->insert(vec.at(i), true);
		}
		for (int i = splitIndex + 1; i < L; i++)
		{
			if (vec.size() == i)
				break;
			rc->insert(vec.at(i), true);
		}

		if (newRoot)
		{
			parent->leftChild = lc;
			parent->rightChild = rc;
		}
		else
		{
			if (parent->middleChild == nullptr)
			{

				if (parent->rightChild == this)
				{
					parent->rightChild = rc;
					parent->middleChild = lc;
				}
				else if (parent->leftChild == this)
				{
					parent->leftChild = lc;
					parent->middleChild = rc;
				}
			}
			else
			{
				if (parent->rightChild == this)
				{
					parent->rightChild = rc;
					parent->bufferChild = lc;
				}
				else if (parent->middleChild == this)
				{
					parent->bufferChild = lc;
					parent->middleChild = rc;
				}
				else if (parent->leftChild == this)
				{
					parent->leftChild = lc;
					parent->bufferChild = rc;
				}

				if (bufferChild != nullptr)
				{
					rc->rightChild = rightChild;
					lc->leftChild = leftChild;
					rightChild->parent = rc;
					leftChild->parent = lc;
					if (bufferChild->max < middleChild->max)
					{
						rc->leftChild = middleChild;
						lc->rightChild = bufferChild;
						middleChild->parent = rc;
						bufferChild->parent = lc;
					}
					else
					{
						rc->leftChild = bufferChild;
						lc->rightChild = middleChild;
						bufferChild->parent = rc;
						middleChild->parent = lc;
					}
				}

				Block* b = parent->split();
				return b;
			}
		}
		if (bufferChild != nullptr)
		{
			rc->rightChild = rightChild;
			lc->leftChild = leftChild;
			rightChild->parent = rc;
			leftChild->parent = lc;
			if (bufferChild->max < middleChild->max)
			{
				rc->leftChild = middleChild;
				lc->rightChild = bufferChild;
				middleChild->parent = rc;
				bufferChild->parent = lc;
			}
			else
			{
				rc->leftChild = bufferChild;
				lc->rightChild = middleChild;
				bufferChild->parent = rc;
				middleChild->parent = lc;
			}
			//int i = 0;
			//parent->print(i);
		}

		return this;
	}

public:
	//takes in a reference to a vector, which is used to push_back pokemon that match search values
	//the vector is a parameter so that the function can work recursively
	void findPokemon(int indexTop, int indexBot, int count, vector<Pokemon*>& results)
	{
		bool testedThisBlock = false;
		//cout << "testing a block of max: " << max << " and min: " << min << endl;
		if (((min >= indexBot) && (indexTop >= min)) || ((max >= indexBot) && (indexTop >= max)) || ((min <= indexBot) && (max >= indexTop)) || ((min >= indexBot) && (max <= indexTop)))
		{
			testedThisBlock = true;
			pokeList->returnPokemon(indexTop, indexBot, count, results);
			if (results.size() == count)
				return;
		}

		if (!isLeaf)
		{
			if (indexTop > max && rightChild)
				rightChild->findPokemon(indexTop, indexBot, count, results);

			if (results.size() == count)
				return;

			if (indexBot < min && leftChild)
				leftChild->findPokemon(indexTop, indexBot, count, results);

			if (results.size() == count)
				return;

			if (testedThisBlock && middleChild)
				middleChild->findPokemon(indexTop, indexBot, count, results);
		}
	}

	//returns the parent of a block
	Block* getParent()
	{
		return parent;
	}

	//returns the status of whether this block is the root
	bool bRoot()
	{
		return isRoot;
	}
};
