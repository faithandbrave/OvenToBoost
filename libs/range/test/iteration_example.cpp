// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <boost/range/iteration.hpp>
#include <boost/range/adaptor/taken.hpp>
#include <boost/range/algorithm/for_each.hpp>

int next(int x)
{
    return x * 2;
}

void disp(int x) { std::cout << x << std::endl; }

int main()
{
    boost::for_each(boost::iteration(1, next) | boost::adaptors::taken(5), disp);
}
