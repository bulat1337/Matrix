#ifndef MATRIX_H
#define MATRIX_H

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

	detail::proxy_row_t<T> operator [] (size_t index)       { return data_[index]; }
	detail::proxy_row_t<T> operator [] (size_t index) const { return data_[index]; }

	size_t nrows() const { return rows_; }
	size_t ncols() const { return cols_; }
};

};

#endif
