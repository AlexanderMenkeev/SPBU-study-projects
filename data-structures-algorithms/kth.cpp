//Задание номер 4 по алгоритмам и структурам данных.
//K-ая порядковая статистика

#include <fstream>
#include <iostream>
#include <ctime>

template <typename Type>
void printArray(Type* M, int n)
{
    for (int i = 0; i < n; i++)
        std::cout << M[i] << " ";
    std::cout << std::endl;
}

void quickSort(int* M, int n)
{
    int i = 0;
    int j = n - 1;
    int pivot = M[n / 2];

    do
    {
        while (M[i] < pivot) { i++; }
        while (M[j] > pivot) { j--; }

        if (i <= j)
        {
            std::swap(M[i], M[j]);
            i++;
            j--;
        }
    } while (i <= j);

    if (j > 0)
        quickSort(M, j + 1);
    if (i < n)
        quickSort(&M[i], n - i);
}

int getXi(int A, int B, int C, int x1, int x2)
{
    return A * x1 + B * x2 + C;
}

int main(int argc, char* argv[])
{
    std::ifstream inFile(argv[1]);
    if (!inFile) return 2;
    std::ofstream outFile(argv[2]);
    if (!outFile) return 3;
    
    int n, k1, k2;
    inFile >> n >> k1 >> k2;
    int* M = new int[n];

    int A, B, C;
    inFile >> A >> B >> C;
    if (n > 2) 
        inFile >> M[0] >> M[1];

    for (int i = 2; i < n; i++)
        M[i] = getXi(A, B, C, M[i - 2], M[i - 1]);

    quickSort(M, n);

    for (int i = k1 - 1; i < k2; i++)
    {
        outFile << M[i];
        if (i < k2 - 1)
            outFile << " ";
    }

    std::cout << "Time: " << clock() << std::endl;
    inFile.close();
    outFile.close();
    return 0;
}