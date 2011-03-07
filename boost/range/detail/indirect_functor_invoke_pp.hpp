// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_RANGE_DETAIL_INDIRECT_FUNCTOR_REF_ARG(n) A##n &a##n
#define BOOST_RANGE_DETAIL_INDIRECT_FUNCTOR_CONST_ARG(n) A##n const &a##n
#define BOOST_RANGE_DETAIL_INDIRECT_FUNCTOR_ARG(r,t,n,e) \
    BOOST_PP_COMMA_IF(n) BOOST_PP_EXPAND(BOOST_PP_CAT(BOOST_RANGE_DETAIL_INDIRECT_FUNCTOR_, e)(n))
/**/

#define BOOST_RANGE_DETAIL_INDIRECT_FUNCTOR_INVOKE_HELPER(n,arg_seq) \
    template <BOOST_PP_ENUM_PARAMS(BOOST_PP_EXPAND(BOOST_PP_SEQ_SIZE(arg_seq)), class A)> \
    typename boost::result_of<indirected_functor_type(BOOST_PP_ENUM_PARAMS(BOOST_PP_EXPAND(BOOST_PP_SEQ_SIZE(arg_seq)), A))>::type \
        operator()(BOOST_PP_SEQ_FOR_EACH_I(BOOST_RANGE_DETAIL_INDIRECT_FUNCTOR_ARG, 0, arg_seq)) \
        { \
            return (*f)(BOOST_PP_ENUM_PARAMS(BOOST_PP_EXPAND(BOOST_PP_SEQ_SIZE(arg_seq)), a)); \
        } \
\
    template <BOOST_PP_ENUM_PARAMS(BOOST_PP_EXPAND(BOOST_PP_SEQ_SIZE(arg_seq)), class A)> \
    typename boost::result_of<indirected_functor_type(BOOST_PP_ENUM_PARAMS(BOOST_PP_EXPAND(BOOST_PP_SEQ_SIZE(arg_seq)), A))>::type \
        operator()(BOOST_PP_SEQ_FOR_EACH_I(BOOST_RANGE_DETAIL_INDIRECT_FUNCTOR_ARG, 0, arg_seq)) const \
        { \
            return (*f)(BOOST_PP_ENUM_PARAMS(BOOST_PP_EXPAND(BOOST_PP_SEQ_SIZE(arg_seq)), a)); \
        } \
/**/

#define BOOST_RANGE_DETAIL_INDIRECT_FUNCTOR_MAKE_RC_SEQ(z,n,t) ((REF_ARG)(CONST_ARG))
#define BOOST_RANGE_DETAIL_INDIRECT_FUNCTOR_INVOKE(z,n,t) \
    BOOST_PP_SEQ_FOR_EACH_PRODUCT(BOOST_RANGE_DETAIL_INDIRECT_FUNCTOR_INVOKE_HELPER, \
                                  BOOST_PP_REPEAT(BOOST_PP_ADD(n,1), \
                                  BOOST_RANGE_DETAIL_INDIRECT_FUNCTOR_MAKE_RC_SEQ, 0))
/**/

typename boost::result_of<indirected_functor_type()>::type
    operator()()
{
    return (*f)();
}

typename boost::result_of<indirected_functor_type()>::type
    operator()() const
{
    return (*f)();
}

BOOST_PP_REPEAT(BOOST_RANGE_DETAIL_INDIRECT_FUNCTOR_MAX_ARITY, BOOST_RANGE_DETAIL_INDIRECT_FUNCTOR_INVOKE, 0)

#undef BOOST_RANGE_DETAIL_INDIRECT_FUNCTOR_INVOKE
#undef BOOST_RANGE_DETAIL_INDIRECT_FUNCTOR_MAKE_RC_SEQ
#undef BOOST_RANGE_DETAIL_INDIRECT_FUNCTOR_INVOKE_HELPER
#undef BOOST_RANGE_DETAIL_INDIRECT_FUNCTOR_ARG
#undef BOOST_RANGE_DETAIL_INDIRECT_FUNCTOR_CONST_ARG
#undef BOOST_RANGE_DETAIL_INDIRECT_FUNCTOR_REF_ARG
/* */

