// Boost.Range 2.0 Extension library
//
// Copyright Akira Takahashi 2011.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/range/algorithm/for_each.hpp>
#include <boost/fusion/include/make_fused.hpp>

namespace boost {
namespace range {

template <class SinglePassRange, class UnaryFunction>
inline void fused_for_each(SinglePassRange& rng, UnaryFunction f)
{
    ::boost::range::for_each(rng, ::boost::fusion::make_fused(f));
}

template <class SinglePassRange, class UnaryFunction>
inline void fused_for_each(const SinglePassRange& rng, UnaryFunction f)
{
    ::boost::range::for_each(rng, ::boost::fusion::make_fused(f));
}

} // namespace range

using range::fused_for_each;

} // namespace boost


