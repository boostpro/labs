///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include "./Array.h"

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
    int array[] = { 0,1,2,3,4,5,6,7,8,9 };

    int result[10] = {0};
    int* i = Transform(array, 10, Square, result);
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
