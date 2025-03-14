#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

int Partition(vector<int> &arr, int low, int high)
{
    int pivot = arr[high]; // Choosing the last element as pivot
    int i = low - 1;       // i keeps track of the correct position of pivot

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]); // Move pivot to its correct position
    return i + 1;
}

void QuickSort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int Pivot = Partition(arr, low, high);
        QuickSort(arr, low, Pivot - 1);
        QuickSort(arr, Pivot + 1, high);
    }
}

int main()
{
    vector<int> vec;
    srand(time(0)); // Seed for random number generation

    // Generate 100000 random numbers between 1 and 10000
    for (int i = 0; i < 1000000; i++)
    {
        vec.push_back(rand() % 10000 + 1);
    }

    auto start = high_resolution_clock::now();
    QuickSort(vec, 0, vec.size() - 1);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Execution Time (Single-threaded): " << duration.count() << " ms\n";

    return 0;
}
