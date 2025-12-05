//Advent of Code Day 4 Part 1
The rolls of paper (@) are arranged on a large grid; the Elves even have a helpful diagram (your puzzle input) indicating where everything is located.

For example:

..@@.@@@@.
@@@.@.@.@@
@@@@@.@.@@
@.@@@@..@.
@@.@@@@.@@
.@@@@@@@.@
.@.@.@.@@@
@.@@@.@@@@
.@@@@@@@@.
@.@.@@@.@.
The forklifts can only access a roll of paper if there are fewer than four rolls of paper in the eight adjacent positions. If you can figure out which rolls of paper the forklifts can access, they'll spend less time looking and more time breaking down the wall to the cafeteria.

In this example, there are 13 rolls of paper that can be accessed by a forklift (marked with x):

..xx.xx@x.
x@@.@.@.@@
@@@@@.x.@@
@.@@@@..@.
x@.@@@@.@x
.@@@@@@@.@
.@.@.@.@@@
x.@@@.@@@@
.@@@@@@@@.
x.x.@@@.x.
Consider your complete diagram of the paper roll locations. How many rolls of paper can be accessed by a forklift?

Thinking:


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Advent of Code Day 4 Part 2
Once a roll of paper can be accessed by a forklift, it can be removed. 
Once a roll of paper is removed, the forklifts might be able to access more rolls of paper, which they might also be able to remove. 
How many total rolls of paper could the Elves remove if they keep repeating this process?

Starting with the same example as above, here is one way you could remove as many rolls of paper as possible, 
using highlighted @ to indicate that a roll of paper is about to be removed, and using x to indicate that a roll of paper was just removed:






/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Lessons learnt:
1. 