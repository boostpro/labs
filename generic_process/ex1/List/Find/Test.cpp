///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include "./List.h"

/////////////////////////////////////////////////////////////////////
bool Test()
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
