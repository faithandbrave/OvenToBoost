#ifndef BOOST_RANGE_RANGE_ITERATION_IMPL_HPP
#define BOOST_RANGE_RANGE_ITERATION_IMPL_HPP

// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/range/iterator_range.hpp>
#include "./detail/iteration_iterator.hpp"

namespace boost {

namespace range {
    template <class Init, class Next>
    inline iterator_range<detail::iteration_iterator<Init, Next> > iteration(const Init& init, Next next)
    {
        typedef detail::iteration_iterator<Init, Next> iter_t;
        return make_iterator_range(iter_t(init, next), iter_t());
    }

} // namespace range

} // namespace boost


#endif // BOOST_RANGE_RANGE_ITERATION_IMPL_HPP

