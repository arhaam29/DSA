/*********************************************************************************************/
/*																						     */
/*   A1 part4 tester file																     */
/*																						     */
/*   To compile: g++ a1recursivemethdstester.cpp recursivemethods.cpp timer.cpp -std=c++0x   */
/*   NOTE: if you are working in windows, change the #define								 */
/*   PLATFORM line in timer.h, see comments in that file									 */
/*																						     */
/*********************************************************************************************/
#include "timer.h"
#include <string>
#include <iostream>
#include <cstdlib>



int* fibArray(int n);
int* IntegerToBinary(int n);
//void fibArrayHelper(int i, int* seq, int n);
bool isArrayEqual(int* a, int* b, int n);

bool test1(std::string& error);
bool test2(std::string& error);
bool test3(std::string& error);
bool test4(std::string& error);
bool test5(std::string& error);
bool test6(std::string& error);
bool test7(std::string& error);
bool test8(std::string& error);
bool test9(std::string& error);
bool test10(std::string& error);
bool test11(std::string& error);
bool test12(std::string& error);

const int numTests = 12;
typedef bool (*TestPtr)(std::string&);
int main(void) {
    TestPtr runTest[numTests] = { test1, test2,test3, test4, test5, test6,
    test7, test8,test9, test10, test11, test12 };

    std::string testSummary[numTests] = { "test_01_00_FibArray",
        "test_01_01_FibArray", "test_01_03_FibArray","test_01_04_FibArray","test_01_05_FibArray",
        "test_01_06_FibArray","test_03_01_IntegerToBinary", "test_03_02_IntegerToBinary",
        "test_03_03_IntegerToBinary","test_03_04_IntegerToBinary","test_03_05_IntegerToBinary",
        "test_03_06_IntegerToBinary"
    };
    std::string msg;
    bool result = true;
    int numPassed = 0;
    for (int i = 0; result && i < numTests; i++) {
        result = runTest[i](msg);
        if (!result) {
            std::cout << "Test " << i + 1 << " - " << testSummary[i] << ": failed." << std::endl;
            std::cout << msg << std::endl;
        }
        else {
            numPassed++;
            std::cout << "Test " << i + 1 << " - " << testSummary[i] << ": passed." << std::endl;
        }
    }
    if (numPassed == numTests) {
        std::cout << "Congratulations! You have passed testing for A1 part 4" << std::endl;
        return 0;
    }
    else {
        std::cout << "Looks like you still have some work left to do" << std::endl;
        return 1;
    }
}
/* Function to check if the arrays are equal or not, same size*/
bool isArrayEqual(int* a, int* b, int n) {
    /* Compare elements of the array */
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i])
            return false;
    }
    /* All elements are same */
    return true;
}
//// --------------------------
bool test1(std::string& error) {
    int n = 2;
    int expected[] = { 1, 1 };
    int* actual = fibArray(n);
    return isArrayEqual(expected, actual, n);
}

bool test2(std::string& error) {
    int n = 3;
    int expected[] = { 1, 1 , 2};
    int* actual = fibArray(n);
    return isArrayEqual(expected, actual, n);
}
bool test3(std::string& error) {
    int n = 4;
    int expected[] = { 1, 1 , 2, 3 };
    int* actual = fibArray(n);
    return isArrayEqual(expected, actual, n);
}
bool test4(std::string& error) {
    int n = 5;
    int expected[] = { 1, 1 , 2, 3 , 5};
    int* actual = fibArray(n);
    return isArrayEqual(expected, actual, n);
}

bool test5(std::string& error) {
    int n = 6;
    int expected[] = { 1, 1 , 2, 3 , 5, 8 };
    int* actual = fibArray(n);
    return isArrayEqual(expected, actual, n);
}

bool test6(std::string& error) {
    int n = 12;
    int expected[] = { 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144 };
    int* actual = fibArray(n);
    return isArrayEqual(expected, actual, n);
}

bool test7(std::string& error) {
    int n = 4;
    int expected[] = { 0, 0 , 1 };
    int* actual = IntegerToBinary(n);
    return isArrayEqual(expected, actual, 3);
}

bool test8(std::string& error) {
    int n = 31;
    int expected[] = { 1, 1, 1, 1, 1 };
    int* actual = IntegerToBinary(n);
    return isArrayEqual(expected, actual, 5);
}
bool test9(std::string& error) {
    int n = 65535;
    int expected[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    int* actual = IntegerToBinary(n);
    return isArrayEqual(expected, actual, 16);
}
bool test10(std::string& error) {
    int n = 1598;
    
    int expected[] = { 0, 1,1,1,1,1,0,0,0,1,1 };
    int* actual = IntegerToBinary(n);
    return isArrayEqual(expected, actual, 11);
}
bool test11(std::string& error) {
    int n = 765;
    int expected[] = { 1,0,1,1,1,1,1,1,0,1};
    int* actual = IntegerToBinary(n);
    return isArrayEqual(expected, actual, 10);
}
bool test12(std::string& error) {
    int n = 582;
    int expected[] = { 0,1,1,0,0,0,1,0,0,1 };
    int* actual = IntegerToBinary(n);
    return isArrayEqual(expected, actual, 10);
}


