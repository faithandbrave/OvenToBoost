// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <vector>
#include <boost/range/split_at.hpp>
#include <boost/range/algorithm/for_each.hpp>

void disp(int x)
{
    std::cout << x << ' ';
}

int main()
{
    const std::vector<int> v = {3, 1, 4, 2, 5, 6};
    boost::range::result_of::split_at<const std::vector<int> >::type r = boost::split_at(v, 1);

    boost::for_each(r.first, disp); std::cout << std::endl;
    boost::for_each(r.second, disp);
}

/*
3 
1 4 2 5 6 
*/

