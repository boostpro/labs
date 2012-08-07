///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>

#include "./Array.h"
#include "./Deque.h"
#include "./List.h"

#include "./GetAt.h"

namespace GetAtTest
{
    /////////////////////////////////////////////////////////////////////
    bool TestArray()
    {
        int array[] = { 0,1,2,3,4,5,6,7,8,9 };

        int& i = GetAt(array, 5);

        if(5 != i)
            return false;

        int& j = GetAt(array, 9);

        if(9 != j)
            return false;

        j = 42;
        if(array[9] != 42)
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

        int&i = GetAt(d.Begin(), 4);

        if(4 != i)
            return false;

        int& j = GetAt(d.Begin(), 8);

        if(8 != j)
            return false;

        int& k = GetAt(d.Begin(), 9);

        if(9 != k)
            return false;

        k = 42;
        if(42 != GetAt(d.Begin(), 9))
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

        int& i = GetAt(l.Begin(), 5);

        if(5 != i)
            return false;

        int&j = GetAt(l.Begin(), 9);

        if(9 != j)
            return false;

        j = 42;
        if(42 != GetAt(l.Begin(), 9))
            return false;

        return true;
    }
  
}

bool TestGetAt()
{
    using namespace GetAtTest;

    if(!TestArray())
        return false;

    if(!TestDeque2())
        return false;

    if(!TestList2())
        return false;

    return true;
}

int main()
{
    if(! TestGetAt())
    {
        std::cerr << "Test failed" << std::endl;
        return 1;
    }

    std::cout << "Test passed" << std::endl;
    return 0;
}
