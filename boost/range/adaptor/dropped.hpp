#ifndef BOOST_RANGE_ADAPTOR_DROPPED_IMPL_HPP
#define BOOST_RANGE_ADAPTOR_DROPPED_IMPL_HPP

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

#include <algorithm> // min
#include <boost/range/adaptor/argument_fwd.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/difference_type.hpp>
#include <boost/range/traversal.hpp>

namespace boost {

namespace range_detail {

    template< class Range >
    struct dropped_range {
        typedef typename range_difference<Range>::type diff_t;
        typedef typename range_iterator<Range>::type iter_t;

        typedef iterator_range<iter_t> const result_type;

        result_type operator()(Range& rng, diff_t n) const
        {
//            BOOST_CONCEPT_ASSERT((SinglePass<Range>));
            return aux(::boost::begin(rng), ::boost::end(rng), n, typename boost::range_traversal<Range>::type());
        }

        template< class Iterator >
        result_type aux(Iterator first, Iterator last, diff_t n, boost::random_access_traversal_tag) const
        {
//            BOOST_CONCEPT_ASSERT((RandomAccess<Range>));
            return result_type(first + (std::min)(last - first, n), last);
        }

        template< class Iterator >
        result_type aux(Iterator first, Iterator last, diff_t n, boost::single_pass_traversal_tag) const
        {
            while (n != 0 && first != last) {
                ++first;
                --n;
            }

            return result_type(first, last);
        }
    };

    template< class T >
    struct dropped_holder : holder<T>
    {
        dropped_holder( T r ) : holder<T>(r)
        { }
    };

    template< class SinglePassRng >
    inline typename dropped_range<SinglePassRng>::result_type
    operator|( SinglePassRng& r,
               const dropped_holder<typename boost::range_difference<SinglePassRng>::type>& f )
    {
        return dropped_range<SinglePassRng>()( r, f.val );
    }

    template< class SinglePassRng >
    inline typename dropped_range<const SinglePassRng>::result_type
    operator|( const SinglePassRng& r,
               const dropped_holder<typename boost::range_difference<SinglePassRng>::type>& f )
    {
        return dropped_range<const SinglePassRng>()( r, f.val );
    }
} // namespace range_detail

    using range_detail::dropped_range;

    namespace adaptors
    {
        namespace
        {
            const range_detail::forwarder<range_detail::dropped_holder>
                dropped =
                   range_detail::forwarder<range_detail::dropped_holder>();
        }

        template<class SinglePassRng>
        inline typename dropped_range<SinglePassRng>::result_type
        drop(SinglePassRng& rng, typename boost::range_difference<SinglePassRng>::type n)
        {
            return dropped_range<SinglePassRng>()(rng, n);
        }

        template<class SinglePassRng>
        inline typename dropped_range<const SinglePassRng>::result_type
        drop(const SinglePassRng& rng, typename boost::range_difference<SinglePassRng>::type n)
        {
            return dropped_range<const SinglePassRng>()(rng, n);
        }

    } // namespace adaptors


} // namespace boost

#endif // BOOST_RANGE_ADAPTOR_DROPPED_IMPL_HPP

