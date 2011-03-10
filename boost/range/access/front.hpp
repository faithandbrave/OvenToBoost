// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RANGE_ACCESS_FRONT_INCLUDE
#define BOOST_RANGE_ACCESS_FRONT_INCLUDE

#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/reference.hpp>
#include <boost/assert.hpp>

namespace boost {

    namespace range_detail {

        struct front_t {
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

        const front_t front = {};

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

    } // namespace range_detail

    namespace range { namespace access {
        using ::boost::range_detail::front;
    }} // namespace range::access
}

#endif // BOOST_RANGE_ACCESS_FRONT_INCLUDE


