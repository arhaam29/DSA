/**************************************************/
/*                                                */
/*  Lab 2 Starter file                            */
/*                                                */
/*  Name: ARHAAM KHAN                             */
/*  Student number: 162087217                     */
/*                                                */
/**************************************************/

/* remember to code these in a RECURSIVE only manner*/

unsigned long long factorial (unsigned int n){
    //factorial of 0 is 1
    if (n == 0)
        return 1;
    else//recursive call
        return n * factorial(n - 1);

}

unsigned long long power (unsigned int base, unsigned int n){

    if (n == 0)
        return 1;//raised to the power of zero
    else
        return base * power(base, n - 1);//recursive call

}
unsigned long long fibonacci (unsigned int n){

    if (n == 0)//0th element
        return 0;
    else if (n == 1)//1st element
        return 1;
    else//recursive call
        return fibonacci(n - 1) + fibonacci(n - 2);

}