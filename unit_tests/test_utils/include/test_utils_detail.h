#ifndef DETAIL_H
#define DETAIL_H

#include <fstream>
#include <optional>

#include "matrix.h" // for Grid, calc_cell_size, get_triangles, inter...
#include "status.h"

namespace test_utils
{

namespace detail
{

inline double get_answer(const std::string &file_name)
{
	std::ifstream answer_file;

	answer_file.exceptions(std::ifstream::badbit);

	answer_file.open(file_name);

	double answer{};

	answer_file >> answer;

	return answer;
}

template <typename T>
std::optional<double> get_result(const std::string &file_name)
{
	matrix::status_t status = matrix::status_t::all_good;

	std::ifstream test_data;

	test_data.open(file_name);

	if (!test_data.is_open())
		status = matrix::status_t::invalid_open;
	if (matrix::check_status(status))
		return std::nullopt;

	size_t dim = 0;
	test_data >> dim;

	matrix::sq_matrix_t<double> matrix(dim);

	for (size_t row = 0; row < dim; ++row)
	{
		for (size_t col = 0; col < dim; ++col)
		{
			test_data >> matrix[row][col];
		}
	}

	return matrix.det();
}

}; // namespace detail

}; // namespace test_utils

#endif
