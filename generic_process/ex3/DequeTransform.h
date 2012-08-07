///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef DEQUE_TRANSFORM_H_BOOST_CONSULTING
#define DEQUE_TRANSFORM_H_BOOST_CONSULTING

#include "./Deque.h"
#include "./Array.h"
#include "./Transform.h"

// Special Transform for Deque iterators.
// This version handles the segmented
// traversal more efficiently.
template<typename Fun, typename Out>
Out DequeTransform(Deque::Iterator begin, Deque::Iterator end, Fun fun, Out out)
{
    // Is the last segment the same as the first?
    if(begin.sfirst == end.sfirst)
    {
        // Transform within the first segment
        out = Transform(begin.first, end.first, fun, out);
    }
    else
    {
        // Transform the first segment
        out = Transform(begin.first, (*begin.sfirst)->last, fun, out);

        // Loop over all the intermediate segments
        for(++begin.sfirst; begin.sfirst != end.sfirst; ++begin.sfirst)
        {
            out = Transform((*begin.sfirst)->first, (*begin.sfirst)->last, fun, out);
        }

        // Transform the last segment.
        out = Transform((*begin.sfirst)->first, end.first, fun, out);
    }

    return out;
}

#endif
