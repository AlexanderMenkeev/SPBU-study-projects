//Задание номер 9 по алгоритмам и структурам данных.
//Реализация очереди с приоритетом

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class PriorityQueue
{
private:
	int PARENT(int i) { return (i - 1) / 2; }

	int LEFT(int i)   { return (2 * i + 1); }

	int RIGHT(int i)  { return (2 * i + 2); }

	void heapify_down(int i)
	{
		int left = LEFT(i);
		int right = RIGHT(i);

		int smallest = i;

		if (left < size() && A[left] < A[i]) {
			smallest = left;
		}

		if (right < size() && A[right] < A[smallest]) {
			smallest = right;
		}

		if (smallest != i)
		{
			std::swap(A[i], A[smallest]);
			heapify_down(smallest);
		}
	}

	void heapify_up(int i)
	{
		if (i && A[PARENT(i)] > A[i])
		{
			std::swap(A[i], A[PARENT(i)]);

			heapify_up(PARENT(i));
		}
	}

public:
	std::vector<int> A;
	unsigned int size() {
		return A.size();
	}

	bool empty() {
		return size() == 0;
	}

	void push(int value)
	{
		A.push_back(value);
		int index = size() - 1;
		heapify_up(index);
	}

	//удаляет минимум и перестраивает дерево
	void extract_min()
	{
		A[0] = A.back();
		A.pop_back();
		heapify_down(0);
	}

	//возвращает минимум
	int top()
	{
		return A.at(0);
	}


	//value - элемент, который нужно заменить
	//y - элемент, на который нужно заменить
	//известно: y < value и value существует
	void decrease_key(int value, int y)
	{
		int i = 0;
		for (i = 0; i < size(); i++)
			if (A[i] == value)
			{
				A[i] = y;
				break;
			}
		if (i != 0)
			heapify_up(i);
	}
};

void print(std::vector<int> vect, int size)
{
	for (int i = 0; i < size; i++)
		std::cout << vect[i] << " ";
	std::cout << std::endl;
}


int main(int argc, char* argv[])
{
	std::ifstream inFile("C:\\Users\\Александр\\github-classroom\\amcp-pit\\task9-priorityqueue-AlexanderMenkeev\\tests\\in\\input9.txt");
	if (!inFile) return 2;
	std::ofstream outFile("C:\\Users\\Александр\\github-classroom\\amcp-pit\\task9-priorityqueue-AlexanderMenkeev\\tests\\out\\output9.txt");
	if (!outFile) return 3;
	

	PriorityQueue tree;
	int x, y;
	int* a = new int[100000];//массив, где хранятся элементы, добавленные операцией push(x)
	int j = 0;				 //счетчик для подсчета номера строки
    char ch;
	while (inFile.get(ch))
	{
		switch (ch)
		{
		//push x
		case 'p':
			inFile.seekg(4, std::ios::cur);
			inFile >> x;
			tree.push(x);
			a[j] = x;
			j++;

			/*std::cout << x << " is inserted" << std::endl;
			print(tree.A, tree.size());*/


			break;

		//extract-min
		case 'e': 
			j++;
			inFile.seekg(11, std::ios::cur);
			if (tree.empty())
				outFile << "*" << '\n';
			else
			{
				x = tree.top();
				tree.extract_min();
				outFile << x << '\n';

				/*std::cout << x << " is extracted" << std::endl;
				print(tree.A, tree.size());*/
			}
			break;

		//decrease-key
		case 'd':
			j++;
			inFile.seekg(12, std::ios::cur);
			inFile >> x >> y;
			tree.decrease_key(a[x - 1], y);


			/*std::cout << a[x - 1] << " is replaced by " << y << std::endl;
			print(tree.A, tree.size());*/

			break;
		}
	}
	
	/*std::cout << std::endl;
	print(tree.A, tree.size());*/
	

	delete[] a;
	std::cout << "Time: " << clock();
	inFile.close();
	outFile.close();
	return 0;
}
