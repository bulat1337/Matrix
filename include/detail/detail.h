#ifndef DETAIL
#define DETAIL

#include <algorithm>

namespace matrix
{

namespace detail
{

template <typename T>
class proxy_row_t
{
  private:
	T* row_;
  public:
	proxy_row_t(T* row): row_(row) {}

	T& operator [] (size_t index) { return row_[index]; }
	const T& operator [] (size_t index) const { return row_[index]; }
};

template <typename T>
class buffer_t
{
  private:
	size_t size_ = 0;
	size_t cols_ = 0;
	T* data_ = nullptr;

  public:
	buffer_t(size_t rows, size_t cols, const T& value):
		  size_(rows * cols)
		, cols_(cols)
		, data_(new T[size_]{})
	{
		std::fill(data_, data_ + size_, value);
	}

	buffer_t(size_t dim, const T& value):
		  size_(dim * dim)
		, cols_(dim)
		, data_(new T[size_]{})
	{
		std::fill(data_, data_ + size_, value);
	}

	template <typename Iter>
	buffer_t(size_t rows, size_t cols, Iter begin, Iter end):
		  size_(rows * cols)
		, cols_(cols)
		, data_(new T[size_]{})
	{
		Iter iter = begin;

		for (size_t id = 0; id < size_; ++id)
		{
			data_[id] = *iter;

			++iter;

			if (iter == end) break;
		}
	}

	buffer_t(const buffer_t& other):
		  size_(other.size_)
		, cols_(other.cols_)
		, data_(new T[size_])
	{
		std::copy(other.data_, other.data_ + other.size_, data_);
	}

	buffer_t& operator = (const buffer_t& other)
	{
		delete[] data_;

		cols_ = other.cols_;
		size_ = other.size_;

		std::copy(other.data_, other.data_ + other.size_, data_);
	}

	buffer_t(buffer_t&& other):
		  size_(std::move(other.size_))
		, cols_(std::move(other.cols_))
		, data_(std::move(other.data_))
	{
		other.data_ = nullptr;
	}

	buffer_t& operator = (buffer_t&& other)
	{
		delete[] data_;

		cols_ = std::move(other.cols_);
		size_ = std::move(other.size_);
		data_ = std::move(other.data_);

		other.data_ = nullptr;
	}

	proxy_row_t<T> operator [] (size_t index)
	{
		return proxy_row_t<T>(data_ + index * cols_);
	}

	~buffer_t()
	{
		delete[] data_;
	}
};

};

};

#endif
