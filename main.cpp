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
    const int num_runs = 10;

    // Output files
    string timefile_name = "time_.csv";
    ofstream timefile(timefile_name);
    string counterfile_name = "counter_.csv";
    ofstream counterfile(counterfile_name);

    // Writing headers for CSV file
    timefile << "arr_sz"
             << ","
             << "avg_insertion_sort_time(ns)"
             << ","
             << "avg_selection_sort_time(ns)"
             << ","
             << "avg_merge_sort_time(ns)"
             << ","
             << "avg_quick_sort_time(ns)"
             << '\n';

    // Writing headers for CSV file
    counterfile << "arr_sz"
                << ","
                << "avg_insertion_sort_counter"
                << ","
                << "avg_selection_sort_counter"
                << ","
                << "avg_merge_sort_counter"
                << ","
                << "avg_quick_sort_counter"
                << '\n';

    for (int arr_size = 1000; arr_size <= 7000; arr_size += 1000)
    {
        // Arrays of size arr_size for each sorting algorithm
        int *insertion_arr = new int[arr_size];
        int *selection_arr = new int[arr_size];
        int *merge_arr = new int[arr_size];
        int *quick_arr = new int[arr_size];

        // Elapsed time for each sorting algorithm
        long insertion_time;
        long selection_time;
        long merge_time;
        long quick_time;

        // Counters for each sorting algorithm
        long insertion_counter;
        long selection_counter;
        long merge_counter;
        long quick_counter;

        // Average elapsed time for each sorting algorithm
        double avg_insertion_time = 0;
        double avg_selection_time = 0;
        double avg_merge_time = 0;
        double avg_quick_time = 0;

        // Average value of the counter for each sorting algorithm
        double avg_insertion_counter = 0;
        double avg_selection_counter = 0;
        double avg_merge_counter = 0;
        double avg_quick_counter = 0;

        // Averaging results over 10 runs
        for (int run_id = 1; run_id <= num_runs; run_id++)
        {
            insertion_counter = selection_counter = merge_counter = quick_counter = globalCM = globalCQ = 0; // Intialize counters to 0
            insertion_time = selection_time = merge_time = quick_time = 0;                                   // Intialize times to 0

            // Intializing arrays
            for (int i = 0; i < arr_size; i++)
            {
                int x = rand() % 100;
                insertion_arr[i] = x;
                selection_arr[i] = x;
                merge_arr[i] = x;
                quick_arr[i] = x;
            }

            // Timing sorts and getting the counters
            auto start_time = chrono::high_resolution_clock::now();
            insertion_counter = insertion_sort(insertion_arr, arr_size);
            auto end_time = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
            insertion_time = duration.count();

            start_time = chrono::high_resolution_clock::now();
            selection_counter = selectionSort(selection_arr, arr_size);
            end_time = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
            selection_time = duration.count();

            start_time = chrono::high_resolution_clock::now();
            mergeSort(merge_arr, 0, arr_size - 1);
            merge_counter = globalCM;
            end_time = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
            merge_time = duration.count();

            start_time = chrono::high_resolution_clock::now();
            quickSort(quick_arr, 0, arr_size - 1);
            quick_counter = globalCQ;
            end_time = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
            quick_time = duration.count();

            // Adding times to the averages for time
            avg_insertion_time += insertion_time;
            avg_selection_time += selection_time;
            avg_merge_time += merge_time;
            avg_quick_time += quick_time;

            // Adding counters to the averages for counters
            avg_insertion_counter += insertion_counter;
            avg_selection_counter += selection_counter;
            avg_merge_counter += merge_counter;
            avg_quick_counter += quick_counter;

            // cout << "Run " << run_id << "\n";
            // cout << string(40, '*') << "\n";

            // cout << "Insertion Sort: ";
            // cout << array_to_string(insertion_arr, arr_size);
            // cout << "\n";
            // cout << "Counter: " << insertion_counter << "\n";
            // cout << "Time:    " << insertion_time << " ns\n\n";

            // cout << "Selection Sort: ";
            // cout << array_to_string(selection_arr, arr_size);
            // cout << "\n";
            // cout << "Counter: " << selection_counter << "\n";
            // cout << "Time:    " << selection_time << " ns\n\n";

            // cout << "Merge Sort:     ";
            // cout << array_to_string(merge_arr, arr_size);
            // cout << "\n";
            // cout << "Counter: " << merge_counter << "\n";
            // cout << "Time:    " << merge_time << " ns\n\n";

            // cout << "Quick Sort:     ";
            // cout << array_to_string(quick_arr, arr_size);
            // cout << "\n";
            // cout << "Counter: " << quick_counter << "\n";
            // cout << "Time:    " << quick_time << " ns\n\n";

            // cout << string(40, '*') << "\n";
            // cout << "\n";
        }

        // Computing averages for time
        // cout << fixed << avg_insertion_time << '\n';
        // cout << num_runs << '\n';
        // cout << (avg_insertion_time / num_runs) << '\n';
        avg_insertion_time /= num_runs;
        avg_selection_time /= num_runs;
        avg_merge_time /= num_runs;
        avg_quick_time /= num_runs;

        // Computing averages for time
        avg_insertion_counter /= num_runs;
        avg_selection_counter /= num_runs;
        avg_merge_counter /= num_runs;
        avg_quick_counter /= num_runs;

        // Print averages to file
        timefile << fixed << arr_size
                 << ","
                 << avg_insertion_time
                 << ","
                 << avg_selection_time
                 << ","
                 << avg_merge_time
                 << ","
                 << avg_quick_time
                 << '\n';

        counterfile << fixed << arr_size
                    << ","
                    << avg_insertion_counter
                    << ","
                    << avg_selection_counter
                    << ","
                    << avg_merge_counter
                    << ","
                    << avg_quick_counter
                    << '\n';

        // Free memory
        delete[] insertion_arr;
        delete[] selection_arr;
        delete[] merge_arr;
        delete[] quick_arr;
    }
    // Close output files
    timefile.close();
    counterfile.close();

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