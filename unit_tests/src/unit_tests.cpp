#include "buffer.h"       // for buffer_t, proxy_row_t
#include "matrix.h"       // for matrix_t, sq_matrix_t
#include "test_utils.h"   // for run_test

#include <gtest/gtest.h>  // for Test, TestInfo (ptr only), Message, CmpHelp...
#include <stddef.h>       // for size_t
#include <string>         // for basic_string
#include <utility>        // for move
#include <vector>         // for vector

class filled_buffer : public testing::Test
{
  protected:
    size_t rows_ = 3;
    size_t cols_ = 4;

    int value_ = 666;

    matrix::detail::buffer_t<int> buffer_{rows_, cols_, value_};
};

TEST_F(filled_buffer, is_filled)
{
    for (size_t row = 0; row < rows_; ++row)
    {
        for (size_t col = 0; col < cols_; ++col)
        {
            EXPECT_EQ(buffer_[row][col], value_);
        }
    }
}

TEST_F(filled_buffer, copy_ctor)
{
    matrix::detail::buffer_t<int> buffer_copy(buffer_);

    for (size_t row = 0; row < rows_; ++row)
    {
        for (size_t col = 0; col < cols_; ++col)
        {
            EXPECT_EQ(buffer_[row][col], buffer_copy[row][col]);
        }
    }
}

TEST_F(filled_buffer, copy_assign)
{
    matrix::detail::buffer_t<int> buffer_copy = buffer_;

    for (size_t row = 0; row < rows_; ++row)
    {
        for (size_t col = 0; col < cols_; ++col)
        {
            EXPECT_EQ(buffer_[row][col], buffer_copy[row][col]);
        }
    }
}

TEST_F(filled_buffer, move_ctor)
{
    matrix::detail::buffer_t<int> buffer_copy(std::move(buffer_));

    for (size_t row = 0; row < rows_; ++row)
    {
        for (size_t col = 0; col < cols_; ++col)
        {
            EXPECT_EQ(buffer_copy[row][col], value_);
        }
    }
}

TEST_F(filled_buffer, move_assign)
{
    matrix::detail::buffer_t<int> buffer_copy = std::move(buffer_);

    for (size_t row = 0; row < rows_; ++row)
    {
        for (size_t col = 0; col < cols_; ++col)
        {
            EXPECT_EQ(buffer_copy[row][col], value_);
        }
    }
}

class filled_matrix : public testing::Test
{
  protected:
    size_t rows_ = 3;
    size_t cols_ = 4;
    int value_ = 777;

    matrix::matrix_t<int> matrix_{rows_, cols_, value_};
};

TEST_F(filled_matrix, is_filled)
{
    for (size_t row = 0; row < rows_; ++row)
    {
        for (size_t col = 0; col < cols_; ++col)
        {
            EXPECT_EQ(matrix_[row][col], value_);
        }
    }
}

TEST_F(filled_matrix, change_element)
{
    int new_value = -1;

    size_t row_id = 2;
    size_t col_id = 3;
    matrix_[row_id][col_id] = new_value;

    EXPECT_EQ(matrix_[row_id][col_id], new_value);
}

namespace
{

class ndc_t
{
  private:
    [[maybe_unused]] int v_;

  public:
    ndc_t(int value)
        : v_(value)
    {}

    bool operator<=>(const ndc_t &other) const = default;
};

}; // namespace

class ndc_elem_buffer : public testing::Test
{
  protected:
    size_t rows_ = 3;
    size_t cols_ = 4;

    int value_ = 666;

    matrix::detail::buffer_t<ndc_t> buffer_{rows_, cols_, value_};
};

TEST_F(ndc_elem_buffer, is_filled)
{
    for (size_t row = 0; row < rows_; ++row)
    {
        for (size_t col = 0; col < cols_; ++col)
        {
            EXPECT_EQ(buffer_[row][col], value_);
        }
    }
}

TEST_F(ndc_elem_buffer, copy_ctor)
{
    matrix::detail::buffer_t<ndc_t> buffer_copy(buffer_);

    for (size_t row = 0; row < rows_; ++row)
    {
        for (size_t col = 0; col < cols_; ++col)
        {
            EXPECT_EQ(buffer_[row][col], buffer_copy[row][col]);
        }
    }
}

TEST_F(ndc_elem_buffer, copy_assign)
{
    matrix::detail::buffer_t<ndc_t> buffer_copy = buffer_;

    for (size_t row = 0; row < rows_; ++row)
    {
        for (size_t col = 0; col < cols_; ++col)
        {
            EXPECT_EQ(buffer_[row][col], buffer_copy[row][col]);
        }
    }
}

TEST_F(ndc_elem_buffer, move_ctor)
{
    matrix::detail::buffer_t<ndc_t> buffer_copy(std::move(buffer_));

    for (size_t row = 0; row < rows_; ++row)
    {
        for (size_t col = 0; col < cols_; ++col)
        {
            EXPECT_EQ(buffer_copy[row][col], value_);
        }
    }
}

TEST_F(ndc_elem_buffer, move_assign)
{
    matrix::detail::buffer_t<ndc_t> buffer_copy = std::move(buffer_);

    for (size_t row = 0; row < rows_; ++row)
    {
        for (size_t col = 0; col < cols_; ++col)
        {
            EXPECT_EQ(buffer_copy[row][col], value_);
        }
    }
}

TEST(matrix_basics, container_copy)
{
    std::vector<int> vec;

    for (int id = 0; id < 100; ++id)
        vec.push_back(id);

    size_t rows = 4;
    size_t cols = 10;

    matrix::matrix_t<int> matrix(rows, cols, vec.begin(), vec.end());

    size_t vec_id = 0;
    for (size_t row = 0; row < rows; ++row)
    {
        for (size_t col = 0; col < cols; ++col)
        {
            EXPECT_EQ(matrix[row][col], vec[vec_id]);
            ++vec_id;
        }
    }
}

TEST(matrix_basics, eye)
{
    size_t dim = 5;
    matrix::sq_matrix_t<int> matrix = matrix::sq_matrix_t<int>::eye(dim);

    for (size_t row = 0; row < dim; ++row)
    {
        for (size_t col = 0; col < dim; ++col)
        {
            if (col == row)
                EXPECT_EQ(matrix[row][col], 1);
            else
                EXPECT_EQ(matrix[row][col], 0);
        }
    }
}

TEST(matrix_basics, rand)
{
    size_t dim = 100;
    matrix::sq_matrix_t<double> matrix = matrix::sq_matrix_t<double>::rand(dim);
}

TEST(common, basic_1) { test_utils::run_test<double>("/common/basic_1"); }

TEST(common, basic_2) { test_utils::run_test<double>("/common/basic_2"); }

#ifdef ENABLE_BD_TESTS

TEST(bd_tests, dim_100) { test_utils::run_test<double>("/bd_tests/dim-100"); }
TEST(bd_tests, dim_150_1)
{
    test_utils::run_test<double>("/bd_tests/dim-150_1");
}
TEST(bd_tests, dim_150_2)
{
    test_utils::run_test<double>("/bd_tests/dim-150_2");
}
TEST(bd_tests, dim_150_3)
{
    test_utils::run_test<double>("/bd_tests/dim-150_3");
}

#endif
