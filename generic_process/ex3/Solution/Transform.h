///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TRANSFORM_H_BOOST_CONSULTING
#define TRANSFORM_H_BOOST_CONSULTING

#include "./Iterator.h"

// Segmented transform
template<typename Iterator, typename Function, typename Output, typename Seg>
Output TransformImpl2(Iterator begin, Iterator end, Function fun, Output out, Seg* sbegin)
{
    Seg* send = Segment(end);

    if(sbegin == send)
    {
        out = Transform(Local(begin), Local(end), fun, out);
    }
    else
    {
        out = Transform(Local(begin), End(*sbegin), fun, out);

        // Loop over all the intermediate segments
        for(++sbegin; sbegin != send; ++sbegin)
        {
            out = Transform(Begin(*sbegin), End(*sbegin), fun, out);
        }

        // Transform the last sbegin.
        out = Transform(Begin(*sbegin), Local(end), fun, out);
    }

    return out;
}

template<typename Iterator, typename Function, typename Output>
Output TransformImpl(Iterator begin, Iterator end, Function fun, Output out, True)
{
    return TransformImpl2(begin, end, fun, out, Segment(begin));
}

// Non-Segmented transform
template<typename Iterator, typename Function, typename Output>
Output TransformImpl(Iterator begin, Iterator end, Function fun, Output out, False)
{
    for(; begin != end; Next(begin))
    {
        *out = fun(Get(begin));
        ++out;
    }
    return out;
}

template<typename Iterator, typename Function, typename Output>
Output Transform(Iterator begin, Iterator end, Function fun, Output out)
{
    return TransformImpl(begin, end, fun, out, IsSegmented(begin));
}

#endif
