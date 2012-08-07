///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIST2_H_BOOST_CONSULTING
#define LIST2_H_BOOST_CONSULTING

#include <climits>
#include <utility>
#include "./Iterator.h"

class List
{
    struct Node
    {
        Node(Node* prev, Node* next, int data)
          : prev(prev)
          , next(next)
          , value(data)
        {}

        Node* prev;
        Node* next;
        int value;
    };

    Node head; // head.value is the size of the list

public:

    // Construct an empty list
    List()
      : head(&head, &head, 0)
    {}

    // Copy a list
    List(List const& that)
      : head(&head, &head, 0)
    {
        for(Node* n = that.head.next; n != &that.head; n = n->next)
        {
            PushBack(n->value);
        }
    }

    // Delete a list
    ~List()
    {
        for(Node* next; head.next != &head; head.next = next)
        {
            next = head.next->next;
            delete head.next;
        }
    }

    bool Empty()
    {
        return head.next == &head;
    }

    int Size()
    {
        return head.value;
    }

    void PushBack(int value)
    {
        Node* n = new Node(head.prev, head.prev->next, value);
        head.prev = n;
        n->prev->next = n;
        ++head.value; // head.value stores the size of the list
    }

    int PopFront()
    {
        assert(head.next != &head);
        Node* p = head.next;
        head.next = p->next;
        p->next->prev = p->prev;
        --head.value; // head.value stores the size of the list
        int value = p->value;
        delete p;
        return value;
    }

    class Iterator
    {
        friend class List;
        Node* n_;

    public:
        typedef int& Reference;

        explicit Iterator(Node* current = 0)
          : n_(current)
        {}

        friend int& Get(Iterator iter)
        {
            return iter.n_->value;
        }

        friend void Next(Iterator& iter)
        {
            iter.n_ = iter.n_->next;
        }

        friend bool operator==(Iterator i1, Iterator i2)
        {
            return i1.n_ == i2.n_;
        }

        friend bool operator!=(Iterator i1, Iterator i2)
        {
            return !(i1 == i2);
        }

        friend Forward Category(Iterator)
        {
            return Forward();
        }
    };

    Iterator Begin()
    {
        return Iterator(head.next);
    }

    Iterator End()
    {
        return Iterator(&head);
    }

    // Remove the value at a position
    void Erase(Iterator pos)
    {
        assert(pos != End());
        pos.n_->prev->next = pos.n_->next;
        pos.n_->next->prev = pos.n_->prev;
        --head.value; // head.value is the size of the list
        delete pos.n_;
    }
};

#endif
