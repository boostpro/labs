///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)


#ifndef ARRAY2_H_BOOST_CONSULTING
#define ARRAY2_H_BOOST_CONSULTING

#include "./Iterator.h"

// Well, this is pretty simple!
typedef int* ArrayIterator;

inline int& Get(ArrayIterator iter)
{
    return *iter;
}

inline void Next(ArrayIterator& iter)
{
    ++iter;
}

inline void Skip(ArrayIterator& iter, int distance)
{
    iter += distance;
}

#endif
