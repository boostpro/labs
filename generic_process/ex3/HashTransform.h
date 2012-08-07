///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef HASH_TRANSFORM_H_BOOST_CONSULTING
#define HASH_TRANSFORM_H_BOOST_CONSULTING

#include "./HashMultiSet.h"
#include "./Transform.h"

// Special transform for HashMultiSet iterators.
// This version handles the segmented
// traversal more efficiently.
template<typename Fun, typename Out>
Out HashTransform(HashMultiSet::Iterator begin, HashMultiSet::Iterator end, Fun fun, Out out)
{
    if(begin.bptr == end.bptr)
    {
        out = Transform(begin.pos, end.pos, fun, out);
    }
    else
    {
        out = Transform(begin.pos, begin.bptr->End(), fun, out);

        // Loop over all the intermediate segments
        for(++begin.bptr; begin.bptr != end.bptr; ++begin.bptr)
        {
            out = Transform(begin.bptr->Begin(), begin.bptr->End(), fun, out);
        }

        // Transform the last segment.
        out = Transform(begin.bptr->Begin(), end.pos, fun, out);
    }

    return out;
}

#endif
