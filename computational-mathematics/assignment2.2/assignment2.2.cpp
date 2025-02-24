#include "Header_Assignment2.2.h"

using namespace std;
int main()
{
	cout.setf(ios::left);
	srand(unsigned(time(0)));
	const int n = 3;
	const int m = 5;
	Matrix* A = new Matrix(n, m, "A");
	Matrix* origin_A = new Matrix(n, m, "origin_A");
	Matrix* L = new Matrix(n, m, "L");
	Matrix* U = new Matrix(n, m, "U");
	fillMatrixRandomly(A, 100);
	copy(A, origin_A);
	LU_decomposition(L, U, A);
	
}

