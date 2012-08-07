///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler, David Abrahams.
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "./Deque.h"
#include "./HashMultiSet.h"
#include "./DequeTransform.h"
#include "./HashTransform.h"
#include "./Transform.h"

int Max = 100000;   // The number of elements in the container
int Loops = 10000;  // The number of times to execute the algorithm in a loop

int Square(int i)   // A function to use in the call to Transform()
{
    return i * i;
}

// A function template for timing the execution
// of a function object.
template<typename Function>
double TimeIt(Function const & fun)
{
    // Do it once outside the loop
    fun();

    // Time how long it takes to execute 
    std::clock_t start = std::clock();

    for(int i=0; i < Loops; ++i)
    {
        fun();
    }

    std::clock_t stop = std::clock();

    return (stop - start) / (float)CLOCKS_PER_SEC;
}

// This spoiler is needed to foil optimizers
// that might remove the call to Transform()
// entirely if the result is not used, which
// would result in a erroneous performance
// test.
void CheckResult(int* result)
{
    if(*(result-1) == 3) // should never be true
    {
        std::printf("ERROR\n");
        std::exit(1);
    }
}

// Function object for invoking the Deque::Transform() member function
struct TimeDequeTransformMember
{
    Deque & deque;
    int (*pfun)(int);
    int *out;

    TimeDequeTransformMember(Deque & deque_, int (*pfun_)(int), int *out_)
      : deque(deque_), pfun(pfun_), out(out_) 
    {}

    void operator()() const
    {
        int * result = deque.Transform(pfun, out);
        CheckResult(result);
    }
};

// Function object for invoking the Transform() algorithm
struct TimeDequeTransformAlgorithm
{
    Deque & deque;
    int (*pfun)(int);
    int *out;

    TimeDequeTransformAlgorithm(Deque & deque_, int (*pfun_)(int), int *out_)
      : deque(deque_), pfun(pfun_), out(out_) 
    {}

    void operator()() const
    {
        int * result = Transform(deque.Begin(), deque.End(), pfun, out);
        CheckResult(result);
    }
};

// Function object for invoking the DequeTransform() algorithm
struct TimeDequeTransformSegmented
{
    Deque & deque;
    int (*pfun)(int);
    int *out;

    TimeDequeTransformSegmented(Deque & deque_, int (*pfun_)(int), int *out_)
      : deque(deque_), pfun(pfun_), out(out_) 
    {}

    void operator()() const
    {
        int * result = DequeTransform(deque.Begin(), deque.End(), pfun, out);
        CheckResult(result);
    }
};

// Function object for invoking the HashMultiSet::Transform() member function
struct TimeHashMultiSetTransformMember
{
    HashMultiSet & hash;
    int (*pfun)(int);
    int *out;

    TimeHashMultiSetTransformMember(HashMultiSet & hash_, int (*pfun_)(int), int *out_)
      : hash(hash_), pfun(pfun_), out(out_) 
    {}

    void operator()() const
    {
        int * result = hash.Transform(pfun, out);
        CheckResult(result);
    }
};

// Function object for invoking the Transform() algorithm
struct TimeHashMultiSetTransformAlgorithm
{
    HashMultiSet & hash;
    int (*pfun)(int);
    int *out;

    TimeHashMultiSetTransformAlgorithm(HashMultiSet & hash_, int (*pfun_)(int), int *out_)
      : hash(hash_), pfun(pfun_), out(out_) 
    {}

    void operator()() const
    {
        int * result = Transform(hash.Begin(), hash.End(), pfun, out);
        CheckResult(result);
    }
};

// Function object for invoking the HashTransform() algorithm
struct TimeHashMultiSetTransformSegmented
{
    HashMultiSet & hash;
    int (*pfun)(int);
    int *out;

    TimeHashMultiSetTransformSegmented(HashMultiSet & hash_, int (*pfun_)(int), int *out_)
      : hash(hash_), pfun(pfun_), out(out_) 
    {}

    void operator()() const
    {
        int * result = HashTransform(hash.Begin(), hash.End(), pfun, out);
        CheckResult(result);
    }
};

int main()
{
    Deque deque;
    HashMultiSet hash;

    // Load up a Deque and a Hash with a bunch of data
    for(int i=0; i < Max; ++i)
    {
        deque.PushBack(i);
        hash.Insert(i);
    }

    // Allocate some space for the result of the transform
    int* out = new int[Max];

    // Time each of the different algorithms for Deque

    std::printf("Deque::Transform(fun, out)                     : %f seconds\n", 
        TimeIt(TimeDequeTransformMember(deque, Square, out)));

    std::printf("Transform(begin, end, fun, out)                : %f seconds\n", 
        TimeIt(TimeDequeTransformAlgorithm(deque, Square, out)));

    std::printf("Transform(begin, end, fun, out) <segmented>    : %f seconds\n", 
        TimeIt(TimeDequeTransformSegmented(deque, Square, out)));

    // Time each of the different algorithms for HashMultiSet

    std::printf("HashMultiSet::Transform(fun, out)              : %f seconds\n", 
        TimeIt(TimeHashMultiSetTransformMember(hash, Square, out)));

    std::printf("Transform(begin, end, fun, out)                : %f seconds\n", 
        TimeIt(TimeHashMultiSetTransformAlgorithm(hash, Square, out)));

    std::printf("Transform(begin, end, fun, out) <segmented>    : %f seconds\n", 
        TimeIt(TimeHashMultiSetTransformSegmented(hash, Square, out)));

    // clean-up
    delete[] out;
    return 0;
}
