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

#include <boost/range/iteration.hpp>

#include <vector>
#include <boost/assign/list_of.hpp>
#include <boost/range/adaptor/taken.hpp>
#include <boost/range/adaptor/dropped.hpp>
#include <boost/range/access/front.hpp>
#include <boost/range/algorithm/equal.hpp>

int next(int x)
{
    return x * 2;
}

int main()
{
    {
        const std::vector<int> expected = boost::assign::list_of(1)(2)(4)(8)(16);

        BOOST_TEST(boost::equal(
            boost::iteration(1, next) | boost::adaptors::taken(5),
            expected
        ));
    }
    {
        const int expected = 4;

        BOOST_TEST(
            (boost::iteration(1, next) | boost::adaptors::dropped(2) | boost::range::access::front)
            == expected
        );
    }

    return boost::report_errors();
}


