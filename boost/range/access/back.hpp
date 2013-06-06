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

#include <boost/config.hpp>
#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/reference.hpp>
#include <boost/range/value_type.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/next_prior.hpp>
#include <boost/assert.hpp>
#include <boost/optional.hpp>

namespace boost {

    namespace range_detail {

        struct back_t {
            template <class Singnature>
            struct result;

            template <class F, class BidirectionalRange>
            struct result<F(BidirectionalRange)> :
                range_reference<
                    typename remove_reference<BidirectionalRange>::type
                > {};

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

        struct value_back_t {
            template <class Signature>
            struct result;

            template <class F, class BidirectionalRange>
            struct result<F(BidirectionalRange)> :
                range_value<
                    typename remove_reference<BidirectionalRange>::type
                > {};

            template <class BidirectionalRange>
            typename range_value<BidirectionalRange>::type
                operator()(const BidirectionalRange& rng) const
            {
                BOOST_ASSERT(!boost::empty(rng));
                return *boost::prior(boost::end(rng));
            }
        };

        struct optional_back_t {
            template <class Singnature>
            struct result;

            template <class F, class BidirectionalRange>
            struct result<F(BidirectionalRange)> {
                typedef boost::optional<
                    typename range_reference<
                        typename remove_reference<BidirectionalRange>::type
                    >::type
                > type;
            };

            template <class BidirectionalRange>
            boost::optional<typename range_reference<BidirectionalRange>::type>
                operator()(BidirectionalRange& rng) const
            {
                if (boost::begin(rng) != boost::end(rng)) {
                    return *boost::prior(boost::end(rng));
                }
                else {
                    return boost::none;
                }
            }

            template <class BidirectionalRange>
            boost::optional<typename range_reference<const BidirectionalRange>::type>
                operator()(const BidirectionalRange& rng) const
            {
                if (boost::begin(rng) != boost::end(rng)) {
                    return *boost::prior(boost::end(rng));
                }
                else {
                    return boost::none;
                }
            }
        };


        const back_t back = {};
        const value_back_t value_back = {};
        const optional_back_t optional_back = {};

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

        template <class BidirectionalRange>
        typename range_value<BidirectionalRange>::type
            operator|(const BidirectionalRange& rng, const value_back_t& f)
        {
            return f(rng);
        }

        template <class BidirectionalRange>
        boost::optional<typename range_reference<BidirectionalRange>::type>
            operator|(BidirectionalRange& rng, const optional_back_t& f)
        {
            return f(rng);
        }

        template <class BidirectionalRange>
        boost::optional<typename range_reference<const BidirectionalRange>::type>
            operator|(const BidirectionalRange& rng, const optional_back_t& f)
        {
            return f(rng);
        }

    } // namespace range_detail

    namespace range { namespace access {
        using ::boost::range_detail::back;
        using ::boost::range_detail::value_back;
        using ::boost::range_detail::optional_back;
    }} // namespace range::access
}

#endif // BOOST_RANGE_ACCESS_BACK_INCLUDE


