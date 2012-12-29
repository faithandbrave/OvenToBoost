#ifndef BOOST_RANGE_ADAPTOR_TAPPED_INCLUDE
#define BOOST_RANGE_ADAPTOR_TAPPED_INCLUDE

// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <algorithm>
#include <boost/range/adaptor/regular_extension/transformed.hpp>

namespace boost {
namespace range_detail {

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

template <class T>
struct tap_holder : holder<T> {
    tap_holder(T r) : holder<T>(r) {}
};

template <class ForwardRng, class UnaryFunction>
inline iterator_range<
            tap_iterator<UnaryFunction, typename range_iterator<ForwardRng>::type> >
    operator|(ForwardRng& rng, const tap_holder<UnaryFunction>& f)
{
    typedef tap_iterator<UnaryFunction, typename range_iterator<ForwardRng>::type> iterator;
    return make_iterator_range(iterator(f.val, boost::begin(rng), boost::end(rng)), iterator(boost::end(rng)));
}

template <class ForwardRng, class UnaryFunction>
inline iterator_range<
            tap_iterator<UnaryFunction, typename range_iterator<const ForwardRng>::type> >
    operator|(const ForwardRng& rng, const tap_holder<UnaryFunction>& f)
{
    typedef tap_iterator<UnaryFunction, typename range_iterator<const ForwardRng>::type> iterator;
    return make_iterator_range(iterator(f.val, boost::begin(rng), boost::end(rng)), iterator(boost::end(rng)));
}


BOOST_RANGE_ADAPTOR_MAKE_REGULAR_OPERATOR(tap_holder);

} // namespace range_detail

namespace adaptors {

using range_detail::tap_iterator;

namespace
{
    const range_detail::forwarder<range_detail::tap_holder>
            tapped =
              range_detail::forwarder<range_detail::tap_holder>();
}


template <class ForwardRng, class UnaryFunction>
inline iterator_range<
            tap_iterator<UnaryFunction, typename range_iterator<ForwardRng>::type> >
    tap(ForwardRng& rng, UnaryFunction f)
{
    return rng | tapped(f);
}

template <class ForwardRng, class UnaryFunction>
inline iterator_range<
            tap_iterator<UnaryFunction, typename range_iterator<ForwardRng>::type> >
    tap(const ForwardRng& rng, UnaryFunction f)
{
    return rng | tapped(f);
}

}} // namespace boost::adaptors

#endif // BOOST_RANGE_ADAPTOR_TAPPED_INCLUDE

