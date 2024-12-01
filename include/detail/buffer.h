#ifndef DETAIL
#define DETAIL

#include <algorithm>
#include <iostream>

#include "log.h"

namespace matrix
{

namespace detail
{

template <typename T>
class buffer_t
{
  protected:
	size_t size_ = 0;

	T *data_ = nullptr;
	size_t ctored_ = 0;

	buffer_t() = default;

	buffer_t(size_t size)
		: size_(size)
		, data_(static_cast<T *>(operator new(sizeof(T) * size)))
	{}

	buffer_t(const buffer_t &other) = delete;
	buffer_t &operator=(const buffer_t &other) = delete;

	buffer_t(buffer_t &&other) noexcept
		: buffer_t()
	{
		swap(other);
	}

	buffer_t &operator=(buffer_t &&other) noexcept
	{
		buffer_t moved(std::move(other));

		swap(*this, moved);

		return *this;
	}

	void swap(buffer_t &other) noexcept
	{
		using std::swap;

		swap(this->size_, other.size_);
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
