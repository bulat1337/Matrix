#ifndef PROXY_ROW_H
#define PROXY_ROW_H

#endif // PROXY_ROW_H

namespace matrix
{

namespace detail
{

template <typename T> class proxy_row_t
{
  private:
	T *row_;

  public:
	proxy_row_t(T *row)
		: row_(row)
	{}

	T &operator[](size_t index) { return row_[index]; }
	const T &operator[](size_t index) const { return row_[index]; }
};

};

};
