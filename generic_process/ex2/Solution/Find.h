///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)


#ifndef FIND_H_BOOST_CONSULTING
#define FIND_H_BOOST_CONSULTING

template<typename Iterator, typename Value>
Iterator Find(Iterator begin, Iterator end, Value value)
{
    while(begin != end)
    {
        if(Get(begin) == value)
            return begin;
        Next(begin);
    }
    return end;
}

#endif
