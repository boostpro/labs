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

    int& i = GetAt(array, 10, 5);

    if(5 != i)
        return false;

    int& j = GetAt(array, 10, 9);

    if(9 != j)
        return false;

    j = 42;
    if(array[9] != 42)
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
