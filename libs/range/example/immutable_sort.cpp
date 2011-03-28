// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/detail/lightweight_test.hpp>
#include <boost/range/adaptor/outdirected.hpp>
#include <boost/range/adaptor/indirected.hpp>
#include <vector>
#include <boost/assign/list_of.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/lambda/lambda.hpp>

using namespace boost::adaptors;
namespace bll = boost::lambda;

void disp(int x) { std::cout << x << ' '; }

int main()
{
    const std::vector<int> v = boost::assign::list_of(3)(1)(4)(2)(5);
    const std::vector<int> expected = boost::assign::list_of(1)(2)(3)(4)(5);

    std::vector<std::vector<int>::const_iterator> iters;
    boost::copy(v | outdirected, std::back_inserter(iters));
    boost::sort(iters, *bll::_1 < *bll::_2);

    BOOST_TEST(boost::equal(iters | indirected, expected));

    return boost::report_errors();
}

