///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TRANSFORM_H_BOOST_CONSULTING
#define TRANSFORM_H_BOOST_CONSULTING

#include "./Iterator.h"
#include "boost/utility/result_of.hpp"
#include "boost/utility/enable_if.hpp"
#include "boost/type_traits/add_reference.hpp"
#include "boost/type_traits/is_class.hpp"
#include "boost/mpl/if.hpp"

template <class T> struct check_type;

// If T is a reference (lvalue), we can at least make sure the result
// isn't a non-const rvalue, and that it has the right constness
template <class U>
struct check_type<U&>
{
    template <class V>
    static void mismatch(V&)
    {
        // When the argument is a T const (rvalue), this will match
        // and V will be deduced as T, so we can get a false negative
        // when U == T const.  There's no way to test for that case.
        BOOST_MPL_ASSERT((boost::is_same<V,U>));
    }
};

// If T is a non-reference, we can check that the result is not an
// lvalue and has the right cv qualification.
template <class U>
struct check_type
{
    template <class V>
    static void mismatch(V& x)
    {
        // This will always fire because V can't be deduced as a
        // reference type.
        x.illegal = 0;
    }

    struct convertible
    {
        convertible(U const&);
    };

    static void mismatch(convertible) {}
};

template <typename F, typename X>
CONCEPT Callable1
{
    // Account for the fact that F might be a function type instead of
    // a class by adding a reference to it.  Since all function call
    // operators must be members, a properly-supported result_of
    // should always give the same answer for result_of<F(...)>::type
    // and result_of<F&(...)>::type.
    typedef typename boost::result_of<
        typename boost::add_reference<F>::type (X)
    >::type result_type;

    BOOST_CONCEPT_USAGE(Callable1)
    {
        check_type<result_type>::mismatch(  detail::get<F>() ( detail::get<X>() )  );
    }
};

template <typename R, typename A0, typename Base = boost::null_archetype<void> >
struct Callable1Archetype : Base
{
    R operator()(A0) const
    {
        return detail::get<R>();
    }
};

namespace boost
{
template <typename R, typename A0, typename Base>
struct result_of<Callable1Archetype<R,A0,Base>&(A0)>
{
    typedef R type;
};
template <typename R, typename A0, typename Base>
struct result_of<Callable1Archetype<R,A0,Base> const&(A0)>
{
    typedef R type;
};
template <typename R, typename A0, typename Base>
struct result_of<Callable1Archetype<R,A0,Base>(A0)>
{
    typedef R type;
};
template <typename R, typename A0, typename Base>
struct result_of<Callable1Archetype<R,A0,Base> const(A0)>
{
    typedef R type;
};
}

BOOST_CONCEPT_ASSERT((Callable1<Callable1Archetype<char*,long*>,long*>));

template <typename Iterator, typename Function, typename Result>
BOOST_CONCEPT_REQUIRES(
    ((ForwardIterator<Iterator>))
    ((Callable1<Function,typename ForwardIterator<Iterator>::reference>)),

(Result*)) Transform(Iterator begin, Iterator end, Function const& fun, Result* out)
{
    for(; begin != end; Next(begin))
    {
        *out = fun(Get(begin));
        ++out;
    }
    return out;
}

inline void check_Transform()
{
    typedef ForwardIteratorArchetype<> Iterator;
    typedef AssignableArchetype2<ForwardIterator<Iterator>::value_type> Result;
    typedef Callable1Archetype<
        ForwardIterator<Iterator>::reference,
        ForwardIterator<Iterator>::reference
    > Function;

    Iterator x;
    Result* y = Transform(x, x, detail::get<Function>(), (Result*)0);
}

#endif // TRANSFORM_H_BOOST_CONSULTING
