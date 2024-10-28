#include <matrix.h>

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
