///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)


#include "./List.h"

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

namespace ListTest
{
    /////////////////////////////////////////////////////////////////////
    bool TestFind()
    {
        List l;
        l.PushBack(-1);
        l.PushBack(0);
        l.PushBack(1);
        l.PushBack(2);
        l.PushBack(3);
        l.PushBack(4);
        l.PushBack(5);
        l.PushBack(6);
        l.PushBack(7);
        l.PushBack(8);
        l.PushBack(9);
        l.PopFront();

        int* pos = l.Find(5);
        if(!pos)
            return false;

        if(5 != *pos)
            return false;

        pos = l.Find(-1);
        if(pos)
            return false;

        return true;
    }

    /////////////////////////////////////////////////////////////////////
    bool TestGetAt()
    {
        List l;
        l.PushBack(-1);
        l.PushBack(0);
        l.PushBack(1);
        l.PushBack(2);
        l.PushBack(3);
        l.PushBack(4);
        l.PushBack(5);
        l.PushBack(6);
        l.PushBack(7);
        l.PushBack(8);
        l.PushBack(9);
        l.PopFront();

        int& i = l.GetAt(5);

        if(5 != i)
            return false;

        int&j = l.GetAt(9);

        if(9 != j)
            return false;

        j = 42;
        if(42 != l.GetAt(9))
            return false;

        return true;
    }

    /////////////////////////////////////////////////////////////////////
    bool TestTransform()
    {
        List l;
        l.PushBack(-1);
        l.PushBack(0);
        l.PushBack(1);
        l.PushBack(2);
        l.PushBack(3);
        l.PushBack(4);
        l.PushBack(5);
        l.PushBack(6);
        l.PushBack(7);
        l.PushBack(8);
        l.PushBack(9);
        l.PopFront();

        int result[10] = {0};
        int* i = l.Transform(Square, result);
        if(i != result + 10)
            return false;

        if(!CheckResult(result))
            return false;

        return true;
    }
}

bool TestList()
{
    using namespace ListTest;

    if(!TestFind())
        return false;

    if(!TestGetAt())
        return false;

    if(!TestTransform())
        return false;

    return true;
}
