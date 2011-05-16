// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <boost/detail/lightweight_test.hpp>
#include <boost/range/algorithm/equal.hpp>

#include <boost/range/split_at.hpp>

#include <vector>
#include <boost/assign/list_of.hpp>

int main()
{
    {
        const std::vector<int> v = boost::assign::list_of(3)(1)(4)(2)(5);
        const std::vector<int> left = boost::assign::list_of(3)(1);
        const std::vector<int> right = boost::assign::list_of(4)(2)(5);

        boost::range::split_at_result<const std::vector<int> >::type r = boost::split_at(v, 2);

        BOOST_TEST(boost::equal(r.first, left));
        BOOST_TEST(boost::equal(r.second, right));
    }
    {
        std::vector<int> v = boost::assign::list_of(3)(1)(4)(2)(5);
        const std::vector<int> left = boost::assign::list_of(3)(1);
        const std::vector<int> right = boost::assign::list_of(4)(2)(5);

        boost::range::split_at_result<std::vector<int> >::type r = boost::split_at(v, 2);

        BOOST_TEST(boost::equal(r.first, left));
        BOOST_TEST(boost::equal(r.second, right));
    }

    return boost::report_errors();
}


