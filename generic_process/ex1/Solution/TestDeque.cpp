///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)


#include "./Deque.h"

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

namespace DequeTest
{
    /////////////////////////////////////////////////////////////////////
    bool TestFind()
    {
        Deque d;
        d.PushBack(-1);
        d.PushBack(0);
        d.PushBack(1);
        d.PushBack(2);
        d.PushBack(3);
        d.PushBack(4);
        d.PushBack(5);
        d.PushBack(6);
        d.PushBack(7);
        d.PushBack(8);
        d.PushBack(9);
        d.PopFront();

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
        Deque d;
        d.PushBack(-1);
        d.PushBack(0);
        d.PushBack(1);
        d.PushBack(2);
        d.PushBack(3);
        d.PushBack(4);
        d.PushBack(5);
        d.PushBack(6);
        d.PushBack(7);
        d.PushBack(8);
        d.PushBack(9);
        d.PopFront();

        int&i = d.GetAt(4);

        if(4 != i)
            return false;

        int& j = d.GetAt(8);

        if(8 != j)
            return false;

        int& k = d.GetAt(9);

        if(9 != k)
            return false;

        k = 42;
        if(42 != d.GetAt(9))
            return false;

        return true;
    }

    /////////////////////////////////////////////////////////////////////
    bool TestTransform()
    {
        Deque d;
        d.PushBack(-1);
        d.PushBack(0);
        d.PushBack(1);
        d.PushBack(2);
        d.PushBack(3);
        d.PushBack(4);
        d.PushBack(5);
        d.PushBack(6);
        d.PushBack(7);
        d.PushBack(8);
        d.PushBack(9);
        d.PopFront();

        int result[10] = {0};
        int* i = d.Transform(Square, result);
        if(i != result + 10)
            return false;

        if(!CheckResult(result))
            return false;

        return true;
    }
}

bool TestDeque()
{
    using namespace DequeTest;

    if(!TestFind())
        return false;

    if(!TestGetAt())
        return false;

    if(!TestTransform())
        return false;

    return true;
}
