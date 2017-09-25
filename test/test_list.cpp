
#include "catch.hpp"
#include "fixed/list.hpp"
#include "fixed/impl/fixed_def.hpp"
#include <string>
#include <cstring>
#include <list>

#include "test_struct.hpp"
#include "test_function_unary.hpp"

template <template <typename, fixed::_impl::container_size_type, template <typename, fixed::_impl::container_size_type> typename> typename LIST_T, 
	template <typename, fixed::_impl::container_size_type> typename Alloc_pattern >
void test_list()
{
	{ //constructor definition check
		auto expected = { 1, 2, 3, 4, 5 };

		LIST_TYPE<int, 20, Alloc_pattern> l;
		
		LIST_TYPE<int, 30, fixed::_impl::basic_heap_allocator> list_on_heap;
		l = list_on_heap;
		fixed::_impl::empty_source alloc_source_inst;
		LIST_TYPE<int, 20, Alloc_pattern> l_with_alloc_source(alloc_source_inst);
		LIST_TYPE<int, 20, Alloc_pattern> l_diff_with_alloc_source(list_on_heap, alloc_source_inst);
		l = l_with_alloc_source;
		l = expected;
		CHECK(std::equal(l.begin(), l.end(), expected.begin(), expected.end()));
		list_on_heap = expected;

		LIST_TYPE<int, 20, Alloc_pattern> l_diff_with_alloc_source_not_empty(list_on_heap, alloc_source_inst);
		CHECK(std::equal(l_diff_with_alloc_source_not_empty.begin(), l_diff_with_alloc_source_not_empty.end(), expected.begin(), expected.end()));


		LIST_TYPE<int, 20, Alloc_pattern> l_copy(l);
		CHECK(std::equal(l_copy.begin(), l_copy.end(), expected.begin(), expected.end()));

		LIST_TYPE<int, 20, Alloc_pattern> l_copy_alloc(l, alloc_source_inst);
		CHECK(std::equal(l_copy_alloc.begin(), l_copy_alloc.end(), expected.begin(), expected.end()));

		LIST_TYPE<int, 20, Alloc_pattern> l_move(std::move(l));
		CHECK(std::equal(l_move.begin(), l_move.end(), expected.begin(), expected.end()));
		CHECK(l.size() == 0);
		CHECK(l.empty());

		LIST_TYPE<int, 20, Alloc_pattern> l_move_alloc(std::move(l_move), alloc_source_inst);
		CHECK(std::equal(l_move_alloc.begin(), l_move_alloc.end(), expected.begin(), expected.end()));
		CHECK(l_move.size() == 0);
		CHECK(l_move.empty());

		LIST_TYPE<int, 20, Alloc_pattern> l_with_size(5);
		CHECK(l_with_size.size() == 5);
		LIST_TYPE<int, 20, Alloc_pattern> l_with_size_alloc(5, alloc_source_inst);
		CHECK(l_with_size_alloc.size() == 5);

		LIST_TYPE<int, 20, Alloc_pattern> l_with_values(5, 2);
		CHECK(l_with_values.size() == 5);
		CHECK(std::all_of(l_with_values.begin(), l_with_values.end(), [](const auto& v) {return v == 2; }));
		LIST_TYPE<int, 20, Alloc_pattern> l_with_values_alloc(5, 2, alloc_source_inst);
		CHECK(l_with_values_alloc.size() == 5);
		CHECK(std::all_of(l_with_values.begin(), l_with_values.end(), [](const auto& v) {return v == 2; }));

		LIST_TYPE<int, 20, Alloc_pattern> l_with_iterator(expected.begin(), expected.end());
		CHECK(l_with_iterator.size() == expected.size());
		CHECK(std::equal(l_with_iterator.begin(), l_with_iterator.end(), expected.begin(), expected.end()));
		LIST_TYPE<int, 20, Alloc_pattern> l_with_iterator_alloc(expected.begin(), expected.end(), alloc_source_inst);
		CHECK(l_with_iterator_alloc.size() == expected.size());
		CHECK(std::equal(l_with_iterator_alloc.begin(), l_with_iterator_alloc.end(), expected.begin(), expected.end()));

	}

	{
		LIST_TYPE<int, 20, Alloc_pattern> l1 = { 1, 2, 3, 4, 5 };
		auto expected = { 1, 2, 3, 4, 5 };
		CHECK(std::equal(l1.begin(), l1.end(), expected.begin(), expected.end()));
		LIST_TYPE<int, 20, Alloc_pattern> l2 = l1;
		CHECK(std::equal(l1.begin(), l1.end(), expected.begin(), expected.end()));
		CHECK(std::equal(l2.begin(), l2.end(), expected.begin(), expected.end()));
		LIST_TYPE<int, 20, Alloc_pattern> l3 = std::move(l2);
		CHECK(std::equal(l3.begin(), l3.end(), expected.begin(), expected.end()));
		CHECK(l2.empty());

		LIST_TYPE<int, 30, Alloc_pattern> l4 = l1;
	}

	{
		LIST_TYPE<int, 30, Alloc_pattern> l;
		auto expected = { 1, 1, 1, 1, 1 };
		l.assign(5, 1);
		CHECK(l.size() == 5);
		CHECK(std::equal(l.begin(), l.end(), expected.begin(), expected.end()));
	}

	{
		LIST_TYPE<int, 30, Alloc_pattern> l;
		auto expected = { 1, 1, 1, 1, 1 };
		l.assign(expected.begin(), expected.end());
		CHECK(l.size() == 5);
		CHECK(std::equal(l.begin(), l.end(), expected.begin(), expected.end()));
	}

	{
		LIST_TYPE<int, 30, Alloc_pattern> l;
		auto expected = { 1, 1, 1, 1, 1 };
		l.assign(expected);
		CHECK(l.size() == 5);
		CHECK(std::equal(l.begin(), l.end(), expected.begin(), expected.end()));
	}

	{
		LIST_TYPE<int, 30, Alloc_pattern> l;
		auto expected = { 1, 2, 3, 4, 5 };
		l.assign(expected.begin(), expected.end());
		CHECK(l.size() == 5);
		CHECK(std::equal(l.begin(), l.end(), expected.begin(), expected.end()));
		CHECK(l.front() == 1);
		CHECK(l.back() == 5);
		auto reverse_expected = { 5, 4, 3, 2, 1 };
		CHECK(std::equal(l.rbegin(), l.rend(), reverse_expected.begin(), reverse_expected.end()));
	}
}

template <template <typename, fixed::_impl::container_size_type, template <typename, fixed::_impl::container_size_type> typename> typename LIST_T,
	template <typename, fixed::_impl::container_size_type> typename Alloc_pattern>
void test_modifiers()
{
	{
		LIST_TYPE<int, 30, Alloc_pattern> l;
		CHECK(l.empty());
		auto expected = { 1, 2, 3, 4, 5 };
		l.assign(expected.begin(), expected.end());
		CHECK(!l.empty());
		l.clear();
		CHECK(l.empty());
	}

	{
		LIST_TYPE<int, 30, Alloc_pattern> l;
		auto expected = { 1, 2, 3, 4, 5 };
		l.assign(expected);

		auto result = l.insert(l.begin(), 0);
		auto exp1 = { 0, 1, 2, 3, 4, 5 };
		CHECK(l.size() == exp1.size());
		CHECK(std::equal(l.begin(), l.end(), exp1.begin(), exp1.end()));
		CHECK(*result == 0);

		auto result2 = l.insert(l.end(), 6);
		auto exp2 = { 0, 1, 2, 3, 4, 5, 6 };
		CHECK(l.size() == exp2.size());
		CHECK(std::equal(l.begin(), l.end(), exp2.begin(), exp2.end()));
		CHECK(*result2 == 6);

		auto result3 = l.insert(l.begin() + 1, 10);
		auto exp3 = { 0, 10, 1, 2, 3, 4, 5, 6 };
		CHECK(l.size() == exp3.size());
		CHECK(std::equal(l.begin(), l.end(), exp3.begin(), exp3.end()));
		CHECK(*result3 == 10);
	}

	{
		LIST_TYPE<int, 30, Alloc_pattern> l;
		auto init = { 1, 2, 3, 4, 5 };
		l.assign(init);

		auto& front = l.front();
		auto& next = *(l.begin() + 1);
		CHECK(front == 1);
		CHECK(next == 2);
		auto result = l.insert(l.begin() + 1, 2, 10);
		auto exp = { 1, 10, 10, 2, 3, 4, 5 };
		CHECK(l.size() == exp.size());
		CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
		CHECK(front == 1);
		CHECK(next == 2);
		auto& new_next = *(l.begin() + 1);
		CHECK(new_next == 10);
		CHECK(*result == 10);
	}

	{
		LIST_TYPE<int, 30, Alloc_pattern> l = { 1, 2, 3, 4, 5 };

		auto& pos0 = l.front();
		auto& pos1 = *(l.begin() + 1);
		auto& pos2 = *(l.begin() + 2);
		auto& pos3 = *(l.begin() + 3);

		CHECK(pos0 == 1);
		CHECK(pos1 == 2);
		CHECK(pos2 == 3);
		CHECK(pos3 == 4);

		auto to_insert = { 10, 11, 12 };
		auto result = l.insert(l.begin() + 2, to_insert.begin(), to_insert.end());
		auto exp = { 1, 2, 10, 11, 12, 3, 4, 5 };
		CHECK(l.size() == exp.size());
		CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));

		CHECK(pos0 == 1);
		CHECK(pos1 == 2);
		CHECK(pos2 == 3);
		CHECK(pos3 == 4);
		CHECK(*result == 10);
	}

	{
		LIST_TYPE<int, 30, Alloc_pattern> l = { 1, 2, 3, 4, 5 };

		auto to_insert = { 10, 11, 12 };
		auto result = l.insert(l.end(), to_insert.begin(), to_insert.end());
		auto exp = { 1, 2, 3, 4, 5, 10, 11, 12 };
		CHECK(l.size() == exp.size());
		CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
		CHECK(*result == 10);
	}

	{
		LIST_TYPE<int, 30, Alloc_pattern> l = { 1, 2, 3, 4, 5 };

		auto to_insert = { 10, 11, 12 };
		auto result = l.insert(l.end(), to_insert);
		auto exp = { 1, 2, 3, 4, 5, 10, 11, 12 };
		CHECK(l.size() == exp.size());
		CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
		CHECK(*result == 10);
	}

	{
		LIST_TYPE<test, 30, Alloc_pattern> l;
		const char* exp = "test";
		l.emplace_back("test");
		CHECK(std::equal(l.front()._val, l.front()._val + 4, exp, exp + 4));
	}

	{
		LIST_TYPE<test, 5, Alloc_pattern> l = {
			test{"toto"}, test{"titi"}, test{"tata"}
		};

		l.emplace(l.begin() + 1, "test");
		auto exp = {
			test{ "toto" }, test{"test"}, test{ "titi" }, test{ "tata" }
		};
		CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
	}
	
	test_erase<LIST_T, Alloc_pattern>();

	{
		LIST_TYPE<int, 5, Alloc_pattern> l{ 0, 1, 2, 3, 4 };
		auto& val = *(l.begin() + 4);
		CHECK(val == 4);
		l.erase(l.begin(), l.begin() + 4);
		auto exp = { 4 };
		CHECK(l.size() == exp.size());
		CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
		CHECK(val == 4);
	}


	test_push_back<LIST_T, Alloc_pattern>();
	test_emplace_back<LIST_T, Alloc_pattern>();
	test_pop_back<LIST_T, Alloc_pattern>();
	test_resize<LIST_T, Alloc_pattern>();
	test_push_front<LIST_T, Alloc_pattern>();
	test_emplace_front<LIST_T, Alloc_pattern>();
}

TEST_CASE("testing lists", "[linear]")
{
	test_list<fixed::list, fixed::_impl::basic_stack_allocator>();
	test_modifiers<fixed::list, fixed::_impl::basic_stack_allocator>();

	test_list<fixed::list, fixed::_impl::basic_heap_allocator>();
	test_modifiers<fixed::list, fixed::_impl::basic_heap_allocator>();
}
