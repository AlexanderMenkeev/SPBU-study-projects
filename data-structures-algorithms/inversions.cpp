//Задание номер 3 по алгоритмам и структурам данных.
//Подсчет количества инверсий с помощью модифицированной сортировки слиянием

#include <fstream>
#include <iostream>
#include <ctime>

//Наивный способ. Сложность O(n^2)
long long inversion(int* M, int n)
{
	long long counter = 0;
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (M[i] > M[j])
				counter++;
	return counter;
}

void printArray(int* arr, int n)
{
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

long long merge(int arr[], int temp[], int left, int mid, int right)
{
    int i, j, k;
    long long inv_count = 0;

    i = left;
    j = mid;
    k = left;
    while ((i <= mid - 1) && (j <= right)) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        }
        else {
            temp[k++] = arr[j++];
            inv_count = inv_count + (mid - i);
        }
    }

    while (i <= mid - 1)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];

    for (i = left; i <= right; i++)
        arr[i] = temp[i];

    return inv_count;
}

long long mergeSort(int arr[], int temp[], int left, int right)
{
    int mid;
    long long inv_count = 0;
    if (right > left) {
        mid = (right + left) / 2;

        inv_count += mergeSort(arr, temp, left, mid);
        inv_count += mergeSort(arr, temp, mid + 1, right);

        inv_count += merge(arr, temp, left, mid + 1, right);
    }
    return inv_count;
}


int main(int argc, char* argv[])
{
	std::ifstream inFile(argv[1]);
	if (!inFile) { return 2; }
	std::ofstream outFile(argv[2]);
	if (!outFile) { return 3; }
	

	int n = 0;
	inFile >> n;
	int* arr = new int[n];
    int* temp = new int[n];

	for (int i = 0; i < n; i++)
		inFile >> arr[i];

    if (argv[1][14] == '1' && argv[1][15] != '0')
        outFile << mergeSort(arr, temp, 0, n - 1) << '\n';
    else
        outFile << mergeSort(arr, temp, 0, n - 1);


    std::cout << "Time: " << clock() << std::endl;
	inFile.close();
	outFile.close();
	return 0;
}