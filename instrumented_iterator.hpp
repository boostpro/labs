// Copyright David Abrahams 2008. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef INSTRUMENTED_ITERATOR_DWA2008522_HPP
# define INSTRUMENTED_ITERATOR_DWA2008522_HPP

# include "boost/iterator/iterator_adaptor.hpp"

template <class Base>
struct instrumented_iterator
  : boost::iterator_adaptor<
        instrumented_iterator<Base>, Base
    >
{
 private:
    typedef instrumented_iterator self;
    
 public:
    static unsigned long movements;
    static unsigned long comparisons;
    static unsigned long dereferences;

    instrumented_iterator(Base b) : self::iterator_adaptor_(b) {}
    instrumented_iterator() {}
    
 private:
    friend class boost::iterator_core_access;
    void advance(typename self::difference_type n)
    {
        this->base_reference() += n;
        ++movements;
    }

    typename self::reference
    dereference() const
    {
        ++dereferences;
        return *this->base();
    }

    void increment()
    {
        ++this->base_reference();
        ++movements;
    }

    void decrement()
    {
        --this->base_reference();
        ++movements;
    }

    template <class T>
    bool equal(T const& other) const
    {
        ++comparisons;
        return this->base() == other.base();
    }
        
    template <class T>
    typename self::difference_type
    distance_to(T const& other) const
    {
        ++comparisons;
        return other.base() - this->base();
    }
};

template <class Base>
unsigned long instrumented_iterator<Base>::movements = 0;

template <class Base>
unsigned long instrumented_iterator<Base>::comparisons = 0;

template <class Base>
unsigned long instrumented_iterator<Base>::dereferences = 0;

#endif // INSTRUMENTED_ITERATOR_DWA2008522_HPP
