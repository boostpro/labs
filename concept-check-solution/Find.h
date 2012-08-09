///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)


#ifndef FIND_H_BOOST_CONSULTING
#define FIND_H_BOOST_CONSULTING

#include "./Iterator.h"

template<typename Iterator>
BOOST_CONCEPT_REQUIRES(
    ((ForwardIterator<Iterator>))
/*    ((Convertible<Value, typename ForwardIterator<Iterator>::value_type>)) */
    ((EqualityComparable<typename ForwardIterator<Iterator>::value_type>)),

    // Archetype revealed need for Value copyability
    // Then it revealed the need for Iterator::value_type == Value (convertibility isn't enough)
    // So we decided to change the function argument
    //
    // Furthermore, 
    
(Iterator)) Find(Iterator begin, Iterator end, typename ForwardIterator<Iterator>::value_type const& value)
{
    while(begin != end)
    {
        typename ForwardIterator<Iterator>::value_type const& v = Get(begin);
        if(v == value)
            return begin;
        Next(begin);
    }
    return end;
}

inline void check_Find()
{
    typedef ForwardIteratorArchetype<
        boost::equality_comparable_archetype<> > Iterator;

    Iterator x;
    x = Find(x, x, detail::get<boost::equality_comparable_archetype<> >());
}
#endif
