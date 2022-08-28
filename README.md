# Iterative, branchless Hanoi solver.
This project showcases an iterative and branchless solution to the well known
[Tower of Hanoi](https://en.wikipedia.org/wiki/Tower_of_Hanoi) puzzle.

## Explanation of the algorithm
The explanation assumes the read is familiar with the Towers of Hanoi puzzle and
its well-known recursive solution.

The recursive solution is optimal in the sense that it uses as few ring moves as
possible.
So producing an algorithm that emits the same sequence of moves is sufficient.

Imagine the source, destination and free stack are placed left to right next to
each other in that order and that the tower.
The source stack contains the discs `1` to  `n` where disc `1` the smallest
disc, and it's on top, whereas `n` is the largest disc, and it's on the bottom
of the source stack. 
Moving a disc left by one means moving a disc from its current stack to the
stack to its left.
If the stack the disc is on is the leftmost stack, move it to the rightmost
stack instead.
Moving a disc one to the right is analogue.
Moving a disc by two means moving a disc by one twice.

Observe:
1) Disc `i` is moved every `2^i` move.
2) If the total number of discs is even, then each odd-numbered disc is moved
   left by one when it is moved, and each even-numbered disc is moved right by
   one when it is moved.
3) If the total number of discs is odd, then it's the other way round.

Combine observations 2 and 3:
Place the destination stack to the right of the source stack when the 
number of discs is odd and place the auxiliary stack the right of the source
stack if the number of discs is even.
Then each even disc is moved by one to the right each time it is moved.
Each odd disc is moved by one to the left each time it is moved, which is the
same as moving it right twice each time it is moved.

Observe:
4) By observation 1, the number of the current step can be used to calculate
   the number of the disc which needs to be moved this step.
5) By observations 1 and 4, the current step and disc number can be used to
   compute how often the disc has been moved before.
6) By combination of observations 2, 3 and 5, the current stack holding the
   disc that needs to be moved this step can be computed, as well as the stack
   that the disc needs to be moved to.

These are all the conceptual step needed for an iterative solution.
The implementation takes advance of the binary representation of numbers to
calculate all of these step using just bitwise operations, addition, subtraction
and multiplication.
The two potentially slow modulo operations get optimized away by the compiler.