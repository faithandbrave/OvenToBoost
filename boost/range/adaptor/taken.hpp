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

			explicit countdown()
			{ }

			explicit countdown(Difference n) :
				m_n(n)
			{ }

		private:
			Difference m_n;
		};
	} // namespace taken_detail

	template <class SinglePassRng>
	struct taken_range {
		typedef typename
            range_difference<SinglePassRng>::type
        diff_t;

        typedef
            boost::adaptors::detail::take_while_iterator<
                typename range_iterator<SinglePassRng>::type,
                taken_detail::countdown<diff_t>
            >
        iter_t;

        typedef
            iterator_range<iter_t> const
        result_type;

        result_type operator()(SinglePassRng& rng, diff_t n) const
        {
//            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            BOOST_ASSERT(0 <= n);
            return aux(boost::begin(rng), boost::end(rng), taken_detail::countdown<diff_t>(n));
        }

        template< class Iterator >
        result_type aux(Iterator first, Iterator last, taken_detail::countdown<diff_t> cd) const
        {
            return result_type(iter_t(first, last, cd), iter_t(last, last, cd));
        }

	};

	template< class T >
    struct taken_holder : holder<T>
    {
        taken_holder( T r ) : holder<T>(r)
        { }
    };

	template< class SinglePassRng >
    inline typename taken_range<const SinglePassRng>::result_type
	operator|( SinglePassRng& r,
			   const taken_holder<typename range_difference<SinglePassRng>::type>& f )
	{
		return taken_range<SinglePassRng>()( r, f.val );
	}

	template< class SinglePassRng >
	inline typename taken_range<const SinglePassRng>::result_type
	operator|( const SinglePassRng& r,
			   const taken_holder<typename range_difference<SinglePassRng>::type>& f )
	{
		return taken_range<const SinglePassRng>()( r, f.val );
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
        inline typename taken_range<SinglePassRng>::result_type
        take(SinglePassRng& rng, typename range_difference<SinglePassRng>::type n)
        {
            return taken_range<SinglePassRng>()(rng, n);
        }

        template<class SinglePassRng>
        inline typename taken_range<const SinglePassRng>::result_type
        take(const SinglePassRng& rng, typename range_difference<SinglePassRng>::type n)
        {
            return taken_range<const SinglePassRng>()(rng, n);
        }

    } // namespace adaptors

} // namespace boost


#endif // BOOST_RANGE_ADAPTOR_TAKEN_IMPL_HPP

