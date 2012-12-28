// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011-2012.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <vector>
#include <boost/assign/list_of.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/range/experimental/adaptor/tapped.hpp>
#include <boost/lambda/lambda.hpp>

void nop(int x)
{
    static_cast<void>(x);
}

int increment(int x)
{
    return x + 1;
}

int main()
{
    using boost::lambda::_1;

    const std::vector<int> v = boost::assign::list_of(1)(2)(3);

    boost::for_each(v |+ boost::adaptors::tapped(std::cout << _1 << '\n')
                      |  boost::adaptors::transformed(increment),
                    nop);
}
/*
output:
1
2
3
*/

