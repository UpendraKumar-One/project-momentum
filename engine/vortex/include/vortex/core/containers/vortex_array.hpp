#pragma once

#include <memory>
#include <new>
#include <cassert>
#include <type_traits>
#include <utility>

namespace vortex::core
{
    template <typename T>
    class VArray
    {
    public:
        VArray(size_t cap)
            : m_capacity(cap), m_size(0)
        {
            m_rawBuffer = static_cast<T *>(::operator new(m_capacity * sizeof(T), std::align_val_t(alignof(T))));
        }

        VArray(const VArray &) = delete;
        VArray(VArray &&) = delete;
        VArray &operator=(const VArray &) = delete;
        VArray &operator=(VArray &&) = delete;

        ~VArray()
        {
            if constexpr (!std::is_trivially_destructible_v<T>)
            {
                for (size_t i = 0; i < m_size; ++i)
                {
                    m_rawBuffer[i].~T();
                }
            }
            ::operator delete(m_rawBuffer, std::align_val_t(alignof(T)));
        }

        T &push_back(const T &obj)
        {
            assert((m_size < m_capacity) && "Out of memory!");
            if (m_size >= m_capacity)
                throw std::bad_alloc();

            T *instantiated_obj = ::new (&m_rawBuffer[m_size]) T(obj);
            ++m_size;

            return *instantiated_obj;
        }

        T &push_back(T &&obj)
        {
            assert((m_size < m_capacity) && "Out of memory!");
            if (m_size >= m_capacity)
                throw std::bad_alloc();

            T *instantiated_obj = ::new (&m_rawBuffer[m_size]) T(std::move(obj));
            ++m_size;

            return *instantiated_obj;
        }

        void pop_back()
        {
            assert((m_size > 0) && "Empty Array!");
            if constexpr (!std::is_trivially_destructible_v<T>)
            {
                m_rawBuffer[--m_size].~T();
            }
        }

        const T &operator[](size_t i) const
        {
            assert(i < m_size && "index out of range!");
            return m_rawBuffer[i];
        }

        T &operator[](size_t i)
        {
            assert(i < m_size && "index out of range!");
            return m_rawBuffer[i];
        }

        size_t size() const
        {
            return m_size;
        }

        size_t capacity() const
        {
            return m_capacity;
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
            return Iterator(&m_rawBuffer[0]);
        }

        Iterator end()
        {
            return Iterator(&m_rawBuffer[m_size]);
        }

        T &back()
        {
            return m_rawBuffer[m_size - 1];
        }

    private:
        size_t m_capacity;
        size_t m_size;
        T *m_rawBuffer;
    };
}