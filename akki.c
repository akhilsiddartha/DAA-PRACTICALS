#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <string>
#include <functional>
#include <iomanip>
using namespace std;

// ---------------------------------------------------------
// Namespace containing template-based sorting algorithms
// ---------------------------------------------------------
namespace Sorting {

    // Bubble Sort with early exit optimization
    template<typename T>
    void bubbleSort(std::vector<T>& arr) {
        std::size_t n = arr.size();
        bool swapped;
        for (std::size_t i = 0; i < n - 1; ++i) {
            swapped = false;
            for (std::size_t j = 0; j < n - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
    }

    // Selection Sort
    template<typename T>
    void selectionSort(std::vector<T>& arr) {
        std::size_t n = arr.size();
        for (std::size_t i = 0; i < n - 1; ++i) {
            std::size_t min_idx = i;
            for (std::size_t j = i + 1; j < n; ++j) {
                if (arr[j] < arr[min_idx]) {
                    min_idx = j;
                }
            }
            if (min_idx != i) {
                std::swap(arr[i], arr[min_idx]);
            }
        }
    }

    // Insertion Sort
    template<typename T>
    void insertionSort(std::vector<T>& arr) {
        std::size_t n = arr.size();
        for (std::size_t i = 1; i < n; ++i) {
            T key = arr[i];
            int j = static_cast<int>(i) - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = key;
        }
    }

    // Merge Sort (Internal Helper)
    template<typename T>
    void merge(std::vector<T>& arr, int l, int m, int r) {
        int n1 = m - l + 1;
        int n2 = r - m;
        std::vector<T> L(n1), R(n2);

        for (int i = 0; i < n1; ++i) L[i] = arr[l + i];
        for (int j = 0; j < n2; ++j) R[j] = arr[m + 1 + j];

        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k++] = L[i++];
            } else {
                arr[k++] = R[j++];
            }
        }
        while (i < n1) arr[k++] = L[i++];
        while (j < n2) arr[k++] = R[j++];
    }

    template<typename T>
    void mergeSortHelper(std::vector<T>& arr, int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2; // Prevents overflow for large arrays
            mergeSortHelper(arr, l, m);
            mergeSortHelper(arr, m + 1, r);
            merge(arr, l, m, r);
        }
    }

    // Merge Sort (Public API)
    template<typename T>
    void mergeSort(std::vector<T>& arr) {
        if (!arr.empty()) {
            mergeSortHelper(arr, 0, static_cast<int>(arr.size()) - 1);
        }
    }

    // Quick Sort (Internal Helper)
    template<typename T>
    int partition(std::vector<T>& arr, int low, int high) {
        T pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (arr[j] < pivot) {
                ++i;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    template<typename T>
    void quickSortHelper(std::vector<T>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSortHelper(arr, low, pi - 1);
            quickSortHelper(arr, pi + 1, high);
        }
    }

    // Quick Sort (Public API)
    template<typename T>
    void quickSort(std::vector<T>& arr) {
         if (!arr.empty()) {
            quickSortHelper(arr, 0, static_cast<int>(arr.size()) - 1);
        }
    }
}

// ---------------------------------------------------------
// Benchmarking Utilities
// ---------------------------------------------------------
namespace Benchmark {

    // Higher-order function to execute and time any sorting algorithm
    template<typename T>
    void runAndMeasure(const std::string& name, std::function<void(std::vector<T>&)> sortFunc, std::vector<T> data) {
        auto start = std::chrono::high_resolution_clock::now();

        sortFunc(data); // The vector is passed by value above, so we don't sort the original array

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        std::cout << std::left << std::setw(18) << name
                  << ": " << std::setw(6) << duration.count() << " microseconds\n";
    }
}

// ---------------------------------------------------------
// Main Execution
// ---------------------------------------------------------
int main() {
    // Note: Increased n to 1000 so timer differences are more obvious
    const std::size_t n = 1000;
    std::vector<int> arr(n);

    // Modern C++11 random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 10000);

    for (std::size_t i = 0; i < n; ++i) {
        arr[i] = distrib(gen);
    }

    std::cout << "========================================\n";
    std::cout << "      Sorting Algorithm Benchmark       \n";
    std::cout << "========================================\n";
    std::cout << "Data Set Size : " << n << " Elements\n";
    std::cout << "Data Type     : Integer\n";
    std::cout << "----------------------------------------\n\n";

    // Pass the algorithm functions into the benchmark runner
    Benchmark::runAndMeasure<int>("Bubble Sort", Sorting::bubbleSort<int>, arr);
    Benchmark::runAndMeasure<int>("Selection Sort", Sorting::selectionSort<int>, arr);
    Benchmark::runAndMeasure<int>("Insertion Sort", Sorting::insertionSort<int>, arr);
    Benchmark::runAndMeasure<int>("Merge Sort", Sorting::mergeSort<int>, arr);
    Benchmark::runAndMeasure<int>("Quick Sort", Sorting::quickSort<int>, arr);

    std::cout << "\n========================================\n";

    return 0;
}
