// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011-2012.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/detail/lightweight_test.hpp>
#include <boost/range/regular.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>

struct nullary_functor {
    typedef int result_type;

    int operator()() const
    {
        return 1;
    }
};

template <class F>
void nullary_result_test(F)
{
    typedef typename boost::result_of<F()>::type result_type;
    BOOST_STATIC_ASSERT((boost::is_same<result_type, int>::value));

    typedef typename boost::tr1_result_of<F()>::type tr1_result_type;
    BOOST_STATIC_ASSERT((boost::is_same<tr1_result_type, int>::value));
}

int main()
{
    nullary_result_test(boost::regular(nullary_functor()));

    return boost::report_errors();
}
