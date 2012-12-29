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
#include <boost/range/algorithm/for_each.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/adaptor/memoized.hpp>
#include <boost/range/experimental/adaptor/tapped.hpp>

int ident(int x)
{
    std::cout << "ident:" << x << std::endl;
    return x;
}

int is_even(int x)
{
    return x % 2 == 0;
}

void tap_print(int x)
{
    std::cout << ":" << x << std::endl;
}

void print(int x)
{
    std::cout << x << std::endl;
}

int main()
{
    std::vector<int> v = {1, 2, 3, 4, 5};

    boost::for_each(v | boost::adaptors::transformed(ident)
                      | boost::adaptors::memoized
                      | boost::adaptors::tapped(tap_print)
                      | boost::adaptors::filtered(is_even),
                    print);
}

/*
output:
ident:1
:1
ident:2
:2
ident:3
:3
ident:4
:4
ident:5
:5
2
4
*/

