#ifndef FIXED_VECTOR_ITERATORS_HPP
#define FIXED_VECTOR_ITERATORS_HPP

#include <cassert>

namespace fixed
{
namespace _impl
{
    template <typename T> struct pointer_iterator
    {
    public:
        typedef T value_type;
        typedef typename std::aligned_storage<sizeof(T), alignof(T)>::type
            aligned_type;
        typedef value_type* pointer;
        typedef value_type& reference;
        typedef std::ptrdiff_t difference_type;
        typedef std::random_access_iterator_tag iterator_category;

        bool operator==(const pointer_iterator& rval) const
        {
            return _value == rval._value;
        }

        bool operator!=(const pointer_iterator& rval) const
        {
            return !operator==(rval);
        }

		value_type* get() { return reinterpret_cast<value_type*>(_value); }
        const value_type* get() const
        {
            return reinterpret_cast<const value_type*>(_value);
        }

        reference operator*() const
        {
            assert(_value != nullptr);
            return reinterpret_cast<reference>(*_value);
        }

		value_type* operator->() { return get(); }
        const value_type* operator->() const { return get(); }

        pointer_iterator() = default;

        pointer_iterator(aligned_type* val)
            : _value(val)
        {
        }

        pointer_iterator(const pointer_iterator&) = default;
        pointer_iterator(pointer_iterator&&) noexcept = default;
        pointer_iterator& operator=(const pointer_iterator&) = default;
        pointer_iterator& operator=(pointer_iterator&&) noexcept = default;

        pointer_iterator& operator++()
        {
            assert(_value != nullptr);
            ++_value;
            return *this;
        }

        pointer_iterator operator++(int)
        {
            assert(_value != nullptr);
            pointer_iterator result = *this;
            ++(*this);
            return result;
        }

        pointer_iterator& operator--()
        {
            assert(_value != nullptr);
            --_value;
            return *this;
        }

        pointer_iterator operator--(int)
        {
            assert(_value != nullptr);
            pointer_iterator result = *this;
            --(*this);
            return result;
        }

        pointer_iterator& operator+=(difference_type n)
        {
            assert(_value != nullptr);
            _value += n;
            return *this;
        }

        pointer_iterator operator+(difference_type n) const
        {
            assert(_value != nullptr);
            return {_value + n};
        }

        pointer_iterator& operator-=(difference_type n)
        {
            assert(_value != nullptr);
            _value -= n;
            return *this;
        }

        pointer_iterator operator-(difference_type n) const
        {
            assert(_value != nullptr);
            return {_value - n};
        }

        difference_type operator-(const pointer_iterator& rval) const
        {
            return _value - rval._value;
        }

        reference operator[](difference_type n)
        {
            assert(_value != nullptr);
            return reinterpret_cast<reference>(_value[n]);
        }

        bool operator<(const pointer_iterator& rval) const
        {
            return _value < rval._value;
        }

        bool operator>(const pointer_iterator& rval) const
        {
            return _value > rval._value;
        }

        bool operator<=(const pointer_iterator& rval) const
        {
            return _value <= rval._value;
        }

        bool operator>=(const pointer_iterator& rval) const
        {
            return _value >= rval._value;
        }

    private:
        aligned_type* _value = nullptr;
    };

    template <typename T> struct const_pointer_iterator
    {
    public:
        typedef T value_type;
        typedef typename std::aligned_storage<sizeof(T), alignof(T)>::type
            aligned_type;
        typedef const T* pointer;
        typedef const T& reference;
        typedef std::ptrdiff_t difference_type;
        typedef std::random_access_iterator_tag iterator_category;

        bool operator==(const const_pointer_iterator& rval) const
        {
            return _value == rval._value;
        }

        bool operator!=(const const_pointer_iterator& rval) const
        {
            return !operator==(rval);
        }

        const value_type* get() const { return reinterpret_cast<value_type*>(_value); }

        const reference operator*() const
        {
            assert(_value != nullptr);
            return reinterpret_cast<const reference>(*_value);
        }

        const value_type* operator->() const { return get(); }

        const_pointer_iterator() = default;

        const_pointer_iterator(const aligned_type* val)
            : _value(const_cast<aligned_type*>(val))
        {
        }

        const_pointer_iterator(const const_pointer_iterator&) = default;
        const_pointer_iterator(const_pointer_iterator&&) noexcept = default;
        const_pointer_iterator& operator=(const const_pointer_iterator&)
            = default;
        const_pointer_iterator& operator=(const_pointer_iterator&&) noexcept
            = default;

		const_pointer_iterator(pointer_iterator<value_type>&& orig)
			: const_pointer_iterator(reinterpret_cast<const aligned_type*>(orig.get()))
		{
			orig = pointer_iterator<value_type>();
		}

        const_pointer_iterator(const pointer_iterator<value_type>& orig)
            : const_pointer_iterator(reinterpret_cast<const aligned_type*>(orig.get()))
        {
        }

        const_pointer_iterator& operator++()
        {
            assert(_value != nullptr);
            ++_value;
            return *this;
        }

        const_pointer_iterator operator++(int)
        {
            assert(_value != nullptr);
            const_pointer_iterator result = (*this);
            ++(*this);
            return result;
        }

        const_pointer_iterator& operator--()
        {
            assert(_value != nullptr);
            _value--;
            return *this;
        }

        const_pointer_iterator operator--(int)
        {
            assert(_value != nullptr);
            const_pointer_iterator result = (*this);
            --(*this);
            return result;
        }

        const_pointer_iterator& operator+=(difference_type n)
        {
            assert(_value != nullptr);
            _value += n;
            return *this;
        }

        const_pointer_iterator operator+(difference_type n) const
        {
            assert(_value != nullptr);
            return {_value + n};
        }

        const_pointer_iterator& operator-=(difference_type n)
        {
            assert(_value != nullptr);
            _value -= n;
            return *this;
        }

        const_pointer_iterator operator-(difference_type n) const
        {
            assert(_value != nullptr);
            return const_pointer_iterator(_value - n);
        }

        difference_type operator-(const const_pointer_iterator& rval) const
        {
            return _value - rval._value;
        }

        reference operator[](difference_type n)
        {
            assert(_value != nullptr);
            return reinterpret_cast<reference>(_value[n]);
        }

        bool operator<(const const_pointer_iterator& rval) const
        {
            return _value < rval._value;
        }

        bool operator>(const const_pointer_iterator& rval) const
        {
            return _value > rval._value;
        }

        bool operator<=(const const_pointer_iterator& rval) const
        {
            return _value <= rval._value;
        }

        bool operator>=(const const_pointer_iterator& rval) const
        {
            return _value >= rval._value;
        }

    private:
        aligned_type* _value = nullptr;
    };

	template <typename T>
	auto operator+(std::ptrdiff_t lval, const pointer_iterator<T>& rval)
	{
		return rval + lval;
	}

	template <typename T>
	auto operator+(std::ptrdiff_t lval, const const_pointer_iterator<T>& rval)
	{
		return rval + lval;
	}

}
}

#endif //! FIXED_VECTOR_ITERATORS_HPP