
$$Factorial Function Analysis:$$
Let n be the value we find factorial for.
T(n) is the number of operations needed to find n!
'''cpp
//code //number of operation runs is commented beside each code line

unsigned long long factorial (unsigned int n){

    unsigned long long fac;//1
		fac = 1;//1
		for (unsigned int i = n; i >= 1; i--)// 1 + n + n
			fac = fac * i;//2*n
	return fac;//1

}


'''
$$T(n)  = {1 + 1 + 1 + n  + n + 2n + 1} = {4n + 4} = {4(n-1)}$$
$$T(n)={4(n-1)}={4n-4}$$
(Ignoring constants)
$$Therefore, for factorial function: T(n) is O(n).$$
$$__________________________$$
$$__________________________$$




$$Power Function Analysis:$$
Let n be the power to which we raise the base for.
T(n) is the number of operations needed to find $(base)^n$.
'''cpp
//code //number of operation runs is commented beside each code line


unsigned long long power (unsigned int base, unsigned int n){

    unsigned long long p;//1
	if (n == 0)//1
		p = 1;//1
	else
	{
		p = 1;//1
		for (unsigned int i = 0; i < n; i++)//1+n+n
			p = p * base;//2*n
	}
	return p;//1

}


'''
$$T(n) = {1 + 1 + 1 + 1 + 1 + 2n + 2n + 1} = {6 + 4n}$$
$$T(n) = {4n + 6}$$
$$Therefore, for Power function: T(n) is O(n).$$
$$__________________________$$
$$__________________________$$



$$Fibonacci Function Analysis:$$
Let n be the element whose fibonacci value we need to find.
T(n) is the number of operations needed to find fib(n).

'''cpp
//code //number of operation runs is commented beside each code line


unsigned long long fibonacci (unsigned int n){

    unsigned long long fib;//1
	if (n == 0)//1
		fib = 0;//1
	else if (n == 1)//1
		fib = 1;//1
	else
	{
		unsigned long long p1 = 0;//1
		unsigned long long p2 = 1;//1
		for (unsigned int i = 1; i < n; i++) //1+ (n-1)+(n-1)
		{
			fib = p1 + p2;//2(n-1)
			p1 = p2;//(n-1)
			p2 = fib;//(n-1)
		}
	}
	return fib;//1

}


'''
$$T(n) = {1+1+1+1+1+1+1+1+(n-1)+(n-1)+2(n-1)+(n-1)+(n-1)+1}$$
$$T(n)={9+n-1+n-1+2n-2+n-1+n-1}$$
$$T(n)={6n+9-6}$$
$$T(n)={6n-3}$$
$$Therefore, for Fibonacci function: T(n) is O(n).$$
$$__________________________$$
$$__________________________$$


$$Bubble Sort Function Analysis:$$
Let n be the size of the array.
T(n) is the number of operations needed to sort the array using bubble sort.
$$Note: n = {size} in the code$$

'''cpp
//code //number of operation runs is commented beside each code line


void bubbleSort(int arr[],int size){

    int tmp;//1                          
    for (int i=0; i<size-1; i++) {   //only outer loop: 1+ n-1 + n-1   
        for (int j=0; j<size-1-i; j++){  //depends on i working shown below
		//n=size we assumed in the beginning
		//i=0 count=n-1
		//i=1 count=n-2
		//i=2 count=n-3......
		//..... i=n-2 count=1
		//therefore for innerloop= n-1 + n-2 + n-3 +....+1
		//thus for both loops the statements below will run (2n-1)*(n-1+ n-2 + n-3 +....+1) times
		//but worst case i=0 and inner runs n-1
		//thus for worst case the statements will run (2n-1)*(n-1) times 
            if (arr[j+1] < arr[j]) { //4*(2n-1)*(n-1)
                tmp = arr[j];//2*(2n-1)*(n-1)             
                arr[j] = arr[j+1];//4*(2n-1)*(n-1)   
                arr[j+1] = tmp;//3*(2n-1)*(n-1)         
            }
        }
    }

}

'''
Therefore, for the above bubble sort we can see that the statements under the nested loop conditions will run:
$(2n-1)*(n-1)$ times.

Thus, we can say:
$$T(n)=1+(2n-1)+(n-1)+(13*(2n-1)*(n-1))$$
We now get a $n^2$ once we expand the above for worst case.
$$T(n)=1+2n-1+n-1+(13*(2n^2-2n-n+1))$$
$$T(n)=3n-1+(13*(2n^2-3n+1))$$
$$T(n)=3n-1+26n^2-39n+13$$
$$T(n)=26n^2-36n+12$$

Thus, ignoring constants,
we get:
$$For Bubble sort function: T(n) is O(n^2)$$





