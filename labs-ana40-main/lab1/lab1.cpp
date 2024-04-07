/**************************************************/
/*                                                */
/*  Lab 1 Starter file                            */
/*                                                */
/*  Name:   ARHAAM KHAN                           */
/*  Student number:  162087217                    */
/*                                                */
/**************************************************/

/* remember to code these in an iterative only manner*/

unsigned long long factorial (unsigned int n){
	// test the update from VS
    unsigned long long fac;
	//	//factorial of zero is 1
		fac = 1;
		for (unsigned int i = n; i >= 1; i--)
			fac = fac * i;//n*n-1*....*1
	return fac;

}

unsigned long long power (unsigned int base, unsigned int n){
    unsigned long long p;//calculated power
	if (n == 0)//if zero
		p = 1;//n^0 = 1 any number to the power of zero is 1
	else
	{
		p = 1;//keep p as 1
		for (unsigned int i = 0; i < n; i++)
			p = p * base;//multiply base 'n' times store and update in p
	}
	return p;
}
unsigned long long fibonacci (unsigned int n){
    unsigned long long fib;
	if (n == 0)//0th element
		fib = 0;
	else if (n == 1)//1st element
		fib = 1;
	else
	{
		unsigned long long p1 = 0;//0th and 1st
		unsigned long long p2 = 1;
		for (unsigned int i = 1; i < n; i++) //start from 1 to the n-1 value
		{
			fib = p1 + p2;//2nd element = 0+1 = 1; 3rd element = 1+1=2
			p1 = p2;
			//update previous1 and previous2
			//previous1=previous2
			//previous 2 becomes current number 
			p2 = fib;
		}
	}

	return fib;

}
