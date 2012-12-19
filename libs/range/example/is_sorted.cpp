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
#include <boost/assign/list_of.hpp>
#include <boost/range/algorithm/sort.hpp>

#include <boost/range/adaptor/adjacent_zipped.hpp>
#include <boost/range/value_type.hpp>
#include <boost/algorithm/cxx11/all_of.hpp>

struct sorted_less {
    typedef bool result_type;

    template <class AdjacentTuple>
    bool operator()(const AdjacentTuple& x) const
    {
        return boost::get<0>(x) < boost::get<1>(x);
    }
};

template <class BidirectionalRange>
bool is_sorted(const BidirectionalRange& r)
{
    using namespace boost::adaptors;
    return boost::algorithm::all_of(r | adjacent_zipped, sorted_less());
}

int main()
{
    std::vector<int> v = boost::assign::list_of(3)(1)(4);

    std::cout << std::boolalpha;
    std::cout << ::is_sorted(v) << std::endl;

    boost::sort(v);
    std::cout << ::is_sorted(v) << std::endl;
}

