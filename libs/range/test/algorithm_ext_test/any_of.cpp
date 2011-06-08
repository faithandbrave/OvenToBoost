// Boost.Range 2.0 Extension library
//
// Copyright Akira Takahashi 2011.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/detail/lightweight_test.hpp>

#include <string>
#include <boost/range/algorithm_ext/any_of.hpp>

struct is_a
{
    bool operator()(char ch) const
    {
        return ch == 'a';
    }
};

int main()
{
    BOOST_TEST( boost::any_of(std::string("bbbbbbbabb"), is_a()) );
    BOOST_TEST(!boost::any_of(std::string("bbbbbbbbbb"), is_a()) );

    return boost::report_errors();
}
