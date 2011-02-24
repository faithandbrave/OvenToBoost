#ifndef BOOST_RANGE_RANGE_DETAIL_ITERATION_ITERATOR_IMPL_HPP
#define BOOST_RANGE_RANGE_DETAIL_ITERATION_ITERATOR_IMPL_HPP

// Boost.Range 2.0 Extension library
// via PStade Oven Library, unfold_iterator
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/assert.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/optional.hpp>

namespace boost { namespace range { namespace detail {

template< class State, class Next >
struct iteration_iterator;


template< class State, class Next >
struct iteration_iterator_super
{
    typedef
        typename boost::remove_reference<
            typename boost::remove_cv<State>::type
        >::type
    val_t;

    typedef
        boost::iterator_facade<
            iteration_iterator<State, Next>,
            val_t,
            boost::single_pass_traversal_tag,
            State
        >
    type;
};


template< class State, class Next >
struct iteration_iterator :
    iteration_iterator_super<State, Next>::type
{
private:
    typedef iteration_iterator self_t;
    typedef typename iteration_iterator_super<State, Next>::type super_t;
    typedef typename super_t::reference ref_t;

public:
    iteration_iterator()
    { }

    iteration_iterator(State const& init, Next next) :
        m_state(init), m_next(next)
    { }

private:
    boost::optional<State> m_state;
    Next m_next;

    friend class boost::iterator_core_access;

    ref_t dereference() const
    {
        BOOST_ASSERT(m_state.is_initialized());
        return *m_state;
    }

    void increment()
    {
        BOOST_ASSERT(m_state.is_initialized());
        m_state = m_next(m_state.get());
    }

    bool equal(self_t const& other) const
    {
        return m_state.is_initialized() != other.m_state.is_initialized() ? false :
               !m_state.is_initialized() && !other.m_state.is_initialized() ? true :
               *m_state == *other.m_state;
    }
};

}}} // namespace boost::range::detail


#endif // BOOST_RANGE_RANGE_DETAIL_ITERATION_ITERATOR_IMPL_HPP

