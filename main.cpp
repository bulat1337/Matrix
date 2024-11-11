#include "buffer.h"  // for proxy_row_t

#include <matrix.h>  // for sq_matrix_t, matrix_t
#include <stddef.h>  // for size_t
#include <iostream>  // for basic_istream, basic_ostream, basic_ios, cin

int main()
{
    size_t dim = 0;
    std::cin >> dim;

    matrix::sq_matrix_t<double> matrix(dim);

    for (size_t row = 0; row < dim; ++row)
        for (size_t col = 0; col < dim; ++col)
            std::cin >> matrix[row][col];

    std::cout << matrix.det() << '\n';

    return 0;
}
