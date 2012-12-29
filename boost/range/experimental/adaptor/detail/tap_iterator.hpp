#ifndef BOOST_RANGE_ADAPTOR_DETAIL_TAP_ITERATOR_INCLUDE
#define BOOST_RANGE_ADAPTOR_DETAIL_TAP_ITERATOR_INCLUDE

// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011-2012.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <algorithm>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace adaptors { namespace detail {

template <class UnaryFunction, class Iterator>
class tap_iterator;

template <class UnaryFunction, class Iterator>
struct tap_iterator_base {
    typedef iterator_adaptor<
        tap_iterator<UnaryFunction, Iterator>
      , Iterator
      , use_default
      , typename mpl::if_<
            is_convertible<
                typename iterator_traversal<Iterator>::type
              , random_access_traversal_tag
            >
          , bidirectional_traversal_tag
          , use_default
        >::type
    > type;
};

template <class UnaryFunction, class Iterator>
class tap_iterator : public tap_iterator_base<UnaryFunction, Iterator>::type {
    typedef typename tap_iterator_base<
          UnaryFunction, Iterator
    >::type super_t;

    friend class iterator_core_access;

    UnaryFunction m_func;
    Iterator m_first;
    Iterator m_end;
    mutable bool m_applied;

public:
    tap_iterator(Iterator x)
        : super_t(x), m_applied(true) {}

    tap_iterator(UnaryFunction f, Iterator x, Iterator end_)
        : super_t(x), m_func(f), m_first(x), m_end(end_), m_applied(false) {}

    typename super_t::reference dereference() const
    {
        apply_func();
        return *this->base();
    }

private:
    void apply_func() const
    {
        if (!m_applied) {
            std::for_each(m_first, m_end, m_func);
            m_applied = true;
        }
    }
};

}}} // namespace boost::adaptors::detail

#endif // BOOST_RANGE_ADAPTOR_DETAIL_TAP_ITERATOR_INCLUDE

