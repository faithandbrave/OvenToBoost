// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/range/adaptor/elements.hpp>

#include <vector>
#include <deque>
#include <list>

#include <string>
#include <boost/range/access/front.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/assign/list_of.hpp>

namespace fusion = boost::fusion;

struct Person {
    int id;
    std::string name;
    int age;

    Person(int id_, const std::string& name_, int age_)
        : id(id_), name(name_), age(age_) {}
};

BOOST_FUSION_ADAPT_STRUCT(
    Person,
    (int, id)(std::string, name)(int, age)
)

template <template <class T, class=std::allocator<T> > class Container>
void test()
{
    using boost::adaptors::elements;
    using boost::adaptors::extract_elements;
    using boost::range::access::front;

    // operator style
    {
        const Container<fusion::vector<int, char, double> > c = boost::assign::list_of
            (fusion::make_vector(1, 'a', 0.1))
            (fusion::make_vector(2, 'b', 0.2))
            (fusion::make_vector(3, 'c', 0.3))
            ;

        const Container<char> expected = boost::assign::list_of('a')('b')('c');
        BOOST_TEST(boost::equal(c | elements<1>(), expected));
    }
    {
        Container<fusion::vector<int, char, double> > c = boost::assign::list_of
            (fusion::make_vector(1, 'a', 0.1))
            (fusion::make_vector(2, 'b', 0.2))
            (fusion::make_vector(3, 'c', 0.3))
            ;

        const Container<char> expected = boost::assign::list_of('a')('b')('c');
        BOOST_TEST(boost::equal(c | elements<1>(), expected));

        c | elements<1>() | front = 'z';
        const Container<int> expected2 = boost::assign::list_of('z')('b')('c');
        BOOST_TEST(boost::equal(c | elements<1>(), expected2));
    }
    {
        Container<Person> c = boost::assign::list_of
            (Person(1, "Alice", 20))
            (Person(2, "Bob", 28))
            (Person(3, "Millia", 16))
            ;

        const Container<std::string> expected =
            boost::assign::list_of("Alice")("Bob")("Millia");

        BOOST_TEST(boost::equal(c | elements<1>(), expected));
    }

    // function style
    {
        const Container<fusion::vector<int, char, double> > c = boost::assign::list_of
            (fusion::make_vector(1, 'a', 0.1))
            (fusion::make_vector(2, 'b', 0.2))
            (fusion::make_vector(3, 'c', 0.3))
            ;

        const Container<char> expected = boost::assign::list_of('a')('b')('c');
        BOOST_TEST(boost::equal(extract_elements<1>(c), expected));
    }
    {
        Container<fusion::vector<int, char, double> > c = boost::assign::list_of
            (fusion::make_vector(1, 'a', 0.1))
            (fusion::make_vector(2, 'b', 0.2))
            (fusion::make_vector(3, 'c', 0.3))
            ;

        const Container<char> expected = boost::assign::list_of('a')('b')('c');
        BOOST_TEST(boost::equal(extract_elements<1>(c), expected));

        front(extract_elements<1>(c)) = 'z';
        const Container<int> expected2 = boost::assign::list_of('z')('b')('c');
        BOOST_TEST(boost::equal(extract_elements<1>(c), expected2));
    }
    {
        Container<Person> c = boost::assign::list_of
            (Person(1, "Alice", 20))
            (Person(2, "Bob", 28))
            (Person(3, "Millia", 16))
            ;

        const Container<std::string> expected =
            boost::assign::list_of("Alice")("Bob")("Millia");

        BOOST_TEST(boost::equal(extract_elements<1>(c), expected));
    }

}

int main()
{
    test<std::vector>();
    test<std::deque>();
    test<std::list>();

    return boost::report_errors();
}
