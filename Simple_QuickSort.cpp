#include <vector>
#include <iostream>

// Helper function to partition the array
int partition(std::vector<int>& nums, int low, int high) {
    int pivot = nums[high]; // Select the last element as the pivot
    int i = low - 1; // Index of smaller element

    for (int j = low; j < high; j++) {
        if (nums[j] < pivot) {
            i++;
            std::swap(nums[i], nums[j]); // Swap elements smaller than pivot
        }
    }
    std::swap(nums[i + 1], nums[high]); // Place pivot in the correct position
    return i + 1; // Return pivot index
}

// Quick Sort function
void quickSort(std::vector<int>& nums, int low, int high) {
    if (low < high) {
        int pi = partition(nums, low, high); // Partition the array

        // Recursively sort elements before and after the partition
        quickSort(nums, low, pi - 1);
        quickSort(nums, pi + 1, high);
    }
}

int main() {
    std::vector<int> nums = {10, 7, 8, 9, 1, 5};
    quickSort(nums, 0, nums.size() - 1);

    // Print the sorted array
    for (const int& num : nums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}

