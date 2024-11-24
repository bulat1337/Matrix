#ifndef MATRIX_H
#define MATRIX_H

#include "buffer.h"
#include "log.h"
#include "utils.h"

#include <cmath>
#include <iostream>
#include <random>
#include <vector>


namespace matrix
{

template <typename T> class matrix_t
{
  protected:
    size_t rows_ = 0;
    size_t cols_ = 0;
    detail::buffer_t<T> data_;

  protected:
    bool pivot(size_t col, size_t &swap_counter)
    {
        T max_elem = std::fabs((*this)[col][col]);
        size_t max_id = col;

        for (size_t row = col; row < nrows(); ++row)
        {
            T elem = std::fabs((*this)[row][col]);
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
    matrix_t(size_t rows, size_t cols, const T &value = T{})
        : rows_(rows)
        , cols_(cols)
        , data_(rows, cols, value)
    {}

    template <typename Iter>
    matrix_t(size_t rows, size_t cols, Iter begin, Iter end)
        : rows_(rows)
        , cols_(cols)
        , data_(rows, cols, begin, end)
    {}

    detail::proxy_row_t<T> operator[](size_t index) { return data_[index]; }
    const detail::proxy_row_t<T> operator[](size_t index) const
    {
        return data_[index];
    }

    size_t nrows() const { return rows_; }
    size_t ncols() const { return cols_; }

    void dump(std::ostream &out = std::clog) const
    {
        for (size_t row = 0; row < rows_; ++row)
        {
            for (size_t col = 0; col < cols_; ++col)
            {
                out << data_[row][col] << "\t\t";
            }
            out << "\n\n";
        }
    }

    void swap_rows(size_t row1, size_t row2)
    {
        if (row1 == row2)
            return;
        for (size_t col = 0; col < cols_; ++col)
        {
            std::swap(data_[row1][col], data_[row2][col]);
        }
    }
};

template <typename T> class sq_matrix_t : public matrix_t<T>
{
  public:
    using matrix_t<T>::dump;
    using matrix_t<T>::rows_;
    using matrix_t<T>::cols_;

  public:
    sq_matrix_t(size_t dim, const T &value = T{})
        : matrix_t<T>(dim, dim, value)
    {}

    template <typename Iter>
    sq_matrix_t(size_t dim, Iter begin, Iter end)
        : matrix_t<T>(dim, dim, begin, end)
    {}

    static sq_matrix_t eye(size_t dim)
    {
        sq_matrix_t<T> result(dim);
        for (size_t id = 0; id < dim; ++id)
        {
            result.data_[id][id] = 1;
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
            result.data_[id][id] = static_cast<double>(distributor(gen)) / 10;
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

        size_t dim = rows_;
        sq_matrix_t<double> upper(*this);

        size_t swap_counter = 0;

        for (size_t col = 0; col < dim; ++col)
        {
            if (!upper.pivot(col, swap_counter))
                return 0.0;

            for (size_t j = col + 1; j < dim; j++)
            {
                LOG("coeff = {} / {}\n", upper[j][col], upper[col][col]);
                double coeff = upper[j][col] / upper[col][col];

                for (size_t k = col; k < dim; k++)
                {
                    LOG("{} -= {} * {}\n", upper[j][k], coeff, upper[col][k]);
                    upper[j][k] -= coeff * upper[col][k];
                    if (std::fabs(upper[j][k] / upper[col][col]) < utils::fp_tolerance)
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
