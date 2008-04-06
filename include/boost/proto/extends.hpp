///////////////////////////////////////////////////////////////////////////////
/// \file extends.hpp
/// Macros and a base class for defining end-user expression types
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_EXTENDS_HPP_EAN_11_1_2006
#define BOOST_PROTO_EXTENDS_HPP_EAN_11_1_2006

#include <boost/proto/detail/prefix.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/expr.hpp>
#include <boost/proto/args.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/generate.hpp>
#include <boost/proto/detail/suffix.hpp>

namespace boost { namespace proto
{
    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_CONST0

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_CONST1 const

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_TEMPLATE_YES_(Z, N) template<BOOST_PP_ENUM_PARAMS_Z(Z, N, typename A)>

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_TEMPLATE_NO_(Z, N)

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_DEFINE_FUN_OP_IMPL_(Z, N, DATA, Const)                                      \
        BOOST_PP_IF(N, BOOST_PROTO_TEMPLATE_YES_, BOOST_PROTO_TEMPLATE_NO_)(Z, N)                   \
        typename boost::result_of<                                                                  \
            proto_domain(                                                                           \
                typename boost::proto::result_of::BOOST_PP_CAT(funop, N)<                           \
                    proto_derived_expr BOOST_PROTO_CONST ## Const                                   \
                  , proto_domain                                                                    \
                    BOOST_PP_ENUM_TRAILING_PARAMS_Z(Z, N, const A)                                  \
                >::type                                                                             \
            )                                                                                       \
        >::type const                                                                               \
        operator ()(BOOST_PP_ENUM_BINARY_PARAMS_Z(Z, N, A, const &a)) BOOST_PROTO_CONST ## Const    \
        {                                                                                           \
            typedef boost::proto::result_of::BOOST_PP_CAT(funop, N)<                                \
                proto_derived_expr BOOST_PROTO_CONST ## Const                                       \
              , proto_domain                                                                        \
                BOOST_PP_ENUM_TRAILING_PARAMS_Z(Z, N, const A)                                      \
            > funop;                                                                                \
            return proto_domain()(                                                                  \
                funop::call(                                                                        \
                    *static_cast<proto_derived_expr BOOST_PROTO_CONST ## Const *>(this)             \
                    BOOST_PP_ENUM_TRAILING_PARAMS_Z(Z, N, a)                                        \
                )                                                                                   \
            );                                                                                      \
        }                                                                                           \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_DEFINE_FUN_OP_CONST(Z, N, DATA)                                             \
        BOOST_PROTO_DEFINE_FUN_OP_IMPL_(Z, N, DATA, 1)

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_DEFINE_FUN_OP_NON_CONST(Z, N, DATA)                                         \
        BOOST_PROTO_DEFINE_FUN_OP_IMPL_(Z, N, DATA, 0)

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_DEFINE_FUN_OP(Z, N, DATA)                                                   \
        BOOST_PROTO_DEFINE_FUN_OP_CONST(Z, N, DATA)                                                 \
        BOOST_PROTO_DEFINE_FUN_OP_NON_CONST(Z, N, DATA)                                             \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_EXTENDS_CHILD(Z, N, DATA)                                                   \
        typedef                                                                                     \
            typename proto_base_expr::BOOST_PP_CAT(proto_child, N)                                  \
        BOOST_PP_CAT(proto_child, N);                                                               \
        /**/

    #define BOOST_PROTO_BASIC_EXTENDS(Expr, Derived, Domain)                                        \
        Expr expr;                                                                                  \
                                                                                                    \
        typedef typename Expr::proto_base_expr proto_base_expr;                                     \
        typedef Domain proto_domain;                                                                \
        typedef Derived proto_derived_expr;                                                         \
        typedef typename proto_base_expr::proto_tag proto_tag;                                      \
        typedef typename proto_base_expr::proto_args proto_args;                                    \
        typedef typename proto_base_expr::proto_arity proto_arity;                                  \
        typedef void proto_is_expr_;                                                                \
        BOOST_PROTO_FUSION_DEFINE_TAG(boost::proto::tag::proto_expr)                                \
        BOOST_PP_REPEAT(BOOST_PROTO_MAX_ARITY, BOOST_PROTO_EXTENDS_CHILD, ~)                        \
                                                                                                    \
        static proto_derived_expr const make(Expr const &expr)                                      \
        {                                                                                           \
            proto_derived_expr that = {expr};                                                       \
            return that;                                                                            \
        }                                                                                           \
                                                                                                    \
        proto_base_expr &proto_base()                                                               \
        {                                                                                           \
            return this->expr.proto_base();                                                         \
        }                                                                                           \
                                                                                                    \
        proto_base_expr const &proto_base() const                                                   \
        {                                                                                           \
            return this->expr.proto_base();                                                         \
        }                                                                                           \
        /**/

        /// INTERNAL ONLY
        ///
    #define BOOST_PROTO_EXTENDS_ASSIGN_IMPL_(Const)                                                 \
        template<typename A>                                                                        \
        typename boost::result_of<                                                                  \
            proto_domain(                                                                           \
                boost::proto::expr<                                                                 \
                    boost::proto::tag::assign                                                       \
                  , boost::proto::list2<                                                            \
                        proto_derived_expr BOOST_PROTO_CONST ## Const &                             \
                      , typename boost::proto::result_of::as_child<A, proto_domain>::type           \
                    >                                                                               \
                >                                                                                   \
            )                                                                                       \
        >::type const                                                                               \
        operator =(A &a) BOOST_PROTO_CONST ## Const                                                 \
        {                                                                                           \
            typedef boost::proto::expr<                                                             \
                boost::proto::tag::assign                                                           \
              , boost::proto::list2<                                                                \
                    proto_derived_expr BOOST_PROTO_CONST ## Const &                                 \
                  , typename boost::proto::result_of::as_child<A, proto_domain>::type               \
                >                                                                                   \
            > that_type;                                                                            \
            that_type that = {                                                                      \
                *static_cast<proto_derived_expr BOOST_PROTO_CONST ## Const *>(this)                 \
              , boost::proto::as_child<proto_domain>(a)                                             \
            };                                                                                      \
            return proto_domain()(that);                                                            \
        }                                                                                           \
                                                                                                    \
        template<typename A>                                                                        \
        typename boost::result_of<                                                                  \
            proto_domain(                                                                           \
                boost::proto::expr<                                                                 \
                    boost::proto::tag::assign                                                       \
                  , boost::proto::list2<                                                            \
                        proto_derived_expr BOOST_PROTO_CONST ## Const &                             \
                      , typename boost::proto::result_of::as_child<A const, proto_domain>::type     \
                    >                                                                               \
                >                                                                                   \
            )                                                                                       \
        >::type const                                                                               \
        operator =(A const &a) BOOST_PROTO_CONST ## Const                                           \
        {                                                                                           \
            typedef boost::proto::expr<                                                             \
                boost::proto::tag::assign                                                           \
              , boost::proto::list2<                                                                \
                    proto_derived_expr BOOST_PROTO_CONST ## Const &                                 \
                  , typename boost::proto::result_of::as_child<A const, proto_domain>::type         \
                >                                                                                   \
            > that_type;                                                                            \
            that_type that = {                                                                      \
                *static_cast<proto_derived_expr BOOST_PROTO_CONST ## Const *>(this)                 \
              , boost::proto::as_child<proto_domain>(a)                                             \
            };                                                                                      \
            return proto_domain()(that);                                                            \
        }                                                                                           \
        /**/

    #define BOOST_PROTO_EXTENDS_ASSIGN_CONST()                                                      \
        BOOST_PROTO_EXTENDS_ASSIGN_IMPL_(1)

    #define BOOST_PROTO_EXTENDS_ASSIGN_NON_CONST()                                                  \
        BOOST_PROTO_EXTENDS_ASSIGN_IMPL_(0)

    #define BOOST_PROTO_EXTENDS_ASSIGN()                                                            \
        BOOST_PROTO_EXTENDS_ASSIGN_CONST()                                                          \
        BOOST_PROTO_EXTENDS_ASSIGN_NON_CONST()                                                      \
        /**/

        /// INTERNAL ONLY
        ///
    #define BOOST_PROTO_EXTENDS_SUBSCRIPT_IMPL_(Const)                                              \
        template<typename A>                                                                        \
        typename boost::result_of<                                                                  \
            proto_domain(                                                                           \
                boost::proto::expr<                                                                 \
                    boost::proto::tag::subscript                                                    \
                  , boost::proto::list2<                                                            \
                        proto_derived_expr BOOST_PROTO_CONST ## Const &                             \
                      , typename boost::proto::result_of::as_child<A, proto_domain>::type           \
                    >                                                                               \
                >                                                                                   \
            )                                                                                       \
        >::type const                                                                               \
        operator [](A &a) BOOST_PROTO_CONST ## Const                                                \
        {                                                                                           \
            typedef boost::proto::expr<                                                             \
                boost::proto::tag::subscript                                                        \
              , boost::proto::list2<                                                                \
                    proto_derived_expr BOOST_PROTO_CONST ## Const &                                 \
                  , typename boost::proto::result_of::as_child<A, proto_domain>::type               \
                >                                                                                   \
            > that_type;                                                                            \
            that_type that = {                                                                      \
                *static_cast<proto_derived_expr BOOST_PROTO_CONST ## Const *>(this)                 \
              , boost::proto::as_child<proto_domain>(a)                                             \
            };                                                                                      \
            return proto_domain()(that);                                                            \
        }                                                                                           \
                                                                                                    \
        template<typename A>                                                                        \
        typename boost::result_of<                                                                  \
            proto_domain(                                                                           \
                boost::proto::expr<                                                                 \
                    boost::proto::tag::subscript                                                    \
                  , boost::proto::list2<                                                            \
                        proto_derived_expr BOOST_PROTO_CONST ## Const &                             \
                      , typename boost::proto::result_of::as_child<A const, proto_domain>::type     \
                    >                                                                               \
                >                                                                                   \
            )                                                                                       \
        >::type const                                                                               \
        operator [](A const &a) BOOST_PROTO_CONST ## Const                                          \
        {                                                                                           \
            typedef boost::proto::expr<                                                             \
                boost::proto::tag::subscript                                                        \
              , boost::proto::list2<                                                                \
                    proto_derived_expr BOOST_PROTO_CONST ## Const &                                 \
                  , typename boost::proto::result_of::as_child<A const, proto_domain>::type         \
                >                                                                                   \
            > that_type;                                                                            \
            that_type that = {                                                                      \
                *static_cast<proto_derived_expr BOOST_PROTO_CONST ## Const *>(this)                 \
              , boost::proto::as_child<proto_domain>(a)                                             \
            };                                                                                      \
            return proto_domain()(that);                                                            \
        }                                                                                           \
        /**/

    #define BOOST_PROTO_EXTENDS_SUBSCRIPT_CONST()                                                   \
        BOOST_PROTO_EXTENDS_SUBSCRIPT_IMPL_(1)

    #define BOOST_PROTO_EXTENDS_SUBSCRIPT_NON_CONST()                                               \
        BOOST_PROTO_EXTENDS_SUBSCRIPT_IMPL_(0)

    #define BOOST_PROTO_EXTENDS_SUBSCRIPT()                                                         \
        BOOST_PROTO_EXTENDS_SUBSCRIPT_CONST()                                                       \
        BOOST_PROTO_EXTENDS_SUBSCRIPT_NON_CONST()                                                   \
        /**/

        /// INTERNAL ONLY
        ///
    #define BOOST_PROTO_EXTENDS_FUNCTION_()                                                         \
        template<typename Sig>                                                                      \
        struct result                                                                               \
        {                                                                                           \
            typedef                                                                                 \
                typename boost::result_of<                                                          \
                    proto_domain(                                                                   \
                        typename boost::proto::result_of::funop<                                    \
                            Sig                                                                     \
                          , proto_derived_expr                                                      \
                          , proto_domain                                                            \
                        >::type                                                                     \
                    )                                                                               \
                >::type                                                                             \
            type;                                                                                   \
        };                                                                                          \
        /**/

    #define BOOST_PROTO_EXTENDS_FUNCTION_CONST()                                                    \
        BOOST_PROTO_EXTENDS_FUNCTION_()                                                             \
        BOOST_PP_REPEAT_FROM_TO(                                                                    \
            0                                                                                       \
          , BOOST_PP_DEC(BOOST_PROTO_MAX_FUNCTION_CALL_ARITY)                                       \
          , BOOST_PROTO_DEFINE_FUN_OP_CONST                                                         \
          , ~                                                                                       \
        )                                                                                           \
        /**/

    #define BOOST_PROTO_EXTENDS_FUNCTION_NON_CONST()                                                \
        BOOST_PROTO_EXTENDS_FUNCTION_()                                                             \
        BOOST_PP_REPEAT_FROM_TO(                                                                    \
            0                                                                                       \
          , BOOST_PP_DEC(BOOST_PROTO_MAX_FUNCTION_CALL_ARITY)                                       \
          , BOOST_PROTO_DEFINE_FUN_OP_NON_CONST                                                     \
          , ~                                                                                       \
        )                                                                                           \
        /**/

    #define BOOST_PROTO_EXTENDS_FUNCTION()                                                          \
        BOOST_PROTO_EXTENDS_FUNCTION_()                                                             \
        BOOST_PP_REPEAT_FROM_TO(                                                                    \
            0                                                                                       \
          , BOOST_PP_DEC(BOOST_PROTO_MAX_FUNCTION_CALL_ARITY)                                       \
          , BOOST_PROTO_DEFINE_FUN_OP                                                               \
          , ~                                                                                       \
        )                                                                                           \
        /**/

    #define BOOST_PROTO_EXTENDS(Expr, Derived, Domain)                                              \
        BOOST_PROTO_BASIC_EXTENDS(Expr, Derived, Domain)                                            \
        BOOST_PROTO_EXTENDS_ASSIGN()                                                                \
        BOOST_PROTO_EXTENDS_SUBSCRIPT()                                                             \
        BOOST_PROTO_EXTENDS_FUNCTION()                                                              \
        /**/

    BOOST_PROTO_BEGIN_ADL_NAMESPACE(exprns_)

    /// \brief Empty type to be used as a dummy template parameter of
    ///     POD expression wrappers. It allows argument-dependent lookup
    ///     to find Proto's operator overloads.
    ///
    /// \c proto::is_proto_expr allows argument-dependent lookup
    ///     to find Proto's operator overloads. For example:
    ///
    /// \code
    /// template<typename T, typename Dummy = proto::is_proto_expr>
    /// struct my_terminal
    /// {
    ///     BOOST_PROTO_BASIC_EXTENDS(
    ///         typename proto::terminal<T>::type
    ///       , my_terminal<T>
    ///       , default_domain
    ///     )
    /// };
    ///
    /// // ...
    /// my_terminal<int> _1, _2;
    /// _1 + _2; // OK, uses proto::operator+
    /// \endcode
    ///
    /// Without the second \c Dummy template parameter, Proto's operator
    /// overloads would not be considered by name lookup.
    struct is_proto_expr
    {};

    /// \brief extends\<\> class template for adding behaviors to a Proto expression template
    ///
    template<
        typename Expr
      , typename Derived
      , typename Domain     BOOST_PROTO_WHEN_BUILDING_DOCS(= default_domain)
      , typename Tag        BOOST_PROTO_WHEN_BUILDING_DOCS(= typename Expr::proto_tag)
    >
    struct extends
    {
        extends()
          : expr()
        {}

        extends(extends const &that)
          : expr(that.expr)
        {}

        extends(Expr const &expr_)
          : expr(expr_)
        {}

        BOOST_PROTO_BASIC_EXTENDS(Expr, Derived, Domain)
        BOOST_PROTO_EXTENDS_ASSIGN_CONST()
        BOOST_PROTO_EXTENDS_SUBSCRIPT_CONST()

        // Instead of using BOOST_PROTO_EXTENDS_FUNCTION, which uses
        // nested preprocessor loops, use file iteration here to generate
        // the operator() overloads, which is more efficient.
        BOOST_PROTO_EXTENDS_FUNCTION_()

        /// INTERNAL ONLY
        ///
    #define BOOST_PP_LOCAL_MACRO(N)                                                             \
        BOOST_PROTO_DEFINE_FUN_OP_CONST(1, N, ~)                                                \
        /**/

        /// INTERNAL ONLY
        ///
    #define BOOST_PP_LOCAL_LIMITS (0, BOOST_PP_DEC(BOOST_PROTO_MAX_FUNCTION_CALL_ARITY))
    #include BOOST_PP_LOCAL_ITERATE()
    };

    /// \brief extends\<\> class template for adding behaviors to a Proto expression template
    ///
    template<typename Expr, typename Derived, typename Domain>
    struct extends<Expr, Derived, Domain, tag::terminal>
    {
        extends()
          : expr()
        {}

        extends(extends const &that)
          : expr(that.expr)
        {}

        extends(Expr const &expr_)
          : expr(expr_)
        {}

        BOOST_PROTO_BASIC_EXTENDS(Expr, Derived, Domain)
        BOOST_PROTO_EXTENDS_ASSIGN()
        BOOST_PROTO_EXTENDS_SUBSCRIPT()

        // Instead of using BOOST_PROTO_EXTENDS_FUNCTION, which uses
        // nested preprocessor loops, use file iteration here to generate
        // the operator() overloads, which is more efficient.
        BOOST_PROTO_EXTENDS_FUNCTION_()

        /// INTERNAL ONLY
        ///
    #define BOOST_PP_LOCAL_MACRO(N)                                                             \
        BOOST_PROTO_DEFINE_FUN_OP(1, N, ~)                                                      \
        /**/

        /// INTERNAL ONLY
        ///
    #define BOOST_PP_LOCAL_LIMITS (0, BOOST_PP_DEC(BOOST_PROTO_MAX_FUNCTION_CALL_ARITY))
    #include BOOST_PP_LOCAL_ITERATE()
    };

    BOOST_PROTO_END_ADL_NAMESPACE(exprns_)

}}

#endif
