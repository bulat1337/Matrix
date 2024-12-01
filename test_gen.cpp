#include <matrix.h> // for sq_matrix_t
#include <stddef.h> // for size_t

int main()
{
	size_t dim = 150;
	matrix::sq_matrix_t<double> matrix = matrix::sq_matrix_t<double>::rand(dim);

	return 0;
}
