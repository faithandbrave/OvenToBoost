// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/range/adaptor/taken.hpp>

#include <vector>
#include <boost/assign/list_of.hpp>
#include <boost/range/adaptor/regular_extension/filtered.hpp>
#include <boost/range/access/front.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/detail/lightweight_test.hpp>

int main()
{
    // operator style
    {
        const std::vector<int> v = boost::assign::list_of(3)(1)(4)(2)(5);
        const std::vector<int> expected = boost::assign::list_of(3)(1);
        BOOST_TEST(boost::equal(v | boost::adaptors::taken(2), expected));
    }
    {
        std::vector<int> v = boost::assign::list_of(3)(1)(4)(2)(5);
        const std::vector<int> expected = boost::assign::list_of(3)(1);
        BOOST_TEST(boost::equal(v | boost::adaptors::taken(2), expected));
    }
    {
        using boost::lambda::_1;

        std::vector<int> v = boost::assign::list_of(3)(1)(4)(2)(5);
        v |+ boost::adaptors::filtered(_1 % 2 == 0)
          | boost::adaptors::taken(1)
          | boost::range::access::front = 0;

        const std::vector<int> expected = boost::assign::list_of(3)(1)(0)(2)(5);
        BOOST_TEST(boost::equal(v, expected));
    }

    // function style
    {
        const std::vector<int> v = boost::assign::list_of(3)(1)(4)(2)(5);
        const std::vector<int> expected = boost::assign::list_of(3)(1);
        BOOST_TEST(boost::equal(boost::adaptors::take(v, 2), expected));
    }
    {
        std::vector<int> v = boost::assign::list_of(3)(1)(4)(2)(5);
        const std::vector<int> expected = boost::assign::list_of(3)(1);
        BOOST_TEST(boost::equal(boost::adaptors::take(v, 2), expected));
    }
    {
        using boost::lambda::_1;

        std::vector<int> v = boost::assign::list_of(3)(1)(4)(2)(5);

        boost::range::access::front(
            boost::adaptors::take(
                boost::adaptors::filter(v, boost::regular(_1 % 2 == 0)),
                1
            )
        ) = 0;

        const std::vector<int> expected = boost::assign::list_of(3)(1)(0)(2)(5);
        BOOST_TEST(boost::equal(v, expected));
    }

    return boost::report_errors();
}
