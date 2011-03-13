// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi, Kohei Takahashi, Koichi Oyama,
// Norihisa Fujita, Yusuke Ichinohe, Takatoshi Kondo, 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <vector>
#include <boost/assign/list_of.hpp>
#include <boost/range/adaptor/taken_while.hpp>
#include <boost/range/adaptor/dropped_while.hpp>
#include <boost/range/adaptor/regular_extension/filtered.hpp>
#include <boost/range/adaptor/regular_extension/transformed.hpp>
#include <boost/lambda/lambda.hpp>

// description:
// regular operator|+() is syntax suggar of regular function.
// ex:)
//   r | taken_while(regular(_1 < 3));
// to
//   r |+ taken_while(_1 < 3);

void disp(int x)
{
    std::cout << x << ' ';
}

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

int main()
{
    using boost::lambda::_1;
    using namespace boost::adaptors;

    const std::vector<int> v = boost::assign::list_of(1)(2)(3)(4)(5)(6);
    for_each_(v |+ taken_while(_1 < 3) |+ dropped_while(_1 == 1), disp);

    std::cout << std::endl;

    for_each_(v |+ filtered(_1 % 2 == 0) |+ transformed(_1 * 2), disp);
}

/*
2
4 8 12
*/
