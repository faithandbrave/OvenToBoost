// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RANGE_REGULAR_INCLUDE
#define BOOST_RANGE_REGULAR_INCLUDE

#include <boost/config.hpp>
#include "./detail/indirect_functor.hpp"
#include <boost/optional.hpp>
#include <boost/operators.hpp> // totally_ordered
#include <boost/swap.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace range {

namespace regular_detail {

template <class X>
struct dummy_assignable {
private:
    typedef dummy_assignable this_type;

public:
    X m_x;

    explicit dummy_assignable(const X& x)
        : m_x(x) {}

    // never called if uninitialized
    this_type& operator=(const this_type&)
    {
        BOOST_ASSERT(false);
        return *this;
    }
};

template <class X>
struct regularized :
    boost::totally_ordered1< regularized<X> > {
private:
    typedef regularized this_type;
    typedef dummy_assignable<X> dummy_assignable_t;
    typedef bool (this_type::*unspecified_bool_type)() const;

public:
    typedef X value_type;

// structors
    explicit regularized() {}

    explicit regularized(const X& x) :
        m_opx(dummy_assignable_t(x))
    { }

// assignments
    this_type& operator=(const this_type& other)
    {
        m_opx.reset(); // Force uninitialized.
        m_opx = other.m_opx;
        return *this;
    }

// dereference
    X& operator*()
    {
        return (*m_opx).m_x;
    }

    const X& operator*() const
    {
        return (*m_opx).m_x;
    }

// bool_testable
    operator unspecified_bool_type() const { return m_opx; }

// swappable
    void swap(this_type& other)
    {
        boost::swap(m_opx, other.m_opx);
    }

// totally_ordered
    bool operator<(const this_type& other) const
    {
        return m_opx < other.m_opx;
    }

    bool operator==(const this_type& other) const
    {
        return m_opx == other.m_opx;
    }

private:
    boost::optional<dummy_assignable_t> m_opx;
};

} // namespace regular_detail

namespace result_of {

template <class F>
struct regular : boost::mpl::identity<
                    detail::indirect_functor<regular_detail::regularized<F> >              
                > {};

} // namespace result_of

template <class F>
inline typename result_of::regular<F>::type regular(F f)
{
    return typename result_of::regular<F>::type(regular_detail::regularized<F>(f));
}

} // namespace range

using range::regular;

} // namespace boost

#endif // BOOST_RANGE_REGULAR_INCLUDE

