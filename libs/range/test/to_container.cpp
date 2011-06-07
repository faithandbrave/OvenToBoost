// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/detail/lightweight_test.hpp>
#include <boost/range/algorithm/equal.hpp>

#include <vector>
#include <boost/assign/list_of.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/to_container.hpp>

bool is_odd(int x) { return x % 2 == 0; }

int main()
{
    // pipe operator style
    {
        const std::vector<int> v1 = boost::assign::list_of(1)(2)(3)(4)(5);
        const std::vector<int> v2 = v1 | boost::adaptors::filtered(is_odd) | boost::to_container;

        BOOST_TEST(boost::equal(
            v2,
            boost::assign::list_of(2)(4)
        ));
    }

    // function style
    {
        const std::vector<int> v1 = boost::assign::list_of(1)(2)(3)(4)(5);
        const std::vector<int> v2 = boost::to_container(boost::adaptors::filter(v1, is_odd));

        BOOST_TEST(boost::equal(
            v2,
            boost::assign::list_of(2)(4)
        ));
    }

    return boost::report_errors();
}


