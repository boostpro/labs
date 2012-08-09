///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef GETAT_H_BOOST_CONSULTING
#define GETAT_H_BOOST_CONSULTING

#include "./Iterator.h"

template<typename Iterator>
BOOST_CONCEPT_REQUIRES(
    ((RandomIterator<Iterator>)),
    (typename Reference<Iterator>::Type)) GetAtImpl(Iterator iter, int i, Random)
{
    Skip(iter, i);
    return Get(iter);
}

template<typename Iterator>
BOOST_CONCEPT_REQUIRES(
    ((ForwardIterator<Iterator>)),
    (typename Reference<Iterator>::Type)) GetAtImpl(Iterator iter, int i, Input)
{
    for(; 0 != i; --i)
    {
        Next(iter);
    }
    return Get(iter);
}

template<typename Iterator>
BOOST_CONCEPT_REQUIRES(
    ((ForwardIterator<Iterator>)),
    (typename Reference<Iterator>::Type)) GetAt(Iterator iter, int i)
{
    return GetAtImpl(iter, i, Category(iter));
}

inline void check_GetAt()
{
    {
        typedef ForwardIteratorArchetype<> Iterator;

        Iterator x;
        ForwardIterator<Iterator>::reference y = GetAt(x, 3);
    }

    {
        typedef RandomIteratorArchetype<> Iterator;

        Iterator x;
        RandomIterator<Iterator>::reference y = GetAt(x, 3);
    }
}

#endif
