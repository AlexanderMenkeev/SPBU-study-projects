#include "header.h"

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

Integral::Integral(std::function<double(double)> _f, double _a, double _b, double _alpha, double _betta, int _n):
    f(_f), a(_a), b(_b), alpha(_alpha), betta(_betta), n(_n) {

    c[0] = c0;
    c[1] = c1;
    c[2] = c2;
}

double* Integral::forward_substitution(Matrix* _L, double* _b)
{
    double* y = new double[n];
    for (int i = 0; i < n; i++)
    {
        double value = _b[i];
        for (int j = 0; j < i; j++)
            value -= _L->mat[i][j] * y[j];

        y[i] = value;
    }
    return y;
}
double* Integral::backward_substitution(Matrix* _U, double* _b)
{
    double eps = 1e-10;
    double* x = new double[n];
    for (int i = n - 1; i > -1; i--)
    {
        if (abs(_U->mat[i][i]) < eps)
        {
            x[i] = rand() % 10;
            std::cout << "x_" << i << " is free variable." << std::endl;
            continue;
        }
        double value = _b[i];

        for (int j = i + 1; j < n; j++)
            value -= _U->mat[i][j] * x[j];

        value /= _U->mat[i][i];
        x[i] = value;
    }
    return x;
}
void Integral::add_new_matrix(std::string _name, bool is_identityMat)
{
    matrixes_map.emplace(_name, new Matrix(n, _name, is_identityMat));
}
void Integral::pivotify(Matrix* _A)
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

void Integral::copy(Matrix* _A, Matrix* _B)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            _B->mat[i][j] = _A->mat[i][j];
}

void Integral::LU_decomposition(Matrix* _A)
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
            
        }

    for (int k = 1; k < n; k++)
    {
        for (int i = k - 1; i < n; i++)
            for (int j = i; j < n; j++) {
                _L->mat[j][i] = _U->mat[j][i] / _U->mat[i][i];
                
            }

        for (int i = k; i < n; i++)
            for (int j = k - 1; j < n; j++) {
                _U->mat[i][j] = _U->mat[i][j] - _L->mat[i][k - 1] * _U->mat[k - 1][j];
                
            }
    }
}

double* Integral::multiplication(Matrix* _A, double* _b)
{
    double* r = new double[n];
    for (int i = 0; i < n; i++)
        r[i] = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            r[i] += _A->mat[i][j] * _b[j];
    return r;
}
Matrix* Integral::multiplication(Matrix* _A, Matrix* _B)
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


double* Integral::LU_solve(Matrix* _A, double* _b)
{
    LU_decomposition(_A);
    _b = multiplication(matrixes_map["P"], _b);

    double* y = forward_substitution(matrixes_map["L"], _b);
    double* x = backward_substitution(matrixes_map["U"], y);

    x = multiplication(matrixes_map["Q"], x);
    return x;
}

double Integral::midpoint(double a, double b, int n)
{
	double h = (b - a) / n;
    double result = 0;
    for (int i = 0; i < n; i++)
        result += f((a + h / 2) + i * h);
    
    return h * result;
}

double Integral::findIntegral()
{
    int N = 100;
    double* xi = new double[n];
    double* mu = new double[n];
    double* A = new double[n];
    double h = (b - a) / N;
    double result = 0;
    for (int i = 0; i < N; i++) {
        std::cout << "Iter: " << i << std::endl;
        xi[0] = a + i * h;
        xi[2] = a + (i + 1) * h;
        xi[1] = (xi[0] + xi[2]) / 2.0;
        print_vector(xi, "xi", n);

        
        mu[0] = c[0](xi[0], xi[2]);
        mu[1] = c[1](xi[0], xi[2]);
        mu[2] = c[2](xi[0], xi[2]);
        print_vector(mu, "mu", n);


        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                matrixes_map["mat"]->mat[i][j] = pow(xi[j], i);

        printMatrix(matrixes_map["mat"]);

        A = LU_solve(matrixes_map["mat"], mu);

        print_vector(A, "A", n);
        std::cout << std::endl;

        result += A[0]*f(xi[0]) + A[1]*f(xi[1]) + A[2]*f(xi[2]);

    }
    return result;
}

void Integral::printMatrix(Matrix* _matrix)
{
    std::cout << "Matrix " << _matrix->name << ":" << std::endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            //std::cout << std::setw(8) << _A->matrix[i][j];
            printf("%7.6f ", _matrix->mat[i][j]);

        std::cout << std::endl;
    }
    std::cout << std::endl;
};

//just functions, not methods
double* createAndFill_vector(int _n, double value)
{
    double* b = new double[_n];
    for (int i = 0; i < _n; i++)
        b[i] = value;
    return b;
}
void print_vector(double* vector, std::string name, int n)
{
    std::cout << name << ": ";
    for (int i = 0; i < n; i++)
        printf("%7.6f ", vector[i]);
    std::cout << std::endl;
}
