#include "matrix.h"

#include <iostream>

#include <gtest/gtest.h> // for Test, TestInfo (ptr only), Message, TEST
#include <string>        // for basic_string

class filled_buffer : public testing::Test
{
  protected:
	size_t rows_ = 3;
	size_t cols_ = 4;

	int value_   = 666;

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
	int value_   = 777;

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

// TEST(common, basic_1) { test_utils::run_test<double>("/common/basic_1"); }

#ifdef ENABLE_BS_TESTS

// TEST(bd_tests, amount_100000)
// {
//     test_utils::run_test<double>("/bd_tests/amount-100000");
// }

#endif
