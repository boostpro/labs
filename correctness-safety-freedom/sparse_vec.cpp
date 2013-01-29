// Copyright David Abrahams 2008. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#define _GLIBCXX_DEBUG 1

#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>

struct sparse
{
    sparse(std::size_t nrows, std::size_t nstored)
    {
        $writeme$
    }

    sparse(sparse const& rhs)
    {
        $writeme$
    }
    
    friend void swap(sparse& x, sparse& y)
    {
        $writeme$
    }

    sparse& operator=(sparse rhs)
    {
        $writeme$
    }

    ~sparse()
    {
        $writeme$
    }
    
    typedef std::vector<double>::iterator iterator;
    typedef std::vector<std::size_t>::iterator row_start_iterator;
    typedef std::vector<std::size_t>::iterator column_index_iterator;
    
    typedef std::vector<double>::const_iterator const_iterator;
    typedef std::vector<std::size_t>::const_iterator row_start_const_iterator;
    typedef std::vector<std::size_t>::const_iterator column_index_const_iterator;
    
    
    const_iterator begin() const
    {
        return data.begin();
    }
    
    const_iterator end() const
    {
        return data.end();
    }
    
    row_start_const_iterator row_start_begin() const
    {
        return row_start.begin();
    }
    
    row_start_const_iterator row_start_end() const
    {
        return row_start.end();
    }

    column_index_const_iterator column_index_begin() const
    {
        return column_index.begin();
    }
    
    column_index_const_iterator column_index_end() const
    {
        return column_index.end();
    }
    
    iterator begin()
    {
        return data.begin();
    }
    
    iterator end()
    {
        return data.end();
    }
    
    row_start_iterator row_start_begin()
    {
        return row_start.begin();
    }
    
    row_start_iterator row_start_end()
    {
        return row_start.end();
    }

    column_index_iterator column_index_begin()
    {
        return column_index.begin();
    }
    
    column_index_iterator column_index_end()
    {
        return column_index.end();
    }
    
 private:
    std::vector<double> data;
    std::vector<std::size_t> row_start;
    std::vector<std::size_t> column_index;
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
