/**************************************************************************/
/*                                                                        */
/*   Experiment 1                                                         */
/*                                                                        */
/*   To compile: g++ experiment.cpp timer.cpp -std=c++0x                 */
/*   Alter this main to help answer your first experiment question        */
/*                                                                        */
/**************************************************************************/


#define _CRT_SECURE_NO_WARNINGS
#include "table.h"
#include "timer.h"
#include <string>
#include <iostream>
#include <cstdlib>

const int maxRecords = 2000000;

void createData(std::string keys[], int data[], int max);
int main() {

    //this makes it easier to supply values on command line without recompiling
    //alternatively you can also just hard code the values and perhaps even loop 
    //through the values to create a csv
    /*if (argc != 3) {
        std::cout << "usage: a.out numrecords capacity" << std::endl;
        return 0;
    }*/

    std::string* keys = new std::string[maxRecords];        //list of test cases. 
    int* data = new int[maxRecords];
    createData(keys, data, maxRecords);


    /*********** IMPORTANT NOTE****************************/

    /****First Experiment: changing the load factor with different random values of numrecords and capacity*******/
    /* We manually entered the data in th experiment.cpp after changing to our preference*/
    
    //int numrecords = 100;
    //values for numrecords: 100, 300, 2550, 3150, 6678, 59400, 7000, 21000, 126035
    //size_t cap = 1000;
    //values for numrecords: 1000, 1100, 8500, 9000, 15900, 108000, 11000, 35000, 180050

    /***Second Experiment: changing the numrecords and capacity but maintaing the same constant load factor of 0.1****/
    //here we use a loop and this code is not commented
    for (int i = 100; i < maxRecords; i *= 3)
    {
        int numrecords = i;
        size_t cap = i * 10;
    std::cout << "number of records: " << numrecords << std::endl;
    std::cout << "capacity: " << cap << std::endl;

    LPTable<int> table1(cap);
    ChainingTable<int> table2(cap);


    //create a timer
    Timer T;


    for (int i = 0; i < numrecords; i++) {
        //start the timer.  think of this like its a stop watch.
        //this is like pressing the start button
        T.start();
        table1.insert(keys[i], data[i]);

        //stop the timer.  this is like pressing pause on a stop watch
        T.stop();
    }
    //currtime reads the time on the stop watch
    std::cout << "LP Table Time: " << T.currtime() << std::endl;

    Timer T2;
    for (int i = 0; i < numrecords; i++) {
        T2.start();
        table2.insert(keys[i], data[i]);
        T2.stop();
    }
    std::cout << "Chaining Table Time: " << T2.currtime() << std::endl;
    std::cout << std::endl;
    }

}




void createData(std::string keys[], int data[], int max) {
    FILE* fp = fopen("dictionary.txt", "r");
    int i = 0;
    std::string front = "A_";
    char curr[50];
    while (fscanf(fp, "%s\n", curr) == 1) {
        keys[i] = curr;
        data[i] = rand() % 100;
        i++;
    }
    int numWords = i;
    int j = 0;
    while (i < max) {
        keys[i] = front + keys[j];
        data[i] = rand() % 100;
        i++;
        j++;
        if (j == numWords) {
            front[0] += 1;
            j = 0;
        }
    }
}

