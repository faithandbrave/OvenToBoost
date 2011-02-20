#ifndef BOOST_RANGE_TRAVERSAL_HPP
#define BOOST_RANGE_TRAVERSAL_HPP

// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/range/config.hpp>
#include <boost/range/iterator.hpp>
#include <boost/iterator/iterator_categories.hpp>

namespace boost
{
    template< class T >
    struct range_traversal : iterator_traversal< typename range_iterator<T>::type >
    { };
}

#endif // BOOST_RANGE_TRAVERSAL_HPP

