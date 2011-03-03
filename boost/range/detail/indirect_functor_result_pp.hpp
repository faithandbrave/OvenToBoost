// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_RANGE_DETAIL_CREATE_INDIRECT_FUNCTOR_RESULT(z, n, _) \
    template <class F2 BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)> \
    struct result<F2(BOOST_PP_ENUM_PARAMS(n, A))> : \
        boost::result_of<indirected_functor_type((BOOST_PP_ENUM_PARAMS(n, A)))> {};
/* */

BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_RANGE_DETAIL_INDIRECT_FUNCTOR_MAX_ARITY),
                    BOOST_RANGE_DETAIL_CREATE_INDIRECT_FUNCTOR_RESULT, _)

