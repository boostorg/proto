#ifndef BOOST_PP_IS_ITERATING
    ///////////////////////////////////////////////////////////////////////////////
    /// \file default.hpp
    /// Contains definition of the _default transform, which gives operators their
    /// usual C++ meanings and uses Boost.Typeof to deduce return types.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #ifndef BOOST_PROTO_TRANSFORM_DEFAULT_HPP_EAN_04_04_2008
    #define BOOST_PROTO_TRANSFORM_DEFAULT_HPP_EAN_04_04_2008

    #include <boost/proto/detail/prefix.hpp>
    #include <boost/preprocessor/iteration/iterate.hpp>
    #include <boost/preprocessor/repetition/repeat.hpp>
    #include <boost/preprocessor/repetition/enum_shifted.hpp>
    #include <boost/preprocessor/repetition/enum_shifted_params.hpp>
    #include <boost/ref.hpp>
    #include <boost/utility/enable_if.hpp>
    #include <boost/type_traits/is_member_pointer.hpp>
    #include <boost/proto/proto_fwd.hpp>
    #include <boost/proto/traits.hpp>
    #include <boost/proto/transform/impl.hpp>
    #include <boost/proto/transform/arg.hpp>
    #include <boost/proto/detail/decltype.hpp>
    #include <boost/proto/detail/suffix.hpp>

    namespace boost { namespace proto
    {
        namespace detail
        {
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
        }

        template<typename Grammar>
        struct _default
          : transform<_default<Grammar> >
        {
            template<typename Expr, typename State, typename Data, typename Tag, long Arity>
            struct impl2;

            template<typename Expr, typename State, typename Data>
            struct impl2<Expr, State, Data, tag::terminal, 0>
              : _value::impl<Expr, State, Data>
            {};

            #define BOOST_PROTO_UNARY_OP_RESULT(OP, TAG)                                            \
            template<typename Expr, typename State, typename Data>                                  \
            struct impl2<Expr, State, Data, TAG, 1>                                                 \
              : transform_impl<Expr, State, Data>                                                   \
            {                                                                                       \
            private:                                                                                \
                typedef typename result_of::child_c<Expr, 0>::type e0;                              \
                typedef typename Grammar::template impl<e0, State, Data>::result_type r0;           \
            public:                                                                                 \
                BOOST_PROTO_DECLTYPE_(OP proto::detail::make<r0>(), result_type)                    \
                result_type operator ()(                                                            \
                    typename impl2::expr_param expr                                                 \
                  , typename impl2::state_param state                                               \
                  , typename impl2::data_param data                                                 \
                ) const                                                                             \
                {                                                                                   \
                    typename Grammar::template impl<e0, State, Data> t0;                            \
                    return OP t0(proto::child_c<0>(expr), state, data);                             \
                }                                                                                   \
            };                                                                                      \
            /**/

            #define BOOST_PROTO_BINARY_OP_RESULT(OP, TAG)                                           \
            template<typename Expr, typename State, typename Data>                                  \
            struct impl2<Expr, State, Data, TAG, 2>                                                 \
              : transform_impl<Expr, State, Data>                                                   \
            {                                                                                       \
            private:                                                                                \
                typedef typename result_of::child_c<Expr, 0>::type e0;                              \
                typedef typename result_of::child_c<Expr, 1>::type e1;                              \
                typedef typename Grammar::template impl<e0, State, Data>::result_type r0;           \
                typedef typename Grammar::template impl<e1, State, Data>::result_type r1;           \
            public:                                                                                 \
                BOOST_PROTO_DECLTYPE_(                                                              \
                    proto::detail::make<r0>() OP proto::detail::make<r1>()                          \
                  , result_type                                                                     \
                )                                                                                   \
                result_type operator ()(                                                            \
                    typename impl2::expr_param expr                                                 \
                  , typename impl2::state_param state                                               \
                  , typename impl2::data_param data                                                 \
                ) const                                                                             \
                {                                                                                   \
                    typename Grammar::template impl<e0, State, Data> t0;                            \
                    typename Grammar::template impl<e1, State, Data> t1;                            \
                    return t0(proto::child_c<0>(expr), state, data)                                 \
                        OP t1(proto::child_c<1>(expr), state, data);                                \
                }                                                                                   \
            };                                                                                      \
            /**/

            BOOST_PROTO_UNARY_OP_RESULT(+, tag::unary_plus)
            BOOST_PROTO_UNARY_OP_RESULT(-, tag::negate)
            BOOST_PROTO_UNARY_OP_RESULT(*, tag::dereference)
            BOOST_PROTO_UNARY_OP_RESULT(~, tag::complement)
            BOOST_PROTO_UNARY_OP_RESULT(&, tag::address_of)
            BOOST_PROTO_UNARY_OP_RESULT(!, tag::logical_not)
            BOOST_PROTO_UNARY_OP_RESULT(++, tag::pre_inc)
            BOOST_PROTO_UNARY_OP_RESULT(--, tag::pre_dec)

            BOOST_PROTO_BINARY_OP_RESULT(<<, tag::shift_left)
            BOOST_PROTO_BINARY_OP_RESULT(>>, tag::shift_right)
            BOOST_PROTO_BINARY_OP_RESULT(*, tag::multiplies)
            BOOST_PROTO_BINARY_OP_RESULT(/, tag::divides)
            BOOST_PROTO_BINARY_OP_RESULT(%, tag::modulus)
            BOOST_PROTO_BINARY_OP_RESULT(+, tag::plus)
            BOOST_PROTO_BINARY_OP_RESULT(-, tag::minus)
            BOOST_PROTO_BINARY_OP_RESULT(<, tag::less)
            BOOST_PROTO_BINARY_OP_RESULT(>, tag::greater)
            BOOST_PROTO_BINARY_OP_RESULT(<=, tag::less_equal)
            BOOST_PROTO_BINARY_OP_RESULT(>=, tag::greater_equal)
            BOOST_PROTO_BINARY_OP_RESULT(==, tag::equal_to)
            BOOST_PROTO_BINARY_OP_RESULT(!=, tag::not_equal_to)
            BOOST_PROTO_BINARY_OP_RESULT(||, tag::logical_or)
            BOOST_PROTO_BINARY_OP_RESULT(&&, tag::logical_and)
            BOOST_PROTO_BINARY_OP_RESULT(&, tag::bitwise_and)
            BOOST_PROTO_BINARY_OP_RESULT(|, tag::bitwise_or)
            BOOST_PROTO_BINARY_OP_RESULT(^, tag::bitwise_xor)
            BOOST_PROTO_BINARY_OP_RESULT(->*, tag::mem_ptr)

            BOOST_PROTO_BINARY_OP_RESULT(=, tag::assign)
            BOOST_PROTO_BINARY_OP_RESULT(<<=, tag::shift_left_assign)
            BOOST_PROTO_BINARY_OP_RESULT(>>=, tag::shift_right_assign)
            BOOST_PROTO_BINARY_OP_RESULT(*=, tag::multiplies_assign)
            BOOST_PROTO_BINARY_OP_RESULT(/=, tag::divides_assign)
            BOOST_PROTO_BINARY_OP_RESULT(%=, tag::modulus_assign)
            BOOST_PROTO_BINARY_OP_RESULT(+=, tag::plus_assign)
            BOOST_PROTO_BINARY_OP_RESULT(-=, tag::minus_assign)
            BOOST_PROTO_BINARY_OP_RESULT(&=, tag::bitwise_and_assign)
            BOOST_PROTO_BINARY_OP_RESULT(|=, tag::bitwise_or_assign)
            BOOST_PROTO_BINARY_OP_RESULT(^=, tag::bitwise_xor_assign)

            #undef BOOST_PROTO_UNARY_OP_RESULT
            #undef BOOST_PROTO_BINARY_OP_RESULT

            template<typename Expr, typename State, typename Data>
            struct impl2<Expr, State, Data, tag::post_inc, 1>
              : transform_impl<Expr, State, Data>
            {
            private:
                typedef typename result_of::child_c<Expr, 0>::type e0;
                typedef typename Grammar::template impl<e0, State, Data>::result_type r0;
            public:
                BOOST_PROTO_DECLTYPE_(proto::detail::make<r0>() ++, result_type)
                result_type operator ()(
                    typename impl2::expr_param expr
                  , typename impl2::state_param state
                  , typename impl2::data_param data
                ) const
                {
                    typename Grammar::template impl<e0, State, Data> t0;
                    return t0(proto::child_c<0>(expr), state, data) ++;
                }
            };

            template<typename Expr, typename State, typename Data>
            struct impl2<Expr, State, Data, tag::post_dec, 1>
              : transform_impl<Expr, State, Data>
            {
            private:
                typedef typename result_of::child_c<Expr, 0>::type e0;
                typedef typename Grammar::template impl<e0, State, Data>::result_type r0;
            public:
                BOOST_PROTO_DECLTYPE_(proto::detail::make<r0>() --, result_type)
                result_type operator ()(
                    typename impl2::expr_param expr
                  , typename impl2::state_param state
                  , typename impl2::data_param data
                ) const
                {
                    typename Grammar::template impl<e0, State, Data> t0;
                    return t0(proto::child_c<0>(expr), state, data) --;
                }
            };

            template<typename Expr, typename State, typename Data>
            struct impl2<Expr, State, Data, tag::subscript, 2>
              : transform_impl<Expr, State, Data>
            {
            private:
                typedef typename result_of::child_c<Expr, 0>::type e0;
                typedef typename result_of::child_c<Expr, 1>::type e1;
                typedef typename Grammar::template impl<e0, State, Data>::result_type r0;
                typedef typename Grammar::template impl<e1, State, Data>::result_type r1;
            public:
                BOOST_PROTO_DECLTYPE_(
                    proto::detail::make<r0>() [ proto::detail::make<r1>() ]
                  , result_type
                )
                result_type operator ()(
                    typename impl2::expr_param expr
                  , typename impl2::state_param state
                  , typename impl2::data_param data
                ) const
                {
                    typename Grammar::template impl<e0, State, Data> t0;
                    typename Grammar::template impl<e1, State, Data> t1;
                    return t0(proto::child_c<0>(expr), state, data) [
                           t1(proto::child_c<1>(expr), state, data) ];
                }
            };

            template<typename Expr, typename State, typename Data>
            struct impl2<Expr, State, Data, tag::if_else_, 3>
              : transform_impl<Expr, State, Data>
            {
            private:
                typedef typename result_of::child_c<Expr, 0>::type e0;
                typedef typename result_of::child_c<Expr, 1>::type e1;
                typedef typename result_of::child_c<Expr, 2>::type e2;
                typedef typename Grammar::template impl<e0, State, Data>::result_type r0;
                typedef typename Grammar::template impl<e1, State, Data>::result_type r1;
                typedef typename Grammar::template impl<e2, State, Data>::result_type r2;
            public:
                BOOST_PROTO_DECLTYPE_(
                    proto::detail::make<r0>()
                  ? proto::detail::make<r1>()
                  : proto::detail::make<r2>()
                  , result_type
                )
                result_type operator ()(
                    typename impl2::expr_param expr
                  , typename impl2::state_param state
                  , typename impl2::data_param data
                ) const
                {
                    typename Grammar::template impl<e0, State, Data> t0;
                    typename Grammar::template impl<e1, State, Data> t1;
                    typename Grammar::template impl<e2, State, Data> t2;
                    return t0(proto::child_c<0>(expr), state, data)
                         ? t1(proto::child_c<1>(expr), state, data)
                         : t2(proto::child_c<2>(expr), state, data);
                }
            };

            template<typename Expr, typename State, typename Data>
            struct impl2<Expr, State, Data, tag::comma, 2>
              : transform_impl<Expr, State, Data>
            {
            private:
                typedef typename result_of::child_c<Expr, 0>::type e0;
                typedef typename result_of::child_c<Expr, 1>::type e1;
                typedef typename Grammar::template impl<e0, State, Data>::result_type r0;
                typedef typename Grammar::template impl<e1, State, Data>::result_type r1;
            public:
                typedef typename proto::detail::comma_result<r0, r1>::type result_type;
                result_type operator ()(
                    typename impl2::expr_param expr
                  , typename impl2::state_param state
                  , typename impl2::data_param data
                ) const
                {
                    typename Grammar::template impl<e0, State, Data> t0;
                    typename Grammar::template impl<e1, State, Data> t1;
                    return t0(proto::child_c<0>(expr), state, data)
                         , t1(proto::child_c<1>(expr), state, data);
                }
            };
            
            #define EVAL_TYPE(Z, N, DATA)                                                           \
                typedef                                                                             \
                    typename result_of::child_c<DATA, N>::type                                      \
                BOOST_PP_CAT(e, N);                                                                 \
                typedef                                                                             \
                    typename Grammar::template impl<BOOST_PP_CAT(e, N), State, Data>::result_type   \
                BOOST_PP_CAT(r, N);                                                                 \
                /**/

            #define EVAL(Z, N, DATA)                                                                \
                typename Grammar::template impl<BOOST_PP_CAT(e, N), State, Data>()(                 \
                    proto::child_c<N>(DATA), state, data                                            \
                )                                                                                   \
                /**/

            #define BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/transform/default.hpp>))
            #include BOOST_PP_ITERATE()

            #undef EVAL_TYPE
            #undef EVAL

            template<typename Expr, typename State, typename Data>
            struct impl
              : impl2<
                    Expr
                  , State
                  , Data
                  , typename transform_impl<Expr, State, Data>::expr::proto_tag
                  , transform_impl<Expr, State, Data>::expr::proto_arity::value
                >
            {};
        };

        template<typename Grammar>
        struct is_callable<_default<Grammar> >
          : mpl::true_
        {};

    }}

    #endif

#else

    #define N BOOST_PP_ITERATION()

        template<typename Expr, typename State, typename Data>
        struct impl2<Expr, State, Data, tag::function, N>
          : transform_impl<Expr, State, Data>
        {
            BOOST_PP_REPEAT(N, EVAL_TYPE, Expr)

            typedef
                typename proto::detail::result_of_fixup<r0>::type
            function_type;

            typedef
                typename boost::result_of<
                    function_type(BOOST_PP_ENUM_SHIFTED_PARAMS(N, r))
                >::type
            result_type;

            #if N == 1
            result_type operator ()(
                typename impl2::expr_param expr
              , typename impl2::state_param state
              , typename impl2::data_param data
            ) const
            {
                return EVAL(~, 0, expr)(BOOST_PP_ENUM_SHIFTED(N, EVAL, expr));
            }
            #else
            result_type operator ()(
                typename impl2::expr_param expr
              , typename impl2::state_param state
              , typename impl2::data_param data
            ) const
            {
                return this->invoke(expr, state, data, is_member_pointer<function_type>());
            }

            result_type invoke(
                typename impl2::expr_param expr
              , typename impl2::state_param state
              , typename impl2::data_param data
              , mpl::false_
            ) const
            {
                return EVAL(~, 0, expr)(BOOST_PP_ENUM_SHIFTED(N, EVAL, expr));
            }

            result_type invoke(
                typename impl2::expr_param expr
              , typename impl2::state_param state
              , typename impl2::data_param data
              , mpl::true_
            ) const
            {
                #define M0(Z, M, expr) BOOST_PP_COMMA_IF(BOOST_PP_SUB(M, 2)) EVAL(Z, M, expr)
                return (detail::deref(EVAL(~, 1, expr)) .* EVAL(~, 0, expr))(
                    BOOST_PP_REPEAT_FROM_TO(2, N, M0, expr)
                );
                #undef M0
            }
            #endif
        };

    #undef N

#endif
