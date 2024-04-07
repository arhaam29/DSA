
Team Members:
1. ARHAAM KHAN
2. ALYSSA LEAN YOUNGE
3. NEGAR KHALILAZAR

$$PART A$$

1. What sorting algorithm was the speaker trying to improve?
**ANS: Quicksort**

2. At what partition size does VS perform a simpler sort algorithm instead of continuing to partition?
**ANS: 32**

3. At what partition size does GNU perform a simpler sort algorithm instead of continuing to partition?
**ANS: 16**

4. Regular insertion sort does a linear search backwards from end of array for correct spot to insert. According to the speaker, why does switching to a binary search not improve performance?
**ANS: 13% pessimization / slower **

5. Describe what is meant by branch prediction? (this may require further research)
**ANS: Branch prediction is an optimization technique which predicts the path a code will take before it is known for sure. 
https://iq.opengenus.org/branch-prediction-explained-with-a-code-example/**
6. What is meant by the informational entropy?
**ANS: A measure of the amount of information contained in a data set that is not redundant or predictable.**

7. If size == 15, what is size & 1? if size == 16, what is size & 1? Explain how right = first + 1 + (size & 1) avoids a conditional check. (hint, & is the bitwise AND operator in C/C++. It takes the bit representation of the two operands and perform an AND operation on each of the corresponding bits to form a final value)
**ANS: 
If size == 15, size & 1 = 1
If size == 16, size & 1 = 0
The expression avoids a conditional check by using the result of the bitwise AND operator to determmine whether or not to add 1 to the size of the buffer (if the result is 1, 1 is added to the size of the buffer while for 0 is not added)**
8. Speaker suggests the following algorithm:
    make_heap()
    unguarded_insertion_sort()

    He suggests that by doing make_heap() first, you can do something called unguarded_insertion_sort(). Explain what is unguarded_insertion_sort() and why it is faster than regular insertion sort. How does performing make_heap() allow you to do this?
**ANS: unguarded_insertion_sort() is a sorting function that divided the array into two parts: sorted and unsorted. The sorted contains the first element of the array and the unsorted contains the rest. It iterates over the unsorted and inserts each element properly in the sorted section. This is faster than regular insertion sort because it removes the overhead of checking whether the current element is smaller than the previous element in the sorted part. Performing make_heap() guarantees the largest element is at the beginning of the array which makes it faster because the only comparison is of each element with the largest element in the sorted section.**  
9. The speaker talks about incoperating your conditionals into your arithmetic. What does this mean? Provide an example of this from the video and explain how the conditional is avoided.
**ANS:
auto right = first + 1 + (size & 1); is an example from the video. Incorperating conditionals into arithmetic means using arithmetic operations to represent conditional statements instead of writing explicit if-else statements. The conditional is avoided by using the bitwise AND operator to chekc if 'size' is odd or even.**

10. The speaker talks about a bug in gnu's implementation. Describe the circumstances of this bug.
**ANS:
It leads to worst case **

11. The speaker shows several graphs about what happens as threshold increases using his new algorithm. The metric of comparison is increased, the metric of moves are increased but time drops... What metric does the author think is missing? Describe the missing metric he speaks about in the video. What is it measuring?
**ANS: 
Collect D(n), average distance between two subsequent array accesses. **

12. What does the speaker mean by fast code is left leaning?
**ANS:
Code that wants to be fast goes to the left of the page or favours simplicity and readability over complex optimization techniques. **

13. What does the speaker mean by not mixing hot and cold code?
**ANS:  
Separating hot code (code that is frequently executed) and cold code (code that is executed infrequently) into different parts of the program to improve performance and reduce possibility of bugs. **

** ****************************** **
$$PART B$$
*Ans:*
**Please check GRAPHS.md**

** ************************* ***
$$PART C$$
1. Did you/your team do all the micro optimizations described? If not, which did you do? Which did you not do?

**Ans: No; Did only modified insertion sort**

What did you/your team find most difficult to understand in the video?
**Ans: The heapify and make heap algorithm Thus, used some other source but the Modified insertion sort idea remains the same**
