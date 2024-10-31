#include <iostream>
#include <matrix.h>

int main()
{
    size_t dim = 150;
    matrix::sq_matrix_t<double> matrix = matrix::sq_matrix_t<double>::rand(dim);

    return 0;
}
