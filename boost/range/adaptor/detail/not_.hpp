#ifndef BOOST_RANGE_ADAPTOR_DETAIL_NOT_HPP
#define BOOST_RANGE_ADAPTOR_DETAIL_NOT_HPP

// Boost Range Library
// polymorphic std::not1
//
// Copyright Akira Takahashi 2011.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace boost { namespace adaptors { namespace detail {

template <class UnaryPred>
class not_t {
    UnaryPred pred_;
public:
    typedef bool result_type;

    explicit not_t(UnaryPred pred)
        : pred_(pred) {}

    template <class A1>
    bool operator()(const A1& a1) const
    {
        return !pred_(a1);
    }

    template <class A1>
    bool operator()(A1& a1) const
    {
        return !pred_(a1);
    }
};

template <class UnaryPred>
inline not_t<UnaryPred> not_(UnaryPred pred)
{
    return not_t<UnaryPred>(pred);
}

} } } // namespace boost::range::adaptors::detail


#endif // BOOST_RANGE_ADAPTOR_DETAIL_NOT_HPP

