#ifndef BOOST_RANGE_ALGORITHM_EXT_ALL_OF
#define BOOST_RANGE_ALGORITHM_EXT_ALL_OF

// Boost.Range 2.0 Extension library
//
// Copyright Akira Takahashi 2011.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/version.hpp>

#if BOOST_VERSION >= 105000
#  pragma message ("Warning: This header is deprecated. Please use: boost/algorithm/cxx11/all_of.hpp")
  #include <boost/algorithm/cxx11/all_of.hpp>

namespace boost {
    namespace range {
        using boost::algorithm::all_of;
    }
    using boost::range::all_of;
}
#else

#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/concepts.hpp>

namespace boost {
namespace range {

    namespace all_of_detail {

        template <class SinglePassIterator, class UnaryPredicate>
        inline bool all_of(SinglePassIterator first, SinglePassIterator last, UnaryPredicate pred)
        {
            for (; first != last; ++first) {
                if (!pred(*first))
                        return false;
            }
            return true;
        }

    } // namespace all_of_detail

    template <class SinglePassRange, class UnaryPredicate>
    inline bool all_of(SinglePassRange& rng, UnaryPredicate pred)
    {
        BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange> ));
        return all_of_detail::all_of(::boost::begin(rng), ::boost::end(rng), pred);
    }

    template <class SinglePassRange, class UnaryPredicate>
    inline bool all_of(const SinglePassRange& rng, UnaryPredicate pred)
    {
        BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange> ));
        return all_of_detail::all_of(::boost::begin(rng), ::boost::end(rng), pred);
    }

} // namespace range

using range::all_of;


} // namespace boost

#endif

#endif // BOOST_RANGE_ALGORITHM_EXT_ALL_OF


