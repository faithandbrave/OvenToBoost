// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <vector>
#include <boost/range/access/front.hpp>
#include <boost/range/adaptor/dropped.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/assign/list_of.hpp>

int main()
{
    using boost::adaptors::dropped;
    using boost::range::access::front;

    // operator style
    {
        const std::vector<int> v = boost::assign::list_of(1)(2)(3)(4)(5)(6);
        BOOST_TEST((v | dropped(2) | front) == 3);
    }
    {
        std::vector<int> v = boost::assign::list_of(1)(2)(3)(4)(5)(6);
        BOOST_TEST((v | dropped(2) | front) == 3);

        v | dropped(2) | front = 0;
        const std::vector<int> expected = boost::assign::list_of(1)(2)(0)(4)(5)(6);
        BOOST_TEST(boost::equal(v, expected));
    }

    // function style
    {
        const std::vector<int> v = boost::assign::list_of(1)(2)(3)(4)(5)(6);
        BOOST_TEST(front(v | dropped(2)) == 3);
    }
    {
        std::vector<int> v = boost::assign::list_of(1)(2)(3)(4)(5)(6);
        BOOST_TEST(front(v | dropped(2)) == 3);

        front(v | dropped(2)) = 0;
        const std::vector<int> expected = boost::assign::list_of(1)(2)(0)(4)(5)(6);
        BOOST_TEST(boost::equal(v, expected));

    }

    return boost::report_errors();
}
