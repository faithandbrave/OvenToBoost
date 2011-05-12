#ifndef BOOST_RANGE_ADAPTOR_TAKEN_IMPL_HPP
#define BOOST_RANGE_ADAPTOR_TAKEN_IMPL_HPP

// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>
#include <boost/concept_check.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/adaptor/argument_fwd.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include "./detail/take_while_iterator.hpp"

namespace boost {
namespace range_detail {

    namespace taken_detail {
        template< class Difference >
        struct countdown
        {
            template< class Iterator >
            bool operator()(Iterator)
            {
                return m_n--
                    != 0; // suppress a VC++ warning.
            }

            countdown() {}
            explicit countdown(Difference n) : m_n(make_diff(n)) {}

        private:
            static Difference make_diff(Difference n)
            {
                BOOST_ASSERT(0 <= n);
                return n;
            }

            Difference m_n;
        };
    } // namespace taken_detail

    template <class SinglePassRng>
    struct taken_range : iterator_range<
                            boost::adaptors::detail::take_while_iterator<
                                typename range_iterator<SinglePassRng>::type,
                                taken_detail::countdown<
                                    typename range_difference<SinglePassRng>::type
                                >
                            >
                         > {
        typedef typename
            range_difference<SinglePassRng>::type
        diff_t;

        typedef
            boost::adaptors::detail::take_while_iterator<
                typename range_iterator<SinglePassRng>::type,
                taken_detail::countdown<diff_t>
            >
        iter_t;

        typedef iterator_range<iter_t> base;

        taken_range(SinglePassRng& rng, diff_t n)
            : base(iter_t(::boost::begin(rng), ::boost::end(rng), taken_detail::countdown<diff_t>(n)),
                   iter_t(::boost::end(rng), ::boost::end(rng), taken_detail::countdown<diff_t>(n)))
        {
        }
    };

    template <class T>
    struct taken_holder : holder<T> {
        taken_holder(T r) : holder<T>(r) {}
    };

    template <class SinglePassRng, class Difference>
    inline taken_range<SinglePassRng>
    operator|( SinglePassRng& r, const taken_holder<Difference>& f )
    {
        return taken_range<SinglePassRng>(r, f.val);
    }

    template <class SinglePassRng, class Difference>
    inline BOOST_DEDUCED_TYPENAME taken_range<const SinglePassRng>::result_type
    operator|( const SinglePassRng& r, const taken_holder<Difference>& f )
    {
        return taken_range<const SinglePassRng>(r, f.val);
    }

} // namespace range_detail

    using range_detail::taken_range;

    namespace adaptors
    {
        namespace
        {
            const range_detail::forwarder<range_detail::taken_holder>
                taken =
                   range_detail::forwarder<range_detail::taken_holder>();
        }

        template<class SinglePassRng>
        inline taken_range<SinglePassRng>
        take(SinglePassRng& rng, BOOST_DEDUCED_TYPENAME range_difference<SinglePassRng>::type n)
        {
            return taken_range<SinglePassRng>(rng, n);
        }

        template<class SinglePassRng>
        inline taken_range<const SinglePassRng>
        take(const SinglePassRng& rng, BOOST_DEDUCED_TYPENAME range_difference<SinglePassRng>::type n)
        {
            return taken_range<const SinglePassRng>(rng, n);
        }

    } // namespace adaptors

} // namespace boost


#endif // BOOST_RANGE_ADAPTOR_TAKEN_IMPL_HPP

