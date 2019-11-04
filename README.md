# RoadToParis 2019

Gara di selezione per SWERC 2019/2020 @ DISI, Università di Trento; 4 novembre 2019.

# Problemi

## A - All Different Directions

[Problem on Kattis](https://open.kattis.com/problems/alldifferentdirections)

[See solution](alldifferentdirections.cpp)

### Problem discussion

Just simulate the movements using the appropriate trigonometric formulas.

## B - Boss Battle

[Problem on Kattis](https://open.kattis.com/problems/bossbattle)

[See solution](bossbattle.cpp)

### Problem discussion

If 1 <= n <= 3, one bomb is sufficient as it immediately defeats the boss.

If n > 3, the best strategy is to choose a fixed direction and throw a bomb every second pillar (the first, then the third, and so on),
because in this way every pillar gets hit and we proceed twice as fast as the boss.
Let's suppose that we go in the clock-wise direction: the worst case scenario is when at the start the boss is two pillars away in the
counter clock-wise direction (n-2 pillars in the clock-wise direction). Since we run twice as fast, the number of steps 'x' needed to
reach the boss can be obtained solving the following trivial equation: (n-2) + x = 2x -> x = n-2.

Hence, the final answer is: max(1, n-2).

## C - Decoding The Hallway

[Problem on Kattis](https://open.kattis.com/problems/decodingthehallway)

[See solution](decodingthehallway.cpp)

### Problem discussion

Given that the length of S is <= 100, it can be proven by induction that if S is not a substring of the sequences with 1 <= n <= 10,
then it doesn't appear as a substring of any longer sequence (the proof is left as a useful exercise to the reader :) ).
Therefore the solution is to generate the first 10 sequences (the pattern can be easily guessed from the small cases) and check whether
S is a substring.

## D - Krtica

[Problem on Kattis](https://open.kattis.com/problems/krtica)

[See solution](krtica.cpp)

### Problem discussion

Let's first consider the second part of the problem, that asks to join two trees A and B minimizing the resulting diameter.
Let d_A and d_B denote the diameters of A and B respectively, and (u, v) the joining edge (u belonging to A and v belonging to B).
The diameter of the resulting tree is the maximum between d_A, d_B and ('longest path in A starting from u' + 1 + 'longest path in B starting from v').
The optimal way to minimize the third term is to draw the edge between the centers of the two diameters, u being the center of d_A and
v being the center of d_B. In this way the third term assumes the minimum value: ceil(d_A / 2) + 1 + ceil(d_B / 2).
Summing up, the resulting diameter is: max(d_A, d_B, ceil(d_A/2) + 1 + ceil(d_B/2)).

To cut the tree in the optimal way, we need to find the edge whose removal minimizes the above expression. Therefore we need to find
efficiently, for every edge, the diameters of the two trees that are created. This can be achieved in O(n) with the following
dynamic programming approach.

Let's root the tree at node 0, and draw the corresponding direct edges. For every node 'x' apart from 0 we compute two values:
1) The diameter of the subtree whose root is 'x'.
2) The diameter of the complementary of subtree '1' (the original tree minus the subtree with 'x' as root).

It can be clearly seen that subtrees (1) and (2) are those that are obtained by removing the edge between 'x' and its predecessor,
and after this removal the length of their diameters will be substituted to d_A and d_B in the formula above.

The diameters of subtrees (1) can be computed recursively as follows: it is the maximum between the diameters of the children of 'x',
and the sum of the two longest paths from 'x' to a leaf (these can be easily precalculated).

The diameters of subtrees (2) are instead the maximum between:
1) The value obtained by computing recursively the diameter (2) from the predecessor of 'x'.
2) The diameter of the subtree whose root is a sibiling of 'x' (a child of the predecessor of 'x' different from 'x').
3) The sum of the two longest paths from the predecessor of 'x' to a leaf (in the subtree of predecessor(x)), not passing from 'x'
   (this is obtained efficiently by precalculating the three longest such paths for every node, in case one of them is passing through 'x').
4) The sum between the longest path from the predecessor of 'x' to a leaf and the longest path starting from the predecessor of 'x' and
   going "upwards", finishing in a leaf from another subtree.

The lenghts of the upward paths of case 4 can also be precomputed recursively.

Once we compute the values (1) and (2) for every node, we cycle through them to see which one minimizes the formula:
max(d_A, d_B, ceil(d_A/2)+1+ceil(d_B/2)).
When the node is found we remove the edge between it and its predecessor, and we join the centers of the diameters of the two resulting trees.
As it is a tree, and not a generic graph, the diameters can be found in O(n) with two BFSs.

## E - Lost In Translation

[Problem on Kattis](https://open.kattis.com/problems/lost)

[See solution](lost.cpp)

### Problem discussion

Build the weighted graph of languages and start a BFS from the root node (English).

For each vertex, register its parent language and the distance from English.
Whenever you find a cheaper connection with the same distance, or a connection with a lower distance, change the parent and update the distance.

Finally, print the sum of the verteces of the resulting tree.

## F - Duty Scheduler

[Problem on Kattis](https://open.kattis.com/problems/dutyscheduler)

[See solution](dutyscheduler.cpp)

### Problem discussion

This is a classical assignment problem which could be solved using flow networks. Modeling could be done as described below.

We have a vertex for every student, a vertex for every day, the sink vertex and the source vertex.
Connect the source to every student-vertex with edges of capacity *x* (*x* is the maximum number of days on which any RA is assigned).
Connect a student-vertex to the day-vertex *d* with an edge of capacity 1 if the student is available to fulfill its RA duty on day *d* (rationale: any student could be assigned at most once every day).
Connect every day-vertex to the sink with edges of capacity 2 (rationale: any day shall have at most 2 RA assigned).

Start with the lowest value of *x* possible - which is ceil(m / (n * 2)). Actually, starting with *x* = 1 is also an option and should not make any difference.
Compute the maximum flow; if the flow value is lower than n * 2 then increment *x* by one and repeat.
Otherwise you found an acceptable assignment.

## G - Sums
[Problem on Kattis](https://open.kattis.com/problems/consecutivesums)

[See solution](consecutivesums.cpp)

### Problem discussion
Remark (Gauss formula):
```math
k + (k+1) + .. + (k+n-1) = n * (k + n - 1)/2
```

Now, let N be the input number, so:

N = n * (k + n - 1)/2

2N = n * (k + n - 1)

We know that n divides 2N and (k + n - 1) divides 2N. The solutions is to try all the divisors of 2N (in O(sqrt(N))) until one of them makes the equations valid. Of course, if we don't find any valid integer the result is "impossible"; otherwise, n will be the number of summands and k the first summand. The problem requires n to be minimal, to do so we just need to start to try the divisors from 2 and stop when we find the first valid answer.
