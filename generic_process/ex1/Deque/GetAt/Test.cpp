///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include "./Deque.h"

/////////////////////////////////////////////////////////////////////
bool Test()
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

int main()
{
    if(! Test())
    {
        std::cerr << "Test failed" << std::endl;
        return 1;
    }

    std::cout << "Test passed" << std::endl;
    return 0;
}
