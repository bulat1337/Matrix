#ifndef DETAIL_H
#define DETAIL_H

#include "matrix.h" // for Grid, calc_cell_size, get_triangles, inter...

namespace test_utils
{

namespace detail
{

inline std::string get_answer(const std::string &file_name)
{
    std::ifstream answer_file;

    answer_file.exceptions(std::ifstream::badbit);

    answer_file.open(file_name);

    std::string answer((std::istreambuf_iterator<char>(answer_file)),
                       std::istreambuf_iterator<char>());

    return answer;
}

template <typename T> std::string get_result(const std::string &file_name)
{
    t_inter::status_t status = t_inter::status_t::all_good;

    std::ifstream test_data;

    test_data.open(file_name);

    if (!test_data.is_open())
        status = t_inter::status_t::invalid_open;
    if (t_inter::check_status(status))
        return std::string();

    std::string result;

	// get result using lib

    return result;
}

}; // namespace detail

}; // namespace test_utils

#endif
