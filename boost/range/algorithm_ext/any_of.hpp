// Boost.Range 2.0 Extension library
//
// Copyright Akira Takahashi 2011.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/concepts.hpp>

namespace boost {
namespace range {

    namespace any_of_detail {

        template <class SinglePassIterator, class UnaryPredicate>
        inline bool any_of(SinglePassIterator first, SinglePassIterator last, UnaryPredicate pred)
        {
            for (; first != last; ++first) {
                if (pred(*first))
                    return true;
            }
            return false;
        }

    } // namespace any_of_detail

    template <class SinglePassRange, class UnaryPredicate>
    inline bool any_of(SinglePassRange& rng, UnaryPredicate pred)
    {
        BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange> ));
        return any_of_detail::any_of(::boost::begin(rng), ::boost::end(rng), pred);
    }

    template <class SinglePassRange, class UnaryPredicate>
    inline bool any_of(const SinglePassRange& rng, UnaryPredicate pred)
    {
        BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange> ));
        return any_of_detail::any_of(::boost::begin(rng), ::boost::end(rng), pred);
    }

} // namespace range

using range::any_of;

} // namespace boost

