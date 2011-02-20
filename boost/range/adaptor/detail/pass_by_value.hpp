#ifndef BOOST_RANGE_ADAPTOR_DETAIL_PASS_BY_HPP
#define BOOST_RANGE_ADAPTOR_DETAIL_PASS_BY_HPP

// via PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/decay.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/remove_cv.hpp>


namespace boost { namespace adaptors { namespace detail {


// same as 'detail::call_param' of Boost.Fusion2.
template< class T >
struct pass_by_reference :
    boost::mpl::eval_if< boost::is_reference<T>,
        boost::mpl::identity<T>,
        boost::add_reference<
            typename boost::add_const<
                typename boost::remove_cv<T>::type
            >::type
        >
    >
{ };


// removes cv-qualifier, cuz 'foo(int const)' is same as 'foo(int)'.
template< class T >
struct pass_by_value :
    boost::remove_cv< 
        // 'decay' calls 'remove_reference'.
        typename boost::decay<T>::type
    >
{ };


}}} // namespace boost::adaptors::detail


#endif // BOOST_RANGE_ADAPTOR_DETAIL_PASS_BY_HPP

