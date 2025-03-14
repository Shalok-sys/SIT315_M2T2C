#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace chrono;

const int DISTANCE_THRESHOLD = 5000; // Threshold for parallel execution

int Partition(vector<int> &arr, int low, int high)
{
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; j++)
        if (arr[j] <= pivot)
            swap(arr[++i], arr[j]);

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quicksort_helper(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pivot = Partition(arr, low, high);

        if ((high - low) < DISTANCE_THRESHOLD)
        {
            quicksort_helper(arr, low, pivot - 1);
            quicksort_helper(arr, pivot + 1, high);
        }
        else
        {
#pragma omp task shared(arr)
            quicksort_helper(arr, low, pivot - 1);

#pragma omp task shared(arr)
            quicksort_helper(arr, pivot + 1, high);

#pragma omp taskwait
        }
    }
}

void quicksort(vector<int> &arr)
{
#pragma omp parallel
    {
#pragma omp single
        quicksort_helper(arr, 0, arr.size() - 1);
    }
}

int main()
{
    vector<int> vec(1000000);
    srand(time(0));
    for (auto &val : vec)
        val = rand() % 10000 + 1;

    auto start = high_resolution_clock::now();
    quicksort(vec); // Calls the parallelized QuickSort
    auto end = high_resolution_clock::now();

    cout << "Execution Time (OpenMP QuickSort): "
         << duration_cast<milliseconds>(end - start).count() << " ms\n";

    return 0;
}
