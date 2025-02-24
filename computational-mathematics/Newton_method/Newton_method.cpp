#include "Newton_header.h"

int main()
{
	NonlinearSystem nls;
	int const n = nls.get_n();
	
	//начальное приближение
	double* x = new double[n];
	x[0] = 0.5; 
	x[1] = 0.5;
	x[2] = 1.5;
	x[3] = -1.0;
	x[4] = -0.5; //-0.2
	x[5] = 1.5;
	x[6] = 0.5; 
	x[7] = -0.5;
	x[8] = 1.5;
	x[9] = -1.5;
	
	x = nls.Newton_method(x, 4);
	//x = nls.modified_Newton_method(x);
	print_vector(x, "Solution", n);
	std::cout << "Time: " << clock() << std::endl;
	delete[] x;
}