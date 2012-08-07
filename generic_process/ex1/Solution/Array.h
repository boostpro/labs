///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)


#ifndef ARRAY_H_BOOST_CONSULTING
#define ARRAY_H_BOOST_CONSULTING

#include <cassert>
#include <cstdlib>
#include <climits>

// For each i in [0,size), write the result of fun(in[i]) to *out
inline int* Transform(int* in, std::size_t size, int (*fun)(int), int* out)
{
    for(std::size_t i=0; i < size; ++i, ++out)
    {
        *out = fun(in[i]);
    }
    return out;
}

inline int& GetAt(int* in, int size, int i)
{
    assert(i < size);
    return in[i];
}

inline int* Find(int* in, std::size_t size, int value)
{
    for(std::size_t i = 0; i < size; ++i)
    {
        if(value == in[i])
            return &in[i];
    }
    return in + size; // not found
}

#endif
