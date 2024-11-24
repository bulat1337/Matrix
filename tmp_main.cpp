#include "buffer.h"  // for proxy_row_t

#include <matrix.h>  // for sq_matrix_t, matrix_t
#include <stddef.h>  // for size_t
#include <iostream>  // for basic_istream, basic_ostream, basic_ios, cin

int main()
{
	std::vector<int> vec;

    for (int id = 0; id < 100; ++id)
        vec.push_back(id);

    size_t rows = 4;
    size_t cols = 10;

	try
	{
		matrix::matrix_t<int> matrix(rows, cols, vec.cbegin(), vec.cend());
	}
	catch (std::logic_error& e)
	{
		std::cout << e.what();
	}

    return 0;
}
