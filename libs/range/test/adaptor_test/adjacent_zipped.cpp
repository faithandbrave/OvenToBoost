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
#include <boost/range/experimental/adaptor/adjacent_zipped.hpp>
#include <boost/range/algorithm_ext/fused_for_each.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/fusion/include/boost_tuple.hpp>

namespace {
    std::vector<int> firsts;
    std::vector<int> seconds;
}

void print(int first, int second)
{
    firsts.push_back(first);
    seconds.push_back(second);
}

int main()
{
    const std::vector<int> v = boost::assign::list_of(1)(2)(3)(4)(5);

    boost::fused_for_each(v | boost::adaptors::adjacent_zipped, print);

    BOOST_TEST(boost::equal(
        firsts,
        boost::assign::list_of(1)(2)(3)(4)
    ));
    BOOST_TEST(boost::equal(
        seconds,
        boost::assign::list_of(2)(3)(4)(5)
    ));

    return boost::report_errors();
}

