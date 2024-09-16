#include <iostream>
#include <vector>
#include <algorithm> 

// Worst case quadratic time, but constant memory! Useful for memory constrained environments

void cycleSort(std::vector<int>& arr) {
    int n = arr.size();

    for (int cycleStart = 0; cycleStart < n - 1; ++cycleStart) {
        int item = arr[cycleStart];
        int pos = cycleStart;

        // Find the position where the item should be
        for (int i = cycleStart + 1; i < n; ++i) {
            if (arr[i] < item) {
                ++pos;
            }
        }

        // If the item is already in the correct position, continue
        if (pos == cycleStart) {
            continue;
        }

        // Skip duplicates
        while (arr[pos] == item) {
            ++pos;
        }

        // Place the item in its correct position
        if (pos != cycleStart) {
            std::swap(item, arr[pos]);
        }

        // Rotate the rest of the cycle
        while (pos != cycleStart) {
            pos = cycleStart;
            // Find where to put the item again
            for (int i = cycleStart + 1; i < n; ++i) {
                if (arr[i] < item) {
                    ++pos;
                }
            }

            // Skip duplicates
            while (arr[pos] == item) {
                ++pos;
            }

            // Place the item in its correct position
            if (arr[pos] != item) {
                std::swap(item, arr[pos]);
            }
        }
    }
}

void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> arr = {10, 5, 3, 2, 4, 5, 1};

    std::cout << "Original array: ";
    printArray(arr);

    cycleSort(arr);

    std::cout << "Sorted array: ";
    printArray(arr);

    return 0;
}

