///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef ITERATOR_H_BOOST_CONSULTING
#define ITERATOR_H_BOOST_CONSULTING

struct Input {};
struct Forward : Input {};
struct Random : Forward {};

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

// And pointers have the following category
template<typename T>
Random Category(T *)
{
    return Random();
}

#endif
