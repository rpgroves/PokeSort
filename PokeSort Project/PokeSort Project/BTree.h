#include "Block.h"

//B Tree Properties
//1. Each node contains a block containing multiple keys, at most I
	//this is achieved in Block.h which allows us to create blocks that split after holding I values

//2. B Trees are N-Ary trees, each node has up to n children. They follow BST properties
	//this is also achieved with Block.insert() which splits when more than n children are held

//3. Tree building is bottom up
	//this is achieved in Block.insert() as well as the insert pokemon are inserted into the bottom only

//4. Order 'n' tree has at most n children
	//see above for part 2

//5. Leaves are the same depth
	//achieved through the bottom up build

//6. Non leaf nodes up to n-1 keys, all keys in sorted order
	//this is achieved through the nature of the Block.h file as when inserting and splitting, once
	//a non leaf node has n-1 keys it must split because that means it will have too many children

	class BTree
{
private:
	//holds a root pointer and a string representing 
	//what value is being searchef for in the tree
	Block* root;
	string searchType;

	//changes the root of the tree
	void appendRoot(Block* b)
	{
		root = b;
	}

public:
	//initializes a new tree
	BTree(string st)
	{
		searchType = st;
		root == nullptr;
	}

	//inserts a pokemon P into the tree, sorting and splitting are done for you
	void insert(Pokemon* p)
	{
		//updates the index of the pokemon using the searchType field
		p->updateSearchedVal(searchType);

		//if no blocks yet, insert one
		if (root == nullptr)
		{
			Block* pushBlock;
			pushBlock = new Block(true, true);
			pushBlock->insert(p, false);
			root = pushBlock;
			return;
		}
		Block* b = nullptr;

		//if there is a block, start insertion at the root
		b = root->insert(p, false);

		//if a value was returned from insert, it was a value we have to delete as a split occured
		if (b != nullptr)
		{
			if (root->getParent() != nullptr)
				if (root->getParent()->bRoot())
					root = b->getParent();
			delete(b);
		}

	}

	//returns a vector of pokemon with 'searchVal' between the two indices (inclusive), larger index comes FIRST
	//count represents the amount of pokemon you would like, in order to get every pokemon, enter indexTop - indexBot in the count field
	vector<Pokemon*> findPokemon(int indexTop, int indexBot, int count)
	{
		vector<Pokemon*> results;
		root->findPokemon(indexTop, indexBot, count, results);
		return results;
	}
};
