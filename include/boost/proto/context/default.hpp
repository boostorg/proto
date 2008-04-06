#ifndef BOOST_PP_IS_ITERATING
    ///////////////////////////////////////////////////////////////////////////////
    /// \file default.hpp
    /// Definintion of default_context, a default evaluation context for
    /// proto::eval() that uses Boost.Typeof to deduce return types
    /// of the built-in operators.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #ifndef BOOST_PROTO_CONTEXT_DEFAULT_HPP_EAN_01_08_2007
    #define BOOST_PROTO_CONTEXT_DEFAULT_HPP_EAN_01_08_2007

    #include <boost/proto/detail/prefix.hpp> // must be first include
    #include <boost/config.hpp>
    #include <boost/preprocessor/iteration/iterate.hpp>
    #include <boost/preprocessor/repetition/enum_shifted.hpp>
    #include <boost/utility/result_of.hpp>
    #include <boost/type_traits/is_const.hpp>
    #include <boost/type_traits/is_function.hpp>
    #include <boost/type_traits/remove_reference.hpp>
    #include <boost/proto/proto_fwd.hpp>
    #include <boost/proto/tags.hpp>
    #include <boost/proto/eval.hpp>
    #include <boost/proto/traits.hpp> // for proto::child_c()
    #include <boost/proto/detail/decltype.hpp>
    #include <boost/proto/detail/suffix.hpp> // must be last include

    namespace boost { namespace proto
    {
    /// INTERNAL ONLY
    ///
    #define UNREF(x) typename boost::remove_reference<x>::type

        namespace context
        {
            template<
                typename Expr
              , typename Context
              , typename Tag        BOOST_PROTO_WHEN_BUILDING_DOCS(= typename Expr::proto_tag)
              , long Arity          BOOST_PROTO_WHEN_BUILDING_DOCS(= Expr::proto_arity::value)
            >
            struct default_eval
            {};

            /// INTERNAL ONLY
            ///
        #define BOOST_PROTO_UNARY_OP_RESULT(OP, TAG)                                                \
            template<typename Expr, typename Context>                                               \
            struct default_eval<Expr, Context, TAG, 1>                                              \
            {                                                                                       \
            private:                                                                                \
                typedef typename proto::result_of::child_c<Expr, 0>::type e0;                       \
                typedef typename proto::result_of::eval<UNREF(e0), Context>::type r0;               \
            public:                                                                                 \
                BOOST_PROTO_DECLTYPE_(OP proto::detail::make<r0>(), result_type)                    \
                result_type operator ()(Expr &expr, Context &ctx) const                             \
                {                                                                                   \
                    return OP proto::eval(proto::child_c<0>(expr), ctx);                            \
                }                                                                                   \
            };                                                                                      \
            /**/

            /// INTERNAL ONLY
            ///
        #define BOOST_PROTO_BINARY_OP_RESULT(OP, TAG)                                               \
            template<typename Expr, typename Context>                                               \
            struct default_eval<Expr, Context, TAG, 2>                                              \
            {                                                                                       \
            private:                                                                                \
                typedef typename proto::result_of::child_c<Expr, 0>::type e0;                       \
                typedef typename proto::result_of::child_c<Expr, 1>::type e1;                       \
                typedef typename proto::result_of::eval<UNREF(e0), Context>::type r0;               \
                typedef typename proto::result_of::eval<UNREF(e1), Context>::type r1;               \
            public:                                                                                 \
                BOOST_PROTO_DECLTYPE_(                                                              \
                    proto::detail::make<r0>() OP proto::detail::make<r1>()                          \
                  , result_type                                                                     \
                )                                                                                   \
                result_type operator ()(Expr &expr, Context &ctx) const                             \
                {                                                                                   \
                    return proto::eval(                                                             \
                        proto::child_c<0>(expr), ctx) OP proto::eval(proto::child_c<1>(expr)        \
                      , ctx                                                                         \
                    );                                                                              \
                }                                                                                   \
            };                                                                                      \
            /**/

            BOOST_PROTO_UNARY_OP_RESULT(+, proto::tag::unary_plus)
            BOOST_PROTO_UNARY_OP_RESULT(-, proto::tag::negate)
            BOOST_PROTO_UNARY_OP_RESULT(*, proto::tag::dereference)
            BOOST_PROTO_UNARY_OP_RESULT(~, proto::tag::complement)
            BOOST_PROTO_UNARY_OP_RESULT(&, proto::tag::address_of)
            BOOST_PROTO_UNARY_OP_RESULT(!, proto::tag::logical_not)
            BOOST_PROTO_UNARY_OP_RESULT(++, proto::tag::pre_inc)
            BOOST_PROTO_UNARY_OP_RESULT(--, proto::tag::pre_dec)

            BOOST_PROTO_BINARY_OP_RESULT(<<, proto::tag::shift_left)
            BOOST_PROTO_BINARY_OP_RESULT(>>, proto::tag::shift_right)
            BOOST_PROTO_BINARY_OP_RESULT(*, proto::tag::multiplies)
            BOOST_PROTO_BINARY_OP_RESULT(/, proto::tag::divides)
            BOOST_PROTO_BINARY_OP_RESULT(%, proto::tag::modulus)
            BOOST_PROTO_BINARY_OP_RESULT(+, proto::tag::plus)
            BOOST_PROTO_BINARY_OP_RESULT(-, proto::tag::minus)
            BOOST_PROTO_BINARY_OP_RESULT(<, proto::tag::less)
            BOOST_PROTO_BINARY_OP_RESULT(>, proto::tag::greater)
            BOOST_PROTO_BINARY_OP_RESULT(<=, proto::tag::less_equal)
            BOOST_PROTO_BINARY_OP_RESULT(>=, proto::tag::greater_equal)
            BOOST_PROTO_BINARY_OP_RESULT(==, proto::tag::equal_to)
            BOOST_PROTO_BINARY_OP_RESULT(!=, proto::tag::not_equal_to)
            BOOST_PROTO_BINARY_OP_RESULT(||, proto::tag::logical_or)
            BOOST_PROTO_BINARY_OP_RESULT(&&, proto::tag::logical_and)
            BOOST_PROTO_BINARY_OP_RESULT(&, proto::tag::bitwise_and)
            BOOST_PROTO_BINARY_OP_RESULT(|, proto::tag::bitwise_or)
            BOOST_PROTO_BINARY_OP_RESULT(^, proto::tag::bitwise_xor)
            BOOST_PROTO_BINARY_OP_RESULT(->*, proto::tag::mem_ptr)

            BOOST_PROTO_BINARY_OP_RESULT(=, proto::tag::assign)
            BOOST_PROTO_BINARY_OP_RESULT(<<=, proto::tag::shift_left_assign)
            BOOST_PROTO_BINARY_OP_RESULT(>>=, proto::tag::shift_right_assign)
            BOOST_PROTO_BINARY_OP_RESULT(*=, proto::tag::multiplies_assign)
            BOOST_PROTO_BINARY_OP_RESULT(/=, proto::tag::divides_assign)
            BOOST_PROTO_BINARY_OP_RESULT(%=, proto::tag::modulus_assign)
            BOOST_PROTO_BINARY_OP_RESULT(+=, proto::tag::plus_assign)
            BOOST_PROTO_BINARY_OP_RESULT(-=, proto::tag::minus_assign)
            BOOST_PROTO_BINARY_OP_RESULT(&=, proto::tag::bitwise_and_assign)
            BOOST_PROTO_BINARY_OP_RESULT(|=, proto::tag::bitwise_or_assign)
            BOOST_PROTO_BINARY_OP_RESULT(^=, proto::tag::bitwise_xor_assign)

        #undef BOOST_PROTO_UNARY_OP_RESULT
        #undef BOOST_PROTO_BINARY_OP_RESULT

            template<typename Expr, typename Context>
            struct default_eval<Expr, Context, proto::tag::terminal, 0>
            {
                typedef
                    typename proto::result_of::value<Expr &>::type
                result_type;

                result_type operator ()(Expr &expr, Context &) const
                {
                    return proto::value(expr);
                }
            };

            // Handle post-increment specially.
            template<typename Expr, typename Context>
            struct default_eval<Expr, Context, proto::tag::post_inc, 1>
            {
            private:
                typedef typename proto::result_of::child_c<Expr, 0>::type e0;
                typedef typename proto::result_of::eval<UNREF(e0), Context>::type r0;
            public:
                BOOST_PROTO_DECLTYPE_(proto::detail::make<r0>() ++, result_type)
                result_type operator ()(Expr &expr, Context &ctx) const
                {
                    return proto::eval(proto::child_c<0>(expr), ctx) ++;
                }
            };

            // Handle post-decrement specially.
            template<typename Expr, typename Context>
            struct default_eval<Expr, Context, proto::tag::post_dec, 1>
            {
            private:
                typedef typename proto::result_of::child_c<Expr, 0>::type e0;
                typedef typename proto::result_of::eval<UNREF(e0), Context>::type r0;
            public:
                BOOST_PROTO_DECLTYPE_(proto::detail::make<r0>() --, result_type)
                result_type operator ()(Expr &expr, Context &ctx) const
                {
                    return proto::eval(proto::child_c<0>(expr), ctx) --;
                }
            };

            // Handle subscript specially.
            template<typename Expr, typename Context>
            struct default_eval<Expr, Context, proto::tag::subscript, 2>
            {
            private:
                typedef typename proto::result_of::child_c<Expr, 0>::type e0;
                typedef typename proto::result_of::child_c<Expr, 1>::type e1;
                typedef typename proto::result_of::eval<UNREF(e0), Context>::type r0;
                typedef typename proto::result_of::eval<UNREF(e1), Context>::type r1;
            public:
                BOOST_PROTO_DECLTYPE_(proto::detail::make<r0>()[proto::detail::make<r1>()], result_type)
                result_type operator ()(Expr &expr, Context &ctx) const
                {
                    return proto::eval(proto::child_c<0>(expr), ctx)[proto::eval(proto::child_c<1>(expr), ctx)];
                }
            };

            // Handle if_else_ specially.
            template<typename Expr, typename Context>
            struct default_eval<Expr, Context, proto::tag::if_else_, 3>
            {
            private:
                typedef typename proto::result_of::child_c<Expr, 0>::type e0;
                typedef typename proto::result_of::child_c<Expr, 1>::type e1;
                typedef typename proto::result_of::child_c<Expr, 2>::type e2;
                typedef typename proto::result_of::eval<UNREF(e0), Context>::type r0;
                typedef typename proto::result_of::eval<UNREF(e1), Context>::type r1;
                typedef typename proto::result_of::eval<UNREF(e2), Context>::type r2;
            public:
                BOOST_PROTO_DECLTYPE_(
                    proto::detail::make<r0>()
                  ? proto::detail::make<r1>()
                  : proto::detail::make<r2>()
                  , result_type
                )
                result_type operator ()(Expr &expr, Context &ctx) const
                {
                    return proto::eval(proto::child_c<0>(expr), ctx)
                         ? proto::eval(proto::child_c<1>(expr), ctx)
                         : proto::eval(proto::child_c<2>(expr), ctx);
                }
            };

            // Handle comma specially.
            template<typename Expr, typename Context>
            struct default_eval<Expr, Context, proto::tag::comma, 2>
            {
            private:
                typedef typename proto::result_of::child_c<Expr, 0>::type e0;
                typedef typename proto::result_of::child_c<Expr, 1>::type e1;
                typedef typename proto::result_of::eval<UNREF(e0), Context>::type r0;
                typedef typename proto::result_of::eval<UNREF(e1), Context>::type r1;
            public:
                typedef typename proto::detail::comma_result<r0, r1>::type result_type;
                result_type operator ()(Expr &expr, Context &ctx) const
                {
                    return proto::eval(proto::child_c<0>(expr), ctx), proto::eval(proto::child_c<1>(expr), ctx);
                }
            };

            // Handle function specially
            #define EVAL_TYPE(Z, N, DATA)                                                           \
                typename proto::result_of::eval<                                                    \
                    typename remove_reference<typename proto::result_of::child_c<DATA, N>::type>::type\
                  , Context                                                                         \
                >::type

            #define EVAL(Z, N, DATA)                                                                \
                proto::eval(proto::child_c<N>(DATA), context)

            #define BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/context/default.hpp>))
            #include BOOST_PP_ITERATE()

            #undef EVAL_TYPE
            #undef EVAL

            /// default_context
            ///
            struct default_context
            {
                /// default_context::eval
                ///
                template<typename Expr, typename ThisContext = default_context const>
                struct eval
                  : default_eval<Expr, ThisContext>
                {};
            };

        } // namespace context

    }} // namespace boost::proto

    #undef UNREF

    #endif

#else

    #define N BOOST_PP_ITERATION()

        template<typename Expr, typename Context>
        struct default_eval<Expr, Context, proto::tag::function, N>
        {
            typedef
                typename proto::detail::result_of_fixup<EVAL_TYPE(~, 0, Expr)>::type
            function_type;

            typedef
                typename boost::result_of<
                    function_type(BOOST_PP_ENUM_SHIFTED(N, EVAL_TYPE, Expr))
                >::type
            result_type;

            result_type operator ()(Expr &expr, Context &context) const
            {
                return EVAL(~, 0, expr)(BOOST_PP_ENUM_SHIFTED(N, EVAL, expr));
            }
        };

    #undef N

#endif
