#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iomanip>  
#include "header.h"

using namespace std;

const int TEST_SIZE = 10000000;
vector<float> testData = generateTestData<float>(TEST_SIZE, 0.0f, 1000000.0f);
vector<float> arr1 = testData;
vector<float> arr2 = testData;
vector<float> arr3 = testData;

void sortTimeCheck();
void searchTimeCheck();

int main()
{
    //sortTimeCheck();

    cout << setprecision(10) << fixed << testData[999] << endl;

    searchTimeCheck();

    return 0;
}

void searchTimeCheck() {
    const int SEARCH_COUNT = 10000; // num search elements   
    sort(arr1.begin(), arr1.end());
    vector<float> searchValues = { testData[999] };
    // Measure time for binary search in library
    auto start = chrono::high_resolution_clock::now();
    for (const float& value : searchValues) {
        std::binary_search(arr1.begin(), arr1.end(), value);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Binary Search in Library Time: " << duration << " microseconds" << endl;

    // Measure time for binary search
    start = chrono::high_resolution_clock::now();
    for (const float& value : searchValues) {
        binarySearch(arr1, value, 0, arr1.size() - 1);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Binary Search Time: " << duration << " microseconds" << endl;

    // Measure time for ternary search
    start = chrono::high_resolution_clock::now();
    for (const float& value : searchValues) {
        ternarySearch(arr1, value, 0, arr1.size() - 1);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Ternary Search Time: " << duration << " microseconds" << endl;

    // Measure time for quaternary search
    start = chrono::high_resolution_clock::now();
    for (const float& value : searchValues) {
        quaternarySearch(arr1, value, 0, arr1.size() - 1);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Quaternary Search Time: " << duration << " microseconds" << endl;

    cout << endl;
}

void sortTimeCheck() {
    // Measure time for selection sort
    auto start = chrono::high_resolution_clock::now();
    selectionSort(arr1);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Selection Sort Time: " << duration << " microseconds" << endl;

    // Measure time for heap sort
    start = chrono::high_resolution_clock::now();
    heapSort(arr2);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Heap Sort Time: " << duration << " microseconds" << endl;

    // Measure time for bubble sort
    start = chrono::high_resolution_clock::now();
    bubbleSort(arr3);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Bubble Sort Time: " << duration << " microseconds" << endl;

    // Measure time for std::sort (library sort)
    vector<float> arrLibrarySort = testData;
    start = chrono::high_resolution_clock::now();
    std::sort(arrLibrarySort.begin(), arrLibrarySort.end());
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Library Sort (std::sort) Time: " << duration << " microseconds" << endl;

    cout << endl;
}
