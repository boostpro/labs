///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

#include "./Array.h"
#include "./Deque.h"
#include "./List.h"
#include "./HashMultiSet.h"

#include <algorithm>

#include "./Transform.h"

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

namespace TransformTest
{
    /////////////////////////////////////////////////////////////////////
    bool TestArray2()
    {
        int array[] = { 0,1,2,3,4,5,6,7,8,9 };

        int result[10] = {0};
        int* i = Transform(array, array + 10, Square, result);
        if(i != result + 10)
            return false;

        if(!CheckResult(result))
            return false;

        return true;
    }

    /////////////////////////////////////////////////////////////////////
    bool TestDeque2()
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
        int* i = Transform(d.Begin(), d.End(), Square, result);
        if(i != result + 10)
            return false;

        if(!CheckResult(result))
            return false;

        return true;
    }

    /////////////////////////////////////////////////////////////////////
    bool TestList2()
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
        int* i = Transform(l.Begin(), l.End(), Square, result);
        if(i != result + 10)
            return false;

        if(!CheckResult(result))
            return false;

        return true;
    }

    /////////////////////////////////////////////////////////////////////
    bool TestHashMultiSet2()
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
        int* i = Transform(d.Begin(), d.End(), Square, result);
        if(i != result + 10)
            return false;
        std::sort(result, i);
        if(!CheckResult(result))
            return false;

        return true;
    }
}

bool TestTransform()
{
    using namespace TransformTest;

    if(!TestArray2())
        return false;

    if(!TestDeque2())
        return false;

    if(!TestList2())
        return false;

    if (!TestHashMultiSet2())
        return false;
    
    return true;
}
