///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
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

    int result[10] = {0};
    int* i = d.Transform(Square, result);
    if(i != result + 10)
        return false;

    if(!CheckResult(result))
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
