///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include "./Array.h"

/////////////////////////////////////////////////////////////////////
bool Test()
{
    int array[] = { 0,1,2,3,4,5,6,7,8,9 };

    int* p = Find(array, 10, 5);
    if(p != array + 5)
        return false;

    if(5 != *p)
        return false;

    p = Find(array, 10, -1);
    if(p != array + 10)
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
