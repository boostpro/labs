///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef DEQUE_H_BOOST_CONSULTING
#define DEQUE_H_BOOST_CONSULTING

#include <cassert>
#include <utility>

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
      : segments(new DequeSegment*[0])
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

    int& GetAt(int i)
    {
        // TODO implement me
    }

    // Others will be working on these.
    // Feel free to give them a crack, too,
    // if you're feeling ambitious.
    int* Find(int value);
    int* Transform(int (*pfun)(int), int* out) const;
};

#endif
