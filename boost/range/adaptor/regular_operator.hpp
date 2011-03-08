#ifndef BOOST_RANGE_ADAPTOR_REGULAR_OPERATOR_INCLUDE
#define BOOST_RANGE_ADAPTOR_REGULAR_OPERATOR_INCLUDE

// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi, Kohei Takahashi, Koichi Oyama,
// Norihisa Fujita, Yusuke Ichinohe, Takatoshi Kondo, 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#define BOOST_RANGE_ADAPTOR_MAKE_REGULAR_OPERATOR(HOLDER) \
    template< class T > \
    inline HOLDER<typename ::boost::range::result_of::regular<T>::type> \
    operator+(const HOLDER<T>& f) \
    { \
        return HOLDER<typename ::boost::range::result_of::regular<T>::type>(regular(f.val)); \
    } \
/* */


#endif // BOOST_RANGE_ADAPTOR_REGULAR_OPERATOR_INCLUDE


