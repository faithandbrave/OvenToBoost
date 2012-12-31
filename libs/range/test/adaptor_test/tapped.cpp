// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011-2012.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/detail/lightweight_test.hpp>
#include <boost/range/experimental/adaptor/tapped.hpp>

#include <vector>
#include <list>

#include <boost/range/algorithm/equal.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>

std::size_t transform_call_count = 0;
std::size_t tap_call_count = 0;

const std::vector<int> input_values = boost::assign::list_of(1)(2)(3)(4)(5);
const std::vector<int> expected_values = boost::assign::list_of(2)(4)(6);
const std::vector<int> transformed_values = boost::assign::list_of(2)(3)(4)(5)(6);

int transform_func(int x)
{
    ++transform_call_count;
    return x + 1;
}

void tap_func(int x)
{
    ++tap_call_count;
    BOOST_TEST(x == transformed_values[transform_call_count - 1]);
}

bool is_even(int x) { return x % 2 == 0; }

template <class Container>
void pipe_style_test()
{
    transform_call_count = 0;
    tap_call_count = 0;

    Container c(input_values.begin(), input_values.end());
    const std::vector<int> expected(expected_values.begin(), expected_values.end());

    BOOST_TEST(boost::equal(
        c | boost::adaptors::transformed(transform_func)
          | boost::adaptors::tapped(tap_func)
          | boost::adaptors::filtered(is_even),
        expected));

    BOOST_TEST(transform_call_count == c.size());
    BOOST_TEST(tap_call_count == c.size());
}

template <class Container>
void regular_operator_test()
{
    transform_call_count = 0;
    tap_call_count = 0;

    Container c(input_values.begin(), input_values.end());
    const std::vector<int> expected(expected_values.begin(), expected_values.end());

    BOOST_TEST(boost::equal(
        c |  boost::adaptors::transformed(transform_func)
          |+ boost::adaptors::tapped(tap_func)
          |  boost::adaptors::filtered(is_even),
        expected));

    BOOST_TEST(transform_call_count == c.size());
    BOOST_TEST(tap_call_count == c.size());
}

template <class Container>
void function_style_test()
{
    transform_call_count = 0;
    tap_call_count = 0;

    Container c(input_values.begin(), input_values.end());
    const std::vector<int> expected(expected_values.begin(), expected_values.end());

    BOOST_TEST(boost::equal(
        boost::adaptors::filter(
            boost::adaptors::tap(
                boost::adaptors::transform(c, transform_func),
                tap_func
            ),
            is_even
        ),
        expected));

    BOOST_TEST(transform_call_count == c.size());
    BOOST_TEST(tap_call_count == c.size());
}

template <template <class T, class Alloc=std::allocator<T> > class Container>
void tap_test()
{
    pipe_style_test<Container<int> >();
    pipe_style_test<const Container<int> >();
    regular_operator_test<Container<int> >();
    regular_operator_test<const Container<int> >();
    function_style_test<Container<int> >();
    function_style_test<const Container<int> >();
}


int main()
{
    tap_test<std::vector>();
    tap_test<std::list>();
    tap_test<std::deque>();

    return boost::report_errors();
}

