// Boost.Range 2.0 Extension library
//
// Copyright Akira Takahashi 2011.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/detail/lightweight_test.hpp>
#include <boost/range/algorithm/equal.hpp>

#include <vector>
#include <list>
#include <boost/assign/list_of.hpp>
#include <boost/range/combine.hpp>
#include <boost/fusion/include/boost_tuple.hpp>

#include <boost/range/algorithm_ext/fused_for_each.hpp>

namespace {
    std::vector<int> value_cache;
    std::vector<char> char_cache;
}

void f(int x, char c)
{
    value_cache.push_back(x);
    char_cache.push_back(c);
}

int main()
{
    const std::vector<int> v = boost::assign::list_of(1)(2)(3);
    const std::list<char> ls = boost::assign::list_of('a')('b')('c');

    boost::fused_for_each(boost::combine(v, ls), f);

    BOOST_TEST(boost::equal(
        v,
        value_cache
    ));

    BOOST_TEST(boost::equal(
        ls,
        char_cache
    ));

    return boost::report_errors();
}


