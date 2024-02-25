#include <iostream>
#include <random>
#include <ctime>
#include <string>
#include <chrono>
#include "sorts.hpp"
using namespace std;

const int ARR_SIZE = 10;

string array_to_string(int arr[], int n)
{
    string repr = "";

    repr += "[";

    for (int i = 0; i < n; i++)
    {
        if (i != n - 1)
            repr += to_string(arr[i]) + ", ";
        else
            repr += to_string(arr[i]);
    }

    repr += "]";
    return repr;
}

int main()
{
    // Seeding random number generator
    srand(time(NULL));

    int *S1 = new int[ARR_SIZE]; // Insertion Sort array
    int *S2 = new int[ARR_SIZE]; // Selection Sort array
    int *S3 = new int[ARR_SIZE]; // Merge Sort array
    int *S4 = new int[ARR_SIZE]; // Quick Sort array

    long time1;
    long time2;
    long time3;
    long time4;

    int c1; // Counter for Insertion Sort
    int c2; // Counter for Selection Sort
    int c3; // Counter for Merge Sort
    int c4; // Counter for Quick Sort

    

    // Averaging results over 10 runs
    for (int runID = 1; runID <= 1; runID++)
    {
        c1 = c2 = c3 = c4 = 0; // Intialize counters to 0
        time1 = time2 = time3 = time4 = 0; // Intialize times to 0

        // Intializing arrays
        for (int i = 0; i < ARR_SIZE; i++)
        {
            int x = rand();
            S1[i] = x;
            S2[i] = x;
            S3[i] = x;
            S4[i] = x;
        }

        auto start_time = chrono::high_resolution_clock::now();
        c1 = insertion_sort(S1, ARR_SIZE);
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
        time1 = duration.count();

        start_time = chrono::high_resolution_clock::now();
        c2 = selectionSort(S2, ARR_SIZE);
        end_time = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
        time2 = duration.count();

        start_time = chrono::high_resolution_clock::now();
        mergeSort(S3, 0, ARR_SIZE);
        end_time = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
        time3 = duration.count();

        start_time = chrono::high_resolution_clock::now();
        quickSort(S4, 0, ARR_SIZE);
        end_time = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
        time4 = duration.count();

        cout << "Run " << runID << "\n";
        cout << string(40, '*') << "\n";

        cout << "Selection Sort: ";
        //cout << array_to_string(S1, ARR_SIZE);
        cout << "\n";
        cout << "Counter: " << c1 << "\n";
        cout << "Time: " << time1 << "\n\n";

        cout << "Insertion Sort: ";
        //cout << array_to_string(S2, ARR_SIZE);
        cout << "\n";
        cout << "Counter: " << c2 << "\n";
        cout << "Time: " << time2 << "\n\n";

        cout << "Merge Sort:     ";
        //cout << array_to_string(S3, ARR_SIZE);
        cout << "\n";
        cout << "Counter: " << c3 << "\n";
        cout << "Time: " << time3 << "\n\n";

        cout << "Quick Sort:     ";
        //cout << array_to_string(S4, ARR_SIZE);
        cout << "\n";
        cout << "Counter: " << c4 << "\n";
        cout << "Time: " << time4 << "\n\n";
        
        cout << string(40, '*') << "\n";
        cout << "\n";
    }

    // Free memory
    delete[] S1;
    delete[] S2;
    delete[] S3;
    delete[] S4;

    return 0;
}