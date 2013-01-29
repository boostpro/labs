// Copyright David Abrahams 2008. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#define _GLIBCXX_DEBUG 1

#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cassert>

struct sparse
{
    sparse(std::size_t nrows, std::size_t nstored)
      : data(new double[nstored]), row_start(0), column_index(0), nrows(nrows), nstored(nstored)
    {
        try
        {
            this->row_start = new std::size_t[nrows];
            this->column_index = new std::size_t[nstored];
        }
        catch(...)
        {
            delete[] this->data;
            delete[] this->row_start;
            throw;
        }
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
        std::swap(x.row_start,y.row_start);
        std::swap(x.column_index,y.column_index);
        std::swap(x.data,y.data);
        std::swap(x.nrows,y.nrows);
        std::swap(x.nstored,y.nstored);
    }

    sparse& operator=(sparse rhs)
    {
        swap(*this,rhs);
        return *this;
    }
    
    ~sparse()
    {
        delete[] this->data;
        delete[] this->row_start;
        delete[] this->column_index;
    }

    typedef double* iterator;
    typedef std::size_t* row_start_iterator;
    typedef std::size_t*  column_index_iterator;
    
    typedef double const* const_iterator;
    typedef std::size_t const* row_start_const_iterator;
    typedef std::size_t const*  column_index_const_iterator;
    
    const_iterator begin() const
    {
        return data;
    }
    
    const_iterator end() const
    {
        return data + nstored;
    }
    
    row_start_const_iterator row_start_begin() const
    {
        return row_start;
    }
    
    row_start_const_iterator row_start_end() const
    {
        return row_start + nrows;
    }

    column_index_const_iterator column_index_begin() const
    {
        return column_index;
    }
    
    column_index_const_iterator column_index_end() const
    {
        return column_index + nstored;
    }
    
    iterator begin()
    {
        return data;
    }
    
    iterator end()
    {
        return data + nstored;
    }
    
    row_start_iterator row_start_begin()
    {
        return row_start;
    }
    
    row_start_iterator row_start_end()
    {
        return row_start + nrows;
    }

    column_index_iterator column_index_begin()
    {
        return column_index;
    }
    
    column_index_iterator column_index_end()
    {
        return column_index + nstored;
    }
    
 private:
    double* data;
    std::size_t* row_start;
    std::size_t* column_index;
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
