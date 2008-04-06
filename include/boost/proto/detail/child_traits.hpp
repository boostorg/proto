///////////////////////////////////////////////////////////////////////////////
/// \file child_traits.hpp
/// Traits class for calculating properties of expression node children.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DETAIL_CHILD_TRAITS_HPP_EAN_04_06_2008
#define BOOST_PROTO_DETAIL_CHILD_TRAITS_HPP_EAN_04_06_2008

namespace boost { namespace proto
{
    namespace detail
    {
        /// \brief Trait for stripping top-level references
        /// and reference wrappers.
        template<typename T>
        struct child_traits
        {
            typedef T value_type;               ///< Suitable for return by value
            typedef T &reference;               ///< Suitable for return by reference
            typedef T const &const_reference;   ///< Suitable for return by const reference
        };

        /// \brief Trait for stripping top-level references
        /// and reference wrappers.
        template<typename T>
        struct child_traits<T &>
        {
            typedef T value_type;               ///< Suitable for return by value
            typedef T &reference;               ///< Suitable for return by reference
            typedef T &const_reference;         ///< Suitable for return by const reference
        };

        /// \brief Trait for stripping top-level references
        /// and reference wrappers.
        template<typename T>
        struct child_traits<T const &>
        {
            typedef T value_type;               ///< Suitable for return by value
            typedef T const &reference;         ///< Suitable for return by reference
            typedef T const &const_reference;   ///< Suitable for return by const reference
        };

        /// \brief Trait for stripping top-level references
        /// and reference wrappers.
        template<typename T, std::size_t N>
        struct child_traits<T (&)[N]>
        {
            typedef T (&value_type)[N];         ///< Suitable for return by value
            typedef T (&reference)[N];          ///< Suitable for return by reference
            typedef T (&const_reference)[N];    ///< Suitable for return by const reference
        };

        /// \brief Trait for stripping top-level references
        /// and reference wrappers.
        template<typename T, std::size_t N>
        struct child_traits<T const (&)[N]>
        {
            typedef T const (&value_type)[N];       ///< Suitable for return by value
            typedef T const (&reference)[N];        ///< Suitable for return by reference
            typedef T const (&const_reference)[N];  ///< Suitable for return by const reference
        };

        /// \brief Trait for stripping top-level references
        /// and reference wrappers.
        template<typename T, std::size_t N>
        struct child_traits<T[N]>
        {
            typedef T (&value_type)[N];             ///< Suitable for return by value
            typedef T (&reference)[N];              ///< Suitable for return by reference
            typedef T const (&const_reference)[N];  ///< Suitable for return by const reference
        };

        /// \brief Trait for stripping top-level references
        /// and reference wrappers.
        template<typename T, std::size_t N>
        struct child_traits<T const[N]>
        {
            typedef T const (&value_type)[N];       ///< Suitable for return by value
            typedef T const (&reference)[N];        ///< Suitable for return by reference
            typedef T const (&const_reference)[N];  ///< Suitable for return by const reference
        };
    }

}}

#endif
