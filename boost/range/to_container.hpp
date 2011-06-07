// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// via pstade::oven::copied

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost {

namespace range_detail {

template <class Range>
class to_container_wrapper {
    Range range_;
public:
    explicit to_container_wrapper(Range& range)
        : range_(range) {}

    template <class Container>
    operator Container() const
    {
        return Container(::boost::begin(range_), ::boost::end(range_));
    }
};

struct to_container_functor {
    template <class>
    struct result;

    template <class F, class Range>
    struct result<F(Range)> {
        typedef to_container_wrapper<const Range> type;
    };

    template <class Range>
    to_container_wrapper<const Range> operator()(const Range& r) const
    {
        return to_container_wrapper<const Range>(r);
    }
};

} // namespace range_detail

namespace {
    const range_detail::to_container_functor to_container = {};
}

template <class Range>
inline range_detail::to_container_wrapper<const Range>
    operator|(const Range& r, range_detail::to_container_functor f)
{
    return f(r);
}

} // namespace boost

