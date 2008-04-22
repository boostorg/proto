///////////////////////////////////////////////////////////////////////////////
/// \file decltype.hpp
/// Contains definition the BOOST_PROTO_DECLTYPE_() macro and assorted helpers
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DETAIL_DECLTYPE_HPP_EAN_04_04_2008
#define BOOST_PROTO_DETAIL_DECLTYPE_HPP_EAN_04_04_2008

#include <boost/proto/detail/prefix.hpp> // must be first include
#include <boost/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/proto/detail/suffix.hpp> // must be last include

// If we're generating doxygen documentation, hide all the nasty
// Boost.Typeof gunk.
#ifndef BOOST_PROTO_BUILDING_DOCS
# ifdef BOOST_HAS_DECLTYPE
#  define BOOST_PROTO_DECLTYPE_(EXPR, TYPE) typedef decltype(EXPR) TYPE;
# else
#  define BOOST_PROTO_DECLTYPE_NESTED_TYPEDEF_TPL_(NESTED, EXPR)                                    \
    BOOST_TYPEOF_NESTED_TYPEDEF_TPL(BOOST_PP_CAT(nested_and_hidden_, NESTED), EXPR)                 \
    static int const sz = sizeof(boost::proto::detail::check_reference(EXPR));                      \
    struct NESTED                                                                                   \
      : boost::mpl::if_c<                                                                           \
            1==sz                                                                                   \
          , typename BOOST_PP_CAT(nested_and_hidden_, NESTED)::type &                               \
          , typename BOOST_PP_CAT(nested_and_hidden_, NESTED)::type                                 \
        >                                                                                           \
    {};
#  define BOOST_PROTO_DECLTYPE_(EXPR, TYPE)                                                         \
    BOOST_PROTO_DECLTYPE_NESTED_TYPEDEF_TPL_(BOOST_PP_CAT(nested_, TYPE), (EXPR))                   \
    typedef typename BOOST_PP_CAT(nested_, TYPE)::type TYPE;
# endif
#else
/// INTERNAL ONLY
///
# define BOOST_PROTO_DECLTYPE_(EXPR, TYPE)                                                          \
    typedef detail::unspecified TYPE;
#endif

namespace boost { namespace proto
{
    namespace detail
    {
        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        struct as_mutable
        {
            typedef T &type;
        };

        template<typename T>
        struct as_mutable<T &>
        {
            typedef T &type;
        };

        template<typename T>
        struct as_mutable<T const &>
        {
            typedef T &type;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        T make();

        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        typename as_mutable<T>::type make_mutable();

        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        char check_reference(T &);

        template<typename T>
        char (&check_reference(T const &))[2];

        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        T &deref(T &t)
        {
            return t;
        }

        template<typename T>
        T const &deref(T const &t)
        {
            return t;
        }

        template<typename T>
        T &deref(T *&t)
        {
            return *t;
        }

        template<typename T>
        T &deref(T *const &t)
        {
            return *t;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename A0, typename A1>
        struct comma_result
        {
            BOOST_PROTO_DECLTYPE_((proto::detail::make<A0>(), proto::detail::make<A1>()), type)
        };

        template<typename A0>
        struct comma_result<A0, void>
        {
            typedef void type;
        };

        template<typename A1>
        struct comma_result<void, A1>
        {
            typedef A1 type;
        };

        template<>
        struct comma_result<void, void>
        {
            typedef void type;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        struct result_of_
          : boost::result_of<T>
        {};

        template<typename T, typename U, typename V>
        struct result_of_<T U::*(V)>
        {
            typedef T type;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T, typename U = T>
        struct result_of_fixup
          : mpl::if_c<is_function<T>::value, T *, U>
        {};

        template<typename T, typename U>
        struct result_of_fixup<T &, U>
          : result_of_fixup<T, T>
        {};

        template<typename T, typename U>
        struct result_of_fixup<T const &, U>
          : result_of_fixup<T, T>
        {};

        template<typename T, typename U>
        struct result_of_fixup<T *, U>
          : result_of_fixup<T, U>
        {};

        template<typename R, typename T, typename U>
        struct result_of_fixup<R T::*, U>
        {
            typedef R T::*type;
        };

        template<typename T, typename U>
        struct result_of_fixup<T const, U>
          : result_of_fixup<T, U>
        {};

        //// Tests for result_of_fixup
        //struct bar {};
        //BOOST_MPL_ASSERT((is_same<bar,        result_of_fixup<bar>::type>));
        //BOOST_MPL_ASSERT((is_same<bar const,  result_of_fixup<bar const>::type>));
        //BOOST_MPL_ASSERT((is_same<bar,        result_of_fixup<bar &>::type>));
        //BOOST_MPL_ASSERT((is_same<bar const,  result_of_fixup<bar const &>::type>));
        //BOOST_MPL_ASSERT((is_same<void(*)(),  result_of_fixup<void(*)()>::type>));
        //BOOST_MPL_ASSERT((is_same<void(*)(),  result_of_fixup<void(* const)()>::type>));
        //BOOST_MPL_ASSERT((is_same<void(*)(),  result_of_fixup<void(* const &)()>::type>));
        //BOOST_MPL_ASSERT((is_same<void(*)(),  result_of_fixup<void(&)()>::type>));

    } // namespace detail
}}

#endif
