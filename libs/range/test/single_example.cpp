// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/range/single.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/lexical_cast.hpp>

std::string to_s(int x)
{
    return boost::lexical_cast<std::string>(x);
}

struct disper {
    template <class T>
    void operator()(const T& x) const
    {
        std::cout << x << std::endl;
    }
};

int main()
{
    const int a = 1;
    boost::for_each(boost::single(a), disper());
    boost::for_each(boost::single(a) | boost::adaptors::transformed(to_s), disper());
}
