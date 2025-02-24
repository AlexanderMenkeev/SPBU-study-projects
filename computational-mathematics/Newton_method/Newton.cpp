#include "Newton_header.h"

Matrix::Matrix(int _n, std::string _name, bool is_identityMat) : n(_n), name(_name)
{
    mat = new double* [n];
    for (int i = 0; i < n; i++)
        mat[i] = new double[n];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mat[i][j] = 0;

    if (is_identityMat)
        for (int i = 0; i < n; i++)
            mat[i][i] = 1;
}
Matrix::Matrix() : n(), name(), mat() {}
Matrix::~Matrix()
{
    for (int i = 0; i < n; i++)
        delete mat[i];
    delete[] mat;
}
void NonlinearSystem::add_new_matrix(std::string _name, bool is_identityMat)
{
    matrixes_map.emplace(_name, new Matrix(n, _name, is_identityMat));
}

NonlinearSystem::NonlinearSystem()
{
	F[0] = F_0; F[1] = F_1; F[2] = F_2; F[3] = F_3; F[4] = F_4; 
	F[5] = F_5;	F[6] = F_6; F[7] = F_7; F[8] = F_8; F[9] = F_9;

	for (int i = 0; i < n; i++)
		J[i] = new std::function<double(double*)>[n];

	J[0][0] = J_00; J[0][1] = J_01; J[0][2] = J_02; J[0][3] = J_03; J[0][4] = J_04; J[0][5] = J_05; J[0][6] = J_06; J[0][7] = J_07; J[0][8] = J_08; J[0][9] = J_09;
	J[1][0] = J_10; J[1][1] = J_11; J[1][2] = J_12; J[1][3] = J_13; J[1][4] = J_14; J[1][5] = J_15; J[1][6] = J_16; J[1][7] = J_17; J[1][8] = J_18; J[1][9] = J_19;
	J[2][0] = J_20; J[2][1] = J_21; J[2][2] = J_22; J[2][3] = J_23; J[2][4] = J_24; J[2][5] = J_25; J[2][6] = J_26; J[2][7] = J_27; J[2][8] = J_28; J[2][9] = J_29;
	J[3][0] = J_30; J[3][1] = J_31; J[3][2] = J_32; J[3][3] = J_33; J[3][4] = J_34; J[3][5] = J_35; J[3][6] = J_36; J[3][7] = J_37; J[3][8] = J_38; J[3][9] = J_39;
	J[4][0] = J_40; J[4][1] = J_41; J[4][2] = J_42; J[4][3] = J_43; J[4][4] = J_44; J[4][5] = J_45; J[4][6] = J_46; J[4][7] = J_47; J[4][8] = J_48; J[4][9] = J_49;
	J[5][0] = J_50; J[5][1] = J_51; J[5][2] = J_52; J[5][3] = J_53; J[5][4] = J_54; J[5][5] = J_55; J[5][6] = J_56; J[5][7] = J_57; J[5][8] = J_58; J[5][9] = J_59;
	J[6][0] = J_60; J[6][1] = J_61; J[6][2] = J_62; J[6][3] = J_63; J[6][4] = J_64; J[6][5] = J_65; J[6][6] = J_66; J[6][7] = J_67; J[6][8] = J_68; J[6][9] = J_69;
	J[7][0] = J_70; J[7][1] = J_71; J[7][2] = J_72; J[7][3] = J_73; J[7][4] = J_74; J[7][5] = J_75; J[7][6] = J_76; J[7][7] = J_77; J[7][8] = J_78; J[7][9] = J_79;
	J[8][0] = J_80; J[8][1] = J_81; J[8][2] = J_82; J[8][3] = J_83; J[8][4] = J_84; J[8][5] = J_85; J[8][6] = J_86; J[8][7] = J_87; J[8][8] = J_88; J[8][9] = J_89;
	J[9][0] = J_90; J[9][1] = J_91; J[9][2] = J_92; J[9][3] = J_93; J[9][4] = J_94; J[9][5] = J_95; J[9][6] = J_96; J[9][7] = J_97; J[9][8] = J_98; J[9][9] = J_99;
}
NonlinearSystem::~NonlinearSystem()
{
   delete[] J;
   delete[] F;
}

double* NonlinearSystem::forward_substitution(Matrix* _L, double* _b)
{
    double* y = createAndFill_vector(n, 0);
    for (int i = 0; i < n; i++)
    {
        double value = _b[i];
        for (int j = 0; j < i; j++) {
            value -= _L->mat[i][j] * y[j];
            arithmetic_operations+=3;
        }

        y[i] = value;
    }
    return y;
}
bool NonlinearSystem::is_equal(Matrix* _A, Matrix* _B)
{
    bool equal = true;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (abs(_A->mat[i][j] - _B->mat[i][j]) > eps)
                equal = false;
    if (equal)
        std::cout << _A->name << " = " << _B->name << std::endl;
    else
        std::cout << _A->name << " != " << _B->name << std::endl;
    return equal;
}
double* NonlinearSystem::backward_substitution(Matrix* _U, double* _b)
{
    double* x = createAndFill_vector(n, 0);
    for (int i = n - 1; i > -1; i--)
    {
        if (abs(_U->mat[i][i]) < eps)
        {
            x[i] = rand() % 10;
            std::cout << "x_" << i << " is free variable." << std::endl;
            continue;
        }
        double value = _b[i];

        for (int j = i + 1; j < n; j++) {
            value -= _U->mat[i][j] * x[j];
            arithmetic_operations+=3;
        }

        value /= _U->mat[i][i];
        x[i] = value;
    }
    return x;
}
void NonlinearSystem::LU_decomposition(Matrix* _A)
{
    //Добавление матриц произойдет, если ключ уникален, то есть только при первом вызове LU_decomposition
    //При последующих вызовах будут использоваться уже созданные матрицы
    add_new_matrix("L");
    add_new_matrix("U");
    Matrix* _L = matrixes_map["L"];
    Matrix* _U = matrixes_map["U"];
    pivotify(_A);
    copy(_A, _U);
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++) {
            _L->mat[j][i] = _U->mat[j][i] / _U->mat[i][i];
            LU_operations+=2;
        }

    for (int k = 1; k < n; k++)
    {
        for (int i = k - 1; i < n; i++)
            for (int j = i; j < n; j++) {
                _L->mat[j][i] = _U->mat[j][i] / _U->mat[i][i];
                LU_operations+=2;
            }

        for (int i = k; i < n; i++)
            for (int j = k - 1; j < n; j++) {
                _U->mat[i][j] = _U->mat[i][j] - _L->mat[i][k - 1] * _U->mat[k - 1][j];
                LU_operations+=3;
            }
    }
}
void NonlinearSystem::pivotify(Matrix* _A)
{
    add_new_matrix("P", true);
    add_new_matrix("Q", true);
    add_new_matrix("E", true);
    Matrix* P = matrixes_map["P"];
    Matrix* Q = matrixes_map["Q"];
    Matrix* E = matrixes_map["E"];
    copy(E, P); copy(E, Q);
    
    for (int i = 0; i < _A->n; i++)
    {
        int pivotRow = i;
        int pivotCol = i;
        for (int j = i; j < n; j++)
            for (int k = i; k < n; k++)
                if (abs(_A->mat[j][k]) > abs(_A->mat[pivotRow][pivotCol]))
                {
                    pivotRow = j;
                    pivotCol = k;
                }

        if (_A->mat[pivotRow][pivotCol] == 0)
        {
            std::cout << "Cannot find pivot element. Determinant of matrix "
                << _A->name << " is equal to zero." << std::endl;
            continue;
        }

        //Если ведущий элемент не диагональный, нужно менять местами строки и/или столбцы 
        if (pivotRow != i)
            for (int j = 0; j < n; j++)
            {
                std::swap(_A->mat[i][j], _A->mat[pivotRow][j]);
                std::swap(P->mat[i][j], P->mat[pivotRow][j]);
            }

        if (pivotCol != i)
            for (int j = 0; j < n; j++)
            {
                std::swap(_A->mat[j][i], _A->mat[j][pivotCol]);
                std::swap(Q->mat[j][i], Q->mat[j][pivotCol]);
            }
    }
}

//copy matrix _A into matrix _B 
void NonlinearSystem::copy(Matrix* _A, Matrix* _B)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            _B->mat[i][j] = _A->mat[i][j];
}
//copy vector _a into vector _b 
void NonlinearSystem::copy(double* _a, double* _b)
{
    for (int i = 0; i < n; i++)
        _b[i] = _a[i];
}
//_A * _b = r
double* NonlinearSystem::multiplication(Matrix* _A, double* _b)
{
    double* r = new double[n];
    for (int i = 0; i < n; i++)
        r[i] = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            r[i] += _A->mat[i][j] * _b[j];
    return r;
}
//_A * _B = R
Matrix* NonlinearSystem::multiplication(Matrix* _A, Matrix* _B)
{
    Matrix* R = new Matrix(n, _A->name + "*" + _B->name);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            R->mat[i][j] = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                R->mat[i][j] += _A->mat[i][k] * _B->mat[k][j];
    return R;
}
double* NonlinearSystem::solve_SLAE(Matrix* _A, double* _b)
{
    LU_decomposition(_A);
    _b = multiplication(matrixes_map["P"], _b);
 
    double* y = forward_substitution(matrixes_map["L"], _b);
    double* x = backward_substitution(matrixes_map["U"], y);
   
    x = multiplication(matrixes_map["Q"], x);
    return x;
}

double* NonlinearSystem::solve_SLAE(double* _b)
{
    _b = multiplication(matrixes_map["P"], _b);

    double* y = forward_substitution(matrixes_map["L"], _b);
    double* x = backward_substitution(matrixes_map["U"], y);

    x = multiplication(matrixes_map["Q"], x);
    return x;
}

void NonlinearSystem::transpose(Matrix* _matrix)
{
    _matrix->name = "transposed_" + _matrix->name;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            std::swap(_matrix->mat[i][j], _matrix->mat[j][i]);
}

bool NonlinearSystem::is_equal(double* _a, double value)
{
    bool equal = true;
    for (int i = 0; i < n; i++)
        if (abs(_a[i] - value) > eps)
            equal = false;
    return equal;
}

double* NonlinearSystem::Newton_method(double* current_x)
{
    Matrix* J; double* f;
    double* dx;
    double* prev_x = createAndFill_vector(n, 0);
    int iter = 0;
    do {
        std::cout << "\n\n";
        std::cout << "iter = " << iter << ":" << std::endl;
        copy(current_x, prev_x);
        J = compute_matrix(prev_x);
        printMatrix(J);

        //f уже имеет противоположный знак. Для решения уравнения J*dx = -f, где dx = current_x - prev_x
        f = compute_vector(prev_x);
        print_vector(f, "-f", n);

        dx = solve_SLAE(J, f);

        print_vector(dx, "dx", n);

        current_x = sum(dx, prev_x);

        iter++;
        print_vector(current_x, "current_x", n);
        print_vector(prev_x, "prev_x", n);

        
    } while (!is_equal(dx, 0));
    std::cout << "Number of operations for LU decomposition: " << LU_operations << std::endl;
    std::cout << "Number of operations for solving SLAEs: " << arithmetic_operations << std::endl;
    std::cout << "Total number of operations: " << arithmetic_operations + LU_operations << std::endl;
    return current_x;
}

double* NonlinearSystem::Newton_method(double* current_x, int k)
{
    Matrix* J; double* f;
    double* dx;


    double* prev_x = createAndFill_vector(n, 0);
    int iter = 0;
    do {
        std::cout << "\n\n";
        std::cout << "iter = " << iter << ":" << std::endl;

        copy(current_x, prev_x);
        f = compute_vector(prev_x);
        print_vector(f, "-f", n);

        if (iter < k) {
            J = compute_matrix(prev_x);
            dx = solve_SLAE(J, f);
            printMatrix(J);
        }
        else
            dx = solve_SLAE(f);

        print_vector(dx, "dx", n);

        current_x = sum(dx, prev_x);

        print_vector(current_x, "current_x", n);
        print_vector(prev_x, "prev_x", n);
        iter++;

    } while (!is_equal(dx, 0));
    std::cout << "Number of operations for LU decomposition: " << LU_operations << std::endl;
    std::cout << "Number of operations for solving SLAEs: " << arithmetic_operations << std::endl;
    std::cout << "Total number of operations: " << arithmetic_operations + LU_operations << std::endl;
    return current_x;
}

double* NonlinearSystem::modified_Newton_method(double* current_x)
{
    Matrix* J; double* f;
    double* dx;
    
    J = compute_matrix(current_x);
    LU_decomposition(J);

    double* prev_x = createAndFill_vector(n, 0);
    int iter = 0;
    do {
        std::cout << "\n\n";
        std::cout << "iter = " << iter << ":" << std::endl;
        copy(current_x, prev_x);
        
        //f уже имеет противоположный знак. Для решения уравнения J*dx = -f, где dx = current_x - prev_x
        f = compute_vector(prev_x);
        print_vector(f, "-f", n);

        dx = solve_SLAE(f);

        print_vector(dx, "dx", n);

        current_x = sum(dx, prev_x);

        iter++;
        print_vector(current_x, "current_x", n);
        print_vector(prev_x, "prev_x", n);


    } while (!is_equal(dx, 0));
    std::cout << "Number of operations for LU decomposition: " << LU_operations << std::endl;
    std::cout << "Number of operations for solving SLAEs: " << arithmetic_operations << std::endl;
    std::cout << "Total number of operations: " << arithmetic_operations + LU_operations << std::endl;
    double* res = current_x;
    return res;
}

double* NonlinearSystem::hybrid_Newton_method(double* current_x, int k)
{
    Matrix* J; double* f;
    double* dx;

  
    double* prev_x = createAndFill_vector(n, 0);
    int iter = 0;
    do {
        std::cout << "\n\n";
        std::cout << "iter = " << iter << ":" << std::endl;
        copy(current_x, prev_x);

        f = compute_vector(prev_x);
        print_vector(f, "-f", n);

        if (iter % k == 0) {
            J = compute_matrix(prev_x);
            dx = solve_SLAE(J, f);
            printMatrix(J);
        }
        else
            dx = solve_SLAE(f);
        
        print_vector(dx, "dx", n);

        current_x = sum(dx, prev_x);

        print_vector(current_x, "current_x", n);
        print_vector(prev_x, "prev_x", n);
        iter++;

    } while (!is_equal(dx, 0));
    std::cout << "Number of operations for LU decomposition: " << LU_operations << std::endl;
    std::cout << "Number of operations for solving SLAEs: " << arithmetic_operations << std::endl;
    std::cout << "Total number of operations: " << arithmetic_operations + LU_operations << std::endl;
   
    return current_x;
}
void NonlinearSystem::printMatrix(Matrix* _matrix)
{
    std::cout << "Matrix " << _matrix->name << ":" << std::endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            //std::cout << std::setw(8) << _A->matrix[i][j];
            printf("%7.3f ", _matrix->mat[i][j]);

        std::cout << std::endl;
    }
    std::cout << std::endl;
};

//a - b = r
double* NonlinearSystem::subtraction(double* a, double* b)
{
    double* r = new double[n];

    for (int i = 0; i < n; i++)
        r[i] = a[i] - b[i];
    return r;
}

//a + b = r
double* NonlinearSystem::sum(double* a, double* b)
{
    double* r = new double[n];

    for (int i = 0; i < n; i++)
        r[i] = a[i] + b[i];
    return r;
}

Matrix* NonlinearSystem::compute_matrix(double* x)
{
    Matrix* J = new Matrix(n, "J");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            J->mat[i][j] = this->J[i][j](x);
    return J;
}

//возвращает -f
double* NonlinearSystem::compute_vector(double* x)
{
    double* r = new double[n];
    for (int i = 0; i < n; i++)
        //сразу меняем знак
        r[i] = -F[i](x);
    return r;
}

Matrix* NonlinearSystem::compute_matrix1(double* x)
{
    Matrix* J = new Matrix(n, "J");
    J->mat[0][0] = j_00(x);
    J->mat[0][1] = j_01(x);
    J->mat[0][2] = j_02(x);

    J->mat[1][0] = j_10(x);
    J->mat[1][1] = j_11(x);
    J->mat[1][2] = j_12(x);

    J->mat[2][0] = j_20(x);
    J->mat[2][1] = j_21(x);
    J->mat[2][2] = j_22(x);
    return J;
}

double* NonlinearSystem::compute_vector1(double* x)
{
    double* r = new double[n];
    r[0] = -f_0(x);
    r[1] = -f_1(x);
    r[2] = -f_2(x);
    return r;
}

//just functions, not methods
void print_vector(double* vector, std::string name, int n)
{
    std::cout << name << ": ";
    for (int i = 0; i < n; i++)
        printf("%7.3f ", vector[i]);
    std::cout << std::endl;
}
double* createAndFill_vector(int _n)
{
    double* b = new double[_n];
    std::cout << "Enter " << _n << " elements of the vector b: ";
    for (int i = 0; i < _n; i++)
        std::cin >> b[i];
    return b;
}
double* createAndFill_vector(int _n, double value)
{
    double* b = new double[_n];
    for (int i = 0; i < _n; i++)
        b[i] = value;
    return b;
}
double* createAndFill_vector_rand(int _n, int max_value)
{
    double* b = new double[_n];
    for (int i = 0; i < _n; i++)
        b[i] = rand() % max_value;
    return b;
}