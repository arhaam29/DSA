$$Factorial Function Analysis$$

n is the number whose factorial is to be found. T(n) is the number of operations to find n factorial.
**See number of operations under comments next to each line in the function**.
''''cpp

unsigned long long factorial (unsigned int n){

    if (n == 0)//1
        return 1;//1
    else
        return n * factorial(n - 1);//3+T(n-1)

}
''''

When$n=0;
T(0)=2$. 
When $n>0$$
$$T(1)={5+T(0)}={5+2}={7}$$
$$T(2)={5+T(1)}={5+5+T(0)}={12}$$
$$...$$
$$T(n-1)={5+T(n-2)}$$

Thus, from above everytime five is repeated n times
$T(n)={5+5+.....+2}$
We reach 2 only when n is zero so 5 repeats n times
So $T(n) ={5+T(n-1)}={5*n + T(0)}$
Thus, $T(n)={5n+T(0)}$
$={5n+2}$ because T(0)=2.
Thus, for recursive factorial function
$$T(n)={5n+2}$$
$$T(n) is O(n)$$
$$ $$


$$Power Function Analysis$$

n is the power to which the base must be raised. T(n) is the number of operations to find $base^n$.
**See number of operations under comments next to each line in the function**.

''''cpp

unsigned long long power (unsigned int base, unsigned int n){
    
    if (n == 0)//1
        return 1;//1
    else
        return base * power(base, n - 1);//3+T(n-1)

}
''''
When$n=0;
T(0)=2$. 
When $n>0$$
$$T(1)={5+T(0)}={5+2}={7}$$
$$T(2)={5+T(1)}={5+5+T(0)}={12}$$
$$...$$
$$T(n-1)={5+T(n-2)}$$

Thus, from above everytime five is repeated n times
$T(n)={5+5+.....+2}$
We reach 2 only when n is zero so 5 repeats n times
So $T(n) ={5+T(n-1)}={5*n + T(0)}$
Thus, $T(n)={5n+T(0)}$
$={5n+2}$ because T(0)=2.
Thus, for recursive power function
$$T(n)={5n+2}$$
$$T(n) is O(n)$$

$$ $$




$$Fibonacci Function Questions$$

i.
ans: **The recursive function is much easier to understand and implement.**

ii.
ans:**The run time of the stated fibonacci funtion is &O(n)& where n is the number whose fib value is to be found.
Reason: Because we simply keep adding the number of operations done and unlike loops we dont run the same set of operations twice.
For the fib we might say its time complexity is O(n). This is my assumption.**

iii.
ans: **Changes made to lab2timing.cpp have been updated and pushed too.**

iv.
ans: **Done using excel spreadsheet.**

v.
ans: **No; The graph is not linear.**


![Lab2-graph](https://user-images.githubusercontent.com/97711825/215302087-aed6d2e5-08ec-4a12-a075-2860ef7cdac7.png)


