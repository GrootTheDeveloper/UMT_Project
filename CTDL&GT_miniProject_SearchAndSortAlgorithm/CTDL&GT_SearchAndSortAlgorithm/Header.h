#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <type_traits>
#include <algorithm>

using namespace std;

template<typename T>
vector<T> generateTestData(int size, T minValue, T maxValue) {
    random_device rd;
    mt19937 gen(2111);

    vector<T> data(size);
    if constexpr (is_integral_v<T> && !is_same_v<T, char>) {
        uniform_int_distribution<T> dis(minValue, maxValue);
        for (int i = 0; i < size; ++i) {
            data[i] = dis(gen);
        }
    }
    else if constexpr (is_floating_point_v<T>) {
        uniform_real_distribution<T> dis(minValue, maxValue);
        for (int i = 0; i < size; ++i) {
            data[i] = dis(gen);
        }
    }
    else if constexpr (is_same_v<T, char>) {
        uniform_int_distribution<int> dis(static_cast<int>(minValue), static_cast<int>(maxValue));
        for (int i = 0; i < size; ++i) {
            data[i] = static_cast<char>(dis(gen));
        }
    }

    return data;
}


template<typename T>
void doSwap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

template <typename T>
void printArray(const vector<T>& arr) {
    for (const auto& elem : arr)
        cout << elem << " ";
    cout << "\n";
}

/*
Selection Sort: Best & Worst case: O(n^2)
Heap Sort: Best & Worst case: O(n log n)
Bubble Sort: Best case: O(n); Worst case: O(n^2)
*/

template <typename T>
void selectionSort(vector<T>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        swap(arr[min_idx], arr[i]);
    }
}

template <typename T>
void heapify(vector<T>& arr, int N, int i) {
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    if (l < N && arr[l] > arr[largest])
        largest = l;

    if (r < N && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, N, largest);
    }
}

template <typename T>
void heapSort(vector<T>& arr) {
    int N = arr.size();
    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(arr, N, i);

    for (int i = N - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

template<typename T>
void bubbleSort(vector<T>& a) {
    int n = a.size();
    bool isSwapped;
    do {
        isSwapped = false;
        for (int i = 0; i < n - 1; i++) {
            if (a[i] > a[i + 1]) {
                doSwap(a[i], a[i + 1]);
                isSwapped = true;
            }
        }
        n--;
    } while (isSwapped);
}

/*
Binary Search:
- Best case: O(1)
- Average case: O(log n)

Ternary Search:
- Best case: O(1)
- Average case: O(log n) (base 3)

Quaternary Search:
- Best case: O(1)
- Average case: O(log n) (base 4)
*/

template<typename T>
bool binarySearch(const vector<T>& a, T value, int left, int right) {
    if (left > right) {
        return false;
    }

    int mid = left + (right - left) / 2;
    if (a[mid] == value) {
        return true;
    }
    else if (a[mid] > value) {
        return binarySearch(a, value, left, mid - 1);
    }
    else {
        return binarySearch(a, value, mid + 1, right);
    }
}

template<typename T>
bool ternarySearch(const vector<T>& a, T value, int left, int right) {
    if (left <= right) {
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;

        if (a[mid1] == value || a[mid2] == value) {
            return true;
        }
        if (a[mid1] > value) {
            return ternarySearch(a, value, left, mid1 - 1);
        }
        else if (a[mid2] < value) {
            return ternarySearch(a, value, mid2 + 1, right);
        }
        else {
            return ternarySearch(a, value, mid1 + 1, mid2 - 1);
        }
    }
    return false;
}

template<typename T>
bool quaternarySearch(const vector<T>& a, T value, int left, int right) {
    if (left <= right) {
        int mid1 = left + (right - left) / 4;
        int mid2 = left + (right - left) / 2;
        int mid3 = left + 3 * (right - left) / 4;

        if (a[mid1] == value || a[mid2] == value || a[mid3] == value) {
            return true;
        }

        if (a[mid1] > value) {
            return quaternarySearch(a, value, left, mid1 - 1);
        }
        else if (a[mid2] > value) {
            return quaternarySearch(a, value, mid1 + 1, mid2 - 1);
        }
        else if (a[mid3] > value) {
            return quaternarySearch(a, value, mid2 + 1, mid3 - 1);
        }
        else {
            return quaternarySearch(a, value, mid3 + 1, right);
        }
    }
    return false;
}

#endif // HEADER_H
