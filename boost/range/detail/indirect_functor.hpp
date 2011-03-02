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

#include <boost/utility/result_of.hpp>

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

    template <class F2, class... Args>
    struct result<F2(Args...)> : boost::result_of<indirected_functor_type(Args...)> {};

    F f;

    indirect_functor() {}
    indirect_functor(F f) : f(f) {}

    template <class... Args>
    typename boost::result_of<indirected_functor_type(Args...)>::type
        operator()(Args&&... args) const
    {
        return (*f)(std::forward<Args>(args)...);
    }

    template <class... Args>
    typename boost::result_of<indirected_functor_type(Args...)>::type operator()(Args&&... args)
    {
        return (*f)(std::forward<Args>(args)...);
    }
};

}}} // namespace boost::range::detail

#endif // BOOST_RANGE_DETAIL_INDIRECT_FUNCTOR_INCLUDE

