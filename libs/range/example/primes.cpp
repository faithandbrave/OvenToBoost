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

#include <vector>
#include <boost/assign/list_of.hpp>
#include <boost/range/adaptor/taken.hpp>

#include <boost/range/adaptor/regular_extension/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/adaptor/dropped.hpp>
#include <boost/range/access/front.hpp>
#include <boost/range/iteration.hpp>
#include <boost/range/any_range.hpp>
#include <boost/lambda/lambda.hpp>

typedef
    boost::any_range<int, boost::single_pass_traversal_tag, int, std::ptrdiff_t>
range;

using boost::lambda::_1;
using namespace boost::adaptors;
using boost::range::access::value_front;

range sieve(range r)
{
    return r | dropped(1) |+ filtered(_1 % value_front(r) != 0);
}

int main()
{
    range primes = boost::iteration(range(boost::iteration(2, boost::regular(_1 + 1))), sieve)
                     | transformed(value_front);

    BOOST_TEST(boost::equal(
        primes | taken(5),
        boost::assign::list_of(2)(3)(5)(7)(11)
    ));

    return boost::report_errors();
}

