#ifndef IMATRIX_H
#define IMATRIX_H

#include "proxy_row.h"
#include "utils.h"

namespace matrix
{

namespace detail
{

template <typename T>
class imatrix_t : private detail::buffer_t<T>
{
  protected:
	using detail::buffer_t<T>::ctored_;
	using detail::buffer_t<T>::data_;
	using detail::buffer_t<T>::size_;

  protected:
	virtual bool pivot(size_t col, size_t &swap_counter)
	{
		T max_elem = std::abs((*this)[col][col]);
		size_t max_id = col;

		for (size_t row = col; row < nrows(); ++row)
		{
			T elem = std::abs((*this)[row][col]);
			if (elem > max_elem)
			{
				max_elem = elem;
				max_id = row;
			}
		}

		if (max_elem < utils::fp_tolerance)
			return false;

		if (max_id != col)
		{
			swap_rows(col, max_id);
			++swap_counter;
		}

		return true;
	}

  public:
	imatrix_t(size_t size = 0)
		: detail::buffer_t<T>(size)
	{}

	virtual detail::proxy_row_t<T> operator[](size_t index) = 0;

	virtual detail::proxy_row_t<const T> operator[](size_t index) const = 0;

	virtual size_t nrows() const = 0;
	virtual size_t ncols() const = 0;

	virtual void dump(std::ostream &out = std::clog) const = 0;

	virtual void swap_rows(size_t row_1, size_t row_2) = 0;

	virtual ~imatrix_t() = default;
};

}; // namespace detail

}; // namespace matrix

#endif // IMATRIX_H
