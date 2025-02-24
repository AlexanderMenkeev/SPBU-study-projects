//Задание номер 6 по алгоритмам и структурам данных.
//Реализация AVL-tree

#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;

struct Node
{
	int height, value;
	Node* left;
	Node* right;
	Node* parent;
	Node(Node* parent, int value)
	{
		left = right = nullptr;
		this->parent = parent;
		this->value = value;
		height = 0;
	}
};

class AVLtree
{
public:
	Node* root;
	AVLtree() { root = nullptr; }

	//methods
	int height(Node* node) { return node != nullptr ? node->height : 0; }
	int max(int a, int b) { return a > b ? a : b; }

	//fixes height of the node and all its ancestors
	void updateHeight(Node* node)
	{
		if (node == nullptr)
			return;

		int lefth, righth;
		lefth = righth = 0;

		if (node->left != nullptr)
			lefth = height(node->left) + 1;
		if (node->right != nullptr)
			righth = height(node->right) + 1;

		node->height = max(lefth, righth);

		updateHeight(node->parent);
	}
	void fixHeight(Node* node)
	{
		if (node == nullptr)
			return;
		int lefth, righth;
		lefth = righth = 0;

		if (node->left != nullptr)
			lefth = height(node->left) + 1;
		if (node->right != nullptr)
			righth = height(node->right) + 1;

		node->height = max(lefth, righth);
	}
	int balanceFactor(Node* node)
	{
		if (node == nullptr)
			return 0;
		int lefth, righth;
		lefth = righth = 0;

		if (node->left != nullptr)
			lefth = height(node->left) + 1;
		if (node->right != nullptr)
			righth = height(node->right) + 1;

		return righth - lefth;
	}

	//if unbalanced node is not found, returns nullptr
	Node* findUnbalancedNode(Node* node)
	{
		while (node != nullptr && balanceFactor(node) < 2 && balanceFactor(node) > -2)
			node = node->parent;

		return node;
	}

	Node* leftRotation(Node* A)
	{
		Node* B = A->right;

		B->parent = A->parent;
		A->parent = B;

		if (B->left != nullptr)
			B->left->parent = A;

		A->right = B->left;
		B->left = A;

		fixHeight(A);
		fixHeight(B);
		return B;
	}
	Node* rightRotation(Node* B)
	{
		Node* A = B->left;

		A->parent = B->parent;
		B->parent = A;

		if (A->right != nullptr)
			A->right->parent = B;

		B->left = A->right;
		A->right = B;

		fixHeight(B);
		fixHeight(A);
		return A;
	}
	Node* doubleRightRotation(Node* C)
	{
		C->left = leftRotation(C->left);
		C = rightRotation(C);
		return C;
	}
	Node* doubleLeftRotation(Node* A)
	{
		A->right = rightRotation(A->right);
		A = leftRotation(A);
		return A;
	}

	Node* doSomeRotation(Node* node, int balanceFactor)
	{
		// balanceFactor = -2  =>  doubleRight or Right
		 //balanceFactor = 2  =>  doubleLeft or Left
		int leftH = 0, rightH = 0;
		if (balanceFactor == -2)
		{
			if (node->left->left != nullptr)
				leftH = height(node->left->left) + 1;
			if (node->left->right != nullptr)
				rightH = height(node->left->right) + 1;

			if (leftH < rightH)
			{
				cout << "doubleRightRotation is done" << endl;
				return doubleRightRotation(node);
			}
			else
			{
				cout << "rightRotation is done" << endl;
				return rightRotation(node);
			}
		}
		else
		{
			if (node->right->left != nullptr)
				leftH = height(node->right->left) + 1;
			if (node->right->right != nullptr)
				rightH = height(node->right->right) + 1;

			if (rightH < leftH)
			{
				cout << "doubleLeftRotation is done" << endl;
				return doubleLeftRotation(node);
			}
			else
			{
				cout << "leftRotation is done" << endl;
				return leftRotation(node);
			}
		}
	}
	void balanceTree(Node* unbalancedNode)
	{
		int bFactor = balanceFactor(unbalancedNode);
		print2D(root, 0);
		cout << "Unbalanced Node = " << unbalancedNode->value << ". Its balance factor = "
			<< bFactor << endl;

		Node* new_node = doSomeRotation(unbalancedNode, bFactor);

		if (new_node->parent == nullptr)
			root = new_node;
		else if (new_node->parent->left == unbalancedNode)
			new_node->parent->left = new_node;
		else
			new_node->parent->right = new_node;
		
		updateHeight(new_node);
		print2D(root, 0);
	}
	void insert(int value)
	{
		if (root == nullptr)
		{
			root = new Node(nullptr, value);
			cout << value << " is inserted as the root" << endl;
			return;
		}

		Node* temp = root;
		while (temp != nullptr)
		{
			if (value < temp->value && temp->left == nullptr)
			{
				temp->left = new Node(temp, value);
				cout << value << " is inserted to the left" << endl;
				updateHeight(temp);
				Node* unbalancedNode = findUnbalancedNode(temp);
				if (unbalancedNode != nullptr)
					balanceTree(unbalancedNode);
				return;
			}
			else if (value < temp->value)
				temp = temp->left;
			



			if (value > temp->value && temp->right == nullptr)
			{
				temp->right = new Node(temp, value);
				cout << value << " is inserted to the right" << endl;
				updateHeight(temp);
				Node* unbalancedNode = findUnbalancedNode(temp);
				if (unbalancedNode != nullptr)
					balanceTree(unbalancedNode);
				return;
			}
			else if (value > temp->value)
				temp = temp->right;
			
		}

	}
	Node* iterativeSearch(int value)
	{
		if (root == nullptr)
			return root;
		else
		{
			Node* temp = root;
			while (temp != nullptr)
			{
				if (value == temp->value)
					return temp;
				else if (value < temp->value)
					temp = temp->left;
				else
					temp = temp->right;
			}
			return nullptr;
		}
	}
	void deleteNode(Node* toDelete)
	{
		if (toDelete == nullptr)
		{
			cout << "Node to delete is not found!" << endl;
			return;
		}
		else
			cout << "Node to delete " << toDelete->value << " is found" << endl;

		Node* minRightNode = minValueNode(toDelete->right);
		Node* maxLeftNode = maxValueNode(toDelete->left);

		if (minRightNode != nullptr)
		{
			toDelete->value = minRightNode->value;
			deleteNode(minRightNode);
			return;
		}
		else if (maxLeftNode != nullptr)
		{
			toDelete->value = maxLeftNode->value;
			deleteNode(maxLeftNode);
			return;
		}
		if (toDelete->left == nullptr && toDelete->right == nullptr && toDelete->parent != nullptr)
		{
			if (toDelete->parent->right == toDelete)
				toDelete->parent->right = nullptr;
			else
				toDelete->parent->left = nullptr;

			updateHeight(toDelete->parent);
			Node* unbalancedNode = findUnbalancedNode(toDelete->parent);
			while (unbalancedNode != nullptr)
			{
				balanceTree(unbalancedNode);
				unbalancedNode = findUnbalancedNode(toDelete->parent);
			}

			delete toDelete;
			print2D(root, 0);
			return;
		}
		else if (toDelete->left == nullptr && toDelete->right == nullptr)
		{
			root = nullptr;
			delete toDelete;
			cout << "Root deleted" << endl;
			print2D(root, 0);
			return;
		}
	}
	Node* minValueNode(Node* node)
	{
		if (node == nullptr)
			return nullptr;
		
		Node* current = node;
		while (current->left != nullptr)
			current = current->left;
		
		return current;
	}
	Node* maxValueNode(Node* node)
	{
		if (node == nullptr)
			return nullptr;

		Node* current = node;
		while (current->right != nullptr)
			current = current->right;
		
		return current;
	}
	void print2D(Node* node, int space)
	{
		if (node == nullptr)
			return;
		space += 10;
		print2D(node->right, space);
		cout << endl;
		for (int i = 5; i < space; i++)
			cout << " ";

		cout << node->value << ":" << node->height;
		if (node->parent != nullptr)
			cout << ":" << node->parent->value;
		cout << endl;
		print2D(node->left, space);
	}
};

int main(int argc, char* argv[])
{
	std::ifstream inFile("C:\\Users\\Александр\\github-classroom\\amcp-pit\\task6-avl-tree-AlexanderMenkeev\\input1.txt");
	if (!inFile)
	{
		return 2;
	}
	std::ofstream outFile("C:\\Users\\Александр\\github-classroom\\amcp-pit\\task6-avl-tree-AlexanderMenkeev\\output1.txt");
	if (!outFile)
	{
		return 3;
	}

	AVLtree tree;
	int n, x;
	char operation;
	inFile >> n;
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
			outFile << tree.balanceFactor(tree.root) << '\n';
			break;

		case '-':
			inFile.ignore(10, ' ');
			inFile >> x;
			tree.deleteNode(tree.iterativeSearch(x));
			outFile << ":" << tree.balanceFactor(tree.root) << '\n';
			break;

		case '?':
			inFile.ignore(10, ' ');
			inFile >> x;
			if (tree.iterativeSearch(x) == nullptr)
				outFile << "false" << '\n';
			else
				outFile << "true" << '\n';
			break;
		}
	}
	tree.print2D(tree.root, 0); cout << endl;
	cout << "Time: " << clock();
	inFile.close();
	outFile.close();
	return 0;
}
