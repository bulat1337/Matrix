#ifndef MATRIX_H
#define MATRIX_H

#include <detail.h>

namespace matrix
{

template <typename T>
class matrix_t
{
  private:
	size_t row_ = 0;
	size_t col_ = 0;
	detail::buffer_t<T> data_;

  public:
	matrix_t(size_t row, size_t col, const T& value = T{}):
		  row_(row)
		, col_(col)
		, data_(row, col, value) {}

	detail::proxy_row_t<T> operator [] (size_t index)       { return data_[index]; }
	detail::proxy_row_t<T> operator [] (size_t index) const { return data_[index]; }


};

};

#endif
