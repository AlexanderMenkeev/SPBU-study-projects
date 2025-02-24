#include "header.h"

std::function<double(double)> f = [](double x)
{
	return 2 * cos(2.5 * x) * exp(x / 3) + 4 * sin(3.5 * x) * exp(-3 * x) + x;
};

int main()
{
	int const n = 3; //количество узлов
	double a = 1.5;  //нижний предел интегрирования
	double b = 3.3;  //верхний предел интегрирования
	double alpha = 1.0 / 3.0; 
	double betta = 0;


	Integral integ(f, a, b, alpha, betta, n);
	integ.add_new_matrix("mat");
	
	std::cout << "sum = ";
	
	printf("%7.10f ", integ.findIntegral());

}