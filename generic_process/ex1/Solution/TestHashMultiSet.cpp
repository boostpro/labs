///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)


#include "./HashMultiSet.h"

#include <algorithm>

static int Square(int i)
{
    return i * i;
}

static bool CheckResult(int* result)
{
    for(int i=0; i < 10; ++i)
        if(result[i] != Square(i))
            return false;
    return true;
}

namespace HashMultiSetTest
{
    /////////////////////////////////////////////////////////////////////
    bool TestFind()
    {
        HashMultiSet d;
        d.Insert(0);
        d.Insert(1);
        d.Insert(2);
        d.Insert(3);
        d.Insert(4);
        d.Insert(5);
        d.Insert(6);
        d.Insert(7);
        d.Insert(8);
        d.Insert(9);

        int* pos = d.Find(5);
        if(!pos)
            return false;

        if(5 != *pos)
            return false;

        pos = d.Find(-1);
        if(pos)
            return false;

        return true;
    }

    /////////////////////////////////////////////////////////////////////
    bool TestGetAt()
    {
        HashMultiSet d;
        d.Insert(0);
        d.Insert(1);
        d.Insert(2);
        d.Insert(3);
        d.Insert(4);
        d.Insert(5);
        d.Insert(6);
        d.Insert(7);
        d.Insert(8);
        d.Insert(9);

        bool found[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        for (int i = 0; i < 10; ++i)
        {
            found[d.GetAt(i)] = true;
        }

        for (int i = 0; i < 10; ++i)
        {
            if (!found[i])
                return false;
        }
        
        return true;
    }

    /////////////////////////////////////////////////////////////////////
    bool TestTransform()
    {
        HashMultiSet d;
        d.Insert(0);
        d.Insert(1);
        d.Insert(2);
        d.Insert(3);
        d.Insert(4);
        d.Insert(5);
        d.Insert(6);
        d.Insert(7);
        d.Insert(8);
        d.Insert(9);

        int result[10] = {0};
        int index[10] = {0};
        int* i = d.Transform(Square, result);
        if(i != result + 10)
            return false;
        std::sort(result, i);
        if(!CheckResult(result))
            return false;

        return true;
    }
}

bool TestHashMultiSet()
{
    using namespace HashMultiSetTest;

    if(!TestFind())
        return false;

    if(!TestGetAt())
        return false;

    if(!TestTransform())
        return false;

    return true;
}
