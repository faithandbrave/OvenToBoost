#ifndef BOOST_RANGE_ADAPTOR_MEMOIZED_INCLUDE
#define BOOST_RANGE_ADAPTOR_MEMOIZED_INCLUDE

// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/concept_check.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/adaptor/argument_fwd.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/range/adaptor/detail/memoized_iterator.hpp>

namespace boost {

namespace range_detail {

    template <class Range>
    struct memoized_range_result {
        typedef
            boost::adaptors::detail::memoize_iterator<
                boost::shared_ptr<
                    boost::adaptors::detail::memo<typename range_iterator<Range>::type>
                >
            >
        iter_t;

        typedef
            iterator_range<iter_t> const
        type;
    };

    template <class Range>
    struct memoized_range : memoized_range_result<Range>::type {
        typedef typename memoized_range_result<Range>::iter_t iter_t;
        typedef typename memoized_range_result<Range>::type base;
        typedef typename iter_t::memo_type memo_t;

        explicit memoized_range(Range& rng)
            : base(
                  iter_t(::boost::make_shared<memo_t>(::boost::begin(rng))),
                  iter_t(::boost::make_shared<memo_t>(::boost::end(rng)))
              )
        {}
    };

    struct memoized_forwarder {};

    template <class SinglePassRange>
    inline memoized_range<SinglePassRange>
        operator|(SinglePassRange& rng, memoized_forwarder)
    {
        return memoized_range<SinglePassRange>(rng);
    }

    template <class SinglePassRange>
    inline memoized_range<const SinglePassRange>
        operator|(const SinglePassRange& rng, memoized_forwarder)
    {
        return memoized_range<const SinglePassRange>(rng);
    }

} // namespace range_detail

using range_detail::memoized_range;

namespace adaptors {
    namespace {
        const range_detail::memoized_forwarder memoized = {};
    }

    template <class SinglePassRange>
    inline memoized_range<SinglePassRange>
        memoize(SinglePassRange& rng)
    {
        return memoized_range<SinglePassRange>(rng);
    }

    template <class SinglePassRange>
    inline memoized_range<const SinglePassRange>
        memoize(const SinglePassRange& rng)
    {
        return memoized_range<const SinglePassRange>(rng);
    }

} // namespace adaptors

} // namespace boost

#endif // BOOST_RANGE_ADAPTOR_MEMOIZED_INCLUDE

