///////////////////////////////////////////////////////////////////////////////
// make_expr.hpp
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <sstream>
#include <boost/version.hpp>
#include <boost/proto/core.hpp>
#include <boost/proto/transform.hpp>
#if BOOST_VERSION >= 103500
#include <boost/fusion/tuple.hpp>
#else
#include <boost/spirit/fusion/sequence/make_tuple.hpp>
#endif
#include <boost/test/unit_test.hpp>

using namespace boost;
using namespace proto;

template<typename E> struct ewrap;

struct mydomain
  : domain<generator<ewrap> >
{};

template<typename E> struct ewrap
  : extends<E, ewrap<E>, mydomain>
{
    explicit ewrap(E const &e = E())
      : extends<E, ewrap<E>, mydomain>(e)
    {}
};

void test_make_expr()
{
    int i = 42;
    terminal<int>::type t1 = make_expr<tag::terminal>(1);
    terminal<int>::type t2 = make_expr<tag::terminal>(i);
    unary_plus<terminal<int>::type>::type p1 = make_expr<tag::unary_plus>(1);
    unary_plus<terminal<int>::type>::type p2 = make_expr<tag::unary_plus>(i);
    BOOST_CHECK_EQUAL(proto::value(proto::child(p2)), 42);

    ewrap<unary_plus<ewrap<terminal<int>::type> >::type> p3 = make_expr<tag::unary_plus, mydomain>(i);
    BOOST_CHECK_EQUAL(proto::value(proto::child(p3)), 42);

    ewrap<plus<
        ewrap<unary_plus<ewrap<terminal<int>::type> >::type>
      , ewrap<terminal<int>::type>
    >::type> p4 = make_expr<tag::plus>(p3, 0);
    BOOST_CHECK_EQUAL(proto::value(proto::child(proto::left(p4))), 42);
}

void test_make_expr_ref()
{
    int i = 42;
    terminal<int const &>::type t1 = make_expr<tag::terminal>(boost::cref(1)); // DANGEROUS
    terminal<int &>::type t2 = make_expr<tag::terminal>(boost::ref(i));
    BOOST_CHECK_EQUAL(&i, &proto::value(t2));
    unary_plus<terminal<int const &>::type>::type p1 = make_expr<tag::unary_plus>(boost::cref(1)); // DANGEROUS
    unary_plus<terminal<int &>::type>::type p2 = make_expr<tag::unary_plus>(boost::ref(i));
    BOOST_CHECK_EQUAL(proto::value(proto::child(p2)), 42);

    ewrap<unary_plus<ewrap<terminal<int &>::type> >::type> p3 = make_expr<tag::unary_plus, mydomain>(boost::ref(i));
    BOOST_CHECK_EQUAL(proto::value(proto::child(p3)), 42);

    ewrap<plus<
        ewrap<unary_plus<ewrap<terminal<int &>::type> >::type> &
      , ewrap<terminal<int>::type>
    >::type> p4 = make_expr<tag::plus>(boost::ref(p3), 0);
    BOOST_CHECK_EQUAL(proto::value(proto::child(proto::left(p4))), 42);
}

void test_make_expr_functional()
{
    int i = 42;
    terminal<int>::type t1 = functor::make_expr<tag::terminal>()(1);
    terminal<int>::type t2 = functor::make_expr<tag::terminal>()(i);
    unary_plus<terminal<int>::type>::type p1 = functor::make_expr<tag::unary_plus>()(1);
    unary_plus<terminal<int>::type>::type p2 = functor::make_expr<tag::unary_plus>()(i);
    BOOST_CHECK_EQUAL(proto::value(proto::child(p2)), 42);

    ewrap<unary_plus<ewrap<terminal<int>::type> >::type> p3 = functor::make_expr<tag::unary_plus, mydomain>()(i);
    BOOST_CHECK_EQUAL(proto::value(proto::child(p3)), 42);

    ewrap<plus<
        ewrap<unary_plus<ewrap<terminal<int>::type> >::type>
      , ewrap<terminal<int>::type>
    >::type> p4 = functor::make_expr<tag::plus, mydomain>()(p3, 0);
    BOOST_CHECK_EQUAL(proto::value(proto::child(proto::left(p4))), 42);
}

void test_make_expr_functional_ref()
{
    int i = 42;
    terminal<int const &>::type t1 = functor::make_expr<tag::terminal>()(boost::cref(1)); // DANGEROUS
    terminal<int &>::type t2 = functor::make_expr<tag::terminal>()(boost::ref(i));
    BOOST_CHECK_EQUAL(&i, &proto::value(t2));
    unary_plus<terminal<int const &>::type>::type p1 = functor::make_expr<tag::unary_plus>()(boost::cref(1)); // DANGEROUS
    unary_plus<terminal<int &>::type>::type p2 = functor::make_expr<tag::unary_plus>()(boost::ref(i));
    BOOST_CHECK_EQUAL(proto::value(proto::child(p2)), 42);

    ewrap<unary_plus<ewrap<terminal<int &>::type> >::type> p3 = functor::make_expr<tag::unary_plus, mydomain>()(boost::ref(i));
    BOOST_CHECK_EQUAL(proto::value(proto::child(p3)), 42);

    ewrap<plus<
        ewrap<unary_plus<ewrap<terminal<int &>::type> >::type> &
      , ewrap<terminal<int>::type>
    >::type> p4 = functor::make_expr<tag::plus, mydomain>()(boost::ref(p3), 0);
    BOOST_CHECK_EQUAL(proto::value(proto::child(proto::left(p4))), 42);
}

void test_unpack_expr()
{
    int i = 42;
    terminal<int>::type t1 = unpack_expr<tag::terminal>(fusion::make_tuple(1));
    terminal<int &>::type t2 = unpack_expr<tag::terminal>(fusion::make_tuple(boost::ref(i)));
    unary_plus<terminal<int>::type>::type p1 = unpack_expr<tag::unary_plus>(fusion::make_tuple(1));
    unary_plus<terminal<int &>::type>::type p2 = unpack_expr<tag::unary_plus>(fusion::make_tuple(boost::ref(i)));
    BOOST_CHECK_EQUAL(proto::value(proto::child(p2)), 42);

    ewrap<unary_plus<ewrap<terminal<int &>::type> >::type> p3 = unpack_expr<tag::unary_plus, mydomain>(fusion::make_tuple(boost::ref(i)));
    BOOST_CHECK_EQUAL(proto::value(proto::child(p3)), 42);

    ewrap<plus<
        ewrap<unary_plus<ewrap<terminal<int &>::type> >::type> &
      , ewrap<terminal<int>::type>
    >::type> p4 = unpack_expr<tag::plus>(fusion::make_tuple(boost::ref(p3), 0));
    BOOST_CHECK_EQUAL(proto::value(proto::child(proto::left(p4))), 42);
}

void test_unpack_expr_functional()
{
    int i = 42;
    terminal<int>::type t1 = functor::unpack_expr<tag::terminal>()(fusion::make_tuple(1));
    terminal<int &>::type t2 = functor::unpack_expr<tag::terminal>()(fusion::make_tuple(boost::ref(i)));
    unary_plus<terminal<int>::type>::type p1 = functor::unpack_expr<tag::unary_plus>()(fusion::make_tuple(1));
    unary_plus<terminal<int &>::type>::type p2 = functor::unpack_expr<tag::unary_plus>()(fusion::make_tuple(boost::ref(i)));
    BOOST_CHECK_EQUAL(proto::value(proto::child(p2)), 42);

    ewrap<unary_plus<ewrap<terminal<int &>::type> >::type> p3 = functor::unpack_expr<tag::unary_plus, mydomain>()(fusion::make_tuple(boost::ref(i)));
    BOOST_CHECK_EQUAL(proto::value(proto::child(p3)), 42);

    ewrap<plus<
        ewrap<unary_plus<ewrap<terminal<int &>::type> >::type> &
      , ewrap<terminal<int>::type>
    >::type> p4 = functor::unpack_expr<tag::plus>()(fusion::make_tuple(boost::ref(p3), 0));
    BOOST_CHECK_EQUAL(proto::value(proto::child(proto::left(p4))), 42);
}

#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
#define _ref(x) call<_ref(x)>
#define Minus(x) call<Minus(x)>
#endif

// Turn all terminals held by reference into ones held by value
struct ByVal
  : or_<
        when<terminal<_>, _make_terminal(_value)>
      , when<nary_expr<_, vararg<ByVal> > >
    >
{};

// Turn all terminals held by value into ones held by reference (not safe in general)
struct ByRef
  : or_<
        when<terminal<_>, _make_terminal(_ref(_value))>
      , when<nary_expr<_, vararg<ByRef> > >
    >
{};

// turn all plus nodes to minus nodes:
struct Minus
  : or_<
        when<terminal<_> >
      , when<plus<Minus, Minus>, _make_minus(Minus(_left), Minus(_right)) >
    >
{};

struct Square
  : or_<
        // Not creating new terminal nodes here,
        // so hold the existing terminals by reference:
        when<terminal<_>, _make_multiplies(_ref(_), _ref(_))>
      , when<plus<Square, Square> >
    >
{};

#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
#undef _ref
#undef Minus
#endif

void test_make_expr_transform()
{
    plus<
        terminal<int>::type
      , terminal<int>::type
    >::type t1 = ByVal()(as_expr(1) + 1);

    plus<
        terminal<int const &>::type
      , terminal<int const &>::type
    >::type t2 = ByRef()(as_expr(1) + 1);

    minus<
        terminal<int>::type
      , terminal<int const &>::type
    >::type t3 = Minus()(as_expr(1) + 1);

    plus<
        multiplies<terminal<int>::type const &, terminal<int>::type const &>::type
      , multiplies<terminal<int const &>::type const &, terminal<int const &>::type const &>::type
    >::type t4 = Square()(as_expr(1) + 1);
}

using namespace unit_test;
///////////////////////////////////////////////////////////////////////////////
// init_unit_test_suite
//
test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite *test = BOOST_TEST_SUITE("test make_expr, unpack_expr and friends");

    test->add(BOOST_TEST_CASE(&test_make_expr));
    test->add(BOOST_TEST_CASE(&test_make_expr_ref));
    test->add(BOOST_TEST_CASE(&test_make_expr_functional));
    test->add(BOOST_TEST_CASE(&test_make_expr_functional_ref));
    test->add(BOOST_TEST_CASE(&test_unpack_expr));
    test->add(BOOST_TEST_CASE(&test_unpack_expr_functional));
    test->add(BOOST_TEST_CASE(&test_make_expr_transform));

    return test;
}
