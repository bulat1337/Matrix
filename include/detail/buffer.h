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
  private:
    size_t size_ = 0;
    size_t cols_ = 0;
    T *data_ = nullptr;

  private:
    void clean_data()
    {
		if (data_)
		{
			for (size_t id = 0; id < size_; ++id)
			{
				data_[id].~T();
			}

			operator delete(data_);
			data_ = nullptr;
		}
    }

  public:
    buffer_t() = default;

    buffer_t(size_t rows, size_t cols, const T &value)
        : size_(rows * cols)
        , cols_(cols)
    {
        data_ = static_cast<T*>(operator new(sizeof(T) * size_));

        for (size_t id = 0; id < size_; ++id)
        {
            new (data_ + id) T(value);
        }
    }

    buffer_t(size_t di , const T &value)
        : size_(dim * dim)
        , cols_(dim)
        , data_(static_cast<T*>(operator new(sizeof(T) * size_)))
    {
        for (size_t id = 0; id < size_; ++id)
        {
            new (data_ + id) T(value);
        }
    }

    template <typename Iter>
    buffer_t(size_t rows, size_t cols, Iter begin, Iter end)
        : size_(rows * cols)
        , cols_(cols)
    {
		if (static_cast<size_t>(std::distance(begin, end)) < size_)
			throw std::logic_error(	"Not enough elements "
									"for matrix initialization");

		data_ = static_cast<T*>(operator new(sizeof(T) * size_));

        Iter iter = begin;

		size_t fill_id = 0;

		while (iter != end && fill_id < size_)
		{
			new (data_ + fill_id) T(*iter);

			++fill_id;
			++iter;
		}
    }

    buffer_t(const buffer_t &other)
        : size_(other.size_)
        , cols_(other.cols_)
        , data_(static_cast<T*>(operator new(sizeof(T) * size_)))
    {
        for (size_t id = 0; id < size_; ++id)
        {
            new (data_ + id) T(other.data_[id]); // throw here ???
        }
    }

    buffer_t(buffer_t&& other) noexcept
        : buffer_t()
    {
        swap(other);
    }

	buffer_t &operator=(const buffer_t& other)
	{
		buffer_t copy(other);

		swap(*this, copy);

        return *this;
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

        swap(this->data_, other.data_);
        swap(this->cols_, other.cols_);
        swap(this->size_, other.size_);
    }

    ~buffer_t()
	{
		MSG("Destructor called\n");
		clean_data();
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
