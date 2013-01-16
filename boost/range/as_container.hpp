#ifndef BOOST_RANGE_AS_CONTAINER_INCLUDE
#define BOOST_RANGE_AS_CONTAINER_INCLUDE

// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// via pstade::oven::copied

#include <boost/config.hpp>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST) && !defined(BOOST_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS)
#define BOOST_RANGE_ENABLE_AS_CONTAINER_SFINAE
#endif

#if defined(BOOST_RANGE_ENABLE_AS_CONTAINER_SFINAE)
#include <initializer_list>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/bool.hpp>
#endif

namespace boost {

namespace range_detail {

#if defined(BOOST_RANGE_ENABLE_AS_CONTAINER_SFINAE)
template <class>
struct is_initializer_list : mpl::false_ {};

template <class T>
struct is_initializer_list<std::initializer_list<T> > : mpl::true_ {};
#endif

template <class Range>
class as_container_wrapper {
    Range range_;
public:
    explicit as_container_wrapper(Range& range)
        : range_(range) {}

#if defined(BOOST_RANGE_ENABLE_AS_CONTAINER_SFINAE)
    template <class Container,
              class Enable = typename boost::disable_if<is_initializer_list<Container>>::type>
    operator Container() const
    {
        return Container(::boost::begin(range_), ::boost::end(range_));
    }
#else
    template <class Container>
    operator Container() const
    {
        return Container(::boost::begin(range_), ::boost::end(range_));
    }
#endif
};

struct as_container_functor {
    template <class>
    struct result;

    template <class F, class Range>
    struct result<F(Range)> {
        typedef as_container_wrapper<const Range> type;
    };

    template <class Range>
    as_container_wrapper<const Range> operator()(const Range& r) const
    {
        return as_container_wrapper<const Range>(r);
    }
};

template <class Range>
inline as_container_wrapper<const Range>
    operator|(const Range& r, as_container_functor f)
{
    return f(r);
}

} // namespace range_detail

namespace {
    const range_detail::as_container_functor as_container = {};
}

} // namespace boost

#if defined(BOOST_RANGE_ENABLE_AS_CONTAINER_SFINAE)
#undef BOOST_RANGE_ENABLE_AS_CONTAINER_SFINAE
#endif

#endif // BOOST_RANGE_AS_CONTAINER_INCLUDE

