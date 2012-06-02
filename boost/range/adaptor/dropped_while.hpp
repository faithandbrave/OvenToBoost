#ifndef BOOST_RANGE_ADAPTOR_DROPPED_WHILE_IMPL_HPP
#define BOOST_RANGE_ADAPTOR_DROPPED_WHILE_IMPL_HPP

// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>
#ifdef BOOST_MSVC
#pragma warning( push )
#pragma warning( disable : 4355 )
#endif

#include <boost/concept_check.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/adaptor/argument_fwd.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/regular.hpp>
#include <boost/range/adaptor/regular_operator.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include "./detail/not_.hpp"

namespace boost {

namespace range_detail {

    template< class Range >
    struct dropped_while_range : iterator_range<typename range_iterator<Range>::type> {
        typedef typename range_iterator<Range>::type iter_t;

        typedef iterator_range<iter_t> base;

        template <class UnaryPredicate>
        dropped_while_range(Range& rng, UnaryPredicate pred)
            : base(std::find_if(::boost::begin(rng), ::boost::end(rng),
                                boost::adaptors::detail::not_(pred)),
                   ::boost::end(rng))
        {
            BOOST_CONCEPT_ASSERT((SinglePassRangeConcept<Range>));
        }
    };

    template< class T >
    struct dropped_while_holder : holder<T>
    {
        dropped_while_holder( T r ) : holder<T>(r)
        { }
    };

    BOOST_RANGE_ADAPTOR_MAKE_REGULAR_OPERATOR(dropped_while_holder);

    template< class SinglePassRng, class UnaryPredicate >
    inline dropped_while_range<SinglePassRng>
    operator|( SinglePassRng& r,
               const dropped_while_holder<UnaryPredicate>& f )
    {
        return dropped_while_range<SinglePassRng>( r, f.val );
    }

    template< class SinglePassRng, class UnaryPredicate >
    inline dropped_while_range<const SinglePassRng>
    operator|( const SinglePassRng& r,
               const dropped_while_holder<UnaryPredicate>& f )
    {
        return dropped_while_range<const SinglePassRng>( r, f.val );
    }
} // namespace range_detail

    using range_detail::dropped_while_range;

    namespace adaptors
    {
        namespace
        {
            const range_detail::forwarder<range_detail::dropped_while_holder>
                dropped_while =
                   range_detail::forwarder<range_detail::dropped_while_holder>();
        }

        template<class SinglePassRng, class UnaryPredicate>
        inline dropped_while_range<SinglePassRng>
        drop_while(SinglePassRng& rng, UnaryPredicate pred)
        {
            return dropped_while_range<SinglePassRng>(rng, pred);
        }

        template<class SinglePassRng, class UnaryPredicate>
        inline dropped_while_range<const SinglePassRng>
        drop_while(const SinglePassRng& rng, UnaryPredicate pred)
        {
            return dropped_while_range<const SinglePassRng>(rng, pred);
        }

    } // namespace adaptors


} // namespace boost

#ifdef BOOST_MSVC
#pragma warning( pop )
#endif

#endif // BOOST_RANGE_ADAPTOR_DROPPED_WHILE_IMPL_HPP

