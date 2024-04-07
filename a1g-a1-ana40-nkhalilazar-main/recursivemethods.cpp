/*******************************************************************/
/*                                                                 */
/*  A1 Part 4: starter file                       */
/*                                                                 */
/*  Author1 Name: <ARHAAM KHAN>                                      */
/*      - function list                                            */
/*  Author2 Name: <NEGAR KHALIAZAR>                                      */
/*      - function list                                            */
/*                                                                 */
/*******************************************************************/
#include <cmath>
int* fibArray(int n);
int* IntegerToBinary(int n);



//fibArray function
int* fibArray(int n) {
   
    //Base case 1 (if n=1) array contains only [1]
    if (n == 1)
    {
        int* arr = new int[n];
        //case 1 array is [1]
        int a1[] = { 1 };
        arr = a1;
        return arr;
    }
    //Base case 2 (if n=2) array contains only [1,1]
    else if (n == 2)
    {
        //case 2 array is [1,1]
        int* arr = new int[n];
        int a1[] = { 1,1 };
        arr = a1;
        return arr;
    }
    //recurisve 
    else
    {
        int* arr = new int[n];
        //length = n
        //recursive call stores the array of previous calls in arr
        arr = fibArray(n - 1);
         //last Index is length-1
        int lastIndex = n - 1;
        //the latest element in array is len-1
        //eg: arr[3] = arr[2] + arr[1] where last index is 3
        arr[lastIndex] = arr[lastIndex - 1] + arr[lastIndex - 2];
        return arr;//return the array
    }
}



///IntegerToBinary Helper function
//helps shift elements to right so that resultion aray matches
//eg: arr[]=[1]
//add another lement 0
//we shift 1 to next position to make the following array: arr[] = [0,1]
int* concat(int* a1, int* a2, int len)
{
    //make arr[0]=0
    if (len == 0)
    {
        a1[0] = 0;
        return a1;
    }
    //keep shifting elements by taking elements from a2 position and placing them one up in a1
    // a1 is actually arr getting updated as seen in the Integer to binary function
    //this a shifting concationation function
    //take elements from a2 and a1 with a1 size one greater than a2
    //make all elements in a2 as elements in a1 but starting from a1[1]
    //intially store a1[0] as 0 to avoid memory issues
    //finally return a1 which will become arr in next function
    else
    {
        //recusrive call we are simply shifting elements to right
        a1 = concat(a1, a2, int(len - 1));
        a1[len] = a2[len - 1];
        return a1;
    }
}

//IntegertoBinary function
int* IntegerToBinary(int n) {
    if (n == 1)
    {
        //base case 1
        // if n reaches 1 we cannot divide by 2 any further
        //so arr[]=[1]
        int* arr = new int[n];
        arr[n - 1] = 1;
        return arr;
    }
    else
    {
        //example n=4;
        // 
        //eg; 4/2 = 2
        // 2/2=1
        int* a2 = IntegerToBinary(n / 2);
        //eg: floor(log2(4))=2
        int len = int(floor(log2(n)));
        //eg: number of didgits in binary is len+1 i.e.,2+1 = 3 for n=4
        int* arr = new int[len + 1];
        concat(arr, a2, (len));//shifting binary elements to right see concat
        //once we have arr
        //we change arr[0] to the next binary digit we calculate
        arr[0] = n % 2;
        return arr;
    }
}








