// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RANGE_DETAIL_INDIRECT_FUNCTOR_INCLUDE
#define BOOST_RANGE_DETAIL_INDIRECT_FUNCTOR_INCLUDE

#include <boost/config.hpp>
#include <boost/utility/result_of.hpp>

#if defined(BOOST_HAS_VARIADIC_TMPL) && defined(BOOST_HAS_RVALUE_REFS)
    #include <utility> // std::forward
#else
    #include <boost/preprocessor/repetition/repeat.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_params.hpp>
    #include <boost/preprocessor/repetition/enum_binary_params.hpp>
    #include <boost/preprocessor/seq/for_each_i.hpp>
    #include <boost/preprocessor/seq/for_each_product.hpp>
    #include <boost/preprocessor/seq/size.hpp>
    #include <boost/preprocessor/facilities/expand.hpp>
    #include <boost/preprocessor/punctuation/comma.hpp>
    #include <boost/preprocessor/arithmetic/add.hpp>

    #if !defined(BOOST_RANGE_DETAIL_INDIRECT_FUNCTOR_MAX_ARITY)
        #define BOOST_RANGE_DETAIL_INDIRECT_FUNCTOR_MAX_ARITY 5
    #endif
#endif

namespace boost { namespace range { namespace detail {

template <class P>
struct pointer_value {
    typedef typename P::value_type type;
};

template <class T>
struct pointer_value<T*> {
    typedef T type;
};

template <class F>
struct indirect_functor {
    typedef typename pointer_value<F>::type indirected_functor_type;

    template <class Signature>
    struct result;

#if defined(BOOST_HAS_VARIADIC_TMPL)
    template <class F2, class... Args>
    struct result<F2(Args...)> : boost::result_of<indirected_functor_type(Args...)> {};
#else
    #include "./indirect_functor_result_pp.hpp"
#endif

    F f;

    indirect_functor() {}
    indirect_functor(F f) : f(f) {}

#if defined(BOOST_HAS_VARIADIC_TMPL) && defined(BOOST_HAS_RVALUE_REFS)
    template <class... Args>
    BOOST_DEDUCED_TYPENAME boost::result_of<indirected_functor_type(Args...)>::type
        operator()(Args&&... args) const
    {
        return (*f)(std::forward<Args>(args)...);
    }

    template <class... Args>
    BOOST_DEDUCED_TYPENAME boost::result_of<indirected_functor_type(Args...)>::type operator()(Args&&... args)
    {
        return (*f)(std::forward<Args>(args)...);
    }
#else
    #include "./indirect_functor_invoke_pp.hpp"
#endif
};

}}} // namespace boost::range::detail

#endif // BOOST_RANGE_DETAIL_INDIRECT_FUNCTOR_INCLUDE

