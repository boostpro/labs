///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <cstdlib>

bool TestArray();
bool TestDeque();
bool TestList();
bool TestHashMultiSet();

int main()
{
    if(! TestArray())
    {
        std::cout << "TestArray failed" << std::endl;
        std::exit(1);
    }

    if(! TestDeque())
    {
        std::cout << "TestDeque failed" << std::endl;
        std::exit(1);
    }

    if(! TestList())
    {
        std::cout << "TestList failed" << std::endl;
        std::exit(1);
    }

    if(! TestHashMultiSet())
    {
        std::cout << "TestHashMultiSet failed" << std::endl;
        std::exit(1);
    }

    std::cout << "Test passed" << std::endl;
    return 0;
}

