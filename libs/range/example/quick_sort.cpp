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

#include <boost/range/adaptor/regular_extension/filtered.hpp>
#include <boost/range/adaptor/dropped.hpp>
#include <boost/range/access/front.hpp>
#include <boost/range/single.hpp>
#include <boost/range/any_range.hpp>
#include <boost/range/join.hpp>
#include <boost/lambda/lambda.hpp>

typedef
    boost::any_range<int, boost::forward_traversal_tag, int&, std::ptrdiff_t>
range;

using boost::lambda::_1;
using namespace boost::adaptors;
using boost::range::access::front;
using boost::range::single;

range quick_sort(range rng)
{
    if (!rng)
        return rng;
    else {
        int& x = rng | front;
        range xs = rng | dropped(1);

        return
            boost::join(
                boost::join(
                    quick_sort(xs |+ filtered(_1 < x)),
                    single(x)
                ),
                quick_sort(xs |+ filtered(_1 >= x))
            );
    }
}

int main()
{
    std::vector<int> v = boost::assign::list_of(3)(2)(5)(4)(6)(1);

    std::cout << quick_sort(range(v)) << std::endl;

    BOOST_TEST(boost::equal(
        quick_sort(range(v)),
        boost::assign::list_of(1)(2)(3)(4)(5)(6)
    ));

    return boost::report_errors();
}
