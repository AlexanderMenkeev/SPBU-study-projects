#pragma once
#include <iostream>
#include <ctime>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <string>

//Матрицы имеют размерность [n][n]
struct Matrix
{
	int n;
	std::string name;
	double** mat;
	Matrix(int _n, std::string _name = "", bool is_identityMat = false);
	Matrix();
	~Matrix();
};


class SLAE
{
private:
	double eps = 1e-9;
	int n;

	double* forward_substitution(Matrix* _L, double* _b);
	double* backward_substitution(Matrix* _U, double* _b);
	void pivotify(Matrix* _A);

	bool is_diagonally_dominant(Matrix* _matrix);
	void extract_column(Matrix* _matrix, double* x, int k);
	void compute_minor(Matrix* _A, Matrix* _matrix, int d);
	double norm(double* _vector);
	double norm(Matrix* _mat);
	int rank(double* vector);
	int rank_Ab(double* b);
	
public:
	std::unordered_map<std::string, Matrix*> matrixes_map;
	SLAE(int _n, double _eps);

	bool is_LU_exist(Matrix* _A);
	void LU_decomposition(Matrix* _A);
	void QR_decomposition(Matrix* _A);

	double* LU_solve(double* _b);
	double* QR_solve(double* _b);

	void solve_Gauss_Seidel(double* x, double* b);
	void solve_Jacobi(double* current_x, double* b);

	Matrix* inverse_matrix();
	double condition_number(Matrix* _mat, Matrix* _invMat);


	void add_new_matrix(std::string _name, bool is_identityMat = false);
	int rank();
	double calculate_determinant();

	bool is_equal(Matrix* _A, Matrix* _B);
	bool is_equal(double* _a, double value);

	double* multiplication(Matrix* _A, double* _b);
	Matrix* multiplication(Matrix* _A, Matrix* _B);
	double* subtraction(double* a, double* b);
	
	void copy(Matrix* _A, Matrix* _B);
	void copy(double* _a, double* _b);
	
	void fillMatrixRandomly(Matrix* _matrix, int max_value);
	void fillMatrix(Matrix* _matrix, double value);
	void fillMatrix(Matrix* _matrix);
	void printMatrix(Matrix* _matrix);
	void print_all_matrixes();
	void transpose(Matrix* _matrix);
	void check_solution(double* x, double* b);
};


void print_vector(double* vector, std::string name, int n);
double* createAndFill_vector(int _n);
double* createAndFill_vector(int _n, double value);
double* createAndFill_vector_rand(int _n, int max_value);
