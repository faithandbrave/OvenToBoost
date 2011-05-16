#ifndef BOOST_RANGE_ADAPTOR_TAKEN_WHILE_IMPL_HPP
#define BOOST_RANGE_ADAPTOR_TAKEN_WHILE_IMPL_HPP

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
#include <boost/range/regular.hpp>
#include <boost/range/adaptor/regular_operator.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include "./detail/pass_by_value.hpp"
#include "./detail/take_while_iterator.hpp"

namespace boost {

namespace range_detail {

    namespace taken_while_detail {
        template< class Predicate >
        struct read_then
        {
            template< class Iterator >
            bool operator()(Iterator it)
            {
                return m_pred(*it);
            }

            explicit read_then()
            { }

            explicit read_then(Predicate pred) :
                m_pred(pred)
            { }

        private:
            Predicate m_pred;
        };

    } // namespace taken_while_detail

    template< class Range, class Predicate >
    struct taken_while_range :
        iterator_range<
            boost::adaptors::detail::take_while_iterator<
                typename range_iterator<Range>::type,
                taken_while_detail::read_then<
                    typename ::boost::adaptors::detail::pass_by_value<Predicate>::type
                >
            >
        >
    {
        typedef
            taken_while_detail::read_then<
                typename ::boost::adaptors::detail::pass_by_value<Predicate>::type
            >
        read_then_pred_t;

        typedef
            boost::adaptors::detail::take_while_iterator<
                typename range_iterator<Range>::type,
                read_then_pred_t
            >
        iter_t;

        typedef iterator_range<iter_t> base;

        taken_while_range(Range& rng, Predicate pred)
            : base(iter_t(::boost::begin(rng), ::boost::end(rng), read_then_pred_t(pred)),
                   iter_t(::boost::end(rng), ::boost::end(rng), read_then_pred_t(pred)))
        {
            BOOST_CONCEPT_ASSERT((SinglePassRangeConcept<Range>));
        }
    };

    template< class T >
    struct taken_while_holder : holder<T>
    {
        taken_while_holder( T r ) : holder<T>(r)
        { }
    };

    BOOST_RANGE_ADAPTOR_MAKE_REGULAR_OPERATOR(taken_while_holder);
    
    template< class SinglePassRng, class BinPredicate >
    inline taken_while_range<SinglePassRng, BinPredicate>
        operator|( SinglePassRng& r,
                   const taken_while_holder<BinPredicate>& f )
    {
        return taken_while_range<SinglePassRng, BinPredicate>(r, f.val);
    }

    template< class SinglePassRng, class BinPredicate >
    inline taken_while_range<const SinglePassRng, BinPredicate>
        operator|( const SinglePassRng& r,
                   const taken_while_holder<BinPredicate>& f )
    {
        return taken_while_range<const SinglePassRng, BinPredicate>(r, f.val);
    }
} // namespace range_detail

    using range_detail::taken_while_range;

    namespace adaptors
    {
        namespace
        {
            const range_detail::forwarder<range_detail::taken_while_holder>
                taken_while =
                   range_detail::forwarder<range_detail::taken_while_holder>();
        }

        template<class SinglePassRng, class BinPredicate>
        inline taken_while_range<SinglePassRng, BinPredicate>
            take_while(SinglePassRng& rng, BinPredicate pred)
        {
            return taken_while_range<SinglePassRng, BinPredicate>(rng, pred);
        }

        template<class SinglePassRng, class BinPredicate>
        inline taken_while_range<const SinglePassRng, BinPredicate>
            take_while(const SinglePassRng& rng, BinPredicate pred)
        {
            return taken_while_range<const SinglePassRng, BinPredicate>(rng, pred);
        }

    } // namespace adaptors


} // namespace boost

#endif // BOOST_RANGE_ADAPTOR_TAKEN_WHILE_IMPL_HPP

