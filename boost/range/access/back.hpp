// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RANGE_ACCESS_BACK_INCLUDE
#define BOOST_RANGE_ACCESS_BACK_INCLUDE

#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/reference.hpp>
#include <boost/next_prior.hpp>
#include <boost/assert.hpp>

namespace boost {

    namespace range_detail {

        struct back_t {
            template <class BidirectionalRange>
            typename range_reference<BidirectionalRange>::type
                operator()(BidirectionalRange& rng) const
            {
                BOOST_ASSERT(!boost::empty(rng));
                return *boost::prior(boost::end(rng));
            }

            template <class BidirectionalRange>
            typename range_reference<const BidirectionalRange>::type
                operator()(const BidirectionalRange& rng) const
            {
                BOOST_ASSERT(!boost::empty(rng));
                return *boost::prior(boost::end(rng));
            }
        };

        const back_t back = {};

        template <class BidirectionalRange>
        typename range_reference<BidirectionalRange>::type
            operator|(BidirectionalRange& rng, const back_t& f)
        {
            return f(rng);
        }

        template <class BidirectionalRange>
        typename range_reference<const BidirectionalRange>::type
            operator|(const BidirectionalRange& rng, const back_t& f)
        {
            return f(rng);
        }

    } // namespace range_detail

    namespace range { namespace access {
        using ::boost::range_detail::back;
    }} // namespace range::access
}

#endif // BOOST_RANGE_ACCESS_BACK_INCLUDE


