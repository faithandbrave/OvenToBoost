// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/range/adaptor/dropped_while.hpp>

#include <vector>
#include <deque>
#include <list>

#include <boost/assign/list_of.hpp>
#include <boost/range/access/front.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/detail/lightweight_test.hpp>

bool is_less4(int x) { return x < 4; }

template <class Container>
void test()
{
    // operator style
    {
        const Container c = boost::assign::list_of(3)(1)(4)(2)(5);
        const Container expected = boost::assign::list_of(4)(2)(5);
        BOOST_TEST(boost::equal(c | boost::adaptors::dropped_while(is_less4), expected));
    }
    {
        Container c = boost::assign::list_of(3)(1)(4)(2)(5);
        const Container expected = boost::assign::list_of(4)(2)(5);
        BOOST_TEST(boost::equal(c | boost::adaptors::dropped_while(is_less4), expected));
    }
    {
        using boost::lambda::_1;

        Container c = boost::assign::list_of(3)(1)(4)(2)(5);
        c |+ boost::adaptors::dropped_while(_1 % 2 != 0)
          |  boost::range::access::front = 0;

        const Container expected = boost::assign::list_of(3)(1)(0)(2)(5);
        BOOST_TEST(boost::equal(c, expected));
    }

    // function style
    {
        const Container c = boost::assign::list_of(3)(1)(4)(2)(5);
        const Container expected = boost::assign::list_of(4)(2)(5);
        BOOST_TEST(boost::equal(boost::adaptors::drop_while(c, is_less4), expected));
    }
    {
        Container c = boost::assign::list_of(3)(1)(4)(2)(5);
        const Container expected = boost::assign::list_of(4)(2)(5);
        BOOST_TEST(boost::equal(boost::adaptors::drop_while(c, is_less4), expected));
    }
    {
        using boost::lambda::_1;

        Container c = boost::assign::list_of(3)(1)(4)(2)(5);

        boost::range::access::front(
            boost::adaptors::drop_while(c, boost::regular(_1 % 2 != 0))
        ) = 0;

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
