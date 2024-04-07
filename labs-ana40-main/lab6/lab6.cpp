#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;


/*Note: The heapify and the make heap were implemented using a different source and the source is cited*/
void heapify(int* arr, int size, int i)
{

    //source: https://www.geeksforgeeks.org/building-heap-from-array/
    int smallest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is smaller than root
    if (l < size && arr[l] < arr[smallest])
        smallest = l;

    // If right child is smaller than smallest so far
    if (r < size && arr[r] < arr[smallest])
        smallest = r;

    // If smallest is not root
    if (smallest != i) {
        swap(arr[i], arr[smallest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, size, smallest);
    }
    //source: https://www.geeksforgeeks.org/building-heap-from-array/
}

/*Note: The heapify and the make heap were implemented using a different source and the source is cited*/
void make_heap(int* arr, int size) {
    //source: https://www.geeksforgeeks.org/building-heap-from-array/
    int startIdx = (size / 2) - 1;

    // Perform reverse level order traversal
    // from last non-leaf node and heapify
    // each node
    for (int i = startIdx; i >= 0; i--) {
        heapify(arr, size, i);
    }
    //source: https://www.geeksforgeeks.org/building-heap-from-array/
}

//unguarded starts at 3
void ungaurded_insertion_Sort(int* arr, int size) {
    int curr;
    int i, j;
    for (i = 3; i < size; i++) {
        curr = arr[i];
        for (j = i; j > 2 && arr[j - 1] > curr; j--) {
            arr[j] = arr[j - 1];
        }
        arr[j] = curr;
    }
}

//normal sort id size<3
void Sort(int* arr, int size) {
    int curr;
    int i, j;
    for (i = 1; i < size; i++) {
        curr = arr[i];
        for (j = i; j > 0 && arr[j - 1] > curr; j--) {
            arr[j] = arr[j - 1];
        }
        arr[j] = curr;
    }
}


/*Only modify this function*/
void insertionSortModified(int arr[], int size) {
    //code from lab6 video
    //source: https://www.youtube.com/watch?v=FJJTYQYB1JQ
    if (size < 3)
    {
        Sort(arr, size);
    }
    else
    {
        make_heap(arr, size);
        ungaurded_insertion_Sort(arr, size);
    }
    //code from lab6 video
}


/*performs the insertion sort algorithm on array from index
left to index right inclusive.  You don't need to change this function*/
void insertionSortStandard(int arr[], int size) {
    int curr;
    int i, j;
    for (i = 1; i < size; i++) {
        curr = arr[i];
        for (j = i; j > 0 && arr[j - 1] > curr; j--) {
            arr[j] = arr[j - 1];
        }
        arr[j] = curr;
    }
}
