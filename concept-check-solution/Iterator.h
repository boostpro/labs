///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef ITERATOR_H_BOOST_CONSULTING
#define ITERATOR_H_BOOST_CONSULTING

#include "boost/concept/assert.hpp"
#include "boost/concept/requires.hpp"
#include "boost/concept/usage.hpp"
#include "boost/concept_archetype.hpp"
#include "boost/concept_check.hpp"
#include "boost/type_traits/add_reference.hpp"
#include "boost/optional.hpp"

namespace detail
{
  template <class T> inline void ignore_unused_variable_warning(T const&) {}

  // The version in the concept check lib (static_object<T>::get)
  // breaks when T is a reference type.
  template <class T>
  typename boost::add_reference<T>::type get()
  {
      static boost::optional<typename boost::add_reference<T>::type> x;
      return *x;
  }
}

#define CONCEPT struct
#define CONCEPT_MAP struct

template <typename T>
CONCEPT EqualityComparable
{
    BOOST_CONCEPT_USAGE(EqualityComparable)
    {
        bool result = (x == x);
        result = (x != x);
        detail::ignore_unused_variable_warning(result);
    }
 private:
    T x;
};

template <typename T>
CONCEPT CopyConstructible
{
    BOOST_CONCEPT_USAGE(CopyConstructible)
    {
        T y(x); 
     }
 private:
    T x;
};

#if 0
template <typename T, typename U> struct Convertible
{
    BOOST_CONCEPT_USAGE(Convertible)
    {
        f(x);
    }
 private:
    T x;
    void f(U);
};
#endif

template<typename T, typename U=T>
CONCEPT Assignable
{
    BOOST_CONCEPT_USAGE(Assignable)
    {
        T& result = (x = y);
        detail::ignore_unused_variable_warning(result);
    }
 private:
    T x;
    U y;
};

template <typename U, typename Base=boost::null_archetype<> >
struct AssignableArchetype2 : Base
{
    AssignableArchetype2& operator=(U const&);
};

template<typename Iterator>
struct Reference
{
    typedef typename Iterator::Reference Type;
};

// Pointers have the following reference type
template<typename T>
struct Reference<T*>
{
    typedef T& Type;
};

template<typename Iterator>
struct ValueType
{
    typedef typename Iterator::ValueType Type;
};

template<typename T>
struct ValueType<T*>
{
    typedef T Type;
};

template<typename T>
struct ValueType<T const*>
{
    typedef T Type;
};


struct Input {};
struct Forward : Input {};
struct Random : Forward {};

template <typename U>
CONCEPT ForwardIterator
  : EqualityComparable<U>, CopyConstructible<U>, Assignable<U>
{
    typedef typename Reference<U>::Type reference;
    typedef typename ValueType<U>::Type value_type;
    BOOST_CONCEPT_ASSERT((CopyConstructible<reference>));
    BOOST_CONCEPT_ASSERT((boost::Convertible<reference,value_type const&>));

    BOOST_CONCEPT_USAGE(ForwardIterator)
    {
        reference r = Get(self);
        Next(self);
        TestCategory(Category(self));
    }
private:
    void TestCategory(Forward);
    U self;
};

template <
    typename ValueType_ = boost::null_archetype<long>
>
struct ForwardIteratorArchetype
{
    // CopyConstructible and Assignable are the defaults
    typedef ValueType_ ValueType;
    struct Reference
      : boost::copy_constructible_archetype<boost::convertible_to_archetype<ValueType> >
    {};

    friend Reference Get(ForwardIteratorArchetype);
    friend void Next(ForwardIteratorArchetype&);
    friend Forward Category(ForwardIteratorArchetype);

    boost::boolean_archetype operator==(ForwardIteratorArchetype) const;
    boost::boolean_archetype operator!=(ForwardIteratorArchetype) const;
};

BOOST_CONCEPT_ASSERT((ForwardIterator<ForwardIteratorArchetype<> >));

template <typename U>
CONCEPT RandomIterator
   : ForwardIterator<U>
{
    BOOST_CONCEPT_USAGE(RandomIterator)
    {
        Skip(self,1);
        TestCategory(Category(self));
    }
private:
    void TestCategory(Random);
    U self;
};

template <typename ValueType_ =  boost::null_archetype<> >
struct RandomIteratorArchetype
  : ForwardIteratorArchetype<ValueType_>
{
    friend void Skip(RandomIteratorArchetype&, int);
    friend Random Category(RandomIteratorArchetype const&);
};
BOOST_CONCEPT_ASSERT((RandomIterator<RandomIteratorArchetype<> >));

template <class T>
T& Get(T* p) { return *p; }
template <class T>
void Next(T*& p) { ++p; }
template <class T>
void Skip(T*& p, int n) { p += n; }

template <typename T>
CONCEPT_MAP RandomIterator<T*>
{
    typedef T& reference;
    typedef T value_type;
};

template <typename T>
CONCEPT_MAP RandomIterator<T const*>
{
    typedef T const& reference;
    typedef T value_type;
};

// And pointers have the following category
template<typename T>
Random Category(T *)
{
    return Random();
}

#endif
