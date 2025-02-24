#include <iostream>

struct node
{
	int value;
	node* next;
	node(int value)
	{
		this->value = value;
		next = nullptr;
	}
};

class list
{
public:
	node* first;
	int length = 0;

	//O(n)
	void push_back(int value)
	{
		if (length == 0)
		{
			first = new node(value);
			length++;
		}
		else
		{
			node* temp = first;
			while (temp->next != nullptr)
				temp = temp->next;
			temp->next = new node(value);
			length++;
		}
	}

	//O(1)
	void push_forward(int value)
	{
		node* temp = new node(value);
		temp->next = first;
		first = temp;
	}

	void print()
	{
		node* temp = first;
		while (temp != nullptr)
		{
			std::cout << temp->value << '\n';
			temp = temp->next;
		}
	}

};

int main()
{
	list myList;
	myList.push_back(5);
	myList.push_back(54);
	myList.push_back(14);
	myList.push_back(513);
	myList.push_back(321);
	myList.push_back(312);
	myList.push_back(132);
	myList.push_forward(1);
	myList.push_forward(1234);
	myList.print();
}