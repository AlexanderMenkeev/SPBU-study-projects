//Задание номер 7 по алгоритмам и структурам данных.
//Реализация b-tree

#include <fstream>
#include <iostream>
#include <ctime>

using namespace std;

#define NEW_ROOT 2
#define MODIFIED_NOT_ROOT 1
#define NOT_MODIFIED 0

#define SEARCH_KEY_NOT_FOUND 's'
#define REMOVE_KEY_NOT_FOUND 'r'

struct BNode {
	BNode** child;
	int* key;
	unsigned size;
	bool leaf;
};

typedef char BTREE_EXCEPTION;


class BTree {
public:
	BNode* root;
	unsigned t;

	BTree(unsigned t) {
		this->t = t;
		root = new BNode();
		initializeNode(root);
		root->leaf = true;
	}

	~BTree() {
		freeNode(root);
		delete root;
	}

	void insert(int k) {
		if (root->size == 2 * t - 1) {
			BNode* newRoot = new BNode;
			initializeNode(newRoot);
			newRoot->leaf = false;
			newRoot->child[0] = root;
			root = newRoot;
			splitChild(newRoot, 0);
		}

		BNode* curr = root;
		while (!curr->leaf) {

			//Find the proper child to go to
			int index = curr->size - 1;
			while (index >= 0 && k < curr->key[index]) {
				index--;
			}
			index++;

			//Split child if full
			if (curr->child[index]->size == 2 * t - 1) {
				splitChild(curr, index);
				if (curr->key[index] < k) {
					index++;
				}
			}
			curr = curr->child[index];
		}
		nodeInsert(curr, k);
	}

	void remove(int k) {
		BNode* curr = root;
		while (true) {
			unsigned i = findIndex(curr, k);

			if (i < curr->size && curr->key[i] == k) {

				// If at a leaf, simply delete it.
				if (curr->leaf) {
					nodeRemove(curr, i);
				}

				// Otherwise replace with predecessor/successor or merge children.
				else {
					BNode* leftKid = curr->child[i];
					BNode* rightKid = curr->child[i + 1];

					// Replace with predecessor.
					if (leftKid->size >= t) {
						while (!(leftKid->leaf)) {
							fixChildSize(leftKid, leftKid->size);
							leftKid = leftKid->child[leftKid->size];
						}
						curr->key[i] = nodeRemove(leftKid, leftKid->size - 1);
					}

					// Replace with successor
					else if (rightKid->size >= t) {
						while (!(rightKid->leaf)) {
							fixChildSize(rightKid, 0);
							rightKid = rightKid->child[0];
						}
						curr->key[i] = nodeRemove(rightKid, 0);
					}

					// Merge children
					else {
						mergeChildren(curr, i);
						curr = leftKid;
						continue;
					}
				}
				return;
			}

			else {

				if (curr->leaf) {
					throw (BTREE_EXCEPTION)REMOVE_KEY_NOT_FOUND;
				}

				char result = fixChildSize(curr, i);
				if (result == NEW_ROOT) {
					curr = root;
				}
				else {
					curr = curr->child[findIndex(curr, k)];
				}
			}
		}
	}


	// pair.first is the node.
	// pair.second is the correct index of the key
	pair<BNode*, unsigned> search(int k) {

		BNode* x = root;

		while (true) {

			unsigned i = findIndex(x, k);

			if (i < x->size && k == x->key[i]) {
				return pair<BNode*, unsigned>(x, i);
			}

			else if (x->leaf) {
				return pair<BNode*, unsigned>(NULL, 0);
			}

			else {
				x = x->child[i];
			}
		}
	}


	// Function to find a key in the tree.
	int searchKey(int k) {
		pair<BNode*, unsigned> node = search(k);
		if (node.first == NULL) {
			throw (BTREE_EXCEPTION)SEARCH_KEY_NOT_FOUND;
		}
		return node.first->key[node.second];
	}

	void printNodeInFile(BNode* node, ofstream& outFile)
	{
		outFile << node->size;
		if (node->size != 0)
			outFile << " ";
		for (unsigned i = 0; i < node->size; i++)
		{
			outFile << node->key[i];
			if (i < node->size - 1)
				outFile << " ";
		}
		outFile << '\n';
	}

	void print() {
		if (root != nullptr) {
			cout << endl;
			printNode(root, 0);
			cout << endl;
		}
	}

private:
	void initializeNode(BNode* node) {
		node->size = 0;
		node->key = new int[2 * t - 1];
		node->child = new BNode * [2 * t];
		for (unsigned i = 0; i < 2 * t; i++)
			node->child[i] = nullptr;
	}

	//Recursively deletes the subtree
	void freeNode(BNode* node) {
		if (!node->leaf) {
			for (unsigned i = 0; i < node->size; i++) {
				freeNode(node->child[i]);
			}
		}
		for (unsigned i = 0; i < 2 * t; i++)
			delete node->child[i];
		delete[] node->child;
		delete[] node->key;
	}

	//if index isn't found, returns node->size
	unsigned findIndex(BNode* node, int k) {
		unsigned i = 0;
		while (i < node->size && node->key[i] < k) {
			i++;
		}
		return i;
	}


	//Inserts k into node.
	unsigned nodeInsert(BNode* node, int k) {

		int index;
		//Make space for k.
		for (index = node->size; index > 0 && k < node->key[index - 1]; index--) {
			node->key[index] = node->key[index - 1];
			node->child[index + 1] = node->child[index];
		}

		//Insert k.
		node->child[index + 1] = node->child[index];
		node->key[index] = k;
		node->size++;

		return index;
	}


	//Removes node->key[index]
	//Returns deleted key
	int nodeRemove(BNode* node, unsigned index) {

		int toReturn = node->key[index];

		node->size--;
		while (index < node->size) {
			node->key[index] = node->key[index + 1];
			node->child[index + 1] = node->child[index + 2];
			index++;
		}
		return toReturn;
	}


	void splitChild(BNode* node, int i) {

		BNode* y = node->child[i];
		BNode* z = new BNode;
		initializeNode(z);
		z->leaf = y->leaf;
		z->size = t - 1;

		for (unsigned j = 0; j < t - 1; j++) {
			z->key[j] = y->key[j + t];
		}
		if (!y->leaf) {
			for (unsigned j = 0; j < t; j++) {
				z->child[j] = y->child[j + t];
			}
		}
		y->size = t - 1;

		nodeInsert(node, y->key[t - 1]);
		node->child[i + 1] = z;
	}


	//Merges child[i+1] of parent with child[i] of parent.
	//Returns an indicator of how it affected the root.
	char mergeChildren(BNode* parent, unsigned i) {

		BNode* leftKid = parent->child[i];
		BNode* rightKid = parent->child[i + 1];


		leftKid->key[leftKid->size] = nodeRemove(parent, i);
		unsigned j = ++(leftKid->size);

		// Move everything from rightKid into leftKid
		for (unsigned k = 0; k < rightKid->size; k++) {
			leftKid->key[j + k] = rightKid->key[k];
			leftKid->child[j + k] = rightKid->child[k];
		}
		leftKid->size += rightKid->size;
		leftKid->child[leftKid->size] = rightKid->child[rightKid->size];

		delete[] rightKid->child;
		delete[] rightKid->key;
		delete rightKid;

		if (parent->size == 0) {
			root = leftKid;
			delete[] parent->child;
			delete[] parent->key;
			delete parent;
			return NEW_ROOT;
		}

		return MODIFIED_NOT_ROOT;
	}


	//Makes sure parent->child[index] has at least minDegree items
	//If it doesn't, then things are fixed
	//Returns a code indicating what action was taken
	char fixChildSize(BNode* parent, unsigned index) {
		BNode* kid = parent->child[index];

		if (kid->size < t) {
			if (index != 0 && index != parent->size)
			{
				BNode* rightKid = parent->child[index + 1];
				BNode* leftKid = parent->child[index - 1];

				//Borrow from right sibling if possible
				if (rightKid->size >= t && rightKid->size > leftKid->size)
				{
					nodeInsert(kid, parent->key[index]);
					kid->child[kid->size] = rightKid->child[0];
					rightKid->child[0] = rightKid->child[1];

					parent->key[index] = nodeRemove(rightKid, 0);
				}

				//Borrow from left sibling if possible.
				else if (leftKid->size >= t)
				{
					for (unsigned i = nodeInsert(kid, parent->key[index - 1]); i != 0; i--) {
						kid->child[i] = kid->child[i - 1];
					}
					kid->child[0] = leftKid->child[leftKid->size];
					parent->key[index - 1] = nodeRemove(leftKid, leftKid->size - 1);
				}
				//If borrowing is not possible, then merge.
				else if (index != 0) {
					return mergeChildren(parent, index - 1);
				}
				else {
					return mergeChildren(parent, index);
				}
				return MODIFIED_NOT_ROOT;
			}
			else if (index == 0)
			{
				BNode* rightKid = parent->child[index + 1];
				//Borrow from right sibling if possible
				if (rightKid->size >= t)
				{
					nodeInsert(kid, parent->key[index]);
					kid->child[kid->size] = rightKid->child[0];
					rightKid->child[0] = rightKid->child[1];

					parent->key[index] = nodeRemove(rightKid, 0);
				}
				//If borrowing is not possible, then merge.
				else if (index != 0) {
					return mergeChildren(parent, index - 1);
				}
				else {
					return mergeChildren(parent, index);
				}
				return MODIFIED_NOT_ROOT;

			}
			else if (index == parent->size)
			{
				BNode* leftKid = parent->child[index - 1];
				//Borrow from left sibling if possible.
				if (leftKid->size >= t)
				{
					for (unsigned i = nodeInsert(kid, parent->key[index - 1]); i != 0; i--) {
						kid->child[i] = kid->child[i - 1];
					}
					kid->child[0] = leftKid->child[leftKid->size];
					parent->key[index - 1] = nodeRemove(leftKid, leftKid->size - 1);
				}
				//If borrowing is not possible, then merge.
				else if (index != 0) {
					return mergeChildren(parent, index - 1);
				}
				else {
					return mergeChildren(parent, index);
				}
				return MODIFIED_NOT_ROOT;
			}
		}

		// If things don't need fixed.
		return NOT_MODIFIED;
	}

	void printNode(BNode* node, unsigned tab) {
		for (unsigned i = 0; i < tab; i++) {
			cout << "  ";
		}

		for (unsigned i = 0; i < node->size; i++)
			cout << node->key[i] << " ";

		cout << endl;

		if (!node->leaf) {
			tab += 5;
			for (int i = node->size; i >= 0; i--) {
				printNode(node->child[i], tab);
			}
		}
	}

};


int main(int argc, char* argv[])
{
	std::ifstream inFile(argv[1]);
	if (!inFile) return 2;
	std::ofstream outFile(argv[2]);
	if (!outFile) return 3;

	int t, n, x;
	char operation;
	inFile >> t >> n;
	BTree tree(t);
	for (int i = 0; i < n; i++)
	{
		inFile.ignore(10, '\n');
		inFile.get(operation);
		switch (operation)
		{
		case '+':
			inFile.ignore(10, ' ');
			inFile >> x;
			tree.insert(x);
			tree.printNodeInFile(tree.root, outFile);
			break;

		case '-':
			inFile.ignore(10, ' ');
			inFile >> x;
			tree.remove(x);
			tree.printNodeInFile(tree.root, outFile);
			break;

		case '?':
			inFile.ignore(10, ' ');
			inFile >> x;
			if (tree.search(x).first == nullptr)
				outFile << "false" << '\n';
			else
				outFile << "true" << '\n';
			break;
		}
	}

	cout << "Time: " << clock();
	inFile.close();
	outFile.close();
	return 0;
}