.. Copyright David Abrahams 2007. Distributed under the Boost
.. Software License, Version 1.0. (See accompanying
.. file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


Iterator const: X a, b
Iterator: X d
Iterator's value type: Y y
Value: Z v

+------------------------------+------------------------------+------------------------------+------------------------------+
|Valid Expression              |Complexity                    |Preconditions                 |Semantics/Postcondition       |
+==============================+==============================+==============================+==============================+
|X c(a)                        |O(1)                          |                              |Equal(a,c) == true            |
|                              |                              |                              |                              |
|X c = a                       |                              |                              |                              |
+------------------------------+------------------------------+------------------------------+------------------------------+
|Equal(a,b)                    |"                             |a and b are members of the    |Equal(a,b) <=> Equal(b,a)     |
|                              |                              |same sequence                 |(symmetric)                   |
|                              |                              |                              |                              |
|                              |                              |                              |Equal(a,a) == true (reflexive)|
|                              |                              |                              |                              |
|                              |                              |                              |Equal(a,b) && Equal(b,c) =>   |
|                              |                              |                              |Equal(a,c) (transitive)       |
+------------------------------+------------------------------+------------------------------+------------------------------+
|Next(d)                       |"                             |d is not past-the-end         |X c(a); Next(a); =>           |
|                              |                              |                              |!Equal(a,c)                   |
+------------------------------+------------------------------+------------------------------+------------------------------+
|Get(a)                        |"                             |a is not past-the-end         |                              |
+------------------------------+------------------------------+------------------------------+------------------------------+
|y == v                        |"                             |                              |y == v <=> v == y             |
+------------------------------+------------------------------+------------------------------+------------------------------+

Notes: 

* The appearance of Equal and == call for clustering an
  EqualityComparable (or regular) concept.

* It's not yet clear what to do with y == v.  Hah, see the
  discussion below.

  This is a really good opportunity for discussion in class.
  Should one milk the code of the algorithm for all the flexibility
  it can offer? "Don't give away the store."
                 

(12:10:25 PM) Dave Abrahams: yo.  I'm just looking at the requirements for find()
(12:10:44 PM) Dave Abrahams: Are there any semantic constraints on EqualityComparable<T,U>?
(12:11:20 PM) Dave Abrahams: (I'm guessing Alex would hate that)
(12:11:27 PM) Doug Gregor: Alex does hate that
(12:11:54 PM) Doug Gregor: Because, basically, you can't write any semantics for EqualityComparable<T, U>... it's totally asymmetric
(12:12:16 PM) Dave Abrahams: Taken by itself it is, anyway.
(12:12:47 PM) Dave Abrahams: you could require EqualityComparable<U,T> to be equivalent, but it's a breaking change.
(12:13:04 PM) Doug Gregor: Then you get some of the semantics, yes
(12:13:18 PM) Dave Abrahams: But you still need to tie it to copying somehow
(12:13:26 PM) Dave Abrahams: if you want to "get regular"
(12:13:29 PM) Doug Gregor: Yes, and you want reflexivity
(12:13:46 PM) Dave Abrahams: Yes, and you can't have that unless T==U
(12:13:56 PM) Doug Gregor: right
(12:14:12 PM) Dave Abrahams: quel mess.
(12:15:25 PM) Doug Gregor: Ja. I do find it interesting that, to express the semantics of operations like find() properly, you have to limit the applicability of the algorithm
(12:15:39 PM) Dave Abrahams: I think if EC<T,U> implied EC<T> and EC<U>, it might be possible to build a sensible semantic framework.
(12:16:18 PM) Doug Gregor: And also implemented EC<U, T>? Equivalence relations need to be commutative, too
(12:16:21 PM) Dave Abrahams: Why is that interesting?  I find it entirely expected that in order to express sensible semantics, one has to impose preconditions.
(12:16:35 PM) Dave Abrahams: Yes of course.
(12:18:19 PM) Doug Gregor: "Interesting" is probably the wrong word... maybe "unfortunate" is better. It makes sense that one needs more preconditions to express semantics, but it creates this tension between "doing it right" and making it more widely applicable
(12:18:58 PM) Dave Abrahams: How can it "be applicable" if it doesn't have sensible semantics? ;-)
(12:19:29 PM) Doug Gregor: If the damn thing works, it's applicable :)
(12:19:46 PM) Dave Abrahams: For some non-definition of "works"?
(12:19:47 PM) Dave Abrahams: :)
(12:19:49 PM) Doug Gregor: Alex and I had this argument a few years ago about concepts. It wasn't the first nor the last time
(12:20:04 PM) Doug Gregor: My definition: nobody complained to me about it
(12:20:20 PM) Dave Abrahams: hehehehe.  I like you, kid.
(12:20:29 PM) Dave Abrahams: (chomps cigar)
(12:21:26 PM) Dave Abrahams: I think it's an accident that the type of the value to find is unconstrained actually.
(12:21:48 PM) Doug Gregor: Yes, it was
(12:21:49 PM) Dave Abrahams: If you think about lifting from concrete algorithms, it would have happened because there were no iterator_traits.
(12:22:15 PM) Dave Abrahams: Very interesting.
(12:22:35 PM) Doug Gregor: I asked Alex about advance(), and why it has the Distance parameter when difference_type is obviously correct
(12:22:41 PM) Dave Abrahams: This will make a very cool discussion in our illicit course.
(12:22:46 PM) Dave Abrahams: Oh, and?
(12:22:59 PM) Doug Gregor: He said, basically, the compilers couldn't handle iterator_traits in the signature, so he had to make it a template parameter
(12:23:15 PM) Dave Abrahams: Kaboom
(12:23:34 PM) Doug Gregor: I didn't ask about find() specifically, but I'm certain it's the same issue
(12:23:40 PM) Dave Abrahams: yep


From http://www.stepanovpapers.com/siekforeword.html

"Note that this merge is not as powerful as the STL merge. It cannot merge a list of floats
and a vector of doubles into a deque of ints. STL algorithms will often do unexpected and, 
in my opinion, undesirable type conversions. If someone needs to merge doubles and floats 
into ints, he or she should use an explicit function object for asymmetric comparison and 
a special output iterator for conversion." -- Alex Stepanov, Sep. 2001

Here's a good description of generic programming.
From http://www.stepanovpapers.com/history%20of%20STL.pdf

"STL is only a limited success. While it became a widely used library, its central intuition 
did not get across. People confuse generic programming with using (and abusing) C++ templates. 
Generic programming is about abstracting and classifying algorithms and data structures. It 
gets its inspiration from Knuth and not from type theory. Its goal is the incremental 
construction of systematic catalogs of useful, efficient and abstract algorithms and data 
structures. Such an undertaking is still a dream."