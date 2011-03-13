// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <vector>
#include <string>
#include <boost/assign/list_of.hpp>
#include <boost/range/adaptor/regular_extension/transformed.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/lambda/lambda.hpp>

struct X {
    int a;
    std::string s;

    X(int a_, const std::string& s_) : a(a_), s(s_) {}
};

struct disper {
    template <class T>
    void operator()(const T& x) const
    {
        std::cout << x << std::endl;
    }
};

int main()
{
    const std::vector<X> v = boost::assign::list_of
        (X(1, "a"))
        (X(2, "b"))
        (X(3, "c"))
        ;

    using boost::lambda::_1;

    boost::for_each(v |+ boost::adaptors::transformed(&_1 ->* &X::s), disper());
}

/*
a
b
c

*/
