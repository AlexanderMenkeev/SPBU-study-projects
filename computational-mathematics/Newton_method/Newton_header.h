#pragma once
#include <iostream>
#include <functional>
#include <unordered_map>
#include <string>

struct Matrix
{
	int n;
	std::string name;
	double** mat;
	Matrix(int _n, std::string _name = "", bool is_identityMat = false);
	Matrix();
	~Matrix();
};

class NonlinearSystem
{
private:
	static const int n = 10;
	int LU_operations = 0;
	int arithmetic_operations = 0;
	double eps = 1e-12;
	std::unordered_map<std::string, Matrix*> matrixes_map;
	std::function<double(double*)> F_0 = [](double* x)
	{ return cos(x[1] * x[0]) - exp(-(3.0 * x[2])) + x[3] * x[4] * x[4] - x[5] - sinh((2.0 * x[7])) * x[8] + (2.0 * x[9]) + 2.000433974165385440; };
	std::function<double(double*)> F_1 = [](double* x)
	{ return sin(x[1] * x[0]) + x[2] * x[8] * x[6] - exp(-x[9] + x[5]) + 3.0 * x[4] * x[4] - x[5] * (x[7] + 1.0) + 10.886272036407019994; };
	std::function<double(double*)> F_2 = [](double* x)
	{ return x[0] - x[1] + x[2] - x[3] + x[4] - x[5] + x[6] - x[7] + x[8] - x[9] - 3.1361904761904761904; };
	std::function<double(double*)> F_3 = [](double* x)
	{ return 2.0 * cos(-x[8] + x[3]) + x[4] / (x[2] + x[0]) - sin(x[1] * x[1]) + pow(cos(x[6] * x[9]), 2.0) - x[7] - 0.1707472705022304757; };
	std::function<double(double*)> F_4 = [](double* x)
	{ return sin(x[4]) + 2.0 * x[7] * (x[2] + x[0]) - exp(-x[6] * (-x[9] + x[5])) + 2.0 * cos(x[1]) - 1.0 / (-x[8] + x[3]) - 0.3685896273101277862; };
	std::function<double(double*)> F_5 = [](double* x)
	{ return exp(x[0] - x[3] - x[8]) + x[4] * x[4] / x[7] + cos(3.0 * x[9] * x[1]) / 2.0 - x[5] * x[2] + 2.0491086016771875115; };
	std::function<double(double*)> F_6 = [](double* x)
	{ return pow(x[1], 3.0) * x[6] - sin(x[9] / x[4] + x[7]) + (x[0] - x[5]) * cos(x[3]) + x[2] - 0.7380430076202798014; };
	std::function<double(double*)> F_7 = [](double* x)
	{ return x[4] * pow(x[0] - 2.0 * x[5], 2.0) - 2.0 * sin(-x[8] + x[2]) + 1.5 * x[3] - exp(x[1] * x[6] + x[9]) + 3.5668321989693809040; };
	std::function<double(double*)> F_8 = [](double* x)
	{ return 7.0 / x[5] + exp(x[4] + x[3]) - 2.0 * x[1] * x[7] * x[9] * x[6] + 3.0 * x[8] - 3.0 * x[0] - 8.4394734508383257499; };
	std::function<double(double*)> F_9 = [](double* x)
	{ return x[9] * x[0] + x[8] * x[1] - (x[7] * x[2]) + sin(x[3] + x[4] + x[5]) * x[6]- 0.78238095238095238096; };
	std::function<double(double*)>* F = new std::function<double(double*)>[n];

	std::function<double(double*)> J_00 = [](double* x) { return -x[1] * sin(x[1] * x[0]); };
	std::function<double(double*)> J_01 = [](double* x) { return -x[0] * sin(x[1] * x[0]); };
	std::function<double(double*)> J_02 = [](double* x) { return 3.0 * exp(-(3.0 * x[2])); };
	std::function<double(double*)> J_03 = [](double* x) { return x[4] * x[4]; };
	std::function<double(double*)> J_04 = [](double* x) { return 2.0 * x[3] * x[4]; };
	std::function<double(double*)> J_05 = [](double* x) { return -1.0; };
	std::function<double(double*)> J_06 = [](double* x) { return  0.0; };
	std::function<double(double*)> J_07 = [](double* x) { return -2.0 * cosh(2.0 * x[7]) * x[8]; };
	std::function<double(double*)> J_08 = [](double* x) { return  -sinh(2.0 * x[7]); };
	std::function<double(double*)> J_09 = [](double* x) { return  2.0; };

	std::function<double(double*)> J_10 = [](double* x) { return  x[1] * cos(x[1] * x[0]); };
	std::function<double(double*)> J_11 = [](double* x) { return x[0] * cos(x[1] * x[0]); };
	std::function<double(double*)> J_12 = [](double* x) { return x[8] * x[6]; };
	std::function<double(double*)> J_13 = [](double* x) { return 0.0; };
	std::function<double(double*)> J_14 = [](double* x) { return 6.0 * x[4]; };
	std::function<double(double*)> J_15 = [](double* x) { return -exp(-x[9] + x[5]) - x[7] - 1.0; };
	std::function<double(double*)> J_16 = [](double* x) { return x[2] * x[8]; };
	std::function<double(double*)> J_17 = [](double* x) { return  -x[5]; };
	std::function<double(double*)> J_18 = [](double* x) { return x[2] * x[6]; };
	std::function<double(double*)> J_19 = [](double* x) { return  exp(-x[9] + x[5]); };

	std::function<double(double*)> J_20 = [](double* x) { return  1.0; };
	std::function<double(double*)> J_21 = [](double* x) { return  -1.0; };
	std::function<double(double*)> J_22 = [](double* x) { return  1.0; };
	std::function<double(double*)> J_23 = [](double* x) { return -1.0; };
	std::function<double(double*)> J_24 = [](double* x) { return  1.0; };
	std::function<double(double*)> J_25 = [](double* x) { return -1.0; };
	std::function<double(double*)> J_26 = [](double* x) { return  1.0; };
	std::function<double(double*)> J_27 = [](double* x) { return -1.0; };
	std::function<double(double*)> J_28 = [](double* x) { return  1.0; };
	std::function<double(double*)> J_29 = [](double* x) { return -1.0; };

	std::function<double(double*)> J_30 = [](double* x) { return -x[4] * pow(x[2] + x[0], -2.0); };
	std::function<double(double*)> J_31 = [](double* x) { return  -2.0 * x[1] * cos(x[1] * x[1]); };
	std::function<double(double*)> J_32 = [](double* x) { return  -x[4] * pow(x[2] + x[0], -2.0); };
	std::function<double(double*)> J_33 = [](double* x) { return  -2.0 * sin(-x[8] + x[3]); };
	std::function<double(double*)> J_34 = [](double* x) { return  1.0 / (x[2] + x[0]); };
	std::function<double(double*)> J_35 = [](double* x) { return  0.0; };
	std::function<double(double*)> J_36 = [](double* x) { return  -2.0 * cos(x[6] * x[9]) * x[9] * sin(x[6] * x[9]); };
	std::function<double(double*)> J_37 = [](double* x) { return -1.0; };
	std::function<double(double*)> J_38 = [](double* x) { return  2.0 * sin(-x[8] + x[3]); };
	std::function<double(double*)> J_39 = [](double* x) { return -2.0 * cos(x[6] * x[9]) * x[6] * sin(x[6] * x[9]); };
	
	std::function<double(double*)> J_40 = [](double* x) { return  2 * x[7]; };
	std::function<double(double*)> J_41 = [](double* x) { return -2.0 * sin(x[1]); };
	std::function<double(double*)> J_42 = [](double* x) { return  2 * x[7]; };
	std::function<double(double*)> J_43 = [](double* x) { return  pow(-x[8] + x[3], -2.0); };
	std::function<double(double*)> J_44 = [](double* x) { return  cos(x[4]); };
	std::function<double(double*)> J_45 = [](double* x) { return  x[6] * exp(-x[6] * (-x[9] + x[5])); };
	std::function<double(double*)> J_46 = [](double* x) { return  -(x[9] - x[5]) * exp(-x[6] * (-x[9] + x[5])); };
	std::function<double(double*)> J_47 = [](double* x) { return  (2 * x[2]) + 2.0 * x[0]; };
	std::function<double(double*)> J_48 = [](double* x) { return  -pow(-x[8] + x[3], -2.0); };
	std::function<double(double*)> J_49 = [](double* x) { return -x[6] * exp(-x[6] * (-x[9] + x[5])); };
	std::function<double(double*)> J_50 = [](double* x) { return  exp(x[0] - x[3] - x[8]); };

	std::function<double(double*)> J_51 = [](double* x) { return -3.0 / 2.0 * x[9] * sin(3.0 * x[9] * x[1]); };
	std::function<double(double*)> J_52 = [](double* x) { return  -x[5]; };
	std::function<double(double*)> J_53 = [](double* x) { return -exp(x[0] - x[3] - x[8]); };
	std::function<double(double*)> J_54 = [](double* x) { return  2 * x[4] / x[7]; };
	std::function<double(double*)> J_55 = [](double* x) { return  -x[2]; };
	std::function<double(double*)> J_56 = [](double* x) { return  0.0; };
	std::function<double(double*)> J_57 = [](double* x) { return  -x[4] * x[4] * pow(x[7], (-2)); };
	std::function<double(double*)> J_58 = [](double* x) { return  -exp(x[0] - x[3] - x[8]); };
	std::function<double(double*)> J_59 = [](double* x) { return  -3.0 / 2.0 * x[1] * sin(3.0 * x[9] * x[1]); };
	std::function<double(double*)> J_60 = [](double* x) { return  cos(x[3]); };

	std::function<double(double*)> J_61 = [](double* x) { return 3.0 * x[1] * x[1] * x[6]; };
	std::function<double(double*)> J_62 = [](double* x) { return  1.0; };
	std::function<double(double*)> J_63 = [](double* x) { return -(x[0] - x[5]) * sin(x[3]); };
	std::function<double(double*)> J_64 = [](double* x) { return  x[9] * pow(x[4], (-2)) * cos(x[9] / x[4] + x[7]); };
	std::function<double(double*)> J_65 = [](double* x) { return -cos(x[3]); };
	std::function<double(double*)> J_66 = [](double* x) { return  pow(x[1], 3.0); };
	std::function<double(double*)> J_67 = [](double* x) { return  -cos(x[9] / x[4] + x[7]); };
	std::function<double(double*)> J_68 = [](double* x) { return  0.0; };
	std::function<double(double*)> J_69 = [](double* x) { return  -1.0 / x[4] * cos(x[9] / x[4] + x[7]); };
	std::function<double(double*)> J_70 = [](double* x) { return  2.0 * x[4] * (x[0] - 2.0 * x[5]); };

	std::function<double(double*)> J_71 = [](double* x) { return  -x[6] * exp(x[1] * x[6] + x[9]); };
	std::function<double(double*)> J_72 = [](double* x) { return  -2.0 * cos(-x[8] + x[2]); };
	std::function<double(double*)> J_73 = [](double* x) { return  1.5; };
	std::function<double(double*)> J_74 = [](double* x) { return  pow(x[0] - 2.0 * x[5], 2.0); };
	std::function<double(double*)> J_75 = [](double* x) { return -4.0 * x[4] * (x[0] - 2.0 * x[5]); };
	std::function<double(double*)> J_76 = [](double* x) { return  -x[1] * exp(x[1] * x[6] + x[9]); };
	std::function<double(double*)> J_77 = [](double* x) { return  0.0; };
	std::function<double(double*)> J_78 = [](double* x) { return  2.0 * cos(-x[8] + x[2]); };
	std::function<double(double*)> J_79 = [](double* x) { return  -exp(x[1] * x[6] + x[9]); };
	std::function<double(double*)> J_80 = [](double* x) { return  -3.0; };

	std::function<double(double*)> J_81 = [](double* x) { return  -2.0 * x[7] * x[9] * x[6]; };
	std::function<double(double*)> J_82 = [](double* x) { return  0.0; };
	std::function<double(double*)> J_83 = [](double* x) { return  exp((x[4] + x[3])); };
	std::function<double(double*)> J_84 = [](double* x) { return  exp((x[4] + x[3])); };
	std::function<double(double*)> J_85 = [](double* x) { return -7.0 * pow(x[5], -2.0); };
	std::function<double(double*)> J_86 = [](double* x) { return  -2.0 * x[1] * x[7] * x[9]; };
	std::function<double(double*)> J_87 = [](double* x) { return -2.0 * x[1] * x[9] * x[6]; };
	std::function<double(double*)> J_88 = [](double* x) { return  3.0; };
	std::function<double(double*)> J_89 = [](double* x) { return  -2.0 * x[1] * x[7] * x[6]; };
	std::function<double(double*)> J_90 = [](double* x) { return  x[9]; };

	std::function<double(double*)> J_91 = [](double* x) { return  x[8]; };
	std::function<double(double*)> J_92 = [](double* x) { return  -x[7]; };
	std::function<double(double*)> J_93 = [](double* x) { return  cos(x[3] + x[4] + x[5]) * x[6]; };
	std::function<double(double*)> J_94 = [](double* x) { return  cos(x[3] + x[4] + x[5]) * x[6]; };
	std::function<double(double*)> J_95 = [](double* x) { return  cos(x[3] + x[4] + x[5]) * x[6]; };
	std::function<double(double*)> J_96 = [](double* x) { return  sin(x[3] + x[4] + x[5]); };
	std::function<double(double*)> J_97 = [](double* x) { return  -x[2]; };
	std::function<double(double*)> J_98 = [](double* x) { return  x[1]; };
	std::function<double(double*)> J_99 = [](double* x) { return  x[0]; };

	std::function<double(double*)>** J = new std::function<double(double*)>* [n];

	//Более простой пример, который можно проверить вручную
	std::function<double(double*)> f_0 = [](double* x) { return  x[0]*x[0] + x[1]*x[1] + x[2]*x[2] - 1; };
	std::function<double(double*)> f_1 = [](double* x) { return  2*x[0]*x[0] + x[1]*x[1] - 4*x[2]; };
	std::function<double(double*)> f_2 = [](double* x) { return  3*x[0]*x[0] - 4*x[1] + x[2]*x[2]; };

	std::function<double(double*)> j_00 = [](double* x) { return  2*x[0]; };
	std::function<double(double*)> j_01 = [](double* x) { return  2*x[1]; };
	std::function<double(double*)> j_02 = [](double* x) { return  2*x[2]; };

	std::function<double(double*)> j_10 = [](double* x) { return  4 * x[0]; };
	std::function<double(double*)> j_11 = [](double* x) { return  2 * x[1]; };
	std::function<double(double*)> j_12 = [](double* x) { return  -4; };

	std::function<double(double*)> j_20 = [](double* x) { return  6 * x[0]; };
	std::function<double(double*)> j_21 = [](double* x) { return  -4; };
	std::function<double(double*)> j_22 = [](double* x) { return  2 * x[2]; };

	//private methods
	bool is_equal(Matrix* _A, Matrix* _B);
	bool is_equal(double* _a, double value);
	void printMatrix(Matrix* _matrix);
	Matrix* multiplication(Matrix* _A, Matrix* _B);
	double* multiplication(Matrix* _A, double* _b);
	void copy(Matrix* _A, Matrix* _B);
	void copy(double* _a, double* _b);
	double* forward_substitution(Matrix* _L, double* _b);
	double* backward_substitution(Matrix* _U, double* _b);
	void add_new_matrix(std::string _name, bool is_identityMat = false);
	void LU_decomposition(Matrix* _A);
	void pivotify(Matrix* _A);
	double* subtraction(double* a, double* b);
	double* sum(double* a, double* b);
	Matrix* compute_matrix(double* x);
	double* compute_vector(double* x);
	
	double* solve_SLAE(Matrix* _A, double* _b);
	double* solve_SLAE(double* _b);
	void transpose(Matrix* _matrix);
	Matrix* compute_matrix1(double* x);
	double* compute_vector1(double* x);

public:
	int get_n(){ return n; }
	NonlinearSystem();
	~NonlinearSystem();
	
	double* Newton_method(double* current_x);
	double* Newton_method(double* current_x, int k);
	double* modified_Newton_method(double* current_x);
	double* hybrid_Newton_method(double* current_x, int k);

	

};


void print_vector(double* vector, std::string name, int n);
double* createAndFill_vector(int _n);
double* createAndFill_vector(int _n, double value);
double* createAndFill_vector_rand(int _n, int max_value);