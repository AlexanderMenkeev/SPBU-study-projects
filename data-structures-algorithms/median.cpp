//Задание номер 2 по алгоритмам и структурам данных. 
//Поиск медианы с помощью сортировки слиянием

#include <fstream>
#include <iostream>
#include <ctime>

struct tuple
{
    double value;
    int indx;
    tuple(double value, int indx)
    {
        this->value = value;
        this->indx = indx;
    }
    tuple() { value = 0; indx = 0; }
};

void merge(tuple* arr, int l, int m, int r);

// l is for left index and r is
// right index of the sub-array
// of arr to be sorted
void mergeSort(tuple* arr, int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2 but avoids
        // overflow for large l & h
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Function to merge the two haves arr[l..m]
// and arr[m+1..r] of array arr[]
void merge(tuple* arr, int l, int m, int r)
{
    int k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    tuple* L = new tuple[n1];
    tuple* R = new tuple[n2];

    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays
    // back into arr[l..r]
    int i = 0;
    int j = 0;
    k = l;

    while (i < n1 && j < n2)
    {
        if (L[i].value <= R[j].value)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements
    // of L[], if there are any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements
    // of R[], if there are any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
    delete[] L;
    delete[] R;
}

void printArray(tuple* arr, int n)
{
    for (int i = 0; i < n; i++)
        std::cout << arr[i].value << " ";
	std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	std::ifstream inFile(argv[1]);
	if (!inFile) { return 2; }

	int n;
	inFile >> n;
	tuple* arr = new tuple[n];

    for (int i = 0; i < n; i++)
        arr[i] = tuple(0, i);

	for (int i = 0; i < n; i++)
		inFile >> arr[i].value;
	
    mergeSort(arr, 0, n - 1);
	
	std::cout << arr[0].indx + 1 << " " << arr[n / 2].indx + 1 << " " << arr[n - 1].indx + 1 << std::endl;
	std::cout << "Time: " << clock() << std::endl;
	inFile.close();
	return 0;
}
