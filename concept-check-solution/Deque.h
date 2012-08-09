///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef DEQUE2_H_BOOST_CONSULTING
#define DEQUE2_H_BOOST_CONSULTING

#include <cassert>
#include <utility>
#include "./Iterator.h"

const int DequeSegmentSize = 5;

// DequeSegment:
//
// -----------------------------------------------------------------------
// |         |         |         |         |         |         |         |
// | first   | last    | data[0] | data[1] | data[2] | data[3] | data[4] |
// |         |         |         |         |         |         |         |
// ------------------------------------^-----------------^----------------
//      |         |                   / \               / \          
//      |         |                    |                 |         
//      |         |                    |                 |         
//      \---------+--------------------/                 |
//                |                                      |
//                |                                      |
//                \--------------------------------------/
//
struct DequeSegment
{
    int* first;  // pointer to the first element in this segment
    int* last;   // pointer to the last+1 element in this segment
    int data[DequeSegmentSize];

    explicit DequeSegment(int offset)
      : first(data + offset)
      , last(first)
    {}
};

// A representation of a position within a Deque
class DequeIterator
{
public:

    DequeSegment** sfirst;
    DequeSegment** slast;
    int* first;

public:

    typedef int& Reference;
    typedef int ValueType;

    DequeIterator(DequeSegment** seg, DequeSegment** seg_end, int* elem)
      : sfirst(seg), slast(seg_end), first(elem)
    {}
};

// Two Deque iterators are equal if they refer to the
// same element
inline bool operator==(DequeIterator i1, DequeIterator i2)
{
    return i1.first == i2.first;
}

inline bool operator!=(DequeIterator i1, DequeIterator i2)
{
    return !(i1 == i2);
}

// "dereference" a deque iterator
inline int& Get(DequeIterator iter)
{
    return *iter.first;
}

// advance a deque iterator by one
inline void Next(DequeIterator& iter)
{
    assert(iter.first != (*iter.sfirst)->last);
    // next element
    ++iter.first;
    // are we at the end of the current segment?
    if(iter.first == (*iter.sfirst)->last)
    {
        // are we at the last segment?
        if(iter.sfirst != iter.slast)
        {
            // next segment
            ++iter.sfirst;
            // move to the first element in the segment
            iter.first = (*iter.sfirst)->first;
        }
    }
}

// advance a deque iterator by N
inline void Skip(DequeIterator& iter, int distance)
{
    // count the number of elements left in the first segment
    int count_first = (*iter.sfirst)->last - iter.first;
    // are we advancing to a point in the current segment?
    if(distance < count_first)
    {
        // advance to that point, and we're done
        iter.first += distance;
    }
    else
    {
        // otherwise, subtract from distance the room
        // in the current segment
        distance -= count_first;
        // Are we advancing exactly to the end of the last segment?
        if((distance / DequeSegmentSize) == (iter.slast - iter.sfirst))
        {
            assert(0 == distance % DequeSegmentSize);
            iter.sfirst = iter.slast;
            iter.first = (*iter.sfirst)->last;
        }
        else
        {
            // advance the segment index
            iter.sfirst += distance / DequeSegmentSize + 1;
            // set the element index to the remainder
            iter.first = (*iter.sfirst)->first + distance % DequeSegmentSize;
        }
    }
}

inline Random Category(DequeIterator)
{
    return Random();
}

// Deque:
//
// ---------------       ---------------
// |              |      |             |       ---------------...-
// | segments     |----->| segments[0] |------>| Segment 0 ...   |         
// |              |      |             |       ---------------...-
// ----------------      ---------------
// |              |      |             |       ---------------...-
// | count        |      | segments[1] |------>| Segment 1 ...   |
// |              |      |             |       ---------------...-
// ----------------      ---------------
//                       |             |       ---------------...-
//                       | segments[2] |------>| Segment 2 ...   |
//                       |             |       ---------------...-
//                       |---- .... ---|
//                       |             |       ---------------...-
//                       | segments[N] |------>| Segment 3 ...   |
//                       |             |       ---------------...-
//                       ---------------
class Deque
{
    // Pointer to the array of segment pointers.
    DequeSegment** segments;
    // Size of the array of segment pointers.
    int count;

public:

    Deque()
      : segments(new DequeSegment*[1])
      , count(0)
    {}

    ~Deque()
    {
        for(int i = 0; i < count; ++i)
            delete segments[i];
        delete[] segments;
    }

    // Add an element to the back of the Deque.
    // May need to allocate a new Segment.
    void PushBack(int value)
    {
        // If there are no segments, or if the last segment
        // is full, add a new segment
        if(0 == count || segments[count-1]->last == segments[count-1]->data + DequeSegmentSize)
        {
            DequeSegment* s = new DequeSegment(0);
            DequeSegment** segs = new DequeSegment*[count+1], ** tmp;
            for(int i = 0; i < count; ++i)
                segs[i] = segments[i];
            segs[count++] = s;
            assert(segs[0]->first);
            tmp = segments;
            segments = segs;
            delete[] tmp;
        }

        // Get the last segment
        DequeSegment* s = segments[count-1];
        // Write into the last position, and increment
        // the last position.
        *s->last++ = value;
    }

    // Remove an element from the front of the Deque.
    // May deallocate a Segment.
    void PopFront()
    {
        assert(0 != count && segments[0]->first != segments[0]->data + DequeSegmentSize);
        if(++segments[0]->first == segments[0]->data + DequeSegmentSize)
        {
            DequeSegment** segs = new DequeSegment*[count-1], ** tmp;
            for(int i = 1; i < count; ++i)
                segs[i-1] = segments[i];
            --count;
            tmp = segments;
            segments = segs;
            delete tmp[0];
            delete[] tmp;
        }
    }

    typedef DequeIterator Iterator;

    Iterator Begin()
    {
        // No segments?
        if(0 == count)
            return Iterator(segments, segments, 0);

        return Iterator(
            segments
          , segments + count - 1
          , segments[0]->first
        );
    }

    Iterator End()
    {
        // No segments?
        if(0 == count)
            return Iterator(segments, segments, 0);

        return Iterator(
            segments + count - 1
          , segments + count - 1
          , segments[count - 1]->last
        );
    }
};

#endif
