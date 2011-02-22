#ifndef BOOST_RANGE_ADAPTOR_OUTDIRECTED_IMPL_HPP
#define BOOST_RANGE_ADAPTOR_OUTDIRECTED_IMPL_HPP

// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/range/adaptor/argument_fwd.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/counting_range.hpp>

namespace boost {
namespace range_detail {

    template <class SinglePassRng>
    struct outdirected_range {
        typedef typename range_iterator<SinglePassRng>::type iter_t;

        typedef
            iterator_range<counting_iterator<iter_t> > const
        result_type;

        result_type operator()(SinglePassRng& rng) const
        {
//            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return counting_range(boost::begin(rng), boost::end(rng));
        }
    };

    struct outdirect_forwarder {};

    template< class SinglePassRng >
    inline typename outdirected_range<const SinglePassRng>::result_type
    operator|( SinglePassRng& r, outdirect_forwarder )
    {
        return outdirected_range<SinglePassRng>()( r );
    }

    template< class SinglePassRng >
    inline typename outdirected_range<const SinglePassRng>::result_type
    operator|( const SinglePassRng& r, outdirect_forwarder )
    {
        return outdirected_range<const SinglePassRng>()( r );
    }

} // namespace range_detail

    using range_detail::outdirected_range;

    namespace adaptors
    {
        namespace
        {
            const range_detail::outdirect_forwarder outdirected =
                                            range_detail::outdirect_forwarder();
        }

        template<class SinglePassRng>
        inline typename outdirected_range<SinglePassRng>::result_type
        outdirect(SinglePassRng& rng)
        {
            return outdirected_range<SinglePassRng>()(rng);
        }

        template<class SinglePassRng>
        inline typename outdirected_range<const SinglePassRng>::result_type
        outdirect(const SinglePassRng& rng)
        {
            return outdirected_range<const SinglePassRng>()(rng);
        }

    } // namespace adaptors

} // namespace boost


#endif // BOOST_RANGE_ADAPTOR_OUTDIRECTED_IMPL_HPP

