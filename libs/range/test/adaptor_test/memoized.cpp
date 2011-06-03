// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/detail/lightweight_test.hpp>
#include <boost/range/algorithm/equal.hpp>

#include <vector>
#include <algorithm>
#include <boost/assign/list_of.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/adaptor/memoized.hpp>

namespace {
	std::vector<int> call_history;
}

struct call_once_checker {
	typedef int result_type;

	int operator()(int x) const
	{
		call_history.push_back(x);
		return x;
	}
};

struct do_null {
	typedef void result_type;

	template <class Range>
	void operator()(const Range&) const {}
};

template <class Range>
void call_twise(const Range& rng)
{
	std::for_each(rng.begin(), rng.end(), do_null());
	std::for_each(rng.begin(), rng.end(), do_null());
}

void call_once_test()
{
	{
		std::vector<int> v = boost::assign::list_of(1)(2)(3);
		call_twise(v | boost::adaptors::transformed(call_once_checker())
				     | boost::adaptors::memoized);

		BOOST_TEST(boost::equal(v, call_history));
	}

	call_history.clear();

	{
		std::vector<int> v = boost::assign::list_of(1)(2)(3);
		call_twise(
			boost::adaptors::memoize(
				boost::adaptors::transform(v, call_once_checker())
			));

		BOOST_TEST(boost::equal(v, call_history));
	}
}

int main()
{
	call_once_test();

	return boost::report_errors();
}


