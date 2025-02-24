//Задание номер 8 по алгоритмам и структурам данных.
//Реализация хэш-таблицы

#include <iostream>
#include <fstream>
#include <list>
using namespace std;

class HashTable
{
private:
	static const int hashGroups = 10;
	list<int>* table = new list<int>[hashGroups];
public:
	bool isEmpty() const;
	int hashFunction(int key);
	void insert(int key);
	void remove(int key);
	int find(int key);
	void printTable();
};

bool HashTable::isEmpty() const
{
	int sum = 0;
	for (int i = 0; i < hashGroups; i++)
		sum += table[i].size();

	if (sum == 0)
		return true;
	else
		return false;
}

int HashTable::hashFunction(int value)
{
	return value % hashGroups;
}

void HashTable::insert(int value)
{
	int key = hashFunction(value);
	list<int>& cell = table[key];
	cell.push_back(value);
}

void HashTable::remove(int value)
{
	int key = hashFunction(value);
	auto& cell = table[key];
	cell.remove(value);
}

void HashTable::printTable()
{
	for (int i = 0; i < hashGroups; i++)
	{
		cout << i << ": ";
		auto& cell = table[i];
		for (auto it = begin(cell); it != end(cell); it++)
			cout << *it << " ";
		cout << endl;
	}
}

int HashTable::find(int value)
{
	int key = hashFunction(value);
	int toReturn = -1;
	auto& cell = table[key];
	for (auto it = begin(cell); it != end(cell); it++)
		if (*it == value)
			toReturn = *it;
	return toReturn;
}

int main(int argc, char* argv[]) {
	std::ifstream inFile(argv[1]);
	if (!inFile)
	{
		return 2;
	}
	std::ofstream outFile(argv[2]);
	if (!outFile)
	{
		return 3;
	}

	int n, x;
	char operation;
	inFile >> n;

	HashTable table;


	for (int i = 0; i < n; i++)
	{
		inFile.ignore(10, '\n');
		inFile.get(operation);
		switch (operation)
		{
		case '+':
			inFile.ignore(10, ' ');
			inFile >> x;
			table.insert(x);
			break;

		case '-':
			inFile.ignore(10, ' ');
			inFile >> x;
			table.remove(x);
			break;

		case '?':
			inFile.ignore(10, ' ');
			inFile >> x;
			if (table.find(x) == x)
				outFile << "true" << '\n';
			else
				outFile << "false" << '\n';
			break;
		}
	}
	cout << "Time: " << clock();
	inFile.close();
	outFile.close();

	return 0;
}