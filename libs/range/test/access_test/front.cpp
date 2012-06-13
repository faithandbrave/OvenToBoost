// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/range/access/front.hpp>

#include <vector>
#include <deque>
#include <list>

#include <boost/range/adaptor/dropped.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/assign/list_of.hpp>

template <class SinglePassContainer>
void test()
{
    using boost::adaptors::dropped;
    using boost::range::access::front;
    using boost::range::access::value_front;

    // operator style
    {
        const SinglePassContainer c = boost::assign::list_of(1)(2)(3)(4)(5)(6);
        BOOST_TEST((c | dropped(2) | front) == 3);
        BOOST_TEST((c | dropped(2) | value_front) == 3);
    }
    {
        SinglePassContainer c = boost::assign::list_of(1)(2)(3)(4)(5)(6);
        BOOST_TEST((c | dropped(2) | front) == 3);
        BOOST_TEST((c | dropped(2) | value_front) == 3);

        c | dropped(2) | front = 0;
        const SinglePassContainer expected = boost::assign::list_of(1)(2)(0)(4)(5)(6);
        BOOST_TEST(boost::equal(c, expected));
    }

    // function style
    {
        const SinglePassContainer c = boost::assign::list_of(1)(2)(3)(4)(5)(6);
        BOOST_TEST(front(c | dropped(2)) == 3);
        BOOST_TEST(value_front(c | dropped(2)) == 3);
    }
    {
        SinglePassContainer c = boost::assign::list_of(1)(2)(3)(4)(5)(6);
        BOOST_TEST(front(c | dropped(2)) == 3);
        BOOST_TEST(value_front(c | dropped(2)) == 3);

        front(c | dropped(2)) = 0;
        const SinglePassContainer expected = boost::assign::list_of(1)(2)(0)(4)(5)(6);
        BOOST_TEST(boost::equal(c, expected));
    }

    // result_of
    {
        const SinglePassContainer c1 = boost::assign::list_of(1)(2)(3);
        const SinglePassContainer c2 = boost::assign::list_of(4)(5)(6);
        const std::vector<SinglePassContainer> c = boost::assign::list_of(c1)(c2);

        const SinglePassContainer expected = boost::assign::list_of
            (1)
            (4)
            ;

        BOOST_TEST(boost::equal(
            c | boost::adaptors::transformed(front),
            expected
        ));

        BOOST_TEST(boost::equal(
            c | boost::adaptors::transformed(value_front),
            expected
        ));
    }

}

int main()
{
    test<std::vector<int> >();
    test<std::deque<int> >();
    test<std::list<int> >();

    return boost::report_errors();
}

