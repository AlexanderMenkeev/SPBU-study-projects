#include "Header.h"

Matrix::Matrix(int _n, std::string _name, bool is_identityMat) : n(_n), name(_name)
{
    mat = new double*[n];
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


/////private:

//A*x = b  =>  L*U*x = b  => L*y = b, где y = U*x
//В этом методе решается L*y = b
double* SLAE::forward_substitution(Matrix* _L, double* _b)
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

//В этом методе решается U*x = y
double* SLAE::backward_substitution(Matrix* _U, double* _y)
{
    double* x = new double[n];
    for (int i = n - 1; i > -1; i--)
    {
        if (abs(_U->mat[i][i]) < eps)
        {
            x[i] = rand() % 10;
            std::cout << "x_" << i << " is free variable." << std::endl;
            continue;
        }
        double value = _y[i];

        for (int j = i + 1; j < n; j++)
            value -= _U->mat[i][j] * x[j];

        value /= _U->mat[i][i];
        x[i] = value;
    }
    return x;
}

//P и Q создаются здесь
void SLAE::pivotify(Matrix* _A)
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

        if (abs(_A->mat[pivotRow][pivotCol]) < eps)
        {
            //std::cout << "Cannot find pivot element" << std::endl;
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


bool SLAE::is_diagonally_dominant(Matrix* _matrix)
{
    double sum = 0;
    for (int i = 0; i < _matrix->n; i++)
    {
        sum = 0;
        for (int j = 0; j < _matrix->n; j++)
            if (i != j)
                sum += abs(_matrix->mat[i][j]);

        if (abs(_matrix->mat[i][i]) < sum)
        {
            std::cout << "Matrix " << _matrix->name
                << " is NOT diagonally dominant." << std::endl;
            return false;
        }
    }
    std::cout << "Matrix " << _matrix->name
        << " is diagonally dominant." << std::endl;
    return true;
}
void SLAE::extract_column(Matrix* _matrix, double* x, int k)
{
    for (int i = 0; i < n; i++)
        x[i] = _matrix->mat[i][k];
}
void SLAE::compute_minor(Matrix* _minor, Matrix* _matrix, int d) {
    for (int i = 0; i < d; i++)
        _minor->mat[i][i] = 1.0;
    for (int i = d; i < n; i++)
        for (int j = d; j < n; j++)
            _minor->mat[i][j] = _matrix->mat[i][j];
}
double SLAE::norm(double* _vector)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += _vector[i] * _vector[i];

    return sqrt(sum);
}
double SLAE::norm(Matrix* _mat)
{
    double max = 0;
    double sum;
    for (int i = 0; i < n; i++)
    {
        sum = 0;
        for (int j = 0; j < n; j++)
            sum += abs(_mat->mat[i][j]);
        if (sum > max)
            max = sum;
    }
    return max;
}
int SLAE::rank(double* vector)
{
    int rank = 0;
    for (int i = 0; i < n; i++)
        if (abs(vector[i]) > eps)
            rank++;
    return rank;
}
int SLAE::rank_Ab(double* b)
{
    int rank = 0;
    Matrix* U = matrixes_map["U"];
    for (int i = 0; i < n; i++)
        if (abs(U->mat[i][i]) > eps)
            rank++;
        else if (abs(b[i] > eps))
            rank++;
        else
            break;
    return rank;
}

/////public:


SLAE::SLAE(int _n, double _eps) : n(_n), eps(_eps) { }


//L и U создаются здесь
void SLAE::LU_decomposition(Matrix* _A)
{
    add_new_matrix("L");
    add_new_matrix("U");
    Matrix* _L = matrixes_map["L"];
    Matrix* _U = matrixes_map["U"];
    pivotify(_A);
    copy(_A, _U);
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            _L->mat[j][i] = _U->mat[j][i] / _U->mat[i][i];

    for (int k = 1; k < n; k++)
    {
        for (int i = k - 1; i < n; i++)
            for (int j = i; j < n; j++)
                _L->mat[j][i] = _U->mat[j][i] / _U->mat[i][i];

        for (int i = k; i < n; i++)
            for (int j = k - 1; j < n; j++)
                _U->mat[i][j] = _U->mat[i][j] - _L->mat[i][k - 1] * _U->mat[k - 1][j];
    }
}




void SLAE::QR_decomposition(Matrix* _A)
{
    std::vector<Matrix*> q;
    add_new_matrix("Q");
    add_new_matrix("R");

    //temp matrix
    Matrix* A_temp = new Matrix(n, "A_temp");
    copy(_A, A_temp);
    Matrix* temp = new Matrix(n, "temp");

    for (int k = 0; k < n - 1; k++)
    {
        q.push_back(new Matrix(n, "Q_" + std::to_string(k)));
        double* e = createAndFill_vector(n, 0);
        double* x = createAndFill_vector(n, 0);
        double a;

        //compute minor
        fillMatrix(temp, 0);
        compute_minor(temp, A_temp, k);

        //extract k-th column into x
        extract_column(temp, x, k);

        a = norm(x);

        if (_A->mat[k][k] > 0) a = -a;

        e[k] = 1;

        //e = x + a*e
        for (int i = 0; i < n; i++)
            e[i] = x[i] + a * e[i];

        //e = e / ||e||
        double norm_e = norm(e);
        for (int i = 0; i < n; i++)
            e[i] = e[i] / norm_e;

        //q[k] = I - 2 *e*e^T
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                q[k]->mat[i][j] = -2 * e[i] * e[j];
        for (int i = 0; i < n; i++)
            q[k]->mat[i][i] += 1;

        //A_temp = q[k] * temp
        A_temp = multiplication(q[k], temp);
    }
    matrixes_map["Q"] = q[0];

    //after this loop, we will obtain Q
    for (int i = 1; i < n - 1; i++)
    {
        temp = multiplication(q[i], matrixes_map["Q"]);
        matrixes_map["Q"] = temp;
    }

    matrixes_map["R"] = multiplication(matrixes_map["Q"], _A);
    transpose(matrixes_map["Q"]);
}

//Предполагается, что LU и QR разложения уже построены
double* SLAE::LU_solve(double* _b)
{
    _b = multiplication(matrixes_map["P"], _b);

    double* y = forward_substitution(matrixes_map["L"], _b);
    
    print_vector(y, "y", n);

    if (rank() != rank_Ab(y)) {
        std::cout << rank() << "!=" << rank_Ab(y) << std::endl;
        std::cout << "rank(A) != rank(A|b). SLAE is inconsistent. Solution does not exist." << std::endl;
        return y;
    }
    else
        std::cout << "rank(A) = rank(A|b). SLAE is consistent." << std::endl;

    double* x = backward_substitution(matrixes_map["U"], y);
    x = multiplication(matrixes_map["Q"], x);
    return x;
}
double* SLAE::QR_solve(double* _b)
{
    transpose(matrixes_map["Q"]);
    double* y = multiplication(matrixes_map["Q"], _b);
    double* x = backward_substitution(matrixes_map["R"], y);
    return x;
}

void SLAE::solve_Gauss_Seidel(double* x, double* _b)
{
    Matrix* A = matrixes_map["A"];
    pivotify(A);
    double* b = createAndFill_vector(n, 0);
    copy(multiplication(matrixes_map["P"], x), x);
    copy(multiplication(matrixes_map["P"], _b), b);
    is_diagonally_dominant(A);

    double* d = new double[n];
    int iter = 0;
    double* difference = subtraction(multiplication(A, x), b);
    while (!is_equal(difference, 0))
    {
        std::cout << std::endl;
        std::cout << "iter = " << iter << ":" << std::endl;
        print_vector(difference, "diff", n);
        double _norm = norm(difference);
        std::cout << "norm of diff: " << _norm << std::endl;
        for (int i = 0; i < n; i++) {
            d[i] = b[i] / A->mat[i][i];
            for (int j = 0; j < n; j++) {
                if (j == i)
                    continue;
                d[i] = d[i] - ((A->mat[i][j] / A->mat[i][i]) * x[j]);
                x[i] = d[i];
            }
        }
        iter++;
        print_vector(d, "x", n);

        difference = subtraction(multiplication(A, x), b);

        if (_norm > 1e+6)
            break;

        //Ограничение числа итераций
        if (iter > 100)
            break;
    }
    copy(multiplication(matrixes_map["Q"], d), x);
}
void SLAE::solve_Jacobi(double* current_x, double* _b)
{
    Matrix* A = matrixes_map["A"];
    pivotify(A);
    double* b = createAndFill_vector(n, 0);
    copy(multiplication(matrixes_map["P"], current_x), current_x);
    copy(multiplication(matrixes_map["P"], _b), b);
    if (!is_diagonally_dominant(A))
        return;
    //is_diagonally_dominant(A);

    double* d = createAndFill_vector(n, 0);
    double* prev_x = createAndFill_vector(n, 0);
    int iter = 0;
    double _norm;
    double* difference = subtraction(multiplication(A, current_x), b);
    while (!is_equal(difference, 0))
    {
        std::cout << std::endl;
        std::cout << "iter = " << iter << ":" << std::endl;
        print_vector(difference, "difference", n);
        _norm = norm(difference);
        std::cout << "norm of difference: " << _norm << std::endl;

        copy(current_x, prev_x);
        for (int i = 0; i < n; i++) {
            d[i] = b[i] / A->mat[i][i];
            for (int j = 0; j < n; j++) {
                if (j == i)
                    continue;
                d[i] = d[i] - ((A->mat[i][j] / A->mat[i][i]) * prev_x[j]);
                current_x[i] = d[i];
            }
        }

        iter++;
        print_vector(current_x, "current_x", n);
        print_vector(prev_x, "prev_x", n);

        difference = subtraction(multiplication(A, current_x), b);

        //Если норма вектора разницы растет, останавливать цикл
        if (_norm > 1e+6)
            break;


        //Ограничение числа итераций
        if (iter > 100)
            break;
    }

    copy(multiplication(matrixes_map["Q"], d), current_x);
    delete[] d;
    delete[] b;
    delete[] prev_x;
    delete[] difference;
}



//Ищет обратную матрицу к измененной матрице А
Matrix* SLAE::inverse_matrix()
{
    Matrix* E = new Matrix(n, "E", true);
    Matrix* result = new Matrix(n, "inv_A");

    if (abs(calculate_determinant()) < eps)
        return result;

    double** y = new double*[n];
    for (int i = 0; i < n; i++)
        y[i] = forward_substitution(matrixes_map["L"], E->mat[i]);

    double** x = new double*[n];
    for (int i = 0; i < n; i++)
        x[i] = backward_substitution(matrixes_map["U"], y[i]);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result->mat[i][j] = x[j][i];
           
    return result;
}
double SLAE::condition_number(Matrix* _mat, Matrix* _invMat)
{
    double norm_invMat = norm(_invMat);
    double norm_Mat = norm(_mat);
    return norm_invMat * norm_Mat;
}

void SLAE::add_new_matrix(std::string _name, bool is_identityMat)
{
    matrixes_map.emplace(_name, new Matrix(n, _name, is_identityMat));
}
int SLAE::rank()
{
    int rank = 0;
    Matrix* U = matrixes_map["U"];
    for (int i = 0; i < n; i++)
        if (abs(U->mat[i][i]) > eps)
            rank++;
        else
            break;
    return rank;
}
double SLAE::calculate_determinant()
{
    double det = 1;
    Matrix* U = matrixes_map["U"];
    for (int i = 0; i < n; i++)
        det *= U->mat[i][i];
    return det;
}

bool SLAE::is_equal(Matrix* _A, Matrix* _B)
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
bool SLAE::is_equal(double* _a, double value)
{
    bool equal = true;
    for (int i = 0; i < n; i++)
        if (abs(_a[i] - value) > eps)
            equal = false;
    return equal;
}


//_A * _b = r
double* SLAE::multiplication(Matrix* _A, double* _b)
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
Matrix* SLAE::multiplication(Matrix* _A, Matrix* _B)
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

//a - b = r
double* SLAE::subtraction(double* a, double* b)
{
    double* r = new double[n];
    
    for (int i = 0; i < n; i++)
        r[i] = a[i] - b[i];
    return r;
}


//copy matrix _A into matrix _B 
void SLAE::copy(Matrix* _A, Matrix* _B)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            _B->mat[i][j] = _A->mat[i][j];
}
//copy vector _a into vector _b 
void SLAE::copy(double* _a, double* _b)
{
    for (int i = 0; i < n; i++)
        _b[i] = _a[i];
}

void SLAE::fillMatrixRandomly(Matrix* _matrix, int max_value)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            _matrix->mat[i][j] = rand() % max_value;
};
void SLAE::fillMatrix(Matrix* _matrix, double value)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            _matrix->mat[i][j] = value;
};
void SLAE::fillMatrix(Matrix* _matrix)
{
    std::cout << "Matrix dimension = " << n << ". Enter the elements of matrix row-wise: ";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            std::cin >> _matrix->mat[i][j];
};
void SLAE::printMatrix(Matrix* _matrix)
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
void SLAE::print_all_matrixes()
{
    for (auto& x : matrixes_map)
        printMatrix(x.second);
}
void SLAE::transpose(Matrix* _matrix)
{
    _matrix->name = "transposed_" + _matrix->name;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            std::swap(_matrix->mat[i][j], _matrix->mat[j][i]);
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

void SLAE::check_solution(double* x, double* b)
{
    double* result = subtraction(multiplication(matrixes_map["Original_A"], x), b);
    if (is_equal(result, 0))
        std::cout << "A*x - b = 0" << std::endl;
    else
        std::cout << "A*x - b != 0" << std::endl;
    print_vector(result, "result", n);
    delete[] result;
}