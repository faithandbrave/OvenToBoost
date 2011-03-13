// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_RESULT_OF_USE_DECLTYPE
#include <iostream>
#include <vector>
#include <boost/assign/list_of.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/regular.hpp>

template <class InputIterator, class F>
void for_each_(InputIterator first, InputIterator last, F f)
{
    InputIterator it; // Default Constructible
    it = first; // Copy Assignable
    for (; it != last; ++it) {
        f(*it);
    }
}

template <class SinglePassRange, class F>
void for_each_(const SinglePassRange& rng, F f)
{
    return for_each_(boost::begin(rng), boost::end(rng), f);
}

void disp(int x)
{
    std::cout << x << ' ';
}

int main()
{
    const std::vector<int> v = boost::assign::list_of(1)(2)(3)(4)(5);
    for_each_(v | boost::adaptors::transformed(boost::regular([](int x) { return x + 1; })), disp);
}

/*
2 3 4 5 6 
*/

