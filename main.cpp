#include <iostream>
#include <random>
#include <ctime>
#include <string>
#include <chrono>
#include <fstream>
#include "sorts.hpp"
using namespace std;

/**
 * @brief Returns string representation of an array.
 *
 * @param arr Array of int
 * @param n Size of array
 * @return string - String representation of the array
 */
string array_to_string(int arr[], int n);

int main()
{
    // Seeding random number generator
    srand(time(NULL));

    const int arr_size = 1000;
    const int num_runs = 10;

    // Output file
    string outfile_name = "arr_size_" + to_string(arr_size) + ".csv";
    ofstream outfile(outfile_name);

    // Writing headers for CSV file
    outfile << "run_id"
            << ","
            << "insertion_sort_counter"
            << ","
            << "insertion_sort_time(ns)"
            << ","
            << "selection_sort_counter"
            << ","
            << "selection_sort_time(ns)"
            << ","
            << "merge_sort_counter"
            << ","
            << "merge_sort_time(ns)"
            << ","
            << "quick_sort_counter"
            << ","
            << "quick_sort_time(ns)"
            << '\n';

    int *I = new int[arr_size]; // Insertion Sort array

    int *S = new int[arr_size]; // Selection Sort array

    int *M = new int[arr_size]; // Merge Sort array

    int *Q = new int[arr_size]; // Quick Sort array

    long timeI;
    long timeS;
    long timeM;
    long timeQ;

    long cI; // Counter for Insertion Sort
    long cS; // Counter for Selection Sort
    long cM; // Counter for Merge Sort
    long cQ; // Counter for Quick Sort

    // Averaging results over 10 runs
    for (int run_id = 1; run_id <= num_runs; run_id++)
    {
        cI = cS = cM = cQ = 0;             // Intialize counters to 0
        timeI = timeS = timeM = timeQ = 0; // Intialize times to 0

        // Intializing arrays
        for (int i = 0; i < arr_size; i++)
        {
            int x = rand();
            I[i] = x;
            S[i] = x;
            M[i] = x;
            Q[i] = x;
        }

        auto start_time = chrono::high_resolution_clock::now();
        cI = insertion_sort(I, arr_size);
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
        timeI = duration.count();

        start_time = chrono::high_resolution_clock::now();
        cS = selectionSort(S, arr_size);
        end_time = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
        timeS = duration.count();

        start_time = chrono::high_resolution_clock::now();
        mergeSort(M, 0, arr_size - 1);
        end_time = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
        timeM = duration.count();

        start_time = chrono::high_resolution_clock::now();
        quickSort(Q, 0, arr_size - 1);
        end_time = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
        timeQ = duration.count();

        // cout << "Run " << run_id << "\n";
        // cout << string(40, '*') << "\n";

        // cout << "Insertion Sort: ";
        // cout << array_to_string(I, arr_size);
        // cout << "\n";
        // cout << "Counter: " << cI << "\n";
        // cout << "Time:    " << timeI << " ns\n\n";

        // cout << "Selection Sort: ";
        // cout << array_to_string(S, arr_size);
        // cout << "\n";
        // cout << "Counter: " << cS << "\n";
        // cout << "Time:    " << timeS << " ns\n\n";

        // cout << "Merge Sort:     ";
        // cout << array_to_string(M, arr_size);
        // cout << "\n";
        // cout << "Counter: " << cM << "\n";
        // cout << "Time:    " << timeM << " ns\n\n";

        // cout << "Quick Sort:     ";
        // cout << array_to_string(Q, arr_size);
        // cout << "\n";
        // cout << "Counter: " << cQ << "\n";
        // cout << "Time:    " << timeQ << " ns\n\n";

        // cout << string(40, '*') << "\n";
        // cout << "\n";

        outfile << run_id
            << ","
            << cI
            << ","
            << timeI
            << ","
            << cS
            << ","
            << timeS
            << ","
            << cM
            << ","
            << timeM
            << ","
            << cQ
            << ","
            << timeQ
            << '\n';
        
    }

    // Free memory
    delete[] I;
    delete[] S;
    delete[] M;
    delete[] Q;

    // Close output file
    outfile.close();

    return 0;
}

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