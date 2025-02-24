#include <iostream>
#include <ctime>

using namespace std;

void split(int* a, int* ID, int first, int last);
void merge(int* a, int* ID, int first, int middle, int last);

void split(int* a, int* ID, int first, int last)
{
	if (first < last)
	{
		int middle = first + (last - first) / 2;
		split(a, ID, first, middle);
		split(a, ID, middle + 1, last);
		merge(a, ID, first, middle, last);
	}
}

void merge(int* a, int* ID, int first, int middle, int last)
{
	int* tmp = new int[last - first + 1];
	int start1 = first, end1 = middle,
		start2 = middle + 1, end2 = last;
	int i = 0;
	while (start1 <= end1 && start2 <= end2)
	{
		if (a[start1] < a[start2])
		{
			tmp[i] = a[start1];
			//swap(ID[i++], ID[start1++]);
		}
		else
		{
			tmp[i] = a[start2];
			//swap(ID[i++], ID[start2++]);
		}
	}
	while (start1 <= end1)
	
		tmp[i] = a[start1];
	
	while (start2 <= end2)
	
		tmp[i] = a[start2];
	
	i = 0; 
	while (first <= last) a[first++] = tmp[i++];
	delete[] tmp;
}


int partition(int* arr, int* ID, int l, int h)
{
	int x = arr[h];
	int i = (l - 1);

	for (int j = l; j <= h - 1; j++) {
		if (arr[j] <= x) {
			i++;
			swap(arr[i], arr[j]);
			swap(ID[i], ID[j]);
		}
	}
	swap(arr[i + 1], arr[h]);
	swap(ID[i+1], ID[h]);
	return (i + 1);
}

/* A[] --> Array to be sorted,
l --> Starting index,
h --> Ending index */
void quickSortIterative(int* arr, int* ID, int l, int h)
{
	// Create an auxiliary stack
	int* stack = new int[h - l + 1];

	// initialize top of stack
	int top = -1;

	// push initial values of l and h to stack
	stack[++top] = l;
	stack[++top] = h;

	// Keep popping from stack while is not empty
	while (top >= 0) {
		// Pop h and l
		h = stack[top--];
		l = stack[top--];

		// Set pivot element at its correct position
		// in sorted array
		int p = partition(arr, ID, l, h);

		// If there are elements on left side of pivot,
		// then push left side to stack
		if (p - 1 > l) {
			stack[++top] = l;
			stack[++top] = p - 1;
		}

		// If there are elements on right side of pivot,
		// then push right side to stack
		if (p + 1 < h) {
			stack[++top] = p + 1;
			stack[++top] = h;
		}
	}
}


int main()
{
	int n = 5;
	srand(int(time(0)));
	int* a = new int[n];
	int* ID = new int[n];
	for (int i = 0; i < n; i++)
		a[i] = rand() % 100;
	for (int i = 0; i < n; i++)
		ID[i] = i;

	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
	quickSortIterative(a, ID, 0, n - 1);
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
	for (int i = 0; i < n; i++)
		cout << ID[i] << " ";
	return 0;
}