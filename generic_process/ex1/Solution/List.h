///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIST_H_BOOST_CONSULTING
#define LIST_H_BOOST_CONSULTING

#include <climits>
#include <utility>
#include <cassert>

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

class List
{
    // head.value stores the size of the list.
    ListNode head;

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

    // Add a value to the end of the list
    void PushBack(int value)
    {
        ListNode* n = new ListNode(head.prev, head.prev->next, value);
        head.prev = n;
        n->prev->next = n;
        ++head.value; // head.value stores the size of the list
    }

    // Remove a value from the front of the list
    int PopFront()
    {
        assert(!Empty());
        ListNode* p = head.next;
        head.next = p->next;
        p->next->prev = p->prev;
        --head.value; // head.value stores the size of the list
        int value = p->value;
        delete p;
        return value;
    }

    int* Transform(int (*pfun)(int), int* out) const
    {
        for(ListNode* n = head.next; n != &head; n = n->next)
        {
            *out++ = pfun(n->value);
        }
        return out;
    }

    // Return the Nth value
    int& GetAt(int i)
    {
        for(ListNode* n = head.next; ; n = n->next, --i)
        {
            assert(n != &head);
            if(0 == i)
                return n->value;
        }
    }

    // Find a value in the list, return the position.
    int* Find(int value)
    {
        for(ListNode* n = head.next; n != &head; n = n->next)
        {
            if(value == n->value)
                return &n->value;
        }
        return 0;
    }
};

#endif
