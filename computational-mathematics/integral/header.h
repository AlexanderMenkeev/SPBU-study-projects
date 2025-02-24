#pragma once
#include <iostream>
#include <functional>
#include <unordered_map>

struct Matrix
{
	int n;
	std::string name;
	double** mat;
	Matrix(int _n, std::string _name = "", bool is_identityMat = false);
	Matrix();
	~Matrix();
};

class Integral
{
private:
	double eps = 1e-10;
	int n;
	double a;
	double b; 
	double alpha;
	double betta;

	std::function<double(double)> f;

public:
	//Моменты весовой функции, посчитанные аналитически
	std::function<double(double, double)> c0 = [](double a, double b)
	{
		return 1.5 * pow(b - 1.5, 2.0 / 3.0)
			 - 1.5 * pow(a - 1.5, 2.0 / 3.0);
	};
	std::function<double(double, double)> c1 = [](double a, double b)
	{
		return 0.6 * pow(b - 1.5, 5.0 / 3.0) + 9.0 / 4.0 * pow(b - 1.5, 2.0 / 3.0) -
			0.6 * pow(a - 1.5, 5.0 / 3.0) - 9.0 / 4.0 * pow(a - 1.5, 2.0 / 3.0);
	};
	std::function<double(double, double)> c2 = [](double a, double b)
	{
		return 3.0 / 8.0 * pow(b - 1.5, 8.0 / 3.0) + 9.0 / 5.0 * pow(b - 1.5, 5.0 / 3.0) + 27.0 / 8.0 * pow(b - 1.5, 2.0 / 3.0)
			- 3.0 / 8.0 * pow(a - 1.5, 8.0 / 3.0) - 9.0 / 5.0 * pow(a - 1.5, 5.0 / 3.0) - 27.0 / 8.0 * pow(a - 1.5, 2.0 / 3.0);
	};
	std::function<double(double, double)>* c = new std::function<double(double, double)>[n];

	std::unordered_map<std::string, Matrix*> matrixes_map;
	double* forward_substitution(Matrix* _L, double* _b);
	double* backward_substitution(Matrix* _U, double* _b);
	void add_new_matrix(std::string _name, bool is_identityMat = false);
	void pivotify(Matrix* _A);
	void copy(Matrix* _A, Matrix* _B);
	double* multiplication(Matrix* _A, double* _b);
	Matrix* multiplication(Matrix* _A, Matrix* _B);
	void LU_decomposition(Matrix* _L);
	double* x;
	Integral(std::function<double(double)> _f, double _a, double _b, double _alpha, double _betta, int _n);
	double midpoint(double a, double b, int n);
	
	double IKF(double x);
	double p(double x);

	double* LU_solve(Matrix* A, double* _b);
	double findIntegral();
	void printMatrix(Matrix* _matrix); 
	
};


double* createAndFill_vector(int _n, double value);
void print_vector(double* vector, std::string name, int n);