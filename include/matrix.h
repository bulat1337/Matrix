#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

#include <detail.h>

namespace matrix
{

template <typename T>
class matrix_t
{
  private:
	size_t rows_ = 0;
	size_t cols_ = 0;
	detail::buffer_t<T> data_;

  public:
	matrix_t(size_t rows, size_t cols, const T& value = T{}):
		  rows_(rows)
		, cols_(cols)
		, data_(rows, cols, value) {}

	matrix_t(size_t dim, const T& value = T{}):
		  rows_(dim)
		, cols_(dim)
		, data_(dim, value) {}

	template <typename Iter>
	matrix_t(size_t rows, size_t cols, Iter begin, Iter end):
		  rows_(rows)
		, cols_(cols)
		, data_(rows, cols, begin, end) {}

	static matrix_t eye(size_t dim)
	{
		matrix::matrix_t<T> result(dim, dim);

		for (size_t id = 0; id < dim; ++id)
		{
			result.data_[id][id] = 1;
		}

		return result;
	}

	detail::proxy_row_t<T> operator [] (size_t index) { return data_[index]; }
	const detail::proxy_row_t<T> operator [] (size_t index) const { return data_[index]; }

	size_t nrows() const { return rows_; }
	size_t ncols() const { return cols_; }

	double det()
	{
		size_t dim = rows_;
		matrix_t<T> L = eye(dim);
		matrix_t<T> U(dim);

		for (size_t i = 0; i < dim; i++)
		{
			for (size_t j = i; j < dim; j++)
			{
				double sumU = 0.0;
				for (size_t k = 0; k < i; k++)
				{
					sumU += L[i][k] * U[k][j];
				}
				U[i][j] = data_[i][j] - sumU;
			}

			for (size_t j = i + 1; j < dim; j++)
			{
				double sumL = 0.0;
				for (size_t k = 0; k < i; k++)
				{
					sumL += L[j][k] * U[k][i];
				}
				L[j][i] = (data_[j][i] - sumL) / U[i][i];
			}
		}

// 		std::cout << "Upper:\n";
// 		for (size_t row = 0; row < dim; ++row)
// 		{
// 			for (size_t col = 0; col < dim; ++col)
// 			{
// 				std::cout << U[row][col] << '\t';
// 			}
// 			std::cout << '\n';
// 		}
//
// 		std::cout << '\n';
//
// 		std::cout << "Lower:\n";
// 		for (size_t row = 0; row < dim; ++row)
// 		{
// 			for (size_t col = 0; col < dim; ++col)
// 			{
// 				std::cout << L[row][col] << '\t';
// 			}
// 			std::cout << '\n';
// 		}

		double det_L = 1.0;
		for (size_t id = 0; id < dim; ++id)
		{
			det_L *= L[id][id];
		}

		double det_U = 1.0;
		for (size_t id = 0; id < dim; ++id)
		{
			det_U *= U[id][id];
		}

		return det_L * det_U;
	}
};

};

#endif
