#ifndef BOOST_RANGE_ADAPTOR_REGULAR_EXTENSION_TRANSFORMED_INCLUDE
#define BOOST_RANGE_ADAPTOR_REGULAR_EXTENSION_TRANSFORMED_INCLUDE

// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi, Kohei Takahashi, Koichi Oyama,
// Norihisa Fujita, Yusuke Ichinohe, Takatoshi Kondo, 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/regular.hpp>
#include <boost/range/adaptor/regular_operator.hpp>

namespace boost { namespace range_detail {

BOOST_RANGE_ADAPTOR_MAKE_REGULAR_OPERATOR(transform_holder);

}} // namespace boost::range_detail

#endif // BOOST_RANGE_ADAPTOR_REGULAR_EXTENSION_TRANSFORMED_INCLUDE


