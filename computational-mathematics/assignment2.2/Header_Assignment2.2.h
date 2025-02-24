#pragma once
#include <iostream>
#include <ctime>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <ctime>
struct Matrix
{
	int n, m;
	std::string name;
	double** mat;
	Matrix(int _n, int _m, std::string _name = "", bool is_identityMat = false);
	Matrix();
	~Matrix();
};

//functions
void printMatrix(Matrix* _matrix);
void copy(Matrix* _A, Matrix* _B);
Matrix* multiplication(Matrix* _A, Matrix* _B);
void pivotify(Matrix* _matrix);
void LU_decomposition(Matrix* _L, Matrix* _U, Matrix* _A);

bool is_equal(Matrix* _A, Matrix* _B, double eps);
void fillMatrixRandomly(Matrix* _matrix, int max_value);
void fillMatrix(Matrix* _matrix);
double* createAndFill_b(int _n);
double* createAndFill_b_rand(int _n, int max_value);