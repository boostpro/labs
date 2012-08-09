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

struct ListNode
{
    ListNode(ListNode* prev, ListNode* next, int data)
      : prev(prev)
      , next(next)
      , value(data)
    {}

    ListNode* prev;
    ListNode* next;
    int value;
};

class ListIterator
{
public:
    ListNode* n_;

public:
    typedef int& Reference;
    typedef int ValueType;

    explicit ListIterator(ListNode* current = 0)
      : n_(current)
    {}
};

inline bool operator==(ListIterator i1, ListIterator i2)
{
    return i1.n_ == i2.n_;
}

inline bool operator!=(ListIterator i1, ListIterator i2)
{
    return !(i1 == i2);
}

inline int& Get(ListIterator iter)
{
    return iter.n_->value;
}

inline void Next(ListIterator& iter)
{
    iter.n_ = iter.n_->next;
}

inline Forward Category(ListIterator)
{
    return Forward();
}

class List
{
    ListNode head; // head.value is the size of the list

public:

    // Construct an empty list
    List()
      : head(&head, &head, 0)
    {}

    // Copy a list
    List(List const& that)
      : head(&head, &head, 0)
    {
        for(ListNode* n = that.head.next; n != &that.head; n = n->next)
        {
            PushBack(n->value);
        }
    }

    // Delete a list
    ~List()
    {
        for(ListNode* next; head.next != &head; head.next = next)
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
        ListNode* n = new ListNode(head.prev, head.prev->next, value);
        head.prev = n;
        n->prev->next = n;
        ++head.value; // head.value stores the size of the list
    }

    int PopFront()
    {
        assert(head.next != &head);
        ListNode* p = head.next;
        head.next = p->next;
        p->next->prev = p->prev;
        --head.value; // head.value stores the size of the list
        int value = p->value;
        delete p;
        return value;
    }

    typedef ListIterator Iterator;

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
