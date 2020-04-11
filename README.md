# DevTechChallenge
Sort an array of 0s, 1s and 2s in linear time complexity

**Description**
Given an array consisting only 0s, 1s and 2s, please provide an algorithm sorting that array in O(n) time complexity. So in the resulting sorted array, 0s will be at starting, then the 1s & then the 2s.

**Content**
*solution.c*: Contains the solution to the problem.
*testing.c*: Contains some functions and inputs to test the solution.
*test.sh*: Generates and runs a program to test the solution. The output is directed to */dev/null*.

**Solution description**
The algorithm goes through all the array content moving 0s to the beginning and 2s to the end of the array leaving 1s in the middle.

**Testing**
Execute *test.sh* to compile and run some test through the solution.
