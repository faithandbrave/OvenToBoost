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

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/reference.hpp>
#include <boost/range/value_type.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/assert.hpp>

namespace boost {

    namespace range_detail {

        struct front_t {
			template <class Signature>
			struct result;

			template <class F, class SinglePassRange>
			struct result<F(SinglePassRange&)> :
                range_reference<
				    BOOST_DEDUCED_TYPENAME remove_reference<SinglePassRange>::type
                > {};

            template <class SinglePassRange>
            BOOST_DEDUCED_TYPENAME range_reference<SinglePassRange>::type
                operator()(SinglePassRange& rng) const
            {
                BOOST_ASSERT(!boost::empty(rng));
                return *boost::begin(rng);
            }

            template <class SinglePassRange>
            BOOST_DEDUCED_TYPENAME range_reference<const SinglePassRange>::type
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
                    BOOST_DEDUCED_TYPENAME remove_reference<SinglePassRange>::type
                > {};

			template <class SinglePassRange>
			BOOST_DEDUCED_TYPENAME range_value<SinglePassRange>::type
				operator()(const SinglePassRange& rng) const
			{
				BOOST_ASSERT(!boost::empty(rng));
				return *boost::begin(rng);
			}
		};

        const front_t front = {};
		const value_front_t value_front = {};

        template <class SinglePassRange>
        BOOST_DEDUCED_TYPENAME range_reference<SinglePassRange>::type
            operator|(SinglePassRange& rng, const front_t& f)
        {
            return f(rng);
        }

        template <class SinglePassRange>
        BOOST_DEDUCED_TYPENAME range_reference<const SinglePassRange>::type
            operator|(const SinglePassRange& rng, const front_t& f)
        {
            return f(rng);
        }

		template <class SinglePassRange>
		BOOST_DEDUCED_TYPENAME range_value<SinglePassRange>::type
			operator|(const SinglePassRange& rng, const value_front_t& f)
		{
			return f(rng);
		}

    } // namespace range_detail

    namespace range { namespace access {
        using ::boost::range_detail::front;
		using ::boost::range_detail::value_front;
    }} // namespace range::access
}

#endif // BOOST_RANGE_ACCESS_FRONT_INCLUDE


