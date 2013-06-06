// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011-2013.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/range/access/at.hpp>

#include <vector>
#include <deque>

#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/assign/list_of.hpp>

template <class RandomAccessContainer>
void test()
{
    using boost::range::access::at;
    using boost::range::access::value_at;
    using boost::range::access::optional_at;

    // operator style
    {
        const RandomAccessContainer c = boost::assign::list_of(3)(1)(4)(2)(5);
        BOOST_TEST((c | at(2)) == 4);
        BOOST_TEST((c | value_at(2)) == 4);
    }
    {
        RandomAccessContainer c = boost::assign::list_of(3)(1)(4)(2)(5);
        BOOST_TEST((c | at(2)) == 4);
        BOOST_TEST((c | value_at(2)) == 4);

        c | at(2) = 0;
        const RandomAccessContainer expected = boost::assign::list_of(3)(1)(0)(2)(5);
        BOOST_TEST(boost::equal(c, expected));
    }
    {
        RandomAccessContainer c = boost::assign::list_of(3)(1)(4);
        BOOST_TEST((c | optional_at(2)).get() == 4);
        BOOST_TEST(!(c | optional_at(3)).is_initialized());

        (c | optional_at(2)).get() = 0;
        const RandomAccessContainer expected = boost::assign::list_of(3)(1)(0);
        BOOST_TEST(boost::equal(c, expected));
    }

    // function style
    {
        const RandomAccessContainer c = boost::assign::list_of(3)(1)(4)(2)(5);
        BOOST_TEST(at(c, 2) == 4);
        BOOST_TEST(value_at(c, 2) == 4);
    }
    {
        RandomAccessContainer c = boost::assign::list_of(3)(1)(4)(2)(5);
        BOOST_TEST(at(c, 2) == 4);
        BOOST_TEST(value_at(c, 2) == 4);

        at(c, 2) = 0;
        const RandomAccessContainer expected = boost::assign::list_of(3)(1)(0)(2)(5);
        BOOST_TEST(boost::equal(c, expected));
    }
    {
        RandomAccessContainer c = boost::assign::list_of(3)(1)(4);
        BOOST_TEST(optional_at(c, 2).get() == 4);
        BOOST_TEST(!optional_at(c, 3).is_initialized());

        optional_at(c, 2).get() = 0;
        const RandomAccessContainer expected = boost::assign::list_of(3)(1)(0);
        BOOST_TEST(boost::equal(c, expected));
    }

    // result_of
    {
        const RandomAccessContainer c1 = boost::assign::list_of(1)(2)(3);
        const RandomAccessContainer c2 = boost::assign::list_of(4)(5)(6);
        const std::vector<RandomAccessContainer > c = boost::assign::list_of(c1)(c2);

        const RandomAccessContainer expected = boost::assign::list_of
            (2)
            (5)
            ;

        BOOST_TEST(boost::equal(
            c | boost::adaptors::transformed(at(1)),
            expected
        ));

        BOOST_TEST(boost::equal(
            c | boost::adaptors::transformed(value_at(1)),
            expected
        ));
    }

}

int main()
{
    test<std::vector<int> >();
    test<std::deque<int> >();

    return boost::report_errors();
}
