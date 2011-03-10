// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RANGE_SPLIT_AT_IMPL_INCLUDE
#define BOOST_RANGE_SPLIT_AT_IMPL_INCLUDE

#include <utility>
#include <boost/range/adaptor/taken.hpp>
#include <boost/range/adaptor/dropped.hpp>

namespace boost {
namespace range {

    namespace result_of {

        template <class SinglePassRange>
        struct split_at {
        private:
            typedef typename ::boost::range_detail::taken_range<SinglePassRange>::result_type taken_type;
            typedef typename ::boost::range_detail::dropped_range<SinglePassRange>::result_type dropped_type;
        public:
            typedef std::pair<taken_type, dropped_type> type;
        };

    } // namespace result_of

    template <class SinglePassRange>
    inline typename result_of::split_at<SinglePassRange>::type
        split_at(SinglePassRange& rng, typename boost::range_difference<SinglePassRange>::type n)
    {
        typedef typename result_of::split_at<SinglePassRange>::type result_type;
        return result_type(rng | adaptors::taken(n),
                           rng | adaptors::dropped(n));
    }

    template <class SinglePassRange>
    inline typename result_of::split_at<const SinglePassRange>::type
        split_at(const SinglePassRange& rng, typename boost::range_difference<SinglePassRange>::type n)
    {
        typedef typename result_of::split_at<const SinglePassRange>::type result_type;
        return result_type(rng | adaptors::taken(n),
                           rng | adaptors::dropped(n));
    }

} // namespace range

using range::split_at;

} // namespace boost

#endif // BOOST_RANGE_SPLIT_AT_IMPL_INCLUDE


