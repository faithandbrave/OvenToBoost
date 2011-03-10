#ifndef BOOST_RANGE_RANGE_SINGLE_IMPL_HPP
#define BOOST_RANGE_RANGE_SINGLE_IMPL_HPP

// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/utility/addressof.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost {

namespace range {
	template <class T>
	inline iterator_range<const T*> single(const T& x)
	{
		return make_iterator_range(boost::addressof(x), boost::addressof(x) + 1);
	}

	template <class T>
	inline iterator_range<T*> single(T& x)
	{
		return make_iterator_range(boost::addressof(x), boost::addressof(x) + 1);
	}
} // namespace range

} // namespace boost


#endif // BOOST_RANGE_RANGE_SINGLE_IMPL_HPP

