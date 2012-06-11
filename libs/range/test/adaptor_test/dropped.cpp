// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/range/adaptor/dropped.hpp>

#include <vector>
#include <deque>
#include <list>

#include <boost/assign/list_of.hpp>
#include <boost/range/access/front.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/detail/lightweight_test.hpp>

template <class Container>
void test()
{
    // operator style
    {
        const Container c = boost::assign::list_of(3)(1)(4)(2)(5);
        const Container expected = boost::assign::list_of(4)(2)(5);
        BOOST_TEST(boost::equal(c | boost::adaptors::dropped(2), expected));
    }
    {
        Container c = boost::assign::list_of(3)(1)(4)(2)(5);
        const Container expected = boost::assign::list_of(4)(2)(5);
        BOOST_TEST(boost::equal(c | boost::adaptors::dropped(2), expected));
    }
    {
        Container c = boost::assign::list_of(3)(1)(4)(2)(5);
        c | boost::adaptors::dropped(2) | boost::range::access::front = 0;

        const Container expected = boost::assign::list_of(3)(1)(0)(2)(5);
        BOOST_TEST(boost::equal(c, expected));
    }

    // function style
    {
        const Container c = boost::assign::list_of(3)(1)(4)(2)(5);
        const Container expected = boost::assign::list_of(4)(2)(5);
        BOOST_TEST(boost::equal(boost::adaptors::drop(c, 2), expected));
    }
    {
        Container c = boost::assign::list_of(3)(1)(4)(2)(5);
        const Container expected = boost::assign::list_of(4)(2)(5);
        BOOST_TEST(boost::equal(boost::adaptors::drop(c, 2), expected));
    }
    {
        Container c = boost::assign::list_of(3)(1)(4)(2)(5);
        boost::range::access::front(boost::adaptors::drop(c, 2)) = 0;

        const Container expected = boost::assign::list_of(3)(1)(0)(2)(5);
        BOOST_TEST(boost::equal(c, expected));
    }
}

int main()
{
    test<std::vector<int> >();
    test<std::deque<int> >();
    test<std::list<int> >();

    return boost::report_errors();
}
