///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef GETAT_H_BOOST_CONSULTING
#define GETAT_H_BOOST_CONSULTING

#include "./Iterator.h"

template<typename Iterator>
typename Reference<Iterator>::Type GetAtImpl(Iterator iter, int i, Random)
{
    Skip(iter, i);
    return Get(iter);
}

template<typename Iterator>
typename Reference<Iterator>::Type GetAtImpl(Iterator iter, int i, Input)
{
    for(; 0 != i; --i)
    {
        Next(iter);
    }
    return Get(iter);
}

template<typename Iterator>
typename Reference<Iterator>::Type GetAt(Iterator iter, int i)
{
    return GetAtImpl(iter, i, Category(iter));
}

#endif
