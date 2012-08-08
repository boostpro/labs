// Copyright David Abrahams 2008. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include "instrumented_iterator.hpp"
#include "boost/iterator/counting_iterator.hpp"
#include "boost/iterator/reverse_iterator.hpp"
#include <algorithm>
#include <vector>
#include <list>
#include <cassert>
#include <iostream>

// Reverse a sequence in-place
//
// Requires: BidirectionalIterator models bidirectional iterator
//
// Complexity: when BidirectionalIterator models random access
//             iterator, at most (finish - start + 1)/2 comparisons.
//             Otherwise, at most finish - start + 1 comparisons.
template <class BidirectionalIterator>
void reverse(BidirectionalIterator start, BidirectionalIterator finish)
{
    $implement me$
}

template <class Container>
void test_reverse(std::size_t size, char const* type_name)
{
    Container seq(
        boost::make_counting_iterator(size),
        boost::make_counting_iterator(size*2));
    
    typedef instrumented_iterator<typename Container::iterator> iterator;
    
    ::reverse( iterator(seq.begin()), iterator(seq.end()) );
    assert(
        std::equal(
            seq.begin(), seq.end(),
                boost::make_reverse_iterator(boost::make_counting_iterator(size*2))
        ));
        
    std::cout << "reversing a " << type_name << " of size " << size
              << " took " << iterator::comparisons << " comparisons." << std::endl;
    
    iterator::comparisons = 0;
}

int main()
{
    for (int size = 0; size <= 100; size ? ++size : (size = 99))
    {
        test_reverse<std::vector<int> >(size, "vector");
        test_reverse<std::list<int> >(size, "list");
    }
}
