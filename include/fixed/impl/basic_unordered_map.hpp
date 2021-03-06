#ifndef HEAPLESS_BASIC_UNORDERED_MAP_HPP
#define HEAPLESS_BASIC_UNORDERED_MAP_HPP

#include <algorithm>
#include <array>
#include <numeric>
#include <utility>
#include <cassert>

#include "fixed/impl/aligned_allocation_pattern.hpp"
#include "fixed/impl/fixed_def.hpp"
#include "fixed/impl/basic_pointer_iterator.hpp"

namespace fixed
{
	namespace _impl
	{
		template <typename Key, typename T, size_t SIZE,
			class Hash = std::hash<Key>, class Pred = std::equal_to<Key>,
			template <typename, size_t> typename Alloc_pattern
			= aligned_stack_allocator>
			class basic_unordered_map
		{
			// typedefs
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef std::pair<const key_type, mapped_type> value_type;
			typedef Hash hasher;
			typedef Pred key_equal;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef value_type* pointer;
			typedef const value_type* const_pointer;
			typedef size_t size_type;
			typedef std::ptrdiff_t difference_type;

			typedef pointer_iterator<value_type> iterator;
			typedef const_pointer_iterator<value_type> const_iterator;
			typedef std::reverse_iterator<iterator> reverse_iterator;
			typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

			template <typename Types, size_type ALLOC_SIZE>
			using allocator_type = Alloc_pattern<Types, ALLOC_SIZE>;

			basic_unordered_map()
			{
				setup_bucket();
			}

			~basic_unordered_map()
			{
				destruct_all();
			}

			std::size_t size() const {
				return _size;
			}

			T& operator[](const Key& key)
			{
				auto hash = _hash(key);
				auto it = std::next(_buckets.begin(), hash % _buckets.max_size());
				node* buck_ptr = *it;
				while (buck_ptr && buck_ptr->next_node && !_equal(buck_ptr->item->first, key))
				{
					buck_ptr = buck_ptr->next_node;
				}
				if (buck_ptr && _equal(buck_ptr->item->first, key))
				{
					return buck_ptr->item->second;
				}
				else
				{
					if (buck_ptr) {
						return allocate_new_node_in(buck_ptr->next_node, key);
					}
					else {
						return allocate_new_node_in(*it, key);
					}
				}
			}

		private:
			struct node
			{
				value_type* item;
				node* next_node;
			};

			/**
			* initialize bucket data with uninitialized value_type data
			*/
			void setup_bucket()
			{
				auto but_data_beg = _bucket_data.begin();
				auto but_data_end = _bucket_data.end();
				auto data_beg = _data.begin();
				auto data_end = _data.end();

				while (data_beg != data_end
					&& but_data_beg != but_data_end) //we do that until we run out of bucket or value_types
				{
					new(&*but_data_beg) node(); //Alloc_pattern distribute raw memory that need to be initialize
					but_data_beg->item = &(*data_beg); //raw memory of value_type will be initialized later
					data_beg = std::next(data_beg);
					but_data_beg = std::next(but_data_beg);
				}
			}

			T& allocate_new_node_in(node*& bucket, const Key& key, const T& val = T())
			{
				if (_size < _buckets.max_size())
				{
					bucket = &(*std::next(_bucket_data.begin(), _size)); //fetching the last in bucket_data : a bucket that don't own any used value_type
					_size++;
					new(bucket->item) value_type(key, val); //the bucket now own a proper value_type
					return bucket->item->second;
				}
				throw std::out_of_range("Container full");
			}

			void destruct_all()
			{
				std::for_each(_bucket_data.begin(), std::next(_bucket_data.begin(), _size), [](node& n)
				{
					n.item->~value_type();
				});
			}

			Alloc_pattern<node*, SIZE> _buckets; // real hash map to node
			Alloc_pattern<node, SIZE>
				_bucket_data; // compact index to data, handle memory recycling
			Alloc_pattern<value_type, SIZE> _data; // sparse data holder
			size_type _size
				= 0; // total size of initialized object & index to the next object
			hasher _hash; // hasher to compute index
			key_equal _equal; // compare to Key

		public:
			//! Warning : does nothing, no reallocation possible
			constexpr void reserve(size_type) {}
		};
	}
}

#endif //! HEAPLESS_BASIC_UNORDERED_MAP_HPP