#ifndef FIXED_BASIC_LIST_ITERATOR_HPP
#define FIXED_BASIC_LIST_ITERATOR_HPP

#include <type_traits>
#include "fixed/impl/fixed_def.hpp"

namespace fixed
{
namespace _impl
{
    template <typename T, typename STORAGE_T> struct basic_listed_vector_iterator
    {
    public:
        typedef T value_type;
        typedef typename std::aligned_storage<sizeof(value_type),
            alignof(value_type)>::type aligned_type;
        typedef value_type* pointer;
        typedef value_type& reference;
        typedef std::ptrdiff_t difference_type;
        typedef std::random_access_iterator_tag iterator_category;

        bool operator==(const basic_listed_vector_iterator& rval) const
        {
            return _value == rval._value;
        }

        bool operator!=(const basic_listed_vector_iterator& rval) const
        {
            return !operator==(rval);
        }

        const STORAGE_T& get() const { return _value; }

        reference operator*() const
        {
            FIXED_CHECK_ITERATOR(_value != STORAGE_T());
            return reinterpret_cast<reference>(**_value);
        }

        pointer operator->() const
        {
            return reinterpret_cast<T*>(*_value);
        }

        basic_listed_vector_iterator() = default;

        basic_listed_vector_iterator(const STORAGE_T& val)
            : _value(val)
        {}

		basic_listed_vector_iterator(STORAGE_T&& val)
			: _value(std::move(val))
		{}

        basic_listed_vector_iterator(const basic_listed_vector_iterator&) = default;
        basic_listed_vector_iterator(basic_listed_vector_iterator&&) noexcept = default;
        basic_listed_vector_iterator& operator=(const basic_listed_vector_iterator&) = default;
        basic_listed_vector_iterator& operator=(basic_listed_vector_iterator&&) noexcept
            = default;

        basic_listed_vector_iterator& operator++()
        {
            FIXED_CHECK_ITERATOR(_value != STORAGE_T());
            ++_value;
            return *this;
        }

        basic_listed_vector_iterator operator++(int)
        {
            FIXED_CHECK_ITERATOR(_value != STORAGE_T());
            basic_listed_vector_iterator result = (*this);
            ++(*this);
            return result;
        }

        basic_listed_vector_iterator& operator--()
        {
            FIXED_CHECK_ITERATOR(_value != STORAGE_T());
            _value--;
            return *this;
        }

        basic_listed_vector_iterator operator--(int)
        {
            FIXED_CHECK_ITERATOR(_value != STORAGE_T());
            basic_listed_vector_iterator result = (*this);
            --(*this);
            return result;
        }

        basic_listed_vector_iterator& operator+=(difference_type n)
        {
            FIXED_CHECK_ITERATOR(_value != STORAGE_T() || n == 0); //Arithmetic with nullptr is probably not something you wanted to do
            _value += n;
            return *this;
        }

        basic_listed_vector_iterator operator+(difference_type n) const
        {
            FIXED_CHECK_ITERATOR(_value != STORAGE_T() || n == 0);
            return {_value + n};
        }

        basic_listed_vector_iterator& operator-=(difference_type n)
        {
            FIXED_CHECK_ITERATOR(_value != STORAGE_T() || n == 0);
            _value -= n;
            return *this;
        }

        basic_listed_vector_iterator operator-(difference_type n) const
        {
            FIXED_CHECK_ITERATOR(_value != STORAGE_T() || n == 0);
            return {_value - n};
        }

        difference_type operator-(const basic_listed_vector_iterator& rval) const
        {
            return _value - rval._value;
        }

        reference operator[](difference_type n)
        {
            FIXED_CHECK_ITERATOR(_value != nullptr);
            return reinterpret_cast<reference>(*_value[n]);
        }

        bool operator<(const basic_listed_vector_iterator& rval) const
        {
            return _value < rval._value;
        }

        bool operator>(const basic_listed_vector_iterator& rval) const
        {
            return _value > rval._value;
        }

        bool operator<=(const basic_listed_vector_iterator& rval) const
        {
            return _value <= rval._value;
        }

        bool operator>=(const basic_listed_vector_iterator& rval) const
        {
            return _value >= rval._value;
        }

    private:
        STORAGE_T _value = STORAGE_T();
    };

    template <typename T, typename STORAGE_T> struct const_basic_list_iterator
    {
    public:
        typedef T value_type;
        typedef const value_type* pointer;
        typedef const value_type& reference;
        typedef std::ptrdiff_t difference_type;
        typedef std::random_access_iterator_tag iterator_category;

        bool operator==(const const_basic_list_iterator& rval) const
        {
            return _value == rval._value;
        }

        bool operator!=(const const_basic_list_iterator& rval) const
        {
            return !operator==(rval);
        }

        const STORAGE_T* get() const { return _value; }

        reference operator*() const
        {
            FIXED_CHECK_ITERATOR(_value != nullptr);
            return **_value;
        }

        pointer operator->() const
        {
            return *_value;
        }

        const_basic_list_iterator() = default;

        const_basic_list_iterator(const STORAGE_T val)
            : _value(val)
        {
        }

        const_basic_list_iterator(const const_basic_list_iterator&) = default;
        const_basic_list_iterator(const_basic_list_iterator&&) noexcept = default;
        const_basic_list_iterator& operator=(const const_basic_list_iterator&) = default;
        const_basic_list_iterator& operator=(const_basic_list_iterator&&) noexcept = default;

		template <typename STO>
        const_basic_list_iterator(const basic_listed_vector_iterator<T, STO>& orig)
            : _value(orig.get())
        {
        }

		template <typename STO>
		const_basic_list_iterator(basic_listed_vector_iterator<T, STO>&& orig)
			: _value(orig.get())
		{
		}



        const_basic_list_iterator& operator++()
        {
            FIXED_CHECK_ITERATOR(_value != nullptr);
            ++_value;
            return *this;
        }

        const_basic_list_iterator operator++(int)
        {
            FIXED_CHECK_ITERATOR(_value != nullptr);
            const_basic_list_iterator result = (*this);
            ++(*this);
            return result;
        }

        const_basic_list_iterator& operator--()
        {
            FIXED_CHECK_ITERATOR(_value != nullptr);
            --_value;
            return *this;
        }

        const_basic_list_iterator operator--(int)
        {
            FIXED_CHECK_ITERATOR(_value != nullptr);
            const_basic_list_iterator result = (*this);
            --(*this);
            return result;
        }

        const_basic_list_iterator& operator+=(difference_type n)
        {
            FIXED_CHECK_ITERATOR(_value != STORAGE_T() || n == 0);
            _value += n;
            return *this;
        }

        const_basic_list_iterator operator+(difference_type n) const
        {
            FIXED_CHECK_ITERATOR(_value != STORAGE_T() || n == 0);
            return {_value + n};
        }

        const_basic_list_iterator& operator-=(difference_type n)
        {
            FIXED_CHECK_ITERATOR(_value != STORAGE_T() || n == 0);
            _value -= n;
            return *this;
        }

        const_basic_list_iterator operator-(difference_type n) const
        {
            FIXED_CHECK_ITERATOR(_value != STORAGE_T() || n == 0);
            return const_basic_list_iterator{_value - n};
        }

        difference_type operator-(const const_basic_list_iterator& rval) const
        {
            return _value - rval._value;
        }

        reference operator[](difference_type n)
        {
            FIXED_CHECK_ITERATOR(_value != STORAGE_T());

            return *_value[n];
        }

        bool operator<(const const_basic_list_iterator& rval) const
        {
            return _value < rval._value;
        }

        bool operator>(const const_basic_list_iterator& rval) const
        {
            return _value > rval._value;
        }

        bool operator<=(const const_basic_list_iterator& rval) const
        {
            return _value <= rval._value;
        }

        bool operator>=(const const_basic_list_iterator& rval) const
        {
            return _value >= rval._value;
        }

    private:
        STORAGE_T _value;
    };

    template <typename T, typename STO>
    auto operator+(std::ptrdiff_t lval, const basic_listed_vector_iterator<T, STO>& rval)
    {
        return rval + lval;
    }

    template <typename T, typename STO>
    auto operator+(
        std::ptrdiff_t lval, const const_basic_list_iterator<T, STO>& rval)
    {
        return rval + lval;
    }
}
}

#endif //! FIXED_BASIC_LIST_ITERATOR_HPP