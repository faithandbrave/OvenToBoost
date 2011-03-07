#ifndef BOOST_RANGE_RANGE_DIRECTORY_RANGE_IMPL_INCLUDE
#define BOOST_RANGE_RANGE_DIRECTORY_RANGE_IMPL_INCLUDE

// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/filesystem/operations.hpp>
#include <boost/range/iterator_range.hpp>

namespace boost { namespace range {

inline iterator_range<filesystem::directory_iterator>
    directory_range(const filesystem::path& p)
{
    return make_iterator_range(filesystem::directory_iterator(p),
                               filesystem::directory_iterator());
}

inline iterator_range<filesystem::recursive_directory_iterator>
    recursive_directory_range(const filesystem::path& p)
{
	return make_iterator_range(filesystem::recursive_directory_iterator(p),
			                   filesystem::recursive_directory_iterator());
}

}} // namespace boost::range

#endif // BOOST_RANGE_RANGE_DIRECTORY_RANGE_IMPL_INCLUDE

