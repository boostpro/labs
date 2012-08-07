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

    // For each element E in the sequence, call
    // (*pfun)(E), assign the result to *out,
    // and increment out. When done, return the
    // final value of out.
    int* Transform(int (*pfun)(int), int* out) const
    {
        // TODO implement me
    }

    // Others will be working on these.
    // Feel free to give them a crack, too,
    // if you're feeling ambitious.
    int* Find(int value);
    int& GetAt(int i);
};

#endif
