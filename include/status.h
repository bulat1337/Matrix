#ifndef STATUS_H
#define STATUS_H

namespace matrix {

enum class status_t { all_good, invalid_open };

inline bool check_status(status_t status) {
  if (status == status_t::all_good)
    return false;

  switch (status) {
  case status_t::all_good:
    return true;
  case status_t::invalid_open:
    std::cerr << "ERROR: Can not open file\n";
    break;
  default:
    std::cerr << "ERROR: Unknown\n";
  }

  return true;
}

}; // namespace matrix

#endif // STATUS_H
