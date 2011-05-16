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

        template <class SinglePassRange, int N>
        struct elements_range :
                transformed_range<
                    element_select<SinglePassRange, N>,
                    SinglePassRange
                >
        {
            typedef
                transformed_range<
                    element_select<SinglePassRange, N>,
                    SinglePassRange
                >
            base;

            explicit elements_range(SinglePassRange& rng)
                : base(element_select<SinglePassRange, N>(), rng) {}
        };

        template <class SinglePassRange, class Key>
        struct elements_key_range :
                transformed_range<
                    element_key_select<SinglePassRange, Key>,
                    SinglePassRange
                >
        {
            typedef
                transformed_range<
                    element_key_select<SinglePassRange, Key>,
                    SinglePassRange
                >
            base;

            explicit elements_key_range(SinglePassRange& rng)
                : base(element_key_select<SinglePassRange, Key>(), rng) {}
        };

    } // namespace range_detail

    namespace range_detail {
        template <int N> struct elements {};
        template <class Key> struct elements_key {};

        template <class SinglePassRange, int N>
        inline elements_range<SinglePassRange, N>
            operator|(SinglePassRange& rng, elements<N>)
        {
            return elements_range<SinglePassRange, N>(rng);
        }

        template <class SinglePassRange, int N>
        inline elements_range<const SinglePassRange, N>
            operator|(const SinglePassRange& rng, elements<N>)
        {
            return elements_range<const SinglePassRange, N>(rng);
        }

        template <class SinglePassRange, class Key>
        inline elements_key_range<SinglePassRange, Key>
            operator|(SinglePassRange& rng, elements_key<Key>)
        {
            return elements_key_range<SinglePassRange, Key>(rng);
        }

        template <class SinglePassRange, class Key>
        inline elements_key_range<const SinglePassRange, Key>
            operator|(const SinglePassRange& rng, elements_key<Key>)
        {
            return elements_key_range<const SinglePassRange, Key>(rng);
        }
    } // namespace range_detail

    using range_detail::elements_range;
    using range_detail::elements_key_range;

    namespace adaptors {
        using range_detail::elements;
        using range_detail::elements_key;

        template <int N, class SinglePassRange>
        inline elements_range<SinglePassRange, N>
            extract_elements(SinglePassRange& rng)
        {
            return rng | elements<N>();
        }

        template <int N, class SinglePassRange>
        inline elements_range<const SinglePassRange, N>
            extract_elements(const SinglePassRange& rng)
        {
            return rng | elements<N>();
        }

        template <class Key, class SinglePassRange>
        inline elements_key_range<SinglePassRange, Key>
            extract_elements_key(SinglePassRange& rng)
        {
            return rng | elements_key<Key>();
        }

        template <class Key, class SinglePassRange>
        inline elements_key_range<const SinglePassRange, Key>
            extract_elements_key(const SinglePassRange& rng)
        {
            return rng | elements_key<Key>();
        }
    } // namespace adaptors

} // namespace boost

#endif // BOOST_RANGE_ADAPTOR_ELEMENTS_INCLUDE


