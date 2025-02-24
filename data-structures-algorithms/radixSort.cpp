#include <fstream>
#include <iostream>
#include <ctime>

struct tuple
{
    int value;
    int indx;
    tuple(int value, int indx)
    {
        this->value = value;
        this->indx = indx;
    }
    tuple() { value = 0; indx = 0; }
};

void print(tuple* arr, int M)
{
	for (int i = 0; i < M; i++)
		std::cout << arr[i].value << " ";
	std::cout << std::endl;
}

void printArr(int* arr, int n, const int m)
{
	for (int i = 0; i < m; i++)
		std::cout << i << ":" << arr[i] << " ";
	std::cout << std::endl;
}


//Буквы имеют следующие коды:
//A = 0, B = 1, C = 2 ... a = 32, b = 33, c = 34 ... z = 57
tuple* countingSort(tuple* arr, int n)
{
	const int m = 59;
	int p[m] = { 0 }; //индекс - код буквы, а значение - количество таких букв в строке
	for (int i = 0; i < n; i++)
		p[arr[i].value - 65]++;
	
	//изменяем массив. Индекс - код буквы, а значение - это позиция, с которой начинается "подмассив" таких букв
	int k = 0, prev = 0, temp = 0;
	while (p[k] == 0 && k < m - 1) //поиск первого ненулевого элемента
		k++;
	prev = p[k + 1];
	p[k + 1] = p[k];
	p[k] = 0;
	for (int i = k + 1; i < m - 2; i++)
	{
		if (prev == 0) {
			prev = p[i + 1];
			p[i + 1] = p[i];
		}
		else
		{
			temp = prev;
			prev = p[i + 1];
			p[i + 1] = temp+p[i];
		}
	}

	tuple* result = new tuple[n];

	for (int i = 0; i < n; i++)
	{
		result[p[arr[i].value - 65]] = arr[i];
		p[arr[i].value - 65]++;
	}
	delete[] arr;
	return result;
}


int main(int argc, char* argv[])
{
    std::ifstream inFile("C:\\Users\\Александр\\github-classroom\\amcp-pit\\task5-radix-sort-AlexanderMenkeev\\tests\\in\\input8.txt", std::ios::binary);
	if (!inFile){ return -2; }
	std::ofstream outFile("C:\\Users\\Александр\\github-classroom\\amcp-pit\\task5-radix-sort-AlexanderMenkeev\\tests\\out\\output8.txt");
	if (!outFile){ return -3; }

	int N, M, K;
	inFile >> N >> M >> K;

	int b = inFile.tellg();
	b += 2;

	char* a = new char[N + 1];
	a[N] = '\0';

    tuple* arr = new tuple[N];
    for (int i = 0; i < N; i++)
        arr[i] = tuple(0, i);

	for (int j = 0; j < K; j++)
	{
		int pos = b + (M - j - 1) * (N + 2);
		inFile.seekg(pos);
		for (int i = 0; i < N; i++)
		{
			inFile.seekg(pos + arr[i].indx);
			inFile.get(a[i]);
		}

		for (int i = 0; i < N; i++)
			arr[i].value = int(a[i]);
		
        arr = countingSort(arr, N);
	}

     for (int i = 0; i < N; i++)
     {
     	outFile << arr[i].indx + 1;
     	if (i != N - 1)
     		outFile << " ";
     }

    delete[] arr;
	delete[] a;
	std::cout << "Time: " << clock() << std::endl;
	inFile.close();
	outFile.close();
	return 0;
}