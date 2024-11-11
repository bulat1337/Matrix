#ifndef DETAIL
#define DETAIL

#include <algorithm>

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
        for (size_t id = 0; id < size_; ++id)
        {
            data_[id].~T();
        }

        operator delete(data_);
    }

  public:
    buffer_t() = default;

    buffer_t(size_t rows, size_t cols, const T &value)
        : size_(rows * cols)
        , cols_(cols)
    {
        data_ = reinterpret_cast<T *>(operator new(sizeof(T) * size_));

        for (size_t id = 0; id < size_; ++id)
        {
            new (data_ + id) T(value);
        }
    }

    buffer_t(size_t dim, const T &value)
        : size_(dim * dim)
        , cols_(dim)
        , data_(reinterpret_cast<T *>(operator new(sizeof(T) * size_)))
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
        , data_(reinterpret_cast<T *>(operator new(sizeof(T) * size_)))
    {
        Iter iter = begin;

        for (size_t id = 0; id < size_; ++id)
        {
            new (data_ + id) T(*iter);

            ++iter;

            if (iter == end)
                break;
        }
    }

    buffer_t(const buffer_t &other)
        : size_(other.size_)
        , cols_(other.cols_)
        , data_(reinterpret_cast<T *>(operator new(sizeof(T) * size_)))
    {
        for (size_t id = 0; id < size_; ++id)
        {
            new (data_ + id) T(other.data_[id]);
        }
    }

    buffer_t &operator=(buffer_t other)
    {
        swap(*this, other);

        return *this;
    }

    buffer_t(buffer_t &&other) noexcept
        : buffer_t()
    {
        swap(other);
    }

    proxy_row_t<T> operator[](size_t index)
    {
        return proxy_row_t<T>(data_ + index * cols_);
    }

	const proxy_row_t<T> operator[](size_t index) const
    {
        return proxy_row_t<T>(data_ + index * cols_);
    }

    void swap(buffer_t &other) noexcept
    {
        using std::swap;

        swap(this->data_, other.data_);
        swap(this->cols_, other.cols_);
        swap(this->size_, other.size_);
    }

    ~buffer_t() { clean_data(); }
};

template <typename T>
inline void swap(buffer_t<T> &lhs, buffer_t<T> &rhs) noexcept
{
    lhs.swap(rhs);
}

}; // namespace detail

}; // namespace matrix

#endif
