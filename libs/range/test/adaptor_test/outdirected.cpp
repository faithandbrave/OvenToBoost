// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/range/adaptor/outdirected.hpp>

#include <vector>
#include <boost/assign/list_of.hpp>
#include <boost/range/adaptor/indirected.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/detail/lightweight_test.hpp>

int main()
{
    // operator style
    {
        int rng[] = {3, 1, 4, 2, 5};
        int* expected[] = {&rng[0], &rng[1], &rng[2], &rng[3], &rng[4]};

        BOOST_TEST(boost::equal(rng | boost::adaptors::outdirected, expected));
    }
    {
        const std::vector<int> v = boost::assign::list_of(3)(1)(4)(2)(5);
        BOOST_TEST(boost::equal(v | boost::adaptors::outdirected | boost::adaptors::indirected, v));
    }

    // function style
    {
        int rng[] = {3, 1, 4, 2, 5};
        int* expected[] = {&rng[0], &rng[1], &rng[2], &rng[3], &rng[4]};

        BOOST_TEST(boost::equal(boost::adaptors::outdirect(rng), expected));
    }
    {
        const std::vector<int> v = boost::assign::list_of(3)(1)(4)(2)(5);
        BOOST_TEST(boost::equal(boost::adaptors::indirect(boost::adaptors::outdirect(v)), v));
    }

    return boost::report_errors();
}
