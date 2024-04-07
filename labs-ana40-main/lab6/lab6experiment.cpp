#include <cstdlib>
#include <iostream>
#include <string>
#include "timer.h"
/********************************************************************/
/*  Lab 6 main                                                      */
/*  To compile:                                                     */
/*     g++ lab6.cpp generatedata.cpp timer.cpp lab6experiments.cpp  */
/*  To run:                                                         */
/*     ./a.out                                                      */
/*                                                                  */
/*  Feel free to modify this main to output data in a way that      */
/*  is easy for you.                                                */
/********************************************************************/

using namespace std;

void generateRandom(int array[], int size);
void generateSorted(int array[], int size);
void generateReversed(int array[], int size);
void generateOrganPipe(int array[], int size);
void generateRotated(int array[], int size);
void generateZeroOne(int array[], int size);

void insertionSortStandard(int arr[], int size);
void insertionSortModified(int arr[], int size);

void printArray(int array[], int size);
typedef void (*GeneratorPtr)(int[], int);
typedef void (*SortPtr)(int[], int);
int main(void) {
    int size = 16;
        int* arrays[5];
        GeneratorPtr generators[5] = { generateRandom, generateSorted, generateReversed, generateOrganPipe, generateRotated };
        SortPtr sort[2] = { insertionSortStandard,insertionSortModified };
        std::string dataName[5] = { "random","sorted", "reversed", "organpipe","rotated" };
        Timer t;

        for (int i = 0; i < 5; i++) {
            arrays[i] = new int[size];
            generators[i](arrays[i], size);
            cout << "standard" << endl;
            t.reset();
            t.start();
            insertionSortStandard(arrays[i], size);
            t.stop();
            std::cout << dataName[i] << " : " << t.currtime() << std::endl;
            cout << "modified" << endl;
            t.reset();
            t.start();
            insertionSortModified(arrays[i], size);
            t.stop();
            std::cout << dataName[i] << " : " << t.currtime() << std::endl;
            delete[] arrays[i];
        }
    return 0;
}
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << ", ";
        if (i % 10 == 9) {
            std::cout << std::endl;
        }
    }
}
