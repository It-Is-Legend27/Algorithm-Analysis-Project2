// CMPS-5243-270: Algorithm Analysis
// 02/28/24
// Angel Badillo
// Kolten Pulliam
// Garrett Mathers
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

    // Total number of runs for each size of array
    const int num_runs = 10;

    // Output files for averages
    string avg_timefile_name = "avg_time_.csv";
    ofstream avg_timefile(avg_timefile_name);
    string avg_counterfile_name = "avg_counter_.csv";
    ofstream avg_counterfile(avg_counterfile_name);

    // Output file for all runs
    string all_timesfile_name = "all_times_.csv";
    ofstream all_timesfile(all_timesfile_name);
    string all_countersfile_name = "all_counters_.csv";
    ofstream all_countersfile(all_countersfile_name);

    // Writing headers for CSV file
    avg_timefile << "arr_sz"
                 << ","
                 << "avg_insertion_sort_time(ns)"
                 << ","
                 << "avg_selection_sort_time(ns)"
                 << ","
                 << "avg_merge_sort_time(ns)"
                 << ","
                 << "avg_quick_sort_time(ns)"
                 << '\n';

    avg_counterfile << "arr_sz"
                    << ","
                    << "avg_insertion_sort_counter"
                    << ","
                    << "avg_selection_sort_counter"
                    << ","
                    << "avg_merge_sort_counter"
                    << ","
                    << "avg_quick_sort_counter"
                    << '\n';

    all_timesfile << "arr_sz"
                  << ","
                  << "run_ID"
                  << ","
                  << "insertion_sort_time(ns)"
                  << ","
                  << "selection_sort_time(ns)"
                  << ","
                  << "merge_sort_time(ns)"
                  << ","
                  << "quick_sort_time(ns)"
                  << '\n';

    all_countersfile << "arr_sz"
                     << ","
                     << "run_ID"
                     << ","
                     << "insertion_sort_counter"
                     << ","
                     << "selection_sort_counter"
                     << ","
                     << "merge_sort_counter"
                     << ","
                     << "quick_sort_counter"
                     << '\n';

    // Perform tests for array sizes 1000 to 7000 in increments of 1000
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
            insertion_counter = selection_counter = merge_counter = quick_counter = global_merge_counter = global_quick_counter = 0; // Intialize counters to 0
            insertion_time = selection_time = merge_time = quick_time = 0;                                                     // Intialize times to 0

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
            merge_counter = global_merge_counter;
            end_time = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
            merge_time = duration.count();

            start_time = chrono::high_resolution_clock::now();
            quickSort(quick_arr, 0, arr_size - 1);
            quick_counter = global_quick_counter;
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

            // Print each run for times to file
            all_timesfile << fixed << arr_size
                          << ","
                          << run_id
                          << ","
                          << avg_insertion_time
                          << ","
                          << avg_selection_time
                          << ","
                          << avg_merge_time
                          << ","
                          << avg_quick_time
                          << '\n';

            // Print each run for counters to file
            all_countersfile << fixed << arr_size
                             << ","
                             << run_id
                             << ","
                             << insertion_counter
                             << ","
                             << selection_counter
                             << ","
                             << merge_counter
                             << ","
                             << quick_counter
                             << '\n';
        }

        // Computing averages for time
        avg_insertion_time /= num_runs;
        avg_selection_time /= num_runs;
        avg_merge_time /= num_runs;
        avg_quick_time /= num_runs;

        // Computing averages for time
        avg_insertion_counter /= num_runs;
        avg_selection_counter /= num_runs;
        avg_merge_counter /= num_runs;
        avg_quick_counter /= num_runs;

        // Print averages for time to file
        avg_timefile << fixed << arr_size
                     << ","
                     << avg_insertion_time
                     << ","
                     << avg_selection_time
                     << ","
                     << avg_merge_time
                     << ","
                     << avg_quick_time
                     << '\n';

        // Print averages for counters to file
        avg_counterfile << fixed << arr_size
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
    avg_timefile.close();
    avg_counterfile.close();
    all_timesfile.close();
    all_countersfile.close();

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