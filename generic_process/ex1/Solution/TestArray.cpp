///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)


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

namespace ArrayTest
{
    /////////////////////////////////////////////////////////////////////
    bool TestFind()
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

    /////////////////////////////////////////////////////////////////////
    bool TestGetAt()
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

    /////////////////////////////////////////////////////////////////////
    bool TestTransform()
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
}

bool TestArray()
{
    using namespace ArrayTest;

    if(!TestFind())
        return false;

    if(!TestGetAt())
        return false;

    if(!TestTransform())
        return false;

    return true;
}
