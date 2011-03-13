
// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <boost/detail/lightweight_test.hpp>
#include <boost/range/algorithm/equal.hpp>

#include <boost/range/single.hpp>

#include <vector>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/assign/list_of.hpp>

struct to_s {
    typedef std::string result_type;

    std::string operator()(int x) const
    {
        return boost::lexical_cast<std::string>(x);
    }
};

int main()
{
    {
        const char c = 'a';
        const std::string expected("a");
        BOOST_TEST(boost::equal(boost::single(c), expected));
    }
    {
        char c = 'a';
        const std::string expected("a");
        BOOST_TEST(boost::equal(boost::single(c), expected));
    }
    {
        const int a = 1;
        const std::vector<std::string> expected = boost::assign::list_of("1");
        BOOST_TEST(boost::equal(
            boost::single(a) | boost::adaptors::transformed(to_s()),
            expected
        ));
    }

    return boost::report_errors();
}

