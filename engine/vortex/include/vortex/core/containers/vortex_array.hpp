#pragma once

#include <memory>
#include <new>
#include <cassert>
#include <type_traits>
#include <utility>

namespace Vortex::Core
{
    template <typename T>
    class VArray
    {
    public:
        VArray(size_t cap)
            : i_capacity_(cap), i_size_(0)
        {
            mem_rawBuffer_ = static_cast<T *>(::operator new(i_capacity_ * sizeof(T), std::align_val_t(alignof(T))));
        }

        VArray(const VArray &) = delete;
        VArray(VArray &&) = delete;
        VArray &operator=(const VArray &) = delete;
        VArray &operator=(VArray &&) = delete;

        ~VArray()
        {
            if constexpr (!std::is_trivially_destructible_v<T>)
            {
                for (size_t i = 0; i < i_size_; ++i)
                {
                    mem_rawBuffer_[i].~T();
                }
            }
            ::operator delete(mem_rawBuffer_, std::align_val_t(alignof(T)));
        }

        T &push_back(const T &obj)
        {
            assert((i_size_ < i_capacity_) && "Out of memory!");
            if (i_size_ >= i_capacity_)
                throw std::bad_alloc();

            T *instantiated_obj = ::new (&mem_rawBuffer_[i_size_]) T(obj);
            ++i_size_;

            return *instantiated_obj;
        }

        T &push_back(T &&obj)
        {
            assert((i_size_ < i_capacity_) && "Out of memory!");
            if (i_size_ >= i_capacity_)
                throw std::bad_alloc();

            T *instantiated_obj = ::new (&mem_rawBuffer_[i_size_]) T(std::move(obj));
            ++i_size_;

            return *instantiated_obj;
        }

        void pop_back()
        {
            assert((i_size_ > 0) && "Empty Array!");
            if constexpr (!std::is_trivially_destructible_v<T>)
            {
                mem_rawBuffer_[--i_size_].~T();
            }
        }

        const T &operator[](size_t i) const
        {
            assert(i < i_size_ && "index out of range!");
            return mem_rawBuffer_[i];
        }

        T &operator[](size_t i)
        {
            assert(i < i_size_ && "index out of range!");
            return mem_rawBuffer_[i];
        }

        size_t size() const
        {
            return i_size_;
        }

        size_t capacity() const
        {
            return i_capacity_;
        }

        struct Iterator
        {
            using iterator_category = std::forward_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = T *;
            using reference = T &;

            pointer it_ptr;

            Iterator(pointer ptr)
                : it_ptr(ptr)
            {
            }

            Iterator &operator++()
            {
                ++it_ptr;
                return *this;
            }

            Iterator operator++(int)
            {
                Iterator tmp = *this;
                ++it_ptr;
                return tmp;
            }

            reference operator*() const
            {
                return *it_ptr;
            }

            pointer operator->()
            {
                return it_ptr;
            }

            friend bool operator==(const Iterator &a, const Iterator &b)
            {
                return a.it_ptr == b.it_ptr;
            }

            friend bool operator!=(const Iterator &a, const Iterator &b)
            {
                return a.it_ptr != b.it_ptr;
            }
        };

        Iterator begin()
        {
            return Iterator(&mem_rawBuffer_[0]);
        }

        Iterator end()
        {
            return Iterator(&mem_rawBuffer_[i_size_]);
        }

        T &back()
        {
            return mem_rawBuffer_[i_size_ - 1];
        }

    private:
        size_t i_capacity_;
        size_t i_size_;
        T *mem_rawBuffer_;
    };
}