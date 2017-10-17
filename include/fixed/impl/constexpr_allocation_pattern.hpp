#ifndef FIXED_CONSTEXPR_ALLOCATION_PATTERN_HPP
#define FIXED_CONSTEXPR_ALLOCATION_PATTERN_HPP

#include "fixed/impl/fixed_def.hpp"
#include <cstddef>

namespace fixed
{
namespace _impl
{
    template <typename T, container_size_type SIZE>
    struct constexpr_stack_allocator
    {
        typedef T inner_type;

    public:
        static_assert(SIZE > 0, "zero sized container not allowed !");

		constexpr constexpr_stack_allocator() noexcept
			: _data()
		{}

        typedef T value_type;
        typedef T aligned_type;
        typedef allocation_pattern_tag allocation_pattern;
        typedef std::true_type noexcept_iterators;
        typedef pointer_iterator<T, aligned_type> iterator;
        typedef const_pointer_iterator<T, aligned_type> const_iterator;

        constexpr aligned_type* data() noexcept { return _data; }
        constexpr const aligned_type* data() const noexcept { return _data; }

        constexpr iterator begin() noexcept { return iterator(data()); }
        constexpr iterator end() noexcept { return iterator(data() + SIZE); }

        constexpr const_iterator begin() const noexcept { return cbegin(); }
        constexpr const_iterator end() const noexcept { return cend(); }
        constexpr const_iterator cbegin() const noexcept
        {
            return const_iterator(_data);
        }
        constexpr const_iterator cend() const noexcept
        {
            return const_iterator(_data + SIZE);
        }

        constexpr T& operator[](container_size_type i)
        {
            FIXED_CHECK_INBOUND(i < SIZE);
            return reinterpret_cast<T&>(_data[i]);
        }
        constexpr const T& operator[](container_size_type i) const
        {
            FIXED_CHECK_INBOUND(i < SIZE);
            return reinterpret_cast<const T&>(_data[i]);
        }

        constexpr bool valid_pointer(const T* ptr) const noexcept
        {
            return ptr >= data() && ptr < data() + max_size();
        }

        constexpr container_size_type max_size() const noexcept { return SIZE; }

    private:
        aligned_type _data[SIZE];
    };
}
}
#endif //! FIXED_CONSTEXPR_ALLOCATION_PATTERN_HPP