//Задание номер 1 по алгоритмам и структурам данных. Очередь с минимумом

#include <fstream>
#include <iostream>
#include <ctime>
#include <limits>
#include <stack>

#define max std::numeric_limits<int>::max()

class Queue {
private:
	std::stack<std::pair<int, int>> in_stack;
	std::stack<std::pair<int, int>> out_stack;
	int minValue = max;

public:
	Queue() {};
	void push_back(int value) {
		if (in_stack.empty())
			minValue = max;
		else if (in_stack.empty())
			minValue = in_stack.top().second;

		if (value < minValue)
			minValue = value;

		in_stack.push(std::make_pair(value, minValue));
	}

	//fills out_stack with contents of in_stack
	void fill_outStack()
	{
		int value = 0;
		minValue = max;
		while (!in_stack.empty())
		{
			value = in_stack.top().first;
			in_stack.pop();
			if (value < minValue)
				minValue = value;

			out_stack.push(std::make_pair(value, minValue));
		}
	}

	void pop_front()
	{
		if (out_stack.empty())
			fill_outStack();
			
		out_stack.pop();
	}

	int find_min()
	{
		if (out_stack.empty()) {
			return in_stack.top().second;
		}
		else if (!in_stack.empty())
		{
			int min_1 = in_stack.top().second;
			int min_2 = out_stack.top().second;
			return min_1 < min_2 ? min_1 : min_2;
		}
		else
			return out_stack.top().second;
	}
};


int main(int argc, char* argv[])
{
	std::ifstream inFile("C:\\Users\\Александр\\github-classroom\\amcp-pit\\task1-minimum-queue-AlexanderMenkeev\\tests\\in\\input3.txt");
	if (!inFile) return 2;
	std::ofstream outFile("C:\\Users\\Александр\\github-classroom\\amcp-pit\\task1-minimum-queue-AlexanderMenkeev\\tests\\out\\output3.txt");
	if (!outFile) return 3;

	int x = 0;
	char operation;
	int n = 0;
	inFile >> n;
	Queue queue;

	for (int i = 0; i < n; i++)
	{
		inFile.ignore(255, '\n');
		inFile.get(operation);
		switch (operation)
		{
		case '+':
			inFile.ignore(255, ' ');
			inFile >> x;
			queue.push_back(x);
			break;
		case '-':
			queue.pop_front();
			break;
		case '?':
			outFile << queue.find_min() << '\n';
			break;
		}
	}

	std::cout << "Time: " << clock() << std::endl;
	inFile.close();
	outFile.close();
	return 0;
}