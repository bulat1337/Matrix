#ifndef DETAIL
#define DETAIL

#include <algorithm>
#include <iostream>

#include "log.h"

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

template <typename T> class buffer_t
{
  protected:
    size_t size_ = 0;

    size_t cols_ = 0;
	size_t rows_ = 0;

    T *data_ = nullptr;
	size_t ctored_ = 0;

  public:
    buffer_t() = default;

    buffer_t(size_t rows, size_t cols)
        : size_(rows * cols)
        , cols_(cols)
		, rows_(rows)
		, data_(static_cast<T*>(operator new(sizeof(T) * size_))) {}

    buffer_t(const buffer_t &other) = delete;
	buffer_t &operator=(const buffer_t& other) = delete;

    buffer_t(buffer_t&& other) noexcept
        : buffer_t()
    {
        swap(other);
    }


	buffer_t &operator=(buffer_t&& other) noexcept
	{
		buffer_t moved(std::move(other));

		swap(*this, moved);

        return *this;
	}

    proxy_row_t<T> operator[](size_t index)
    {
        return proxy_row_t<T>(data_ + index * cols_);
    }

	proxy_row_t<const T> operator[](size_t index) const
    {
        return proxy_row_t<const T>(data_ + index * cols_);
    }

    void swap(buffer_t &other) noexcept
    {
        using std::swap;

        swap(this->size_, other.size_);
        swap(this->cols_, other.cols_);
        swap(this->rows_, other.rows_);
        swap(this->data_, other.data_);
        swap(this->ctored_, other.ctored_);
    }

    ~buffer_t()
	{
		for (size_t id = 0; id < ctored_; ++id)
		{
			data_[id].~T();
		}

		operator delete(data_);
		data_ = nullptr;
	}
};

template <typename T>
inline void swap(buffer_t<T> &lhs, buffer_t<T> &rhs) noexcept
{
    lhs.swap(rhs);
}


}; // namespace detail

}; // namespace matrix

#endif
