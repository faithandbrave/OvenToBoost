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

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/reference.hpp>
#include <boost/range/value_type.hpp>
#include <boost/range/distance.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/next_prior.hpp>
#include <boost/assert.hpp>

namespace boost {

    namespace range_detail {

        template <class Difference>
        struct at_forwarder {
			template <class Signature>
            struct result;

            template <class F, class RandomAccessRange>
            struct result<F(RandomAccessRange)> :
                range_reference<
                    BOOST_DEDUCED_TYPENAME remove_reference<RandomAccessRange>::type
                > {};

            Difference n;
            explicit at_forwarder(Difference n_) : n(n_) {}

			template <class RandomAccessRange>
            BOOST_DEDUCED_TYPENAME range_reference<RandomAccessRange>::type
                operator()(RandomAccessRange& rng) const
            {
                BOOST_ASSERT(0 <= n && n < distance(rng));
                return *(boost::begin(rng) + n);
            }

            template <class RandomAccessRange>
            BOOST_DEDUCED_TYPENAME range_reference<const RandomAccessRange>::type
                operator()(const RandomAccessRange& rng) const
            {
                BOOST_ASSERT(0 <= n && n < distance(rng));
                return *(boost::begin(rng) + n);
            }
        };

        template <class Difference>
        struct value_at_forwarder {
			template <class Signature>
            struct result;

            template <class F, class RandomAccessRange>
            struct result<F(RandomAccessRange)> :
                range_value<
                    BOOST_DEDUCED_TYPENAME remove_reference<RandomAccessRange>::type
                > {};

            Difference n;
            explicit value_at_forwarder(Difference n_) : n(n_) {}

			template <class RandomAccessRange>
            BOOST_DEDUCED_TYPENAME range_value<RandomAccessRange>::type
                operator()(const RandomAccessRange& rng) const
            {
                BOOST_ASSERT(0 <= n && n < distance(rng));
                return *(boost::begin(rng) + n);
            }
        };

        struct at_t {
            template <class Signature>
            struct result;

            template <class F, class RandomAccessRange>
            struct result<F(RandomAccessRange)> :
                range_reference<
                    BOOST_DEDUCED_TYPENAME remove_reference<RandomAccessRange>::type
                > {};

            template <class Difference>
            at_forwarder<Difference> operator()(Difference n) const
            {
                return at_forwarder<Difference>(n);
            }

            template <class RandomAccessRange>
            BOOST_DEDUCED_TYPENAME range_reference<RandomAccessRange>::type
                operator()(RandomAccessRange& rng,
                           BOOST_DEDUCED_TYPENAME range_difference<RandomAccessRange>::type n) const
            {
                BOOST_ASSERT(0 <= n && n < distance(rng));
                return *(boost::begin(rng) + n);
            }

            template <class RandomAccessRange>
            BOOST_DEDUCED_TYPENAME range_reference<const RandomAccessRange>::type
                operator()(const RandomAccessRange& rng,
                           BOOST_DEDUCED_TYPENAME range_difference<RandomAccessRange>::type n) const
            {
                BOOST_ASSERT(0 <= n && n < distance(rng));
                return *(boost::begin(rng) + n);
            }
        };

        struct value_at_t {
            template <class Signature>
            struct result;

            template <class F, class RandomAccessRange>
            struct result<F(RandomAccessRange)> :
                range_value<
                    BOOST_DEDUCED_TYPENAME remove_reference<RandomAccessRange>::type
                > {};

            template <class Difference>
            value_at_forwarder<Difference> operator()(Difference n) const
            {
                return value_at_forwarder<Difference>(n);
            }

            template <class RandomAccessRange>
            BOOST_DEDUCED_TYPENAME range_value<RandomAccessRange>::type
                operator()(const RandomAccessRange& rng,
                           BOOST_DEDUCED_TYPENAME range_difference<RandomAccessRange>::type n) const
            {
                BOOST_ASSERT(0 <= n && n < distance(rng));
                return *(boost::begin(rng) + n);
            }
        };

        const at_t at = {};
        const value_at_t value_at = {};

        template <class RandomAccessRange, class Difference>
        BOOST_DEDUCED_TYPENAME range_reference<RandomAccessRange>::type
            operator|(RandomAccessRange& rng, const at_forwarder<Difference>& f)
        {
            return f(rng);
        }

        template <class RandomAccessRange, class Difference>
        BOOST_DEDUCED_TYPENAME range_reference<const RandomAccessRange>::type
            operator|(const RandomAccessRange& rng, const at_forwarder<Difference>& f)
        {
            return f(rng);
        }

        template <class RandomAccessRange, class Difference>
        BOOST_DEDUCED_TYPENAME range_value<RandomAccessRange>::type
            operator|(const RandomAccessRange& rng, const value_at_forwarder<Difference>& f)
        {
            return f(rng);
        }

    } // namespace range_detail

    namespace range { namespace access {
        using ::boost::range_detail::at;
        using ::boost::range_detail::value_at;
    }} // namespace range::access
}

#endif // BOOST_RANGE_ACCESS_AT_INCLUDE


