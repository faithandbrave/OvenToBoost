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
#include <boost/operators.hpp> // totally_ordered

#if defined(BOOST_NO_VARIADIC_TEMPLATES) || defined(BOOST_NO_RVALUE_REFERENCES)
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
struct indirect_functor : boost::totally_ordered1< indirect_functor<F> >{
    typedef typename pointer_value<F>::type indirected_functor_type;
    typedef indirect_functor this_type;

    template <class Signature>
    struct result;

#if !defined(BOOST_NO_VARIADIC_TEMPLATES)
    template <class F2, class... Args>
    struct result<F2(Args...)> : boost::result_of<indirected_functor_type(Args...)> {};
#else
    #include "./indirect_functor_result_pp.hpp"
#endif

    F f;

    indirect_functor() {}
    indirect_functor(F f) : f(f) {}

#if !defined(BOOST_NO_VARIADIC_TEMPLATES) && !defined(BOOST_NO_RVALUE_REFERENCES)
    template <class... Args>
    typename boost::result_of<indirected_functor_type(Args...)>::type
        operator()(Args&&... args) const
    {
        return (*f)(static_cast<Args&&>(args)...);
    }

    template <class... Args>
    typename boost::result_of<indirected_functor_type(Args...)>::type operator()(Args&&... args)
    {
        return (*f)(static_cast<Args&&>(args)...);
    }
#else
    #include "./indirect_functor_invoke_pp.hpp"
#endif

    bool operator<(const this_type& other) const
    {
        return f < other.f;
    }

    bool operator==(const this_type& other) const
    {
        return f == other.f;
    }
};

}}} // namespace boost::range::detail

namespace boost {
#if !defined(BOOST_RESULT_OF_USE_DECLTYPE) || defined(BOOST_NO_DECLTYPE)
    template <class F>
    struct result_of<boost::range::detail::indirect_functor<F>()> {
        typedef typename boost::result_of<
            typename boost::range::detail::indirect_functor<F>::indirected_functor_type()
        >::type type;
    };
#endif
    template <class F>
    struct tr1_result_of<boost::range::detail::indirect_functor<F>()> {
        typedef typename boost::tr1_result_of<
            typename boost::range::detail::indirect_functor<F>::indirected_functor_type()
        >::type type;
    };
}

#endif // BOOST_RANGE_DETAIL_INDIRECT_FUNCTOR_INCLUDE

