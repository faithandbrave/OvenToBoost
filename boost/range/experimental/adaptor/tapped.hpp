#ifndef BOOST_RANGE_ADAPTOR_TAPPED_INCLUDE
#define BOOST_RANGE_ADAPTOR_TAPPED_INCLUDE

// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/range/adaptor/regular_extension/transformed.hpp>

namespace boost {
namespace range_detail {

template <class F, class ValueType>
class tapped_functor {
    F f;
public:
    typedef ValueType result_type;

    explicit tapped_functor(F f)
        : f(f) {}

    result_type operator()(const result_type& x) const
    {
        f(x);
        return x;
    }
};

template <class ForwardRng, class F>
struct tap_result {
    typedef
        tapped_functor<F, typename boost::range_value<ForwardRng>::type>
    functor;

    typedef
        boost::transformed_range<
            functor,
            ForwardRng
        >
    type;
};

template <class T>
struct tap_holder : holder<T> {
    tap_holder(T r) : holder<T>(r) {}
};

template <class ForwardRng, class UnaryFunction>
inline typename tap_result<ForwardRng, UnaryFunction>::type
    operator|(ForwardRng& rng, const tap_holder<UnaryFunction>& f)
{
    typedef typename tap_result<ForwardRng, UnaryFunction>::functor functor;
    return rng | boost::adaptors::transformed(functor(f.val));
}

template <class ForwardRng, class UnaryFunction>
inline typename tap_result<const ForwardRng, UnaryFunction>::type
    operator|(const ForwardRng& rng, const tap_holder<UnaryFunction>& f)
{
    typedef typename tap_result<const ForwardRng, UnaryFunction>::functor functor;
    return rng | boost::adaptors::transformed(functor(f.val));
}


BOOST_RANGE_ADAPTOR_MAKE_REGULAR_OPERATOR(tap_holder);

} // namespace range_detail

namespace adaptors {

namespace
{
    const range_detail::forwarder<range_detail::tap_holder>
            tapped =
              range_detail::forwarder<range_detail::tap_holder>();
}


template <class ForwardRng, class F>
inline typename range_detail::tap_result<ForwardRng, F>::type
    tap(ForwardRng& rng, F f)
{
    return rng | tapped(f);
}

template <class ForwardRng, class F>
inline typename range_detail::tap_result<const ForwardRng, F>::type
    tap(const ForwardRng& rng, F f)
{
    return rng | tapped(f);
}


}} // namespace boost::adaptors

#endif // BOOST_RANGE_ADAPTOR_TAPPED_INCLUDE

