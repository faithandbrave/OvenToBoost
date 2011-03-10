// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RANGE_ACCESS_AT_INCLUDE
#define BOOST_RANGE_ACCESS_AT_INCLUDE

#include <boost/range/begin.hpp>
#include <boost/range/reference.hpp>
#include <boost/range/distance.hpp>
#include <boost/next_prior.hpp>
#include <boost/assert.hpp>

namespace boost {

    namespace range_detail {

        template <class Difference>
        struct at_forwarder {
            Difference n;
            explicit at_forwarder(Difference n_) : n(n_) {}
        };

        struct at_t {
            template <class Difference>
            at_forwarder<Difference> operator()(Difference n) const
            {
                return at_forwarder<Difference>(n);
            }

            template <class RandomAccessRange>
            typename range_reference<RandomAccessRange>::type
                operator()(RandomAccessRange& rng,
                           typename range_difference<RandomAccessRange>::type n) const
            {
                BOOST_ASSERT(0 <= n && n < distance(rng));
                return *(boost::begin(rng) + n);
            }

            template <class RandomAccessRange>
            typename range_reference<const RandomAccessRange>::type
                operator()(const RandomAccessRange& rng,
                           typename range_difference<RandomAccessRange>::type n) const
            {
                BOOST_ASSERT(0 <= n && n < distance(rng));
                return *(boost::begin(rng) + n);
            }
        };

        const at_t at = {};

        template <class RandomAccessRange, class Difference>
        typename range_reference<RandomAccessRange>::type
            operator|(RandomAccessRange& rng, const at_forwarder<Difference>& f)
        {
            return at(rng, f.n);
        }

        template <class RandomAccessRange, class Difference>
        typename range_reference<const RandomAccessRange>::type
            operator|(const RandomAccessRange& rng, const at_forwarder<Difference>& f)
        {
            return at(rng, f.n);
        }

    } // namespace range_detail

    namespace range { namespace access {
        using ::boost::range_detail::at;
    }} // namespace range::access
}

#endif // BOOST_RANGE_ACCESS_AT_INCLUDE


