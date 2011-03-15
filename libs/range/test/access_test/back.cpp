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
#include <boost/range/access/back.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/assign/list_of.hpp>

int main()
{
    using boost::range::access::back;
    using boost::range::access::value_back;

    // operator style
    {
        const std::vector<int> v = boost::assign::list_of(3)(1)(4)(2)(5);
        BOOST_TEST((v | back) == 5);
        BOOST_TEST((v | value_back) == 5);
    }
    {
        std::vector<int> v = boost::assign::list_of(3)(1)(4)(2)(5);
        BOOST_TEST((v | back) == 5);
        BOOST_TEST((v | value_back) == 5);

        v | back = 0;
        const std::vector<int> expected = boost::assign::list_of(3)(1)(4)(2)(0);
        BOOST_TEST(boost::equal(v, expected));
    }

    // function style
    {
        const std::vector<int> v = boost::assign::list_of(3)(1)(4)(2)(5);
        BOOST_TEST(back(v) == 5);
        BOOST_TEST(value_back(v) == 5);
    }
    {
        std::vector<int> v = boost::assign::list_of(3)(1)(4)(2)(5);
        BOOST_TEST(back(v) == 5);
        BOOST_TEST(value_back(v) == 5);

        back(v) = 0;
        const std::vector<int> expected = boost::assign::list_of(3)(1)(4)(2)(0);
        BOOST_TEST(boost::equal(v, expected));
    }

    // result_of
    {
        const std::vector<int> v1 = boost::assign::list_of(1)(2)(3);
        const std::vector<int> v2 = boost::assign::list_of(4)(5)(6);
        const std::vector<std::vector<int> > v = boost::assign::list_of(v1)(v2);

        const std::vector<int> expected = boost::assign::list_of
            (3)
            (6)
            ;

        BOOST_TEST(boost::equal(
            v | boost::adaptors::transformed(back),
            expected
        ));

        BOOST_TEST(boost::equal(
            v | boost::adaptors::transformed(value_back),
            expected
        ));
    }

    return boost::report_errors();
}

