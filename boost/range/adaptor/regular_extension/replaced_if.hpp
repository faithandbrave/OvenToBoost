#ifndef BOOST_RANGE_ADAPTOR_REGULAR_EXTENSION_REPLACED_IF_INCLUDE
#define BOOST_RANGE_ADAPTOR_REGULAR_EXTENSION_REPLACED_IF_INCLUDE

#include <boost/range/adaptor/replaced_if.hpp>
#include <boost/range/regular.hpp>

// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi, Kohei Takahashi, Koichi Oyama,
// Norihisa Fujita, Yusuke Ichinohe, Takatoshi Kondo, 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

namespace boost { namespace range_detail {

    template< class Pred, class T >
    inline replace_if_holder<typename ::boost::range::result_of::regular<Pred>::type, T>
    operator+(const replace_if_holder<Pred, T>& f)
    {
        typedef
            replace_if_holder<
                typename ::boost::range::result_of::regular<Pred>::type, T
            >
        result_type;

        return result_type(regular(f.pred()), f.to());
    }

}} // namespace boost::range_detail

#endif // BOOST_RANGE_ADAPTOR_REGULAR_EXTENSION_REPLACED_IF_INCLUDE


