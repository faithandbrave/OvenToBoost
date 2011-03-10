// Boost.Range 2.0 Extension library
// via PStade Oven Library
//
// Copyright Akira Takahashi 2011.
// Copyright Shunsuke Sogame 2005-2007.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/range/adaptor/elements.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <boost/range/access/front.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/fusion/include/map.hpp>
#include <boost/fusion/include/adapt_assoc_struct.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/assign/list_of.hpp>

namespace fusion = boost::fusion;

struct id_tag {};
struct name_tag {};
struct age_tag {};

struct Person {
    int id;
    std::string name;
    int age;

    Person(int id_, const std::string& name_, int age_)
        : id(id_), name(name_), age(age_) {}
};

BOOST_FUSION_ADAPT_ASSOC_STRUCT(
    Person,
    (int, id, id_tag)
    (std::string, name, name_tag)
    (int, age, age_tag)
)

typedef fusion::map<
    fusion::pair<id_tag, int>,
    fusion::pair<name_tag, std::string>,
    fusion::pair<age_tag, int>
> map_type;

int main()
{
    using boost::adaptors::elements_key;
    using boost::adaptors::extract_elements_key;
    using boost::range::access::front;

    // operator style
    {
        const std::vector<map_type> v = boost::assign::list_of
            (map_type(fusion::make_pair<id_tag>(1),
                      fusion::make_pair<name_tag>("Alice"),
                      fusion::make_pair<age_tag>(20))
             )
            (map_type(fusion::make_pair<id_tag>(2),
                      fusion::make_pair<name_tag>("Bob"),
                      fusion::make_pair<age_tag>(28))
             )
            (map_type(fusion::make_pair<id_tag>(3),
                      fusion::make_pair<name_tag>("Millia"),
                      fusion::make_pair<age_tag>(16))
             )
            ;

        const std::vector<std::string> expected = boost::assign::list_of("Alice")("Bob")("Millia");
        BOOST_TEST(boost::equal(v | elements_key<name_tag>(), expected));
    }
    {
        std::vector<map_type> v = boost::assign::list_of
            (map_type(fusion::make_pair<id_tag>(1),
                      fusion::make_pair<name_tag>("Alice"),
                      fusion::make_pair<age_tag>(20))
             )
            (map_type(fusion::make_pair<id_tag>(2),
                      fusion::make_pair<name_tag>("Bob"),
                      fusion::make_pair<age_tag>(28))
             )
            (map_type(fusion::make_pair<id_tag>(3),
                      fusion::make_pair<name_tag>("Millia"),
                      fusion::make_pair<age_tag>(16))
             )
            ;

        const std::vector<std::string> expected = boost::assign::list_of("Alice")("Bob")("Millia");
        BOOST_TEST(boost::equal(v | elements_key<name_tag>(), expected));

        v | elements_key<name_tag>() | front = "Akira";
        const std::vector<std::string> expected2 = boost::assign::list_of("Akira")("Bob")("Millia");
        BOOST_TEST(boost::equal(v | elements_key<name_tag>(), expected2));
    }
    {
        std::vector<Person> v = boost::assign::list_of
            (Person(1, "Alice", 20))
            (Person(2, "Bob", 28))
            (Person(3, "Millia", 16))
            ;

        const std::vector<std::string> expected =
            boost::assign::list_of("Alice")("Bob")("Millia");

        BOOST_TEST(boost::equal(v | elements_key<name_tag>(), expected));
    }

    // function style
    {
        const std::vector<map_type> v = boost::assign::list_of
            (map_type(fusion::make_pair<id_tag>(1),
                      fusion::make_pair<name_tag>("Alice"),
                      fusion::make_pair<age_tag>(20))
             )
            (map_type(fusion::make_pair<id_tag>(2),
                      fusion::make_pair<name_tag>("Bob"),
                      fusion::make_pair<age_tag>(28))
             )
            (map_type(fusion::make_pair<id_tag>(3),
                      fusion::make_pair<name_tag>("Millia"),
                      fusion::make_pair<age_tag>(16))
             )
            ;

        const std::vector<std::string> expected = boost::assign::list_of("Alice")("Bob")("Millia");
        BOOST_TEST(boost::equal(extract_elements_key<name_tag>(v), expected));
    }
    {
        std::vector<map_type> v = boost::assign::list_of
            (map_type(fusion::make_pair<id_tag>(1),
                      fusion::make_pair<name_tag>("Alice"),
                      fusion::make_pair<age_tag>(20))
             )
            (map_type(fusion::make_pair<id_tag>(2),
                      fusion::make_pair<name_tag>("Bob"),
                      fusion::make_pair<age_tag>(28))
             )
            (map_type(fusion::make_pair<id_tag>(3),
                      fusion::make_pair<name_tag>("Millia"),
                      fusion::make_pair<age_tag>(16))
             )
            ;

        const std::vector<std::string> expected = boost::assign::list_of("Alice")("Bob")("Millia");
        BOOST_TEST(boost::equal(extract_elements_key<name_tag>(v), expected));

        front(extract_elements_key<name_tag>(v)) = "Akira";
        const std::vector<std::string> expected2 = boost::assign::list_of("Akira")("Bob")("Millia");
        BOOST_TEST(boost::equal(extract_elements_key<name_tag>(v), expected2));
    }
    {
        std::vector<Person> v = boost::assign::list_of
            (Person(1, "Alice", 20))
            (Person(2, "Bob", 28))
            (Person(3, "Millia", 16))
            ;

        const std::vector<std::string> expected =
            boost::assign::list_of("Alice")("Bob")("Millia");

        BOOST_TEST(boost::equal(extract_elements_key<name_tag>(v), expected));
    }

    return boost::report_errors();
}
