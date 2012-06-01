#ifndef BOOST_RANGE_ALGORITHM_EXT_NONE_OF
#define BOOST_RANGE_ALGORITHM_EXT_NONE_OF

// Boost.Range 2.0 Extension library
//
// Copyright Akira Takahashi 2011.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/version.hpp>

#if BOOST_VERSION >= 105000
#  pragma message ("Warning: This header is deprecated. Please use: boost/algorithm/cxx11/none_of.hpp")
  #include <boost/algorithm/cxx11/none_of.hpp>

namespace boost {
    namespace range {
        using boost::algorithm::none_of;
    }
    using boost::range::none_of;
}
#else

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

#endif

#endif // BOOST_RANGE_ALGORITHM_EXT_NONE_OF

