// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <boost/detail/lightweight_test.hpp>

#include <boost/range/directory_range.hpp>

#include <vector>
#include <string>
#include <boost/assign/list_of.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/range/algorithm/find.hpp>

template <class InputIterator, class Pred>
bool all(InputIterator first, InputIterator last, Pred pred)
{
    for (; first != last; ++first) {
        if (!pred(*first))
            return false;
    }
    return true;
}

template <class SinglePassRange, class Pred>
bool all(const SinglePassRange& rng, Pred pred)
{
    return all(boost::begin(rng), boost::end(rng), pred);
}

namespace {
    const std::vector<std::string> filenames = boost::assign::list_of
        ("a.txt")
        ("b.png")
        ("c_dir")
        ;

    const std::vector<std::string> recursive_filenames = boost::assign::list_of
        ("a.txt")
        ("b.png")
        ("c_dir")
        ("d.cpp")
        ;
}

bool exist_check(const boost::filesystem::path& p)
{
    return boost::find(filenames, p.filename()) != boost::end(filenames);
}

bool recursive_exist_check(const boost::filesystem::path& p)
{
    return boost::find(recursive_filenames, p.filename()) != boost::end(recursive_filenames);
}

int main()
{
    const boost::filesystem::path path("./directory_range_test_dir");

    BOOST_TEST(all(boost::directory_range(path), exist_check));
    BOOST_TEST(all(boost::recursive_directory_range(path), recursive_exist_check));

    return boost::report_errors();
}
