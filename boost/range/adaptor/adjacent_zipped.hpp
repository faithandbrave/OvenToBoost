#ifndef BOOST_RANGE_ADAPTOR_ADJACENT_ZIPPED_IMPL_HPP
#define BOOST_RANGE_ADAPTOR_ADJACENT_ZIPPED_IMPL_HPP

// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011-2012.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>
#include <boost/concept_check.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/adaptor/argument_fwd.hpp>
#include <boost/range/adaptor/dropped.hpp>
#include <boost/range/combine.hpp>
#include <boost/range/iterator.hpp>
#include <boost/next_prior.hpp>
#include <boost/tuple/tuple.hpp>

namespace boost {

namespace range_detail {
    struct adjacent_zipped_forwarder {};

    template <class BidirectionalRng>
    struct adjacent_zipped_range
        : boost::range::combined_range<boost::tuple<
              typename boost::range_iterator<BidirectionalRng>::type,
              typename boost::range_iterator<
                  const boost::dropped_range<BidirectionalRng>
              >::type
          > > {

        BOOST_RANGE_CONCEPT_ASSERT((BidirectionalRangeConcept<BidirectionalRng>));

        typedef
            boost::range::combined_range<boost::tuple<
                typename boost::range_iterator<BidirectionalRng>::type,
                typename boost::range_iterator<
                    const boost::dropped_range<BidirectionalRng>
                >::type
            > >
        base;

        explicit adjacent_zipped_range(BidirectionalRng& r)
            : base(boost::combine(
                        boost::make_iterator_range(boost::begin(r), get_end(r)),
                        r | boost::adaptors::dropped(get_drop_count(r))
                    )) {}

    private:
        static typename boost::range_iterator<BidirectionalRng>::type get_end(BidirectionalRng& r)
        {
            typedef typename boost::range_iterator<BidirectionalRng>::type iter;
            iter first = boost::begin(r);
            iter last = boost::end(r);
            return first == last ? last : boost::prior(last);
        }

        static typename boost::range_difference<BidirectionalRng>::type
            get_drop_count(BidirectionalRng& r)
        {
            typedef typename boost::range_iterator<BidirectionalRng>::type iter;
            iter first = boost::begin(r);
            iter last = boost::end(r);
            return first == last ? 0 : 1;
        }
    };

    template <class BidirectionalRng>
    inline adjacent_zipped_range<BidirectionalRng>
    operator|(BidirectionalRng& r, adjacent_zipped_forwarder)
    {
        return adjacent_zipped_range<BidirectionalRng>(r);
    }

    template <class BidirectionalRng>
    inline adjacent_zipped_range<const BidirectionalRng>
    operator|(const BidirectionalRng& r, adjacent_zipped_forwarder)
    {
        return adjacent_zipped_range<const BidirectionalRng>(r);
    }

} // namespace range_detail

    using range_detail::adjacent_zipped_range;

    namespace adaptors
    {
        namespace
        {
            const range_detail::adjacent_zipped_forwarder adjacent_zipped = {};
        }

        template <class BidirectionalRng>
        inline adjacent_zipped_range<BidirectionalRng>
        adjacent_zip(BidirectionalRng& rng)
        {
            return rng | adjacent_zipped;
        }

        template <class BidirectionalRng>
        inline adjacent_zipped_range<const BidirectionalRng>
        adjacent_zip(const BidirectionalRng& rng)
        {
            return rng | adjacent_zipped;
        }

    } // namespace adaptors


} // namespace boost

#endif // BOOST_RANGE_ADAPTOR_ADJACENT_ZIPPED_IMPL_HPP

