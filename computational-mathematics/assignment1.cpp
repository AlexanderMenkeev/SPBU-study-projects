//#include <iostream>
//#include "math.h"
//#include <iomanip>
//using namespace std;
//
//double approx_sin(double x)
//{
//	double sin = 0, eps = 0.0001, delta = 0;
//	int k = 0;
//	do {
//		double denum = 1;
//		double buf = sin;
//		for (int i = 2; i <= 2 * k + 1; i++)
//			denum *= i;
//		sin += pow(-1, k) * pow(x, 2 * k + 1) / denum;
//		delta = sin - buf;
//		k++;
//	} while (abs(delta) > eps);
//	return sin;
//}
//
//double approx_exp(double x)
//{
//	double exp = 0, eps = 0.0001, delta = 0;
//	int k = 0;
//	do
//	{
//		double denum = 1;
//		double buf = exp;
//		for (int i = 1; i <= k; i++)
//			denum *= i;
//		exp += pow(x, k) / denum;
//		delta = exp - buf;
//		k++;
//	} while (abs(delta) > eps);
//	return exp;
//}
//
//double approx_sqrt(double x)
//{
//	double sqrt = 1 + x / 2, eps = 0.0001, delta = 0;
//	int k = 0;
//	do
//	{
//		double buf = sqrt;
//		sqrt = (buf + x / buf) / 2;
//		delta = sqrt - buf;
//		k++;
//	} while (abs(delta) > eps);
//	return sqrt;
//}
//
//
//int main()
//{
//	double x1 = 0.5, x2 = 0.6;
//	double f_exact = 0, f_approx = 0, error = 0;
//
//	cout.setf(ios::left);
//
//	cout << "   " << setw(20) << "x" << setw(25) << "f_approx" 
//		<< setw(25) << "f_exact" << setw(25) << "error" << endl;
//	do
//	{
//		//Считаем
//		f_approx = approx_sqrt(1 + x1) * approx_exp(x1 + 0.5) * approx_sin(0.3 * x1 + 0.7);
//		f_exact = sqrt(1 + x1) * exp(x1 + 0.5) * sin(0.3 * x1 + 0.7);
//		error = abs(f_exact - f_approx);
//
//		//Выводим
//		cout.unsetf(ios::fixed);
//		cout << "   " << setw(20) << x1;
//		cout << setprecision(10) << fixed << setw(25) << f_approx
//			<< setw(25) << f_exact << setw(25) << error << endl;
//		x1 += 0.01;
//	} while (x1 <= x2+0.00001);
//}