#ifndef FIXED_TEST_FUNCTIONS_UNARY_CONTAINERS_HPP
#define FIXED_TEST_FUNCTIONS_UNARY_CONTAINERS_HPP

#include "fixed/impl/fixed_def.hpp"
#include "test_struct.hpp"

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_noexcept_constructor()
{
    static_assert(fixed::_impl::is_nothrow_default_constructible_v<
                      CONTAINER_T<int, 10, Alloc_pattern>>,
        "Not noexcept default constructible");
    static_assert(fixed::_impl::is_nothrow_move_constructible_v<
                      CONTAINER_T<int, 10, Alloc_pattern>>,
        "Not noexcept move constructible");
    static_assert(fixed::_impl::is_nothrow_move_assignable_v<
                      CONTAINER_T<int, 10, Alloc_pattern>>,
        "Not noexcept move assignable");

    static_assert(fixed::_impl::is_nothrow_default_constructible_v<
                      CONTAINER_T<test_move, 10, Alloc_pattern>>,
        "Not noexcept default constructible");
    static_assert(fixed::_impl::is_nothrow_move_constructible_v<
                      CONTAINER_T<test_move, 10, Alloc_pattern>>,
        "Not noexcept move constructible");
    static_assert(fixed::_impl::is_nothrow_move_assignable_v<
                      CONTAINER_T<test_move, 10, Alloc_pattern>>,
        "Not noexcept move assignable");
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_canonical_constructor()
{
    // default constructor
    {
        CONTAINER_T<int, 20, Alloc_pattern> l;
        CONTAINER_T<test_move, 20, Alloc_pattern> lm;
    }

    fixed::_impl::empty_source alloc_source_inst;
    {
        CONTAINER_T<int, 20, Alloc_pattern> l(alloc_source_inst);
        CONTAINER_T<test_move, 20, Alloc_pattern> lm(alloc_source_inst);
    }

	{
		//CONTAINER_T<int, 20, Alloc_pattern> l(fixed::_impl::empty_source());
		//CONTAINER_T<test_move, 20, Alloc_pattern> lm(fixed::_impl::empty_source());
	}

    //! default constructor

    // copy constructor
    {
        auto exp = {1, 2, 3};
        CONTAINER_T<int, 20, Alloc_pattern> l;
        l.push_back(1);
        l.push_back(2);
        l.push_back(3);

        CHECK(l.size() == 3);
        CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));

        CONTAINER_T<int, 20, Alloc_pattern> r(l);

        CHECK(l.size() == 3);
        CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));

        CHECK(r.size() == 3);
        CHECK(std::equal(r.begin(), r.end(), exp.begin(), exp.end()));

#ifdef FIXED_CONTAINER_CHECK_BOUND
        try
        {
            CONTAINER_T<int, 1, Alloc_pattern> m(r);
            CHECK(false);
        }
        catch(std::exception&)
        {
        }
#endif

        CHECK(r.size() == 3);
        CHECK(std::equal(r.begin(), r.end(), exp.begin(), exp.end()));
    }

    {
        auto exp = {1, 2, 3};
        CONTAINER_T<int, 20, Alloc_pattern> l;
        l.push_back(1);
        l.push_back(2);
        l.push_back(3);

        CHECK(l.size() == 3);
        CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));

        CONTAINER_T<int, 20, Alloc_pattern> r(l, alloc_source_inst);

        CHECK(l.size() == 3);
        CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));

        CHECK(r.size() == 3);
        CHECK(std::equal(r.begin(), r.end(), exp.begin(), exp.end()));

		//CONTAINER_T<int, 20, Alloc_pattern> r1(l, fixed::_impl::empty_source());

#ifdef FIXED_CONTAINER_CHECK_BOUND
        try
        {
            CONTAINER_T<int, 1, Alloc_pattern> m(r, alloc_source_inst);
            CHECK(false);
        }
        catch(std::exception&)
        {
        }
#endif

        CHECK(r.size() == 3);
        CHECK(std::equal(r.begin(), r.end(), exp.begin(), exp.end()));
    }
    //! copy constructors
    // move constructors
    {
        auto exp = {1, 2, 3};
        CONTAINER_T<int, 20, Alloc_pattern> l;
        l.push_back(1);
        l.push_back(2);
        l.push_back(3);

        CHECK(l.size() == 3);
        CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));

        CONTAINER_T<int, 20, Alloc_pattern> r(std::move(l));

        CHECK(l.size() == 0);

        CHECK(r.size() == 3);
        CHECK(std::equal(r.begin(), r.end(), exp.begin(), exp.end()));

#ifdef FIXED_CONTAINER_CHECK_BOUND
        try
        {
            CONTAINER_T<int, 1, Alloc_pattern> m(std::move(r));
            CHECK(false);
        }
        catch(std::exception&)
        {
        }
#endif

        CHECK(r.size() == 3);
        CHECK(std::equal(r.begin(), r.end(), exp.begin(), exp.end()));
    }

    {
        auto exp = {1, 2, 3};
        CONTAINER_T<int, 20, Alloc_pattern> l;
        l.push_back(1);
        l.push_back(2);
        l.push_back(3);

        CHECK(l.size() == 3);
        CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));

        CONTAINER_T<int, 20, Alloc_pattern> r(std::move(l), alloc_source_inst);

        CHECK(l.size() == 0);

        CHECK(r.size() == 3);
        CHECK(std::equal(r.begin(), r.end(), exp.begin(), exp.end()));

		//CONTAINER_T<int, 20, Alloc_pattern> r1(std::move(l), fixed::_impl::empty_source());

#ifdef FIXED_CONTAINER_CHECK_BOUND
        try
        {
            CONTAINER_T<int, 1, Alloc_pattern> m(
                std::move(r), alloc_source_inst);
            CHECK(false);
        }
        catch(std::exception&)
        {
        }
#endif

        CHECK(r.size() == 3);
        CHECK(std::equal(r.begin(), r.end(), exp.begin(), exp.end()));
    }

    {
        auto exp = {"test", "titi", "toto"};
        CONTAINER_T<test_move, 20, Alloc_pattern> l;
        l.emplace_back("test");
        l.emplace_back("titi");
        l.emplace_back("toto");

        CHECK(l.size() == 3);
        CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));

        CONTAINER_T<test_move, 20, Alloc_pattern> r(std::move(l));

        CHECK(l.size() == 0);

        CHECK(r.size() == 3);
        CHECK(std::equal(r.begin(), r.end(), exp.begin(), exp.end()));

#ifdef FIXED_CONTAINER_CHECK_BOUND
        try
        {
            CONTAINER_T<test_move, 1, Alloc_pattern> m(std::move(r));
            CHECK(false);
        }
        catch(std::exception&)
        {
        }
#endif

        CHECK(r.size() == 3);
        CHECK(std::equal(r.begin(), r.end(), exp.begin(), exp.end()));
    }

    {
        auto exp = {"test", "titi", "toto"};
        CONTAINER_T<test_move, 20, Alloc_pattern> l;
        l.emplace_back("test");
        l.emplace_back("titi");
        l.emplace_back("toto");

        CHECK(l.size() == 3);
        CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));

        CONTAINER_T<test_move, 20, Alloc_pattern> r(
            std::move(l), alloc_source_inst);

        CHECK(l.size() == 0);

        CHECK(r.size() == 3);
        CHECK(std::equal(r.begin(), r.end(), exp.begin(), exp.end()));

#ifdef FIXED_CONTAINER_CHECK_BOUND
        try
        {
            CONTAINER_T<test_move, 1, Alloc_pattern> m(
                std::move(r), alloc_source_inst);
            CHECK(false);
        }
        catch(std::exception&)
        {
        }
#endif

        CHECK(r.size() == 3);
        CHECK(std::equal(r.begin(), r.end(), exp.begin(), exp.end()));
    }
    //! test move constructors
    // test init list constructors
    {
        auto exp = {0, 1, 2};
        CONTAINER_T<int, 20, Alloc_pattern> l{0, 1, 2};
        CHECK(l.size() == 3);
        CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
    }

    {
#ifdef FIXED_CONTAINER_CHECK_BOUND
        auto exp = {0, 1, 2};
        try
        {
            CONTAINER_T<int, 1, Alloc_pattern> l{0, 1, 2};
            CHECK(false);
        }
        catch(const std::exception&)
        {
        }
#endif
    }

    {
        auto exp = {0, 1, 2};
        CONTAINER_T<int, 20, Alloc_pattern> l(exp, alloc_source_inst);
        CHECK(l.size() == 3);
        CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));

		//CONTAINER_T<int, 20, Alloc_pattern> l1(exp, fixed::_impl::empty_source());

    }

#ifdef FIXED_CONTAINER_CHECK_BOUND
    {
        auto exp = {0, 1, 2};
        try
        {
            CONTAINER_T<int, 1, Alloc_pattern> l(exp, alloc_source_inst);
            CHECK(false);
        }
        catch(const std::exception&)
        {
        }
    }
#endif
    //! test init list constructors

    // test copy assignment
    {
        auto exp = {1, 2, 3};
        CONTAINER_T<int, 20, Alloc_pattern> l;
        l.push_back(1);
        l.push_back(2);
        l.push_back(3);

        CHECK(l.size() == exp.size());
        CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));

        {
            CONTAINER_T<int, 20, Alloc_pattern> r;
            r.push_back(4);
            r.push_back(5);
            r.push_back(6);
            r.push_back(7);

            auto r_exp = {4, 5, 6, 7};
            CHECK(r.size() == r_exp.size());
            CHECK(std::equal(r.begin(), r.end(), r_exp.begin(), r_exp.end()));

            r = l;

            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));

            CHECK(r.size() == exp.size());
            CHECK(std::equal(r.begin(), r.end(), exp.begin(), exp.end()));

            CONTAINER_T<int, 1, Alloc_pattern> m;
#ifdef FIXED_CONTAINER_CHECK_BOUND
            CHECK_THROWS(m = r);
#endif //!NDEBUG

            CHECK(r.size() == 3);
            CHECK(std::equal(r.begin(), r.end(), exp.begin(), exp.end()));
        }
        {
            CONTAINER_T<int, 10, Alloc_pattern> r1;
            r1.push_back(4);
            r1.push_back(5);
            r1.push_back(6);
            r1.push_back(7);

            auto r_exp = {4, 5, 6, 7};
            CHECK(r1.size() == r_exp.size());
            CHECK(std::equal(r1.begin(), r1.end(), r_exp.begin(), r_exp.end()));

            r1 = l;

            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));

            CHECK(r1.size() == exp.size());
            CHECK(std::equal(r1.begin(), r1.end(), exp.begin(), exp.end()));
        }
    }
    //! test copy assignement

    // test move assignement
    {
        auto exp = {"test", "titi", "toto"};
        CONTAINER_T<test_move, 20, Alloc_pattern> l;
        l.emplace_back("test");
        l.emplace_back("titi");
        l.emplace_back("toto");

        CHECK(l.size() == exp.size());
        CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));

        CONTAINER_T<test_move, 20, Alloc_pattern> r;
        r = std::move(l);

        CHECK(l.size() == 0);
        CHECK(r.size() == exp.size());
        CHECK(std::equal(r.begin(), r.end(), exp.begin(), exp.end()));

        CONTAINER_T<test_move, 1, Alloc_pattern> m;
#ifdef FIXED_CONTAINER_CHECK_BOUND
		CHECK_THROWS(m = std::move(r));
#endif
        CHECK(r.size() == exp.size());
        CHECK(std::equal(r.begin(), r.end(), exp.begin(), exp.end()));
    }

    {
        auto exp = {"test", "titi", "toto"};
        CONTAINER_T<test_move, 20, Alloc_pattern> l;
        l.emplace_back("test");
        l.emplace_back("titi");
        l.emplace_back("toto");

        CHECK(l.size() == exp.size());
        CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));

        CONTAINER_T<test_move, 10, Alloc_pattern> r;
        r = std::move(l);

        CHECK(l.size() == 0);
        CHECK(r.size() == exp.size());
        CHECK(std::equal(r.begin(), r.end(), exp.begin(), exp.end()));

        CONTAINER_T<test_move, 1, Alloc_pattern> m;
#ifdef FIXED_CONTAINER_CHECK_BOUND
		CHECK_THROWS(m = std::move(r));
#endif
        CHECK(r.size() == exp.size());
        CHECK(std::equal(r.begin(), r.end(), exp.begin(), exp.end()));
    }

    //! test move assignement
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_constructor()
{
    test_canonical_constructor<CONTAINER_T, Alloc_pattern>();
    { // constructor definition check
        auto expected = {1, 2, 3, 4, 5};

        CONTAINER_T<int, 20, Alloc_pattern> l;

        CONTAINER_T<int, 30, fixed::_impl::aligned_heap_allocator> list_on_heap;
        l = list_on_heap;

        fixed::_impl::empty_source alloc_source_inst;

        {
            CONTAINER_T<int, 20, Alloc_pattern> l_with_alloc_source(
                alloc_source_inst);

            CONTAINER_T<test_move, 20, Alloc_pattern> l_with_alloc_source_m(
                alloc_source_inst);

            l = l_with_alloc_source;
            l = expected;
            CHECK(std::equal(
                l.begin(), l.end(), expected.begin(), expected.end()));
        }

        CONTAINER_T<int, 20, Alloc_pattern> l_diff_with_alloc_source(
            list_on_heap, alloc_source_inst);

        list_on_heap = expected;

        CONTAINER_T<int, 20, Alloc_pattern> l_diff_with_alloc_source_not_empty(
            list_on_heap, alloc_source_inst);

        CHECK(std::equal(l_diff_with_alloc_source_not_empty.begin(),
            l_diff_with_alloc_source_not_empty.end(), expected.begin(),
            expected.end()));

        CONTAINER_T<int, 20, Alloc_pattern> l_copy(l);
        CHECK(std::equal(
            l_copy.begin(), l_copy.end(), expected.begin(), expected.end()));

        CONTAINER_T<int, 20, Alloc_pattern> l_copy_alloc(l, alloc_source_inst);
        CHECK(std::equal(l_copy_alloc.begin(), l_copy_alloc.end(),
            expected.begin(), expected.end()));

        CONTAINER_T<int, 20, Alloc_pattern> l_move(std::move(l));
        CHECK(std::equal(
            l_move.begin(), l_move.end(), expected.begin(), expected.end()));
        CHECK(l.size() == 0);
        CHECK(l.empty());

        {
            CONTAINER_T<test_move, 20, Alloc_pattern> origin;
            origin.push_back(test_move("test"));
            origin.push_back(test_move("toto"));
            origin.push_back(test_move("titi"));

            CHECK(origin.size() == 3);

            CONTAINER_T<test_move, 20, Alloc_pattern> l_test_move(
                std::move(origin));
            CHECK(origin.size() == 0);
            CHECK(l_test_move.size() == 3);

            auto exp = {"test", "toto", "titi"};
            CHECK(std::equal(l_test_move.begin(), l_test_move.end(),
                exp.begin(), exp.end()));
        }

        CONTAINER_T<int, 20, Alloc_pattern> l_move_alloc(
            std::move(l_move), alloc_source_inst);
        CHECK(std::equal(l_move_alloc.begin(), l_move_alloc.end(),
            expected.begin(), expected.end()));
        CHECK(l_move.size() == 0);
        CHECK(l_move.empty());

        CONTAINER_T<int, 20, Alloc_pattern> l_with_size(5);
        CHECK(l_with_size.size() == 5);
        CONTAINER_T<int, 20, Alloc_pattern> l_with_size_alloc(
            5, alloc_source_inst);
        CHECK(l_with_size_alloc.size() == 5);

        CONTAINER_T<int, 20, Alloc_pattern> l_with_values(5, 2);
        CHECK(l_with_values.size() == 5);
        CHECK(std::all_of(l_with_values.begin(), l_with_values.end(),
            [](const auto& v) { return v == 2; }));
        CONTAINER_T<int, 20, Alloc_pattern> l_with_values_alloc(
            5, 2, alloc_source_inst);
        CHECK(l_with_values_alloc.size() == 5);
        CHECK(std::all_of(l_with_values.begin(), l_with_values.end(),
            [](const auto& v) { return v == 2; }));

        CONTAINER_T<int, 20, Alloc_pattern> l_with_iterator(
            expected.begin(), expected.end());
        CHECK(l_with_iterator.size() == expected.size());
        CHECK(std::equal(l_with_iterator.begin(), l_with_iterator.end(),
            expected.begin(), expected.end()));
        CONTAINER_T<int, 20, Alloc_pattern> l_with_iterator_alloc(
            expected.begin(), expected.end(), alloc_source_inst);
        CHECK(l_with_iterator_alloc.size() == expected.size());
        CHECK(std::equal(l_with_iterator_alloc.begin(),
            l_with_iterator_alloc.end(), expected.begin(), expected.end()));
    }
    {
        CONTAINER_T<test_emplace_struct, 10, Alloc_pattern> test;
        std::vector<test_emplace_struct> vec_ref;

        unsigned int array_test[] = {1u, 2u};
        test.push_back(test_emplace_struct());
        vec_ref.push_back(test_emplace_struct());
        test.push_back({30, 'b', array_test});
        vec_ref.push_back({30, 'b', array_test});

        CONTAINER_T<test_emplace_struct, 10, Alloc_pattern> test2 = test;

        CHECK(std::equal(
            test.begin(), test.end(), vec_ref.begin(), vec_ref.end()));
        CHECK(std::equal(test.begin(), test.end(), test2.begin(), test2.end()));
    }

    {
        CONTAINER_T<std::string, 10, Alloc_pattern> words1{
            "the", "frogurt", "is", "also", "cursed"};
        {
            auto expected = {"the", "frogurt", "is", "also", "cursed"};
            CHECK(std::equal(words1.begin(), words1.end(), expected.begin(),
                expected.end()));
        }

        // words2 == words1
        CONTAINER_T<std::string, 10, Alloc_pattern> words2(
            words1.begin(), words1.end());
        {
            auto expected = {"the", "frogurt", "is", "also", "cursed"};
            CHECK(std::equal(words2.begin(), words2.end(), expected.begin(),
                expected.end()));
        }
    }

    {
        // c++11 initializer list syntax:
        CONTAINER_T<std::string, 10, Alloc_pattern> words1{
            "the", "frogurt", "is", "also", "cursed"};
        {
            auto expected = {"the", "frogurt", "is", "also", "cursed"};
            CHECK(std::equal(words1.begin(), words1.end(), expected.begin(),
                expected.end()));
        }

        // words2 == words1
        CONTAINER_T<std::string, 10, Alloc_pattern> words2(
            words1.begin(), words1.end());
        {
            auto expected = {"the", "frogurt", "is", "also", "cursed"};
            CHECK(std::equal(words2.begin(), words2.end(), expected.begin(),
                expected.end()));
        }

        // words3 == words1
        CONTAINER_T<std::string, 10, Alloc_pattern> words3(words1);
        {
            auto expected = {"the", "frogurt", "is", "also", "cursed"};
            CHECK(std::equal(words3.begin(), words3.end(), expected.begin(),
                expected.end()));
        }
    }

    {
        // c++11 initializer list syntax:
        CONTAINER_T<std::string, 5, Alloc_pattern> words1{
            "the", "frogurt", "is", "also", "cursed"};
        {
            auto expected = {"the", "frogurt", "is", "also", "cursed"};
            CHECK(std::equal(words1.begin(), words1.end(), expected.begin(),
                expected.end()));
        }

        // words2 == words1
        CONTAINER_T<std::string, 10, Alloc_pattern> words2(
            words1.begin(), words1.end());
        {
            auto expected = {"the", "frogurt", "is", "also", "cursed"};
            CHECK(std::equal(words2.begin(), words2.end(), expected.begin(),
                expected.end()));
        }

        // words3 == words1
        CONTAINER_T<std::string, 10, Alloc_pattern> words3(words1);
        {
            auto expected = {"the", "frogurt", "is", "also", "cursed"};
            CHECK(std::equal(words3.begin(), words3.end(), expected.begin(),
                expected.end()));
        }

        // words4 is {"Mo", "Mo", "Mo", "Mo", "Mo"}
        CONTAINER_T<std::string, 10, Alloc_pattern> words4(5, "Mo");
        {
            auto expected = {"Mo", "Mo", "Mo", "Mo", "Mo"};
            CHECK(std::equal(words4.begin(), words4.end(), expected.begin(),
                expected.end()));
        }
    }
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_operator_assignment()
{
    {
        CONTAINER_T<int, 10, Alloc_pattern> nums1{3, 1, 4, 6, 5, 9};
        CONTAINER_T<int, 2, Alloc_pattern> nums2;
#ifdef FIXED_CONTAINER_CHECK_BOUND
		CHECK_THROWS(nums2 = nums1);
#endif
    }

    {
        CONTAINER_T<test_move, 10, Alloc_pattern> r;
        r.emplace_back("test");
        CONTAINER_T<test_move, 10, Alloc_pattern> l;
        l = std::move(r);
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> nums1{3, 1, 4, 6, 5, 9};
        CONTAINER_T<int, 6, Alloc_pattern> nums2;
        CONTAINER_T<int, 20, Alloc_pattern> nums3;

        auto exp = {3, 1, 4, 6, 5, 9};
        CHECK(nums1.size() == 6);
        CHECK(std::equal(nums1.begin(), nums1.end(), exp.begin(), exp.end()));
        CHECK(nums2.size() == 0);
        CHECK(nums3.size() == 0);
        // copy assignment copies data from nums1 to nums2
        nums2 = nums1;

        CHECK(nums1.size() == 6);
        CHECK(std::equal(nums1.begin(), nums1.end(), exp.begin(), exp.end()));
        CHECK(nums2.size() == 6);
        CHECK(std::equal(nums2.begin(), nums2.end(), exp.begin(), exp.end()));
        CHECK(nums3.size() == 0);
        // move assignment moves data from nums1 to nums3,
        // modifying both nums1 and nums3
        nums3 = std::move(nums1);

        CHECK(nums1.size() == 0);
        CHECK(nums2.size() == 6);
        CHECK(std::equal(nums2.begin(), nums2.end(), exp.begin(), exp.end()));
        CHECK(nums3.size() == 6);
        CHECK(std::equal(nums3.begin(), nums3.end(), exp.begin(), exp.end()));
    }

    {
        CONTAINER_T<int, 20, Alloc_pattern> l1 = {1, 2, 3, 4, 5};
        auto expected = {1, 2, 3, 4, 5};
        CHECK(
            std::equal(l1.begin(), l1.end(), expected.begin(), expected.end()));
        CONTAINER_T<int, 20, Alloc_pattern> l2 = l1;
        CHECK(
            std::equal(l1.begin(), l1.end(), expected.begin(), expected.end()));
        CHECK(
            std::equal(l2.begin(), l2.end(), expected.begin(), expected.end()));
        CONTAINER_T<int, 20, Alloc_pattern> l3 = std::move(l2);
        CHECK(
            std::equal(l3.begin(), l3.end(), expected.begin(), expected.end()));
        CHECK(l2.empty());
    }

    {
        CONTAINER_T<int, 20, Alloc_pattern> l1 = {1, 2, 3, 4, 5};
        CONTAINER_T<int, 20, Alloc_pattern> l2 = {1, 2, 3};

        l1 = l2;
        auto exp = {1, 2, 3};
        CHECK(l1.size() == l2.size());
        CHECK(std::equal(l1.begin(), l1.end(), l2.begin(), l2.end()));
        CHECK(std::equal(exp.begin(), exp.end(), l2.begin(), l2.end()));
    }

    {
        CONTAINER_T<int, 20, Alloc_pattern> l1 = {1, 2, 3, 4, 5};
        CONTAINER_T<int, 20, Alloc_pattern> l2 = {9, 8, 6, 4, 3, 5, 6};

        l1 = l2;
        auto exp = {9, 8, 6, 4, 3, 5, 6};
        CHECK(l1.size() == l2.size());
        CHECK(std::equal(l1.begin(), l1.end(), l2.begin(), l2.end()));
        CHECK(std::equal(exp.begin(), exp.end(), l2.begin(), l2.end()));
    }

    {
        CONTAINER_T<int, 20, Alloc_pattern> l1 = {1, 2, 3, 4, 5};
        CONTAINER_T<int, 10, Alloc_pattern> l2 = {1, 2, 3};

        l1 = l2;
        auto exp = {1, 2, 3};
        CHECK(l1.size() == l2.size());
        CHECK(std::equal(l1.begin(), l1.end(), l2.begin(), l2.end()));
        CHECK(std::equal(exp.begin(), exp.end(), l2.begin(), l2.end()));
    }

    {
        CONTAINER_T<int, 20, Alloc_pattern> l1 = {1, 2, 3, 4, 5};
        CONTAINER_T<int, 10, Alloc_pattern> l2 = {9, 8, 6, 4, 3, 5, 6};

        l1 = l2;
        auto exp = {9, 8, 6, 4, 3, 5, 6};
        CHECK(l1.size() == l2.size());
        CHECK(std::equal(l1.begin(), l1.end(), l2.begin(), l2.end()));
        CHECK(std::equal(exp.begin(), exp.end(), l2.begin(), l2.end()));
    }
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_destructor()
{
    {
        int i = 0;
        {
            CONTAINER_T<test_construct, 5, Alloc_pattern> c;
            for(typename CONTAINER_T<test_construct, 5,
                    Alloc_pattern>::size_type v
                = 0;
                v < c.max_size(); v++)
            {
                c.push_back(test_construct(i));
            }
            CHECK(c.size() == c.max_size());
            CHECK(c.size() == 5);
            CHECK(c.empty() == false);
            CHECK(i == 5);
        }
        CHECK(i == 0);
    }
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_begin_end()
{
    {
        CONTAINER_T<int, 20, Alloc_pattern> vec{
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        CHECK(std::distance(vec.begin(), vec.end()) > 0);
        CHECK(static_cast<std::size_t>(std::distance(vec.begin(), vec.end()))
            == vec.size());
    }

    {
        CONTAINER_T<int, 20, Alloc_pattern> vec{
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        auto beg = vec.begin();
        auto end = vec.end();
        typename CONTAINER_T<int, 20, Alloc_pattern>::size_type i = 0;

        CHECK(beg != end);

        while(i < vec.size())
        {
            CHECK(beg < end);
            CHECK((beg + i) != end);
            ++i;
        }
    }

    {
        CONTAINER_T<int, 20, Alloc_pattern> vec{
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        auto beg = vec.begin();
        auto end = vec.end();

        CHECK(beg <= end);
        ++beg;
        CHECK(beg < end);
        beg++;
        CHECK(end > beg);
        beg = beg + 1;
        CHECK(end >= beg);
        CHECK(beg != end);
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> myvector = {10, 20, 30, 40, 50};

        auto expected = {10, 20, 30, 40, 50};
        int i = 0;
        for(auto it = myvector.cbegin(); it != myvector.cend(); ++it)
        {
            CHECK(*it == *(expected.begin() + i));
            i++;
        }
    }
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_rbegin_rend()
{
    CONTAINER_T<int, 20, Alloc_pattern> vec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    {
        auto reverse = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        CHECK(std::equal(
            vec.rbegin(), vec.rend(), reverse.begin(), reverse.end()));
    }

    {
        CHECK(static_cast<std::size_t>(std::distance(vec.rbegin(), vec.rend()))
            == vec.size());
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> myvector(
            5); // 5 default-constructed ints

        int i = 0;

        typename CONTAINER_T<int, 10, Alloc_pattern>::reverse_iterator rit
            = myvector.rbegin();
        for(; rit != myvector.rend(); ++rit)
            *rit = ++i;
        CHECK(i == 5);
        for(typename CONTAINER_T<int, 10, Alloc_pattern>::iterator it
            = myvector.begin();
            it != myvector.end(); ++it)
        {
            CHECK(*it == i);
            i--;
        }
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> myvector(5);

        typename CONTAINER_T<int, 10, Alloc_pattern>::reverse_iterator rbit
            = myvector.rbegin();
        typename CONTAINER_T<int, 10, Alloc_pattern>::reverse_iterator reit
            = myvector.rend();
        typename CONTAINER_T<int, 10, Alloc_pattern>::iterator it
            = myvector.begin() + (myvector.size() - 1);
        int i = 0;
        while(rbit != reit)
        {
            CHECK(&*it == &*rbit);
            --it;
            ++rbit;
            ++i;
        }
        CHECK(i == 5);
    }
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_front()
{
    {
        CONTAINER_T<int, 10, Alloc_pattern> c = {10, 20, 30, 40, 50};
        CHECK(c.front() == 10);
    }

    {
        const CONTAINER_T<int, 10, Alloc_pattern> c = {10, 20, 30, 40, 50};
        CHECK(c.front() == 10);
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> c = {10, 20, 30, 40, 50};
        CHECK(c.front() == (*c.begin()));
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> c;
#ifdef FIXED_CONTAINER_CHECK_BOUND
		CHECK_THROWS(c.front());
#endif
    }
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_back()
{
    {
        CONTAINER_T<int, 10, Alloc_pattern> c = {10, 20, 30, 40, 50};
        CHECK(c.back() == 50);
    }

    {
        const CONTAINER_T<int, 10, Alloc_pattern> c = {10, 20, 30, 40, 50};
        CHECK(c.back() == 50);
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> c = {10, 20, 30, 40, 50};
        CHECK(c.back() == (*--c.end()));
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> c;
#ifdef FIXED_CONTAINER_CHECK_BOUND
		CHECK_THROWS(c.back());
#endif
    }
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_operator_array()
{
    {
        CONTAINER_T<int, 10, Alloc_pattern> myvector = {10, 20, 30, 40, 50};

        auto expected = {10, 20, 30, 40, 50};
        for(std::size_t i = 0; i < expected.size(); i++)
        {
            CHECK(myvector[i] == *(expected.begin() + i));
        }
    }

    {
        const CONTAINER_T<int, 10, Alloc_pattern> myvector
            = {10, 20, 30, 40, 50};

        auto expected = {10, 20, 30, 40, 50};
        for(std::size_t i = 0; i < expected.size(); i++)
        {
            CHECK(myvector[i] == *(expected.begin() + i));
        }
    }
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_at()
{
    {
        CONTAINER_T<int, 10, Alloc_pattern> myvector = {10, 20, 30, 40, 50};

        auto expected = {10, 20, 30, 40, 50};
        for(std::size_t i = 0; i < expected.size(); i++)
        {
            CHECK(myvector.at(i) == *(expected.begin() + i));
        }

        CHECK(myvector.front() == 10);
        CHECK(myvector.back() == 50);
#ifdef FIXED_CONTAINER_CHECK_BOUND
		CHECK_THROWS(myvector.at(myvector.max_size() + 1));
#endif
    }

    {
        const CONTAINER_T<int, 10, Alloc_pattern> myvector
            = {10, 20, 30, 40, 50};

        auto expected = {10, 20, 30, 40, 50};
        for(std::size_t i = 0; i < expected.size(); i++)
        {
            CHECK(myvector.at(i) == *(expected.begin() + i));
        }

        CHECK(myvector.front() == 10);
        CHECK(myvector.back() == 50);
#ifdef FIXED_CONTAINER_CHECK_BOUND
		CHECK_THROWS(myvector.at(myvector.max_size() + 1));
#endif
    }
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_vector_data()
{
    {
        static_assert(
            std::is_same<typename Alloc_pattern<int, 10>::aligned_type,
                typename CONTAINER_T<int, 10,
                    Alloc_pattern>::aligned_type>::value,
            "vector aligned_type is supposed to be the same of it's "
            "Alloc_pattern");
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> myvector = {10, 20, 30, 40, 50};
        int* ptr = reinterpret_cast<int*>(myvector.data());

        {
            auto beg = myvector.begin();
            auto end = myvector.end();
            typename CONTAINER_T<int, 10, Alloc_pattern>::size_type i = 0;

            while(beg != end)
            {
                CHECK(ptr + i == &*beg);
                ++i;
                ++beg;
            }
        }

        myvector.erase(myvector.begin() + 2);

        {
            auto beg = myvector.begin();
            auto end = myvector.end();
            typename CONTAINER_T<int, 10, Alloc_pattern>::size_type i = 0;

            while(beg != end)
            {
                CHECK(ptr + i == &*beg);
                ++i;
                ++beg;
            }
        }
    }
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_clear()
{
    {
        CONTAINER_T<int, 10, Alloc_pattern> c = {10, 20, 30, 40, 50};

        CHECK(c.size() == 5);
        CHECK(c.empty() == false);
        c.clear();
        CHECK(c.size() == 0);
        CHECK(c.empty() == true);
    }

    {
        int i = 0;
        CONTAINER_T<test_construct, 10, Alloc_pattern> c;
        c.emplace_back(i);
        c.emplace_back(i);
        c.emplace_back(i);
        c.emplace_back(i);
        CHECK(c.size() == 4);
        CHECK(c.empty() == false);
        CHECK(i == 4);
        c.clear();
        CHECK(c.size() == 0);
        CHECK(c.empty() == true);
        CHECK(i == 0);
    }
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_assign()
{
    {
        CONTAINER_T<char, 5, Alloc_pattern> characters;

        characters.assign(5, 'a');

        CHECK(characters.size() == 5);
        int iteration = 0;
        for(auto& c : characters)
        {
            CHECK(c == 'a');
            iteration++;
        }
        CHECK(iteration == 5);
    }

    {
        CONTAINER_T<int, 30, Alloc_pattern> l;
        auto expected = {1, 1, 1, 1, 1};
        l.assign(5, 1);
        CHECK(l.size() == 5);
        CHECK(std::equal(l.begin(), l.end(), expected.begin(), expected.end()));
    }

    {
        CONTAINER_T<int, 15, Alloc_pattern> l;
        for(auto i = l.size(); i <= l.max_size(); i++)
        {
            l.assign(i, 1);
            CHECK(l.size() == i);
            CHECK(std::all_of(
                l.begin(), l.end(), [](auto& val) { return val == 1; }));
        }

        for(auto i = l.max_size(); i > 0; i--)
        {
            l.assign(i, 1);
            CHECK(l.size() == i);
            CHECK(std::all_of(
                l.begin(), l.end(), [](auto& val) { return val == 1; }));
        }
#ifdef FIXED_CONTAINER_CHECK_BOUND
		CHECK_THROWS(l.assign(l.max_size() + 1, 1));
#endif
    }

    {
        CONTAINER_T<int, 30, Alloc_pattern> l;
        auto expected = {1, 1, 1, 1, 1};
        l.assign(expected.begin(), expected.end());
        CHECK(l.size() == 5);
        CHECK(std::equal(l.begin(), l.end(), expected.begin(), expected.end()));
    }

    {
        CONTAINER_T<int, 1, Alloc_pattern> l;
        auto expected = {1, 1, 1, 1, 1};
#ifdef FIXED_CONTAINER_CHECK_BOUND
		CHECK_THROWS(l.assign(expected));
#endif
    }

    {
        CONTAINER_T<int, 30, Alloc_pattern> l;
        auto expected = {1, 2, 3, 4, 5};
        l.assign(expected.begin(), expected.end());
        CHECK(l.size() == 5);
        CHECK(std::equal(l.begin(), l.end(), expected.begin(), expected.end()));
        CHECK(l.front() == 1);
        CHECK(l.back() == 5);
        auto reverse_expected = {5, 4, 3, 2, 1};
        CHECK(std::equal(l.rbegin(), l.rend(), reverse_expected.begin(),
            reverse_expected.end()));
    }

    {
        CONTAINER_T<int, 30, Alloc_pattern> l;
        CHECK(l.empty());
        auto expected = {1, 2, 3, 4, 5};
        l.assign(expected.begin(), expected.end());
        CHECK(!l.empty());
        l.clear();
        CHECK(l.empty());
    }
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_generic_capacity()
{
    {
        CONTAINER_T<int, 10, Alloc_pattern> c;

        CHECK(c.empty());
        c = {10, 20, 30, 40, 50};
        CHECK(!c.empty());
        CHECK(c.size() == 5);
        c.clear();
        CHECK(c.empty());
        CHECK(c.max_size() >= 10);
#ifdef FIXED_CONTAINER_CHECK_BOUND
		CHECK_THROWS(c.resize(c.max_size() + 1));
#endif
    }
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_vector_capacity_func()
{
    CONTAINER_T<int, 10, Alloc_pattern> c;

    c.shrink_to_fit();
    CHECK(c.capacity() >= 10);
    c.reserve(10);
    CHECK(c.capacity() >= 10);
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_insert()
{
    {
        CONTAINER_T<int, 30, Alloc_pattern> l;
        auto expected = {1, 2, 3, 4, 5};
        l.assign(expected);

        auto result = l.insert(l.begin(), 0);
        auto exp1 = {0, 1, 2, 3, 4, 5};
        CHECK(l.size() == exp1.size());
        CHECK(std::equal(l.begin(), l.end(), exp1.begin(), exp1.end()));
        CHECK(*result == 0);

        auto result2 = l.insert(l.end(), 6);
        auto exp2 = {0, 1, 2, 3, 4, 5, 6};
        CHECK(l.size() == exp2.size());
        CHECK(std::equal(l.begin(), l.end(), exp2.begin(), exp2.end()));
        CHECK(*result2 == 6);

        auto result3 = l.insert(l.begin() + 1, 10);
        auto exp3 = {0, 10, 1, 2, 3, 4, 5, 6};
        CHECK(l.size() == exp3.size());
        CHECK(std::equal(l.begin(), l.end(), exp3.begin(), exp3.end()));
        CHECK(*result3 == 10);
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> l;

        for(auto i = l.size(); i < l.max_size(); i++)
        {
            l.insert(l.begin(), int(i));
        }
        auto exp = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        CHECK(l.size() == exp.size());
        CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
#ifdef FIXED_CONTAINER_CHECK_BOUND
		CHECK_THROWS(l.insert(l.begin(), int(1)));
#endif
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> l;

        for(auto i = l.size(); i < l.max_size(); i++)
        {
            l.insert(l.end(), int(i));
        }
        auto exp = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        CHECK(l.size() == exp.size());
        CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
#ifdef FIXED_CONTAINER_CHECK_BOUND
		CHECK_THROWS(l.insert(l.end(), int(1)));
#endif
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> l;

        for(auto i = l.size(); i < l.max_size(); i++)
        {
            l.insert(l.end(), int(i));
        }
        auto exp = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        CHECK(l.size() == exp.size());
        CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
#ifdef FIXED_CONTAINER_CHECK_BOUND
		CHECK_THROWS(l.insert(l.end(), int(1)));
#endif
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> l = {0};

        for(auto i = l.size(); i < l.max_size(); i++)
        {
            l.insert(l.begin() + 1, int(i));
        }
        auto exp = {0, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        CHECK(l.size() == exp.size());
        CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
#ifdef FIXED_CONTAINER_CHECK_BOUND
		CHECK_THROWS(l.insert(l.end(), int(1)));
#endif
    }

    {
        CONTAINER_T<int, 30, Alloc_pattern> l = {1, 2, 3, 4, 5};

        auto to_insert = {10, 11, 12};
        auto result = l.insert(l.end(), to_insert.begin(), to_insert.end());
        auto exp = {1, 2, 3, 4, 5, 10, 11, 12};
        CHECK(l.size() == exp.size());
        CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        CHECK(*result == 10);
    }

    {
        CONTAINER_T<int, 30, Alloc_pattern> l = {1, 2, 3, 4, 5};

        auto to_insert = {10, 11, 12};
        auto result = l.insert(l.end(), to_insert);
        auto exp = {1, 2, 3, 4, 5, 10, 11, 12};
        CHECK(l.size() == exp.size());
        CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        CHECK(*result == 10);
    }
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_erase()
{
    {
        CONTAINER_T<int, 10, fixed::_impl::aligned_stack_allocator> v
            = {0, 1, 2, 3, 4};
#ifdef FIXED_CONTAINER_CHECK_BOUND
		CHECK_THROWS(v.erase(v.end()));
#endif
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::vector<int> expected{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

        c.erase(c.begin());
        expected.erase(expected.begin());
        CHECK(std::equal(c.begin(), c.end(), expected.begin(), expected.end()));

        expected.erase(expected.begin() + 2, expected.begin() + 5);
        c.erase(c.begin() + 2, c.begin() + 5);

        CHECK(std::equal(c.begin(), c.end(), expected.begin(), expected.end()));

        expected.erase(expected.begin() + (expected.size() - 1));
        c.erase(c.begin() + (c.size() - 1));
        CHECK(c.size() == expected.size());
        CHECK(std::equal(c.begin(), c.end(), expected.begin(), expected.end()));
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> v = {0, 1, 2, 3, 4};
        auto it = v.erase(v.begin());
        auto exp = {1, 2, 3, 4};
        CHECK(v.size() == exp.size());
        CHECK(std::equal(v.begin(), v.end(), exp.begin(), exp.end()));
        CHECK(*it == 1);
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> v = {0, 1, 2, 3, 4};
        auto it = v.erase(v.begin() + 1);
        auto exp = {0, 2, 3, 4};
        CHECK(v.size() == exp.size());
        CHECK(std::equal(v.begin(), v.end(), exp.begin(), exp.end()));
        CHECK(*it == 2);
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> v = {0, 1, 2, 3, 4};
        auto it = v.erase(v.begin() + 2);
        auto exp = {0, 1, 3, 4};
        CHECK(v.size() == exp.size());
        CHECK(std::equal(v.begin(), v.end(), exp.begin(), exp.end()));
        CHECK(*it == 3);
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> v = {0, 1, 2, 3, 4};
        auto it = v.erase(v.begin() + 3);
        auto exp = {0, 1, 2, 4};
        CHECK(v.size() == exp.size());
        CHECK(std::equal(v.begin(), v.end(), exp.begin(), exp.end()));
        CHECK(*it == 4);
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> v = {0, 1, 2, 3, 4};
        auto it = v.erase(v.begin() + 4);
        auto exp = {0, 1, 2, 3};
        CHECK(v.size() == exp.size());
        CHECK(std::equal(v.begin(), v.end(), exp.begin(), exp.end()));
        CHECK(it == v.end());
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> v = {0, 1, 2, 3, 4};
        auto it = v.erase(v.begin() + 0, v.begin() + 2);
        auto exp = {2, 3, 4};
        CHECK(v.size() == exp.size());
        CHECK(std::equal(v.begin(), v.end(), exp.begin(), exp.end()));
        CHECK(*it == 2);
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> v = {0, 1, 2, 3, 4};
        auto it = v.erase(v.begin() + 1, v.begin() + 3);
        auto exp = {0, 3, 4};
        CHECK(v.size() == exp.size());
        CHECK(std::equal(v.begin(), v.end(), exp.begin(), exp.end()));
        CHECK(*it == 3);
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> v = {0, 1, 2, 3, 4};
        auto it = v.erase(v.begin() + 2, v.begin() + 4);
        auto exp = {0, 1, 4};
        CHECK(v.size() == exp.size());
        CHECK(std::equal(v.begin(), v.end(), exp.begin(), exp.end()));
        CHECK(*it == 4);
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> v = {0, 1, 2, 3, 4};
        auto it = v.erase(v.begin() + 3, v.begin() + 5);
        auto exp = {0, 1, 2};
        CHECK(v.size() == exp.size());
        CHECK(std::equal(v.begin(), v.end(), exp.begin(), exp.end()));
        CHECK(it == v.end());
    }

    {
        CONTAINER_T<int, 5, Alloc_pattern> l{0, 1, 2, 3, 4};
        auto result = l.erase(l.begin());
        auto exp = {1, 2, 3, 4};
        CHECK(l.size() == exp.size());
        CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        CHECK(*result == 1);

        while(l.size())
        {
            l.erase(l.begin());
        }
#ifdef FIXED_CONTAINER_CHECK_BOUND
		CHECK_THROWS(l.erase(l.end()));
#endif
    }

    {
        CONTAINER_T<int, 5, Alloc_pattern> l{0, 1, 2, 3, 4};
        l.erase(l.begin(), l.begin() + 5);
        CHECK(l.empty());
    }

    {
        CONTAINER_T<int, 5, Alloc_pattern> l{0, 1, 2, 3, 4};
        l.erase(l.begin() + 1, l.begin() + 5);
        auto exp = {0};
        CHECK(l.size() == exp.size());
        CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
    }
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_resize()
{
    {
        int v = 0;
        {
            CONTAINER_T<test_construct, 5, Alloc_pattern> l;
            for(typename CONTAINER_T<int, 5, Alloc_pattern>::size_type i = 0;
                i < l.max_size(); i++)
            {
                l.resize(i, test_construct(v));
                CHECK(l.size() == i);
                CHECK(v == int(i));
            }
        }
        CHECK(v == 0);
    }

    {
        CONTAINER_T<int, 5, Alloc_pattern> l;
        for(typename CONTAINER_T<int, 5, Alloc_pattern>::size_type i = 0;
            i < l.max_size(); i++)
        {
            l.resize(i);
            CHECK(l.size() == i);
        }
    }

    {
        CONTAINER_T<int, 5, Alloc_pattern> l;

        for(typename CONTAINER_T<int, 5, Alloc_pattern>::size_type i = 0;
            i <= l.max_size(); i++)
        {
            l.resize(i);
            CHECK(l.size() == i);
        }
        for(typename CONTAINER_T<int, 5, Alloc_pattern>::size_type i
            = l.max_size();
            i > 0; i--)
        {
            l.resize(i);
            CHECK(l.size() == i);
        }
    }

    {
        CONTAINER_T<int, 5, Alloc_pattern> l;
#ifdef FIXED_CONTAINER_CHECK_BOUND
		CHECK_THROWS(l.resize(l.max_size() + 1));
#endif
    }
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_push_front()
{
    {
        CONTAINER_T<int, 5, Alloc_pattern> l;
        l.push_front(0);
        {
            auto exp = {0};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
        l.push_front(1);
        {
            auto exp = {1, 0};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
        l.push_front(2);
        {
            auto exp = {2, 1, 0};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
        l.push_front(3);
        {
            auto exp = {3, 2, 1, 0};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
        l.push_front(4);
        {
            auto exp = {4, 3, 2, 1, 0};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
#ifdef FIXED_CONTAINER_CHECK_BOUND
		CHECK_THROWS(l.push_front(5));
#endif
    }

    {
        CONTAINER_T<test_move, 5, Alloc_pattern> l;
        test_move m("test");
        l.push_front(std::move(m));
        CHECK(m._val == nullptr);
    }
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_emplace_front()
{
    {
        CONTAINER_T<int, 5, Alloc_pattern> l;
        l.emplace_front(0);
        {
            auto exp = {0};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
        l.emplace_front(1);
        {
            auto exp = {1, 0};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
        l.emplace_front(2);
        {
            auto exp = {2, 1, 0};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
        l.emplace_front(3);
        {
            auto exp = {3, 2, 1, 0};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
        l.emplace_front(4);
        {
            auto exp = {4, 3, 2, 1, 0};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
#ifdef FIXED_CONTAINER_CHECK_BOUND
		CHECK_THROWS(l.emplace_front(5));
#endif
    }

    {
        unsigned int val = 1;
        CONTAINER_T<test_emplace_struct, 5, Alloc_pattern> l;
        l.emplace_front(2, 'c', &val);
    }
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_push_back()
{
    {
        CONTAINER_T<std::size_t, 5, Alloc_pattern> l;

        for(typename CONTAINER_T<std::size_t, 5, Alloc_pattern>::size_type i
            = 0;
            i < l.max_size(); i++)
        {
            l.push_back(i);
            CHECK(l.size() == i + 1);
            CHECK(l.back() == i);
        }
#ifdef FIXED_CONTAINER_CHECK_BOUND
		CHECK_THROWS(l.push_back(0u));
#endif
    }

    {
        CONTAINER_T<std::size_t, 5, Alloc_pattern> l;
        l.push_back(0);
        {
            auto exp = {0u};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
        l.push_back(1);
        {
            auto exp = {0u, 1u};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
        l.push_back(2);
        {
            auto exp = {0u, 1u, 2u};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
        l.push_back(3);
        {
            auto exp = {0u, 1u, 2u, 3u};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
        l.push_back(4);
        {
            auto exp = {0u, 1u, 2u, 3u, 4u};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
#ifdef FIXED_CONTAINER_CHECK_BOUND
		CHECK_THROWS(l.push_back(5));
#endif
    }

    {
        CONTAINER_T<test_move, 5, Alloc_pattern> l;
        l.push_back(test_move("test"));
        CHECK(l.size() == 1);
        test_move val("toto");
        l.push_back(std::move(val));
        CHECK(val._val == nullptr);
        CHECK(l.size() == 2);
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> myvector;
        for(int i = 1; i <= 5; i++)
            myvector.push_back(i);

        int i = 1;
        for(typename CONTAINER_T<int, 10, Alloc_pattern>::iterator it
            = myvector.begin();
            it != myvector.end(); ++it)
        {
            CHECK(*it == i);
            i++;
        }
    }
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_emplace_back()
{
    {
        CONTAINER_T<std::size_t, 5, Alloc_pattern> l;

        for(typename CONTAINER_T<std::size_t, 5, Alloc_pattern>::size_type i
            = 0;
            i < l.max_size(); i++)
        {
            l.emplace_back(i);
            CHECK(l.size() == i + 1);
            CHECK(l.back() == i);
        }
#ifdef FIXED_CONTAINER_CHECK_BOUND
		CHECK_THROWS(l.emplace_back(0u));
#endif
    }

    {
        CONTAINER_T<std::size_t, 5, Alloc_pattern> l;
        l.emplace_back(0);
        {
            auto exp = {0u};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
        l.emplace_back(1);
        {
            auto exp = {0u, 1u};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
        l.emplace_back(2);
        {
            auto exp = {0u, 1u, 2u};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
        l.emplace_back(3);
        {
            auto exp = {0u, 1u, 2u, 3u};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
        l.emplace_back(4);
        {
            auto exp = {0u, 1u, 2u, 3u, 4u};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
#ifdef FIXED_CONTAINER_CHECK_BOUND
		CHECK_THROWS(l.emplace_back(5));
#endif
    }

    {
        CONTAINER_T<test_move, 5, Alloc_pattern> l;
        l.emplace_back(test_move("test"));
        CHECK(l.size() == 1);
        test_move val("toto");
        l.emplace_back(std::move(val));
        CHECK(val._val == nullptr);
        CHECK(l.size() == 2);
    }

    {
        unsigned int val;
        CONTAINER_T<test_emplace_struct, 5, Alloc_pattern> l;
        l.emplace_back(0, 'c', &val);
        CHECK(l.size() == 1);
        test_emplace_struct exp{0, 'c', &val};
        CHECK(l.back() == exp);
    }
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_pop_back()
{
    {
        CONTAINER_T<std::size_t, 5, Alloc_pattern> l;

        for(typename CONTAINER_T<std::size_t, 5, Alloc_pattern>::size_type i
            = 0;
            i < l.max_size(); i++)
        {
            l.emplace_back(i);
            CHECK(l.size() == i + 1);
            CHECK(l.back() == i);
        }
        for(typename CONTAINER_T<std::size_t, 5, Alloc_pattern>::size_type i
            = 0;
            i < l.max_size(); i++)
        {
            CHECK(l.size() == 5 - i);
            CHECK(l.back() == 4 - i);
            l.pop_back();
        }
    }

    {
        CONTAINER_T<int, 5, Alloc_pattern> l = {0, 1, 2, 3, 4};
        l.pop_back();
        {
            auto exp = {0, 1, 2, 3};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
        l.pop_back();
        {
            auto exp = {0, 1, 2};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
        l.pop_back();
        {
            auto exp = {0, 1};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
        l.pop_back();
        {
            auto exp = {0};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
        l.pop_back();
        CHECK(l.size() == 0);
#ifdef FIXED_CONTAINER_CHECK_BOUND
		CHECK_THROWS(l.pop_back());
#endif
    }

    {
        int val = 0;
        CONTAINER_T<test_construct, 5, Alloc_pattern> l(5, test_construct(val));
        CHECK(val == 5);

        for(int i = 0; i < 5; i++)
        {
            l.pop_back();
            CHECK(val == int(l.size()));
        }
    }
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_swap()
{
    {
        CONTAINER_T<int, 5, Alloc_pattern> lval{1, 2, 3};
        CONTAINER_T<int, 4, Alloc_pattern> rval{3, 4};

        auto exp1 = {1, 2, 3};
        auto exp2 = {3, 4};
        lval.swap(rval);

        CHECK(lval.size() == exp2.size());
        CHECK(std::equal(lval.begin(), lval.end(), exp2.begin(), exp2.end()));
        CHECK(rval.size() == exp1.size());
        CHECK(std::equal(rval.begin(), rval.end(), exp1.begin(), exp1.end()));
    }

    {
        CONTAINER_T<int, 5, Alloc_pattern> lval{1, 2, 3, 4, 5};
        CONTAINER_T<int, 4, Alloc_pattern> rval{3, 4};
#ifdef FIXED_CONTAINER_CHECK_BOUND
		CHECK_THROWS(lval.swap(rval));
#endif
    }
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_emplace()
{
    {
        CONTAINER_T<test, 5, Alloc_pattern> l
            = {test{"toto"}, test{"titi"}, test{"tata"}};

        l.emplace(l.begin() + 1, "test");
        auto exp = {test{"toto"}, test{"test"}, test{"titi"}, test{"tata"}};
        CHECK(l.size() == exp.size());
        CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
    }

    {
        unsigned int val;
        CONTAINER_T<test_emplace_struct, 5, Alloc_pattern> l
            = {test_emplace_struct{0, 'a', &val},
                test_emplace_struct{1, 'z', &val},
                test_emplace_struct{2, 'e', &val}};

        l.emplace(l.end(), 3, 'r', &val);
        {
            auto exp = {test_emplace_struct{0, 'a', &val},
                test_emplace_struct{1, 'z', &val},
                test_emplace_struct{2, 'e', &val},
                test_emplace_struct{3, 'r', &val}};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
        l.emplace(l.end(), 4, 't', &val);
        {
            auto exp = {test_emplace_struct{0, 'a', &val},
                test_emplace_struct{1, 'z', &val},
                test_emplace_struct{2, 'e', &val},
                test_emplace_struct{3, 'r', &val},
                test_emplace_struct{4, 't', &val}};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
#ifdef FIXED_CONTAINER_CHECK_BOUND
        CHECK_THROWS(l.emplace(l.end(), 5, 'y', &val));
#endif
    }

    {
        CONTAINER_T<test_move, 5, Alloc_pattern> l;

        l.emplace(l.end(), test_move("test"));
        test_move mov("test");
        l.emplace(l.end(), std::move(mov));
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> l{1, 2, 4};
        auto result = l.emplace(l.begin() + 2, 3);
        {
            auto exp = {1, 2, 3, 4};
            CHECK(*result == 3);
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
        result = l.emplace(l.begin() + 4, 5);
        {
            auto exp = {1, 2, 3, 4, 5};
            CHECK(*result == 5);
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
        result = l.emplace(l.begin(), 0);
        {
            auto exp = {0, 1, 2, 3, 4, 5};
            CHECK(*result == 0);
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        }
    }
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_list_constant_reference()
{
    {
        CONTAINER_T<int, 5, Alloc_pattern> l{0, 1, 2, 3, 4};
        auto& val = *(l.begin() + 4);
        CHECK(val == 4);
        l.erase(l.begin(), l.begin() + 4);
        {
            auto exp = {4};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
            CHECK(val == 4);
        }
        l.push_front(0);
        auto& val0 = *(l.begin());
        {
            auto exp = {0, 4};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
            CHECK(val == 4);
            CHECK(val0 == 0);
        }
        l.push_front(1);
        auto& val1 = *(l.begin());
        {
            auto exp = {1, 0, 4};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
            CHECK(val == 4);
            CHECK(val0 == 0);
            CHECK(val1 == 1);
        }
    }

    {
        CONTAINER_T<int, 30, Alloc_pattern> l;
        auto init = {1, 2, 3, 4, 5};
        l.assign(init);

        auto& front = l.front();
        auto& next = *(l.begin() + 1);
        CHECK(front == 1);
        CHECK(next == 2);
        auto result = l.insert(l.begin() + 1, 2, 10);
        auto exp = {1, 10, 10, 2, 3, 4, 5};
        CHECK(l.size() == exp.size());
        CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        CHECK(front == 1);
        CHECK(next == 2);
        auto& new_next = *(l.begin() + 1);
        CHECK(new_next == 10);
        CHECK(*result == 10);
    }

    {
        CONTAINER_T<int, 30, Alloc_pattern> l = {1, 2, 3, 4, 5};

        auto& pos0 = l.front();
        auto& pos1 = *(l.begin() + 1);
        auto& pos2 = *(l.begin() + 2);
        auto& pos3 = *(l.begin() + 3);

        CHECK(pos0 == 1);
        CHECK(pos1 == 2);
        CHECK(pos2 == 3);
        CHECK(pos3 == 4);

        auto to_insert = {10, 11, 12};
        auto result
            = l.insert(l.begin() + 2, to_insert.begin(), to_insert.end());
        auto exp = {1, 2, 10, 11, 12, 3, 4, 5};
        CHECK(l.size() == exp.size());
        CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));

        CHECK(pos0 == 1);
        CHECK(pos1 == 2);
        CHECK(pos2 == 3);
        CHECK(pos3 == 4);
        CHECK(*result == 10);
    }
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_list_constant_iterator()
{
    {
        CONTAINER_T<int, 5, Alloc_pattern> l{0, 1, 2, 3, 4};
        auto val = (l.begin() + 4);
        CHECK(val == 4);
        l.erase(l.begin(), l.begin() + 4);
        {
            auto exp = {4};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
            CHECK(*val == 4);
        }
        l.push_front(0);
        auto val0 = (l.begin());
        {
            auto exp = {0, 4};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
            CHECK(*val == 4);
            CHECK(*val0 == 0);
        }
        l.push_front(1);
        auto val1 = (l.begin());
        {
            auto exp = {1, 0, 4};
            CHECK(l.size() == exp.size());
            CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
            CHECK(*val == 4);
            CHECK(*val0 == 0);
            CHECK(*val1 == 1);
        }
    }
    {
        CONTAINER_T<int, 30, Alloc_pattern> l;
        auto init = {1, 2, 3, 4, 5};
        l.assign(init);

        auto& front = l.front();
        auto next = (l.begin() + 1);
        CHECK(front == 1);
        CHECK(next == 2);
        auto result = l.insert(l.begin() + 1, 2, 10);
        auto exp = {1, 10, 10, 2, 3, 4, 5};
        CHECK(l.size() == exp.size());
        CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));
        CHECK(front == 1);
        CHECK(*next == 2);
        auto new_next = (l.begin() + 1);
        CHECK(*new_next == 10);
        CHECK(*result == 10);
    }

    {
        CONTAINER_T<int, 30, Alloc_pattern> l = {1, 2, 3, 4, 5};

        auto& pos0 = l.front();
        auto pos1 = (l.begin() + 1);
        auto pos2 = (l.begin() + 2);
        auto pos3 = (l.begin() + 3);

        CHECK(pos0 == 1);
        CHECK(*pos1 == 2);
        CHECK(*pos2 == 3);
        CHECK(*pos3 == 4);

        auto to_insert = {10, 11, 12};
        auto result
            = l.insert(l.begin() + 2, to_insert.begin(), to_insert.end());
        auto exp = {1, 2, 10, 11, 12, 3, 4, 5};
        CHECK(l.size() == exp.size());
        CHECK(std::equal(l.begin(), l.end(), exp.begin(), exp.end()));

        CHECK(pos0 == 1);
        CHECK(*pos1 == 2);
        CHECK(*pos2 == 3);
        CHECK(*pos3 == 4);
        CHECK(*result == 10);
    }
}

template <template <typename, fixed::_impl::size_t,
              template <typename, fixed::_impl::size_t> typename>
          typename CONTAINER_T,
    template <typename, fixed::_impl::size_t>
    typename Alloc_pattern>
void test_pop_front()
{
    {
        CONTAINER_T<int, 10, Alloc_pattern> c = {10, 20, 30, 40, 50};
        auto exp = {20, 30, 40, 50};
        c.pop_front();
        CHECK(c.size() == exp.size());
        CHECK(std::equal(c.begin(), c.end(), exp.begin(), exp.end()));
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> c = {20, 30, 40, 50};
        auto exp = {30, 40, 50};
        c.pop_front();
        CHECK(c.size() == exp.size());
        CHECK(std::equal(c.begin(), c.end(), exp.begin(), exp.end()));
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> c = {30, 40, 50};
        auto exp = {40, 50};
        c.pop_front();
        CHECK(c.size() == exp.size());
        CHECK(std::equal(c.begin(), c.end(), exp.begin(), exp.end()));
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> c = {40, 50};
        auto exp = {50};
        c.pop_front();
        CHECK(c.size() == exp.size());
        CHECK(std::equal(c.begin(), c.end(), exp.begin(), exp.end()));
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> c = {50};
        c.pop_front();
        CHECK(c.size() == 0);
    }

    {
        CONTAINER_T<int, 10, Alloc_pattern> c;
#ifdef FIXED_CONTAINER_CHECK_BOUND
        CHECK_THROWS(c.pop_front());
#endif
    }

    {
        int i = 0;
        CONTAINER_T<test_construct, 10, Alloc_pattern> c;
        c.push_back(test_construct(i));
        CHECK(i == 1);
        c.pop_front();
        CHECK(c.size() == 0);
        CHECK(i == 0);
    }
}

#endif //! FIXED_TEST_FUNCTIONS_UNARY_CONTAINERS_HPP
