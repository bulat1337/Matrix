#ifndef MATRIX_H
#define MATRIX_H

#include "buffer.h"
#include "imatrix.h"
#include "log.h"
#include "proxy_row.h"
#include "utils.h"

#include <cmath>
#include <iostream>
#include <random>
#include <vector>

namespace matrix
{

template <typename T>
class matrix_t final : public detail::imatrix_t<T>
{
  private:
	size_t rows_ = 0;
	size_t cols_ = 0;

	using detail::imatrix_t<T>::ctored_;
	using detail::imatrix_t<T>::data_;
	using detail::imatrix_t<T>::size_;

  public:
	matrix_t(size_t rows, size_t cols, const T &value = T{})
		: detail::imatrix_t<T>(rows * cols)
		, rows_(rows)
		, cols_(cols)
	{
		for (size_t id = 0; id < size_; ++id)
		{
			new (data_ + id) T(value);
			++ctored_;
		}
	}

	template <typename Iter>
	matrix_t(size_t rows, size_t cols, Iter begin, Iter end)
		: detail::imatrix_t<T>(rows * cols)
		, rows_(rows)
		, cols_(cols)
	{
		if (static_cast<size_t>(std::distance(begin, end)) < size_)
			throw std::logic_error("Not enough elements "
								   "for matrix initialization");

		Iter iter = begin;

		for (size_t filled = 0; filled < size_; ++filled, ++iter)
		{
			new (data_ + filled) T(*iter);
			++ctored_;
		}
	}

	matrix_t(matrix_t &&other) = default;
	matrix_t &operator=(matrix_t &&other) = default;

	matrix_t(const matrix_t &other)
		: detail::imatrix_t<T>(other.rows_ * other.cols_)
		, rows_(other.rows_)
		, cols_(other.cols_)
	{
		for (size_t id = 0; id < size_; ++id)
		{
			new (data_ + id) T(other.data_[id]);
			++ctored_;
		}
	}

	matrix_t &operator=(const matrix_t<T> &other)
	{
		matrix_t tmp(other);
		std::swap(*this, tmp);

		return *this;
	}

	detail::proxy_row_t<T> operator[](size_t index) override
	{
		return detail::proxy_row_t<T>(data_ + index * cols_);
	}

	detail::proxy_row_t<const T> operator[](size_t index) const override
	{
		return detail::proxy_row_t<const T>(data_ + index * cols_);
	}

	size_t nrows() const override { return rows_; }
	size_t ncols() const override { return cols_; }

	void dump(std::ostream &out = std::clog) const override
	{
		for (size_t row = 0; row < rows_; ++row)
		{
			for (size_t col = 0; col < cols_; ++col)
			{
				out << (*this)[row][col] << "\t\t";
			}
			out << "\n\n";
		}
	}

	void swap_rows(size_t row_1, size_t row_2) override
	{
		if (row_1 == row_2)
			return;
		for (size_t col = 0; col < cols_; ++col)
		{
			std::swap((*this)[row_1][col], (*this)[row_2][col]);
		}
	}
};

template <typename T>
class sq_matrix_t : public detail::imatrix_t<T>
{
  private:
	size_t dim_ = 0;

	using detail::imatrix_t<T>::ctored_;
	using detail::imatrix_t<T>::data_;
	using detail::imatrix_t<T>::size_;

  public:
	sq_matrix_t(size_t dim, const T &value = T{})
		: detail::imatrix_t<T>(dim * dim)
		, dim_(dim)
	{
		for (size_t id = 0; id < size_; ++id)
		{
			new (data_ + id) T(value);
			++ctored_;
		}
	}

	template <typename Iter>
	sq_matrix_t(size_t dim, Iter begin, Iter end)
		: detail::imatrix_t<T>(dim * dim)
		, dim_(dim)
	{
		if (static_cast<size_t>(std::distance(begin, end)) < size_)
			throw std::logic_error("Not enough elements "
								   "for matrix initialization");

		Iter iter = begin;

		for (size_t filled = 0; filled < size_; ++filled, ++iter)
		{
			new (data_ + filled) T(*iter);
			++ctored_;
		}
	}

	sq_matrix_t(sq_matrix_t &&other) = default;
	sq_matrix_t &operator=(sq_matrix_t &&other) = default;

	sq_matrix_t(const sq_matrix_t &other)
		: detail::imatrix_t<T>(other.dim_ * other.dim_)
		, dim_(other.dim_)
	{
		for (size_t id = 0; id < size_; ++id)
		{
			new (data_ + id) T(other.data_[id]);
			++ctored_;
		}
	}

	sq_matrix_t &operator=(const sq_matrix_t<T> &other)
	{
		sq_matrix_t tmp(other);
		std::swap(*this, tmp);

		return *this;
	}

	detail::proxy_row_t<T> operator[](size_t index) override
	{
		return detail::proxy_row_t<T>(data_ + index * dim_);
	}

	detail::proxy_row_t<const T> operator[](size_t index) const override
	{
		return detail::proxy_row_t<const T>(data_ + index * dim_);
	}

	size_t nrows() const override { return dim_; }
	size_t ncols() const override { return dim_; }

	void dump(std::ostream &out = std::clog) const override
	{
		for (size_t row = 0; row < dim_; ++row)
		{
			for (size_t col = 0; col < dim_; ++col)
			{
				out << (*this)[row][col] << "\t\t";
			}
			out << "\n\n";
		}
	}

	void swap_rows(size_t row_1, size_t row_2) override
	{
		if (row_1 == row_2)
			return;
		for (size_t col = 0; col < dim_; ++col)
		{
			std::swap((*this)[row_1][col], (*this)[row_2][col]);
		}
	}

	static sq_matrix_t eye(size_t dim)
	{
		sq_matrix_t<T> result(dim);
		for (size_t id = 0; id < dim; ++id)
		{
			result[id][id] = 1;
		}
		return result;
	}

	static sq_matrix_t rand(size_t dim)
	{
		sq_matrix_t<T> result(dim);

		std::random_device rd{};
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distributor(4, 20);
		std::uniform_int_distribution<> row_distr(0, static_cast<int>(dim - 1));

		for (size_t id = 0; id < dim; ++id)
		{
			result[id][id] = static_cast<double>(distributor(gen)) / 10;
		}

#ifdef DUMP_MATRIX
		MSG("\nDIAGONAL:\n");
		result.dump();
#endif

#ifdef ENABLE_LOGGING
		double determinant = 1.0;
		for (size_t id = 0; id < dim; ++id)
			determinant *= result[id][id];
#endif
		LOG("DETERMINANT: {}\n", determinant);

		for (size_t id = 0; id < 10; ++id)
			for (size_t row = 0; row < dim; ++row)
			{
				size_t other_row = static_cast<size_t>(row_distr(gen));
				if (row != other_row)
				{
					for (size_t col = 0; col < dim; ++col)
						result[row][col] += result[other_row][col];
				}
			}

#ifdef DUMP_MATRIX
		MSG("\nRANDOM:\n");
		result.dump();
#endif
		return result;
	}

	double det() const
	{
#ifdef DUMP_MATRIX
		MSG("Calculating determinant of:\n");
		dump();
#endif

		size_t dim = dim_;
		sq_matrix_t<double> upper(*this);

		size_t swap_counter = 0;

		for (size_t col = 0; col < dim; ++col)
		{
			if (!upper.pivot(col, swap_counter))
				return 0.0;

			for (size_t j = col + 1; j < dim; j++)
			{
				double coeff = upper[j][col] / upper[col][col];

				for (size_t k = col; k < dim; k++)
				{
					upper[j][k] -= coeff * upper[col][k];
					if (std::fabs(upper[j][k] / upper[col][col]) <
						utils::fp_tolerance)
						upper[j][k] = 0.0;
				}

#ifdef DUMP_MATRIX
				upper.dump();
#endif
			}
		}

#ifdef DUMP_MATRIX
		upper.dump();
#endif

		double determinant = 1.0;

		for (size_t id = 0; id < dim; ++id)
		{
			determinant *= upper[id][id];
		}

		return (swap_counter % 2 == 0) ? determinant : -determinant;
	}
};

} // namespace matrix

#endif
