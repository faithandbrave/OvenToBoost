#ifndef BOOST_RANGE_ADAPTOR_DETAIL_MEMOIZE_ITERATOR_INCLUDE
#define BOOST_RANGE_ADAPTOR_DETAIL_MEMOIZE_ITERATOR_INCLUDE


// via PStade.Oven
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


/*=============================================================================
    Copyright (c) 2001, Daniel C. Nuffer
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/


// References:
//
// [1] Daniel C. Nuffer, multi_pass iterator, Boost.Spirit, 2001.
//     http://www.boost.org/libs/spirit/doc/multi_pass.html


// Differences from References[1]:
//
// 1. No unique-check; rarely unique in range.
// 2. No end-iterator-check; it seems redundant.


// Note:
//
// According to 28.2.2.3/1, references to elements of deque is always valid
// if you don't insert the middle of the deque.


#include <deque>
#include <boost/assert.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/noncopyable.hpp>
#include <boost/pointee.hpp>


namespace boost { namespace adaptors { namespace detail {

template< class Iterator >
struct memo :
    private boost::noncopyable
{
private:
    typedef typename boost::iterator_value<Iterator>::type value_t;
    typedef std::deque<value_t> table_t;

public:
    typedef Iterator iterator_type;
    typedef typename table_t::size_type index_type;

    explicit memo(Iterator it) :
        m_base(it), m_baseIndex(0)
    {
    }

    bool is_in_table(index_type i) const
    {
        return is_in_table_aux(i);
    }

    value_t const& deref(index_type i) // strong
    {
        BOOST_ASSERT(i <= m_baseIndex);

        if (!is_in_table_aux(i)) {
            BOOST_ASSERT(i == m_baseIndex && m_baseIndex == m_table.size());
            m_table.push_back(*m_base); // strong
        }

        return m_table[i];
    }

    index_type next(index_type i) // strong
    {
        BOOST_ASSERT(i <= m_baseIndex);

        bool pushed = false;
        if (i == m_baseIndex) {
            if (m_baseIndex == m_table.size()) {
                m_table.push_back(*m_base); // strong
                pushed = true;
            }

            try {
                ++m_base;
            }
            catch (...) {
                if (pushed)
                    m_table.pop_back(); // nothrow
                throw;
            }

            ++m_baseIndex; // nothrow
        }

        return i + 1;
    }

    Iterator base() const
    {
        return m_base;
    }

private:
    Iterator m_base;
    index_type m_baseIndex;
    table_t m_table;

    bool is_in_table_aux(index_type i) const
    {
        BOOST_ASSERT(i <= m_baseIndex);
        return i != m_table.size();
    }
};


template< class MemoPtr >
struct memoize_iterator;


template< class MemoPtr >
struct memoize_iterator_super
{
    typedef typename
        boost::pointee<MemoPtr>::type
    memo_t;

    typedef typename
        memo_t::iterator_type
    iter_t;

    typedef typename
        boost::iterator_value<iter_t>::type
    value_t;

    typedef
        boost::iterator_facade<
            memoize_iterator<MemoPtr>,
            value_t,
            boost::forward_traversal_tag,
            value_t const&,
            typename boost::iterator_difference<iter_t>::type
        >
    type;
};


template< class MemoPtr >
struct memoize_iterator :
    memoize_iterator_super<MemoPtr>::type
{
private:
    typedef typename memoize_iterator_super<MemoPtr>::type super_t;
    typedef typename super_t::reference ref_t;

public:
    typedef typename boost::pointee<MemoPtr>::type memo_type;
 
    explicit memoize_iterator()
    { }

    explicit memoize_iterator(MemoPtr const& pmemo) :
        m_pmemo(pmemo), m_index(0)
    { }

// as adaptor
    typedef typename memo_type::iterator_type base_type;

    base_type base() const
    {
        return m_pmemo->base();
    }

private:
    MemoPtr m_pmemo;
    typename memo_type::index_type m_index;

    bool is_in_table() const
    {
        return m_pmemo->is_in_table(m_index);
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        return m_pmemo->deref(m_index);
    }

    bool equal(memoize_iterator const& other) const
    {
        if (is_in_table() && other.is_in_table())
            return m_index == other.m_index;
        else if (!is_in_table() && !other.is_in_table())
            return base() == other.base();
        else
            return false;
    }

    void increment()
    {
        m_index = m_pmemo->next(m_index);
    }
};


} } } // namespace boost::adaptors::detail


#endif // BOOST_RANGE_ADAPTOR_DETAIL_MEMOIZE_ITERATOR_INCLUDE

