// Copyright David Abrahams 2008. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#define _GLIBCXX_DEBUG 1

#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include "boost/scoped_array.hpp"

struct sparse
{
    sparse(std::size_t nrows, std::size_t nstored)
      : data(new double[nstored]),
        row_start(new std::size_t[nrows]),
        column_index(new std::size_t[nstored]),
        nrows(nrows),
        nstored(nstored)
    {
    }

    sparse(sparse const& rhs)
      : data(0), row_start(0), column_index(0), nrows(0), nstored(0)
    {
        sparse tmp(rhs.nrows, rhs.nstored);
        std::copy(rhs.begin(), rhs.end(), tmp.begin());
        std::copy(rhs.row_start_begin(), rhs.row_start_end(), tmp.row_start_begin());
        std::copy(rhs.column_index_begin(), rhs.column_index_end(), tmp.column_index_begin());
        
        swap(*this,tmp);
    }
    
    friend void swap(sparse& x, sparse& y)
    {
        swap(x.row_start,y.row_start);
        swap(x.column_index,y.column_index);
        swap(x.data,y.data);
        std::swap(x.nrows,y.nrows);
        std::swap(x.nstored,y.nstored);
    }

    sparse& operator=(sparse rhs)
    {
        swap(*this,rhs);
		return *this;
    }
    
    typedef double* iterator;
    typedef std::size_t* row_start_iterator;
    typedef std::size_t*  column_index_iterator;
    
    typedef double const* const_iterator;
    typedef std::size_t const* row_start_const_iterator;
    typedef std::size_t const*  column_index_const_iterator;
    
    const_iterator begin() const
    {
        return data.get();
    }
    
    const_iterator end() const
    {
        return data.get() + nstored;
    }
    
    row_start_const_iterator row_start_begin() const
    {
        return row_start.get();
    }
    
    row_start_const_iterator row_start_end() const
    {
        return row_start.get() + nrows;
    }

    column_index_const_iterator column_index_begin() const
    {
        return column_index.get();
    }
    
    column_index_const_iterator column_index_end() const
    {
        return column_index.get() + nstored;
    }
    
    iterator begin()
    {
        return data.get();
    }
    
    iterator end()
    {
        return data.get() + nstored;
    }
    
    row_start_iterator row_start_begin()
    {
        return row_start.get();
    }
    
    row_start_iterator row_start_end()
    {
        return row_start.get() + nrows;
    }

    column_index_iterator column_index_begin()
    {
        return column_index.get();
    }
    
    column_index_iterator column_index_end()
    {
        return column_index.get() + nstored;
    }
    
 private:
    boost::scoped_array<double> data;
    boost::scoped_array<std::size_t> row_start;
    boost::scoped_array<std::size_t> column_index;
    std::size_t nrows;
    std::size_t nstored;
};


int main()
{
    std::size_t const dim = 10;

    // make a lower triangular matrix
    sparse s(dim, dim * (dim + 1)/2);
    
    sparse::iterator p = s.begin();
    sparse::row_start_iterator row_start = s.row_start_begin();
    sparse::column_index_iterator col_index = s.column_index_begin();

    for (std::size_t r = 0; r < dim; ++r)
    {
        *row_start++ = p - s.begin();
        for (std::size_t c = 0; c <= r; ++c)
        {
            *p++ = r * c;
            *col_index++ = c;
        }
    }

    sparse x = s;
    sparse y(s);
    y=x;

    for (sparse::iterator q = s.begin(); q != s.end(); ++q)
    {
        std::cout << &*q << " = " << *q << '\n';
    }
}
