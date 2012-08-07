// Copyright David Abrahams 2007. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef HASHSET_DWA2007816_H
#define HASHSET_DWA2007816_H

#include <cassert>
#include <utility>
#include <cstdlib>
#include "./List.h"

// A hash is an array of lists, called "buckets"

class HashMultiSetBase
{
protected:
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

class HashMultiSet : HashMultiSetBase
{
    static const std::size_t maxload = 10;

public:
    HashMultiSet()
      : HashMultiSetBase()
    {
    }

    HashMultiSet(HashMultiSet const& rhs, std::size_t bcount = 0)
      : HashMultiSetBase(bcount ? bcount : rhs.bcount)
    {
        for (std::size_t i = 0; i < rhs.bcount; ++i)
        {
            List tmp(rhs.buckets[i]);
            while(!tmp.Empty())
            {
                Insert(tmp.PopFront());
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

    int* Transform(int (*pfun)(int), int* out) const
    {
        List* begin = buckets, * end = buckets + bcount;
        for (; begin != end; ++begin)
        {
            out = begin->Transform(pfun, out);
        }
        return out;
    }

    int const& GetAt(int i)
    {
        assert(i >= 0 && (std::size_t)i < len);

        for (std::size_t n = 0; ; ++n)
        {
            assert(n < bcount);
            int size = buckets[n].Size();
            if(i < size)
                return buckets[n].GetAt(i);
            else
                i -= size;
        }
    }

    int* Find(int value)
    {
        #if 0 // linear search
        for (int n = 0; n < bcount; ++n)
        #else // O(1)
        std::size_t n = value % bcount;
        #endif
        {
            int* pos = buckets[n].Find(value);
            if(pos)
            {
                return pos;
            }
        }
        return 0;
    }
};

#endif // HASHSET_DWA2007816_H
