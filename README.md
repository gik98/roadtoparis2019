# RoadToParis 2019

Gara di selezione per SWERC 2019/2020 @ DISI, Università di Trento; 4 novembre 2019.

# Problemi

## A - All Different Directions

[Problem on Kattis](https://open.kattis.com/problems/alldifferentdirections)

[See solution](alldifferentdirections.cpp)

### Problem discussion

Just simulate the movements using the appropriate trigonometric formulas.

## B - Decoding The Hallway

[Problem on Kattis](https://open.kattis.com/problems/decodingthehallway)

[See solution](decodingthehallway.cpp)

### Problem discussion

Given that the length of S is <= 100, it can be proven by induction that if S is not a substring of the sequences with 1 <= n <= 10,
then it doesn't appear as a substring of any longer sequence (the proof is left as a useful exercise to the reader :) ).
Therefore the solution is to generate the first 10 sequences (the pattern can be easily guessed from the small cases) and check whether
S is a substring.

## C - Duty Scheduler

[Problem on Kattis](https://open.kattis.com/problems/dutyscheduler)

[See solution](dutyscheduler.cpp)

### Problem discussion

This is a classical assignment problem which could be solved using flow networks. Modeling could be done as described below.

We have a vertex for every student, a vertex for every day, the sink vertex and the source vertex.
Connect the source to every student-vertex with edges of capacity *x* (*x* is the maximum number of days on which any RA is assigned).
Connect a student-vertex to the day-vertex *d* with an edge of capacity 1 if the student is available to fulfill its RA duty on day *d* (rationale: any student could be assigned at most once every day).
Connect every student to the sink with edges of capacity 2 (rationale: any day shall have at most 2 RA assigned).

Start with the lowest value of *x* possible - which is ceil(m / (n * 2)). Actually, starting with *x* = 1 is also an option and should not make any difference.
Compute the maximum flow; if the flow value is lower than n * 2 then increment *x* by one and repeat.
Otherwise you found an acceptable assignment.

## D - Lost In Translation

[Problem on Kattis](https://open.kattis.com/problems/lost)

[See solution](lost.cpp)

### Problem discussion

Build the weighted graph of languages and start a BFS from the root node (English).

For each vertex, register its parent language and the distance from English.
Whenever you find a cheaper connection with the same distance, or a connection with a lower distance, change the parent and update the distance.

Finally, print the sum of the verteces of the resulting tree.

## E - Aaah!

[Problem on Kattis](https://open.kattis.com/problems/aaah)

[See solution](aaah.cpp)

### Problem discussion

Compare the lengths of the two strings.

## F - ???
Troviamo un problema di DP

## G - Boss Battle

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
