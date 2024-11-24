#include "buffer.h"  // for proxy_row_t

#include <matrix.h>  // for sq_matrix_t, matrix_t
#include <stddef.h>  // for size_t
#include <iostream>  // for basic_istream, basic_ostream, basic_ios, cin

int main()
{
    size_t dim = 0;
    if (!std::cin.good() || !(std::cin >> dim))
	{
		std::cerr << "The dimension of the matrix must be a number.\n";
		return 0;
	}

    matrix::sq_matrix_t<double> matrix(dim);

    for (size_t row = 0; row < dim; ++row)
        for (size_t col = 0; col < dim; ++col)
		{
            if (!std::cin.good() || !(std::cin >> matrix[row][col]))
			{
				std::cerr << "The matrix elements must be numbers.\n";
				return 0;
			}
		}

    std::cout << matrix.det() << '\n';

    return 0;
}
