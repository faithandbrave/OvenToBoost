#ifndef BOOST_RANGE_ADAPTOR_ELEMENTS_INCLUDE
#define BOOST_RANGE_ADAPTOR_ELEMENTS_INCLUDE

#include <boost/config.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/reference.hpp>
#include <boost/mpl/assert.hpp>

namespace boost {
    namespace range_detail {
        template <class SinglePassRange, int N>
        struct element_select {
            typedef typename range_reference<SinglePassRange>::type argument_type;
            typedef typename remove_reference<argument_type>::type element_type;
            typedef typename fusion::result_of::at_c<element_type, N>::type result_type;

            result_type operator()(argument_type r) const
            {
                return fusion::at_c<N>(r);
            }
        };

        template <class SinglePassRange, class Key>
        struct element_key_select {
            typedef typename range_reference<SinglePassRange>::type argument_type;
            typedef typename remove_reference<argument_type>::type element_type;
            typedef typename fusion::result_of::at_key<element_type, Key>::type result_type;

            result_type operator()(argument_type r) const
            {
                return fusion::at_key<Key>(r);
            }
        };
    } // namespace range_detail

    namespace range { namespace result_of {
        template <class SinglePassRange, int N>
        struct elements {
            typedef
                range_detail::transformed_range<
                    range_detail::element_select<SinglePassRange, N>,
                    SinglePassRange
                >
            type;
        };

        template <class SinglePassRange, class Key>
        struct elements_key {
            typedef
                range_detail::transformed_range<
                    range_detail::element_key_select<SinglePassRange, Key>,
                    SinglePassRange
                >
            type;
        };
    }} // namespace range::result_of

    namespace range_detail {
        template <int N> struct elements {};
        template <class Key> struct elements_key {};

        template <class SinglePassRange, int N>
        inline BOOST_DEDUCED_TYPENAME ::boost::range::result_of::elements<SinglePassRange, N>::type
            operator|(SinglePassRange& rng, elements<N>)
        {
            return rng | ::boost::adaptors::transformed(element_select<SinglePassRange, N>());
        }

        template <class SinglePassRange, int N>
        inline BOOST_DEDUCED_TYPENAME ::boost::range::result_of::elements<const SinglePassRange, N>::type
            operator|(const SinglePassRange& rng, elements<N>)
        {
            return rng | ::boost::adaptors::transformed(element_select<const SinglePassRange, N>());
        }

        template <class SinglePassRange, class Key>
        inline BOOST_DEDUCED_TYPENAME ::boost::range::result_of::elements_key<SinglePassRange, Key>::type
            operator|(SinglePassRange& rng, elements_key<Key>)
        {
            return rng | ::boost::adaptors::transformed(element_key_select<SinglePassRange, Key>());
        }

        template <class SinglePassRange, class Key>
        inline BOOST_DEDUCED_TYPENAME ::boost::range::result_of::elements_key<const SinglePassRange, Key>::type
            operator|(const SinglePassRange& rng, elements_key<Key>)
        {
            return rng | ::boost::adaptors::transformed(element_key_select<const SinglePassRange, Key>());
        }
    } // namespace range_detail

    namespace adaptors {
        using range_detail::elements;
        using range_detail::elements_key;

        template <int N, class SinglePassRange>
        inline BOOST_DEDUCED_TYPENAME ::boost::range::result_of::elements<SinglePassRange, N>::type
            extract_elements(SinglePassRange& rng)
        {
            return rng | elements<N>();
        }

        template <int N, class SinglePassRange>
        inline BOOST_DEDUCED_TYPENAME ::boost::range::result_of::elements<const SinglePassRange, N>::type
            extract_elements(const SinglePassRange& rng)
        {
            return rng | elements<N>();
        }

        template <class Key, class SinglePassRange>
        inline BOOST_DEDUCED_TYPENAME ::boost::range::result_of::elements_key<SinglePassRange, Key>::type
            extract_elements_key(SinglePassRange& rng)
        {
            return rng | elements_key<Key>();
        }

        template <class Key, class SinglePassRange>
        inline BOOST_DEDUCED_TYPENAME ::boost::range::result_of::elements_key<const SinglePassRange, Key>::type
            extract_elements_key(const SinglePassRange& rng)
        {
            return rng | elements_key<Key>();
        }
    } // namespace adaptors

} // namespace boost

#endif // BOOST_RANGE_ADAPTOR_ELEMENTS_INCLUDE


