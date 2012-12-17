// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011-2012.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/detail/lightweight_test.hpp>
#include <boost/range/algorithm/equal.hpp>

#include <vector>
#include <boost/range/adaptor/adjacent_zipped.hpp>
#include <boost/range/algorithm_ext/fused_for_each.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/fusion/include/boost_tuple.hpp>

namespace {
    std::vector<int> firsts;
    std::vector<int> seconds;
}

void mutable_fun(int& first, int& second)
{
    ++first;
    ++second;
}

void constant_fun(int first, int second)
{
    firsts.push_back(first);
    seconds.push_back(second);
}

std::vector<int> init_values()
{
    return boost::assign::list_of(1)(2)(3)(4)(5);
}

template <class Container, class Expression>
void mutable_test(Container& c, const Expression& expr)
{
    boost::fused_for_each(expr, mutable_fun);

    BOOST_TEST(boost::equal(
        c,
        boost::assign::list_of(2)(4)(5)(6)(6)
    ));
}

template <class Container, class Expression>
void constant_test(const Container& c, const Expression& expr)
{
    boost::fused_for_each(expr, constant_fun);

    BOOST_TEST(boost::equal(
        firsts,
        boost::assign::list_of(1)(2)(3)(4)
    ));
    BOOST_TEST(boost::equal(
        seconds,
        boost::assign::list_of(2)(3)(4)(5)
    ));

    firsts.clear();
    seconds.clear();
}

void never_call_fun(int first, int second)
{
    BOOST_TEST(false);
}

void empty_test()
{
    const std::vector<int> v;
    boost::fused_for_each(v | boost::adaptors::adjacent_zipped, never_call_fun);
}

int main()
{
    // pipe style (mutable)
    {
        std::vector<int> v = init_values();
        mutable_test(v, v | boost::adaptors::adjacent_zipped);
    }

    // pipe style (constant)
    {
        const std::vector<int> v = init_values();
        constant_test(v, v | boost::adaptors::adjacent_zipped);
    }

    // function style (mutable)
    {
        std::vector<int> v = init_values();
        mutable_test(v, boost::adaptors::adjacent_zip(v));
    }

    // function style (constant)
    {
        std::vector<int> v = init_values();
        constant_test(v, boost::adaptors::adjacent_zip(v));
    }

    empty_test();

    return boost::report_errors();
}

