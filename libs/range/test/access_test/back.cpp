// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011-2013.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <vector>
#include <deque>
#include <list>

#include <boost/range/access/back.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/assign/list_of.hpp>

template <class BidirectionalContainer>
void test()
{
    using boost::range::access::back;
    using boost::range::access::value_back;
    using boost::range::access::optional_back;

    // operator style
    {
        const BidirectionalContainer c = boost::assign::list_of(3)(1)(4)(2)(5);
        BOOST_TEST((c | back) == 5);
        BOOST_TEST((c | value_back) == 5);
    }
    {
        BidirectionalContainer c = boost::assign::list_of(3)(1)(4)(2)(5);
        BOOST_TEST((c | back) == 5);
        BOOST_TEST((c | value_back) == 5);

        c | back = 0;
        const BidirectionalContainer expected = boost::assign::list_of(3)(1)(4)(2)(0);
        BOOST_TEST(boost::equal(c, expected));
    }
    {
        BidirectionalContainer c = boost::assign::list_of(1)(2)(3);
        BOOST_TEST((c | optional_back).get() == 3);
       
        boost::optional<int&> opt = c | optional_back;
        opt.get() = 0;

        const BidirectionalContainer expected = boost::assign::list_of(1)(2)(0);
        BOOST_TEST(boost::equal(c, expected));

        BidirectionalContainer c2;
        BOOST_TEST(!(c2 | optional_back).is_initialized());
    }

    // function style
    {
        const BidirectionalContainer c = boost::assign::list_of(3)(1)(4)(2)(5);
        BOOST_TEST(back(c) == 5);
        BOOST_TEST(value_back(c) == 5);
    }
    {
        BidirectionalContainer c = boost::assign::list_of(3)(1)(4)(2)(5);
        BOOST_TEST(back(c) == 5);
        BOOST_TEST(value_back(c) == 5);

        back(c) = 0;
        const BidirectionalContainer expected = boost::assign::list_of(3)(1)(4)(2)(0);
        BOOST_TEST(boost::equal(c, expected));
    }
    {
        BidirectionalContainer c = boost::assign::list_of(1)(2)(3);
        BOOST_TEST(optional_back(c).get() == 3);
       
        boost::optional<int&> opt = optional_back(c);
        opt.get() = 0;

        const BidirectionalContainer expected = boost::assign::list_of(1)(2)(0);
        BOOST_TEST(boost::equal(c, expected));

        BidirectionalContainer c2;
        BOOST_TEST(!optional_back(c2).is_initialized());
    }

    // result_of
    {
        const BidirectionalContainer c1 = boost::assign::list_of(1)(2)(3);
        const BidirectionalContainer c2 = boost::assign::list_of(4)(5)(6);
        const std::vector<BidirectionalContainer > c = boost::assign::list_of(c1)(c2);

        const BidirectionalContainer expected = boost::assign::list_of
            (3)
            (6)
            ;

        BOOST_TEST(boost::equal(
            c | boost::adaptors::transformed(back),
            expected
        ));

        BOOST_TEST(boost::equal(
            c | boost::adaptors::transformed(value_back),
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

