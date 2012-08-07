// Copyright David Abrahams 2007. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef HASHSET_DWA2007816_H
# define HASHSET_DWA2007816_H

#include <cassert>
#include <utility>
#include <cstdlib>
#include "./List.h"
#include "./Iterator.h"

///////////////////////////////////////////////////////////////////////////////
// A representation of a position within a HashMultiSet
class HashMultiSetIterator
{
public:
    List*          bptr; // pointer to bucket
    List*          bend; // pointer to last bucket
    List::Iterator pos;  // position within bucket

public:
    typedef int const& Reference;

    HashMultiSetIterator(List* bptr, List* bend, List::Iterator pos)
      : bptr(bptr)
      , bend(bend)
      , pos(pos)
    {}

    void Satisfy()
    {
        while(pos == bptr->End())
        {
            if(bptr == bend)
                break;
            ++bptr;
            pos = bptr->Begin();
        }
    }
};

inline bool operator==(HashMultiSetIterator i1, HashMultiSetIterator i2)
{
    return i1.bptr == i2.bptr && i1.pos == i2.pos;
}

inline bool operator!=(HashMultiSetIterator i1, HashMultiSetIterator i2)
{
    return !(i1 == i2);
}

inline int const& Get(HashMultiSetIterator iter)
{
    return Get(iter.pos);
}

inline void Next(HashMultiSetIterator& iter)
{
    Next(iter.pos);
    iter.Satisfy();
}

inline Forward Category(HashMultiSetIterator)
{
    return Forward();
}

///////////////////////////////////////////////////////////////////////////////
class HashMultiSetBase
{
public:
    std::size_t len;
    std::size_t bcount;
    List* buckets;

public:
    HashMultiSetBase(std::size_t bcount = 7)
      : len(0)
      , bcount(bcount)
      , buckets(new List[bcount])
    {
    }

    ~HashMultiSetBase()
    {
        delete[] buckets;
    }

    static void swap(std::size_t& l, std::size_t& r)
    {
        std::size_t t = l;
        l = r;
        r = t;
    }

    static void swap(List*& l, List*& r)
    {
        List* t = l;
        l = r;
        r = t;
    }

    void swap(HashMultiSetBase& rhs)
    {
        swap(len, rhs.len);
        swap(bcount, rhs.bcount);
        swap(buckets, rhs.buckets);
    }
};

///////////////////////////////////////////////////////////////////////////////
class HashMultiSet : public HashMultiSetBase
{
    static const std::size_t maxload = 10;
    
public:
    HashMultiSet() {}

    HashMultiSet(HashMultiSet const& rhs, std::size_t bcount = 0)
      : HashMultiSetBase(bcount ? bcount : rhs.bcount)
    {
        for (std::size_t i = 0; i < rhs.bcount; ++i)
        {
            List& bucket = rhs.buckets[i];
            List::Iterator cur = bucket.Begin();
            List::Iterator end = bucket.End();
            for (; cur != end; Next(cur))
            {
                Insert(Get(cur));
            }
        }
    }

    HashMultiSet& operator=(HashMultiSet rhs)
    {
        rhs.swap(*this);
        return *this;
    }

    // Add an element to the hash table
    void Insert(int value)
    {
        if (len / bcount >= maxload)
        {
            HashMultiSet tmp(*this, bcount * 2);
            swap(tmp);
        }

        std::size_t i = value % bcount;
        buckets[i].PushBack(value);
        ++len;
    }

    typedef HashMultiSetIterator Iterator;

    Iterator Begin()
    {
        Iterator it(buckets, buckets + bcount - 1, buckets[0].Begin());
        it.Satisfy(); // move to the first non-empty position.
        return it;
    }

    Iterator End()
    {
        List* slast = buckets + bcount - 1;
        return Iterator(slast, slast, slast->End());
    }

    // Here's the container-based version of Transform
    // for comparison purposes.
    int* Transform(int (*pfun)(int), int* out) const
    {
        List* begin = buckets, * end = buckets + bcount;
        for (; begin != end; ++begin)
        {
            out = begin->Transform(pfun, out);
        }
        return out;
    }
};

#endif // HASHSET_DWA2007816_H
