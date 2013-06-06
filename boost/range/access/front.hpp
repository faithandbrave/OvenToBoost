// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011-2013.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RANGE_ACCESS_FRONT_INCLUDE
#define BOOST_RANGE_ACCESS_FRONT_INCLUDE

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/reference.hpp>
#include <boost/range/value_type.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/assert.hpp>
#include <boost/optional.hpp>

namespace boost {

    namespace range_detail {

        struct front_t {
            template <class Signature>
            struct result;

            template <class F, class SinglePassRange>
            struct result<F(SinglePassRange&)> :
                range_reference<
                    typename remove_reference<SinglePassRange>::type
                > {};

            template <class SinglePassRange>
            typename range_reference<SinglePassRange>::type
                operator()(SinglePassRange& rng) const
            {
                BOOST_ASSERT(!boost::empty(rng));
                return *boost::begin(rng);
            }

            template <class SinglePassRange>
            typename range_reference<const SinglePassRange>::type
                operator()(const SinglePassRange& rng) const
            {
                BOOST_ASSERT(!boost::empty(rng));
                return *boost::begin(rng);
            }
        };

        struct value_front_t {
            template <class Signature>
            struct result;

            template <class F, class SinglePassRange>
            struct result<F(SinglePassRange)> :
                range_value<
                    typename remove_reference<SinglePassRange>::type
                > {};

            template <class SinglePassRange>
            typename range_value<SinglePassRange>::type
                operator()(const SinglePassRange& rng) const
            {
                BOOST_ASSERT(!boost::empty(rng));
                return *boost::begin(rng);
            }
        };

        struct optional_front_t {
            template <class Signature>
            struct result;

            template <class F, class SinglePassRange>
            struct result<F(SinglePassRange&)> {
                typedef boost::optional<
                    typename range_reference<
                        typename remove_reference<SinglePassRange>::type
                    >::type
                > type;
            };

            template <class SinglePassRange>
            boost::optional<typename range_reference<SinglePassRange>::type>
                operator()(SinglePassRange& rng) const
            {
                if (boost::begin(rng) != boost::end(rng)) {
                    return *boost::begin(rng);
                }
                else {
                    return boost::none;
                }
            }

            template <class SinglePassRange>
            boost::optional<typename range_reference<const SinglePassRange>::type>
                operator()(const SinglePassRange& rng) const
            {
                if (boost::begin(rng) != boost::end(rng)) {
                    return *boost::begin(rng);
                }
                else {
                    return boost::none;
                }
            }
        };

        const front_t front = {};
        const value_front_t value_front = {};
        const optional_front_t optional_front = {};

        template <class SinglePassRange>
        typename range_reference<SinglePassRange>::type
            operator|(SinglePassRange& rng, const front_t& f)
        {
            return f(rng);
        }

        template <class SinglePassRange>
        typename range_reference<const SinglePassRange>::type
            operator|(const SinglePassRange& rng, const front_t& f)
        {
            return f(rng);
        }

        template <class SinglePassRange>
        typename range_value<SinglePassRange>::type
            operator|(const SinglePassRange& rng, const value_front_t& f)
        {
            return f(rng);
        }

        template <class SinglePassRange>
        boost::optional<typename range_reference<SinglePassRange>::type>
            operator|(SinglePassRange& rng, const optional_front_t& f)
        {
            return f(rng);
        }

        template <class SinglePassRange>
        boost::optional<typename range_reference<const SinglePassRange>::type>
            operator|(const SinglePassRange& rng, const optional_front_t& f)
        {
            return f(rng);
        }

    } // namespace range_detail

    namespace range { namespace access {
        using ::boost::range_detail::front;
        using ::boost::range_detail::value_front;
        using ::boost::range_detail::optional_front;
    }} // namespace range::access
}

#endif // BOOST_RANGE_ACCESS_FRONT_INCLUDE


