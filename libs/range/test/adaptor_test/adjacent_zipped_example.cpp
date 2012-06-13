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
#include <boost/range/experimental/adaptor/adjacent_zipped.hpp>
#include <boost/range/algorithm_ext/fused_for_each.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/fusion/include/boost_tuple.hpp>

void print(int first, int second)
{
    std::cout << first << ", " << second << std::endl;
}

int main()
{
    const std::vector<int> v = boost::assign::list_of(1)(2)(3)(4)(5);

    boost::fused_for_each(v | boost::adaptors::adjacent_zipped, print);
}

/*
output:
1, 2
2, 3
3, 4
4, 5
*/

