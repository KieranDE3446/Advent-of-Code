//Advent of code day 3 Part 1

There are batteries nearby that can supply emergency power to the escalator for just such an occasion. The batteries are each labeled with their joltage rating, a value from 1 to 9. You make a note of their joltage ratings (your puzzle input). For example:

987654321111111
811111111111119
234234234234278
818181911112111
The batteries are arranged into banks; each line of digits in your input corresponds to a single bank of batteries. Within each bank, you need to turn on exactly two batteries; the joltage that the bank produces is equal to the number formed by the digits on the batteries you've turned on. For example, if you have a bank like 12345 and you turn on batteries 2 and 4, the bank would produce 24 jolts. (You cannot rearrange batteries.)

You'll need to find the largest possible joltage each bank can produce. In the above example:

In 987654321111111, you can make the largest joltage possible, 98, by turning on the first two batteries.
In 811111111111119, you can make the largest joltage possible by turning on the batteries labeled 8 and 9, producing 89 jolts.
In 234234234234278, you can make 78 by turning on the last two batteries (marked 7 and 8).
In 818181911112111, the largest joltage you can produce is 92.
The total output joltage is the sum of the maximum joltage from each bank, so in this example, the total output joltage is 98 + 89 + 78 + 92 = 357.

There are many batteries in front of you. Find the maximum joltage possible from each bank; what is the total output joltage?


//Steps:
//1.a) Start with a single bank
//1.b) Sort the array of ints into a descending list
//1.c) Take the two highest numbers and concatenate them into a single value
//1.d) Take that value as the max joltage for the bank
Rethinking
2.a) Create function to return the largest possible number (as a string) of length n that can be formed by picking digits from s IN ORDER
2.b) Loop through the string s up to index s.size()-n Because you must leave at least n-1 digits to the right to complete the subsequence
2.c) Track the largest digit found (max_digit) and its position (pos)
2.d) This ensures you pick the leftmost maximum digit that still leaves enough room
2.e) Return this digit + this function called again with n-1 to find the other digit(s)
3.a) Sum up this returned 2 digit value for every batterybank

Your puzzle answer was 17085.


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Advent of Code Day 3 Part 2

Now, you need to make the largest joltage by turning on exactly twelve batteries within each bank.

The joltage output for the bank is still the number formed by the digits of the batteries you've turned on; the only difference is that now there will be 12 digits in each bank's joltage output instead of two.

Consider again the example from before:

987654321111111
811111111111119
234234234234278
818181911112111
Now, the joltages are much larger:

In 987654321111111, the largest joltage can be found by turning on everything except some 1s at the end to produce 987654321111.
In the digit sequence 811111111111119, the largest joltage can be found by turning on everything except some 1s, producing 811111111119.
In 234234234234278, the largest joltage can be found by turning on everything except a 2 battery, a 3 battery, and another 2 battery near the start to produce 434234234278.
In 818181911112111, the joltage 888911112111 is produced by turning on everything except some 1s near the front.
The total output joltage is now much larger: 987654321111 + 811111111119 + 434234234278 + 888911112111 = 3121910778619.

What is the new total output joltage?

Steps:
1.a) Take the solution from part 1
1.b) Update the number passed to the highest_n_digit_number function to 12 (from 2)
1.c) Update the type of return value (when converted forom string) to a long long
2.a) Update the highest_n_digit_number to use greedy monotonic stack approach
2.b) Traverse each digit, if the current digit 'c' is larger than the last digit in the stack, and we still have
removals left, pop the smaller digit (because keeping the larger one gives a bigger number)
2.c) Push the current digit onto the stack
3.a) Trim excess digits if necessary
3.b) If we didn't remove enough during traversal, chop off from the end


Your puzzle answer was 169408143086082.

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Lessons learnt:
1. The Greedy Monotonic Stack approach
1.a) It is a technique where you maintain a stack in a sorted order (either increasing or decreasing) and 
greedily decide whether to push/pop elements to achieve an optimal solution.

 1.b) ex: "5271" with largest 3-digit, to_remove = num of digits - num of digits desired
 1.b)i) Read 5, 
 Stack = [5], to_remove = 1
 1.b)ii) Read 2, 2 is smaller than 5, we could pop 5 if we wanted a smaller number, but we want larger, so keep both
 Stack = [5,2], to_remove = 1
 1.b)iii) Read 7, Compare with top (2) since 7 > 2, and we still have removals left, pop 2
 Stack = [5,7], to_remove = 0
 1.b)iv) Read 1, Push 1, Stack = [5,7,1]
 1.b)v) since we need 3 digits, all done


 2. Running c++ code:
 > g++ d3_p1.cpp -o d3_p1.exe
 >Get-Content input.txt | .\d3_p1.exe