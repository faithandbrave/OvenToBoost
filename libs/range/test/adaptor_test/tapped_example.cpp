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
#include <boost/lambda/lambda.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/range/adaptor/regular_extension/filtered.hpp>
#include <boost/range/adaptor/regular_extension/transformed.hpp>
#include <boost/range/adaptor/memoized.hpp>
#include <boost/range/experimental/adaptor/tapped.hpp>

void print(int x)
{
    std::cout << x << std::endl;
}

int main()
{
    std::vector<int> v = {1, 2, 3, 4, 5};

    using boost::lambda::_1;
    boost::for_each(v |+ boost::adaptors::transformed(_1 + 1)
                      |+ boost::adaptors::tapped(std::cout << _1 << " is tapped\n")
                      |+ boost::adaptors::filtered(_1 % 2 == 0),
                    print);
}
/*
output:
2 is tapped
3 is tapped
4 is tapped
5 is tapped
6 is tapped
2
4
6
*/

