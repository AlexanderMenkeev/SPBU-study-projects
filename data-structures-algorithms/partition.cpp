//Задание номер 0 по алгоритмам и структурам данных.
//Подсчет количества разбиений натурального числа с помощью таблицы

#include <iostream>
#include <ctime>

using namespace std;
long long partition(int n, int k)
{
	n++;
	long long** partition = new long long* [n];
	for (int i = 0; i < n; i++)
		partition[i] = new long long[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			partition[i][j] = 0;

	if (n > 1)
	{
		for (int ind = 0; ind < n; ind++)
		{
			partition[1][ind] = 1;
			partition[ind][0] = 1;
			if (ind != 0)
				partition[ind][1] = 1;
		}
	}

	for (int i = 2; i < n; i++)
		for (int j = 2; j < n; j++)
		{
			if (i > j)
				partition[i][j] = partition[i - 1][j];
			else
				partition[i][j] = partition[i - 1][j] + partition[i][j - i];
		}

	return partition[k][n - 1] - partition[k - 1][n - 1];
}

int main()
{
	int n, k;
	cin >> n >> k;
	cout << partition(n, k) << endl;
	cout << "Time: " << clock() << endl;
}
