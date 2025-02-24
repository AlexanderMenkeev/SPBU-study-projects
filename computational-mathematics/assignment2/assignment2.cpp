#include "Header.h"

int main()
{
	std::cout.setf(std::ios::left);
    srand(unsigned(time(0)));

	const double eps = 1e-9;
	const int n = 3;
	SLAE slae(n, eps);

	double* b = createAndFill_vector_rand(n, 10);
	print_vector(b, "b", n);

	slae.add_new_matrix("A");
	slae.add_new_matrix("Original_A");
	slae.fillMatrixRandomly(slae.matrixes_map["A"], 50);
	slae.copy(slae.matrixes_map["A"], slae.matrixes_map["Original_A"]);

	//slae.LU_decomposition(slae.matrixes_map["A"]);
	//slae.print_all_matrixes();

	////Проверка LU разложения
	//Matrix* PA = slae.multiplication(slae.matrixes_map["P"], slae.matrixes_map["Original_A"]);
	//Matrix* PAQ = slae.multiplication(PA, slae.matrixes_map["Q"]);
	//Matrix* LU = slae.multiplication(slae.matrixes_map["L"], slae.matrixes_map["U"]);
	//slae.is_equal(LU, PAQ);

	//std::cout << '\n';
	////Пункт 1а) Вычислить определитель матрицы А
	//std::cout << "det A = " << slae.calculate_determinant() << std::endl;



	//std::cout << '\n';
	////Пункт 1b) Решить СЛАУ
	//double* x = slae.LU_solve(b);
	//
	//print_vector(x, "Solution of the system", n);

	// 
	////Должно быть: A*x - b = 0
	//slae.check_solution(x, b);


	//std::cout << '\n';
	////Пункт 1с) Найти обратную матрицу
	//Matrix* inv_A = slae.inverse_matrix();

	////Проверка правильности нахождения обратной матрицы
	////Должно быть: A*invA = E, invA*A = E
	//Matrix* A_by_invA = slae.multiplication(slae.matrixes_map["A"], inv_A);
	//slae.is_equal(A_by_invA, slae.matrixes_map["E"]);
	//Matrix* invA_by_A = slae.multiplication(inv_A, slae.matrixes_map["A"]);
	//slae.is_equal(invA_by_A, slae.matrixes_map["E"]);



	//std::cout << '\n';
	////Пункт 1d) Найти число обусловленности
	////Для подсчета числа обусловленности используется норма ||A||_infinity
	//std::cout << "Condition number of matrix A = "
	//	<< slae.condition_number(slae.matrixes_map["A"], inv_A) << std::endl;

	//
	//std::cout << '\n';
	//

	slae.printMatrix(slae.matrixes_map["Original_A"]);
	slae.QR_decomposition(slae.matrixes_map["Original_A"]);
	slae.matrixes_map["Q"]->name = "Q";
	slae.matrixes_map["R"]->name = "R";
	Matrix* QR = slae.multiplication(slae.matrixes_map["Q"], slae.matrixes_map["R"]);
	
	slae.is_equal(slae.matrixes_map["Original_A"], QR);
	double* x = slae.QR_solve(b);
	print_vector(b, "b", n);
	print_vector(x, "Solution of the system by QR", n);

	slae.check_solution(x, b);

	//gaussss
	/*double* x_gauss = createAndFill_vector(n, 0);
	slae.solve_Gauss_Seidel(x_gauss, b);
	
	slae.check_solution(x_gauss, b);
	print_vector(b, "b", n);
	print_vector(x_gauss, "Solution of the system by gauss", n);*/

	

	double* x_jacobi = createAndFill_vector(n, 0);
	slae.solve_Jacobi(x_jacobi, b);
	slae.printMatrix(slae.matrixes_map["A"]);
	slae.check_solution(x_jacobi, b);
	print_vector(b, "b", n);
	print_vector(x_jacobi, "Solution of the system by jacobi", n);
	print_vector(x, "Solution of the system by QR", n);

	std::cout << "Time:" << clock() << '\n';

}