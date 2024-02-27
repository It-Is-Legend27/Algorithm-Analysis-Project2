#ifndef PROJECT2_SORTS
#define PROJECT2_SORTS
// CMPS-5243-270: Algorithm Analysis
// 02/28/24
// Angel Badillo
// Kolten Pulliam
// Garrett Mathers
#include <iostream>
#include <algorithm> // For swap function
using namespace std;

// Global variables for counters for recursive sorts
long global_quick_counter = 0;
long global_merge_counter = 0;

/**
 * @brief Performs insertion sort on an unsorted array of integers.
 * Source: https://www.geeksforgeeks.org/insertion-sort/
 * @param arr Array of int
 * @param n Size of array
 * @return int - Number of comparisons performed
 */
int insertion_sort(int arr[], int n)
{
    int comp_counter = 0; // Counter for comparisons

    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        // Move elements of arr[0..i-1],
        // that are greater than key,
        // to one position ahead of their
        // current position
        while (j >= 0 && arr[j] > key)
        {
            comp_counter++; // Increment counter

            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }

    return comp_counter;
}

/**
 * @brief Perforns selection sort on an unsorted array of integers.
 * Source: https://www.geeksforgeeks.org/selection-sort/
 * @param arr Array of int
 * @param n Size of array
 * @return int = Number of comparisons performed
 */
int selectionSort(int arr[], int n)
{
    int comp_counter = 0; // Counter for comparisons

    int i, j, min_idx;

    // One by one move boundary of
    // unsorted subarray
    for (i = 0; i < n - 1; i++)
    {

        // Find the minimum element in
        // unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            comp_counter++; // Increment counter

            if (arr[j] < arr[min_idx])
                min_idx = j;
        }

        // Swap the found minimum element
        // with the first element
        if (min_idx != i)
            swap(arr[min_idx], arr[i]);
    }

    return comp_counter;
}

/**
 * @brief Merges two subarrays created in merge sort.
 * Source: https://www.geeksforgeeks.org/merge-sort/
 * @param array Array of int
 * @param left Left most index
 * @param mid Middle index
 * @param right Rightmost index
 */
void merge(int array[], int const left, int const mid,
           int const right)
{
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;

    // Create temp arrays
    auto *leftArray = new int[subArrayOne],
         *rightArray = new int[subArrayTwo];

    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];

    auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
    {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo])
        {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else
        {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne)
    {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo)
    {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}

/**
 * @brief Performs merge sort on an unsorted array of integers.
 * Source: https://www.geeksforgeeks.org/merge-sort/
 * @param array Array of int
 * @param begin Leftmost index
 * @param end Rightmost index
 */
void mergeSort(int array[], int const begin, int const end)
{
    global_merge_counter++; // Increment global counter

    if (begin >= end)
        return;

    int mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

/**
 * @brief Partions the array and returns the index of the pivot.
 * Source: https://www.geeksforgeeks.org/quick-sort/
 * @param arr Array of int
 * @param low Leftmost index
 * @param high Rightmost index
 * @return int - index of pivot
 */
int partition(int arr[], int low, int high)
{
    // choose the pivot

    int pivot = arr[high];
    // Index of smaller element and Indicate
    // the right position of pivot found so far
    int i = (low - 1);

    for (int j = low; j <= high; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            // Increment index of smaller element
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

/**
 * @brief Performs quick sort on an unordered array of integers.
 * Source: https://www.geeksforgeeks.org/quick-sort/
 * @param arr Array of int
 * @param low Leftmost index
 * @param high Rightmost index
 */
void quickSort(int arr[], int low, int high)
{
    global_quick_counter++; // Increment global counter

    // when low is less than high
    if (low < high)
    {
        // pi is the partition return index of pivot

        int pi = partition(arr, low, high);

        // Recursion Call
        // smaller element than pivot goes left and
        // higher element goes right
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

#endif