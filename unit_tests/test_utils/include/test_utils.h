#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "test_utils_detail.h"
#include "utils.h"

#include <cmath>
#include <string>

#include <gtest/gtest.h> // for Test, TestInfo (ptr only), Message, TEST

namespace test_utils
{

const double answer_tol = 1e-4;

template <typename T> void run_test(const std::string &test_name)
{
    std::string test_folder = "data";

    std::string test_path =
        std::string(TEST_DATA_DIR) + test_folder + test_name;

    auto result = detail::get_result<T>(test_path + ".dat");
    double answer = detail::get_answer(test_path + ".ans");

	std::cout << "answer: " << result.value() << '\n';
	std::cout << "real answer: " << answer << '\n';

    EXPECT_TRUE(std::fabs(result.value() - answer) < answer_tol);
}

}; // namespace test_utils

#endif
