#include "Header_Assignment2.2.h"

Matrix::Matrix(int _n, int _m, std::string _name, bool is_identityMat) : n(_n), m(_m), name(_name)
{
    mat = new double* [n];
    for (int i = 0; i < n; i++)
        mat[i] = new double[m];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            mat[i][j] = 0;

    if (is_identityMat)
        for (int i = 0; i < n; i++)
            mat[i][i] = 1;
}
Matrix::Matrix(): mat(), m(), n(), name() {}
Matrix::~Matrix()
{
    for (int i = 0; i < n; i++)
        delete mat[i];
    delete[] mat;
}


//functions
void printMatrix(Matrix* _matrix)
{
    std::cout << "Matrix " << _matrix->name << ":" << std::endl;
    for (int i = 0; i < _matrix->n; i++)
    {
        for (int j = 0; j < _matrix->m; j++)
            //std::cout << std::setw(8) << _A->matrix[i][j];
            printf("%7.1f ", _matrix->mat[i][j]);

        std::cout << std::endl;
    }
    std::cout << std::endl;
};


//Предполагается, что n <= m
void pivotify(Matrix* _matrix)
{
    //Создаются единичные матрицы перестановок строк и столбцов
    Matrix* E = new Matrix(_matrix->m, _matrix->m, "E", true);
    fillMatrixRandomly(E, 100);
    Matrix* origin_A = new Matrix(_matrix->n, _matrix->m, "origin_A");
    copy(_matrix, origin_A);
    Matrix* P = new Matrix(_matrix->n, _matrix->n, "P", true);
    Matrix* Q = new Matrix(_matrix->m, _matrix->m, "Q", true);
    for (int i = 0; i < _matrix->n; i++)
    {
        int pivotRow = i;
        int pivotCol = i;
        for (int j = i; j < _matrix->n; j++)
            for (int k = i; k < _matrix->m; k++)
                if (abs(_matrix->mat[j][k]) > abs(_matrix->mat[pivotRow][pivotCol]))
                {
                    pivotRow = j;
                    pivotCol = k;
                }

        if (_matrix->mat[pivotRow][pivotCol] == 0)
        {
            std::cout << "Cannot find pivot element. Determinant of matrix " 
                << _matrix->name << " is equal to zero." << std::endl;
            continue;
        }

        //Если ведущий элемент не диагональный, нужно менять местами строки и/или столбцы 
        if (pivotRow != i)
            for (int j = 0; j < _matrix->m; j++)
            {
                std::swap(_matrix->mat[i][j], _matrix->mat[pivotRow][j]);
                if (j < _matrix->n)
                    std::swap(P->mat[i][j], P->mat[pivotRow][j]);
            }

        if (pivotCol != i)
            for (int j = 0; j < _matrix->m; j++)
            {
                if (j < _matrix->n)
                    std::swap(_matrix->mat[j][i], _matrix->mat[j][pivotCol]);
                std::swap(Q->mat[j][i], Q->mat[j][pivotCol]);
            }
        std::cout << "swap" << pivotRow << pivotCol << std::endl;
        printMatrix(P);
        printMatrix(Q);
    }
    printMatrix(P);
    printMatrix(Q);
    Matrix* R = multiplication(P, origin_A);
    Matrix* Re = multiplication(R, Q);
    printMatrix(Re);
    is_equal(_matrix, Re, 1e-10);
    std::cout << std::endl;

}

void LU_decomposition(Matrix* _L, Matrix* _U, Matrix* _A)
{
    pivotify(_A);
    copy(_A, _U);
    for (int i = 0; i < _L->n; i++)
        for (int j = i; j < _L->m; j++)
            _L->mat[j][i] = _U->mat[j][i] / _U->mat[i][i];

    for (int k = 1; k < _L->n; k++)
    {
        for (int i = k - 1; i < _L->n; i++)
            for (int j = i; j < _L->n; j++)
                _L->mat[j][i] = _U->mat[j][i] / _U->mat[i][i];

        for (int i = k; i < _U->n; i++)
            for (int j = k - 1; j < _U->n; j++)
                _U->mat[i][j] = _U->mat[i][j] - _L->mat[i][k - 1] * _U->mat[k - 1][j];
    }
}

//_A * _B = R
Matrix* multiplication(Matrix* _A, Matrix* _B)
{
    Matrix* R = new Matrix(_A->n, _B->m, _A->name + "*" + _B->name);
    if (_A->m != _B->n) {
        std::cout << "Cannot do multiplication. Dimensions do not match!" << std::endl;
        return R;
    }

    for (int i = 0; i < _A->n; i++)
        for (int j = 0; j < _B->m; j++)
            for (int k = 0; k < _A->m; k++)
                R->mat[i][j] += _A->mat[i][k] * _B->mat[k][j];
    return R;
}

//copy matrix _A into matrix _B 
void copy(Matrix* _A, Matrix* _B)
{
    if (_A->n != _B->n || _A->m != _B->m) {
        std::cout << "Cannot copy. Dimensions do not match!" << std::endl;
        return;
    }
    for (int i = 0; i < _A->n; i++)
        for (int j = 0; j < _B->m; j++)
            _B->mat[i][j] = _A->mat[i][j];
}

bool is_equal(Matrix* _A, Matrix* _B, double eps)
{
    if (_A->n != _B->n || _A->m != _B->m) {
        std::cout << _A->name << " != " << _B->name << std::endl;
        return false;
    }
    bool equal = true;
    
    for (int i = 0; i < _A->n; i++)
        for (int j = 0; j < _A->m; j++)
            if (abs(_A->mat[i][j] - _B->mat[i][j]) > eps)
                equal = false;
    if (equal)
        std::cout << _A->name << " = " << _B->name << std::endl;
    else
        std::cout << _A->name << " != " << _B->name << std::endl;
    return equal;
}

void fillMatrixRandomly(Matrix* _matrix, int max_value)
{
    for (int i = 0; i < _matrix->n; i++)
        for (int j = 0; j < _matrix->m; j++)
            _matrix->mat[i][j] = rand() % max_value;
};
void fillMatrix(Matrix* _matrix)
{
    std::cout << "Matrix dimensions = " << _matrix->n << "x" << _matrix->m << ". Enter the elements of matrix row-wise: ";
    for (int i = 0; i < _matrix->n; i++)
        for (int j = 0; j < _matrix->m; j++)
            std::cin >> _matrix->mat[i][j];
};
double* createAndFill_b(int _n)
{
    double* b = new double[_n];
    std::cout << "Enter " << _n << " elements of the vector b: ";
    for (int i = 0; i < _n; i++)
        std::cin >> b[i];
    return b;
}
double* createAndFill_b_rand(int _n, int max_value)
{
    double* b = new double[_n];
    for (int i = 0; i < _n; i++)
        b[i] = rand() % max_value;
    return b;
}