// Boost.Range 2.0 Extension library
//
// Copyright Akira Takahashi 2011.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/range/algorithm_ext/any_of.hpp>

namespace boost {
namespace range {

template <class SinglePassRange, class UnaryPredicate>
inline bool none_of(SinglePassRange& rng, UnaryPredicate pred)
{
    return !::boost::range::any_of(rng, pred);
}

template <class SinglePassRange, class UnaryPredicate>
inline bool none_of(const SinglePassRange& rng, UnaryPredicate pred)
{
    return !::boost::range::any_of(rng, pred);
}

} // namespace range

using range::none_of;

} // namespace boost

