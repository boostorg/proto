///////////////////////////////////////////////////////////////////////////////
/// \file ref.hpp
/// Utility for storing a sub-expr by reference
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_REF_HPP_EAN_04_01_2005
#define BOOST_PROTO_REF_HPP_EAN_04_01_2005

#include <boost/proto/detail/prefix.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/detail/suffix.hpp>

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma warning(push)
# pragma warning(disable : 4510) // default constructor could not be generated
# pragma warning(disable : 4512) // assignment operator could not be generated
# pragma warning(disable : 4610) // user defined constructor required
#endif

namespace boost { namespace proto
{
    namespace result_of
    {
        /// \brief Trait for stripping top-level references
        /// and reference wrappers.
        template<typename T>
        struct unref
        {
            typedef T type;                     ///< Suitable for return by value
            typedef T &reference;               ///< Suitable for return by reference
            typedef T const &const_reference;   ///< Suitable for return by const reference
        };

        /// \brief Trait for stripping top-level references
        /// and reference wrappers.
        template<typename T>
        struct unref<T &>
        {
            typedef T type;                     ///< Suitable for return by value
            typedef T &reference;               ///< Suitable for return by reference
            typedef T &const_reference;         ///< Suitable for return by const reference
        };

        /// \brief Trait for stripping top-level references
        /// and reference wrappers.
        template<typename T>
        struct unref<T const &>
        {
            typedef T type;                     ///< Suitable for return by value
            typedef T const &reference;         ///< Suitable for return by reference
            typedef T const &const_reference;   ///< Suitable for return by const reference
        };

        /// \brief Trait for stripping top-level references
        /// and reference wrappers.
        template<typename T, std::size_t N>
        struct unref<T (&)[N]>
        {
            typedef T (&type)[N];               ///< Suitable for return by value
            typedef T (&reference)[N];          ///< Suitable for return by reference
            typedef T (&const_reference)[N];    ///< Suitable for return by const reference
        };

        /// \brief Trait for stripping top-level references
        /// and reference wrappers.
        template<typename T, std::size_t N>
        struct unref<T const (&)[N]>
        {
            typedef T const (&type)[N];             ///< Suitable for return by value
            typedef T const (&reference)[N];        ///< Suitable for return by reference
            typedef T const (&const_reference)[N];  ///< Suitable for return by const reference
        };

        /// \brief Trait for stripping top-level references
        /// and reference wrappers.
        template<typename T, std::size_t N>
        struct unref<T[N]>
        {
            typedef T (&type)[N];                   ///< Suitable for return by value
            typedef T (&reference)[N];              ///< Suitable for return by reference
            typedef T const (&const_reference)[N];  ///< Suitable for return by const reference
        };

        /// \brief Trait for stripping top-level references
        /// and reference wrappers.
        template<typename T, std::size_t N>
        struct unref<T const[N]>
        {
            typedef T const (&type)[N];             ///< Suitable for return by value
            typedef T const (&reference)[N];        ///< Suitable for return by reference
            typedef T const (&const_reference)[N];  ///< Suitable for return by const reference
        };
    }

}}

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma warning(pop)
#endif

#endif
