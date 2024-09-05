#include <vector>
#include <iostream>

// Helper function to merge two sorted halves
void merge(std::vector<int>& nums, int left, int mid, int right) {
    int n1 = mid - left + 1;  // Size of the left half
    int n2 = right - mid;     // Size of the right half

    // Create temporary arrays for the left and right halves
    std::vector<int> L(n1), R(n2);

    // Copy data to temp arrays
    for (int i = 0; i < n1; i++)
        L[i] = nums[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = nums[mid + 1 + i];

    // Merge the temp arrays back into nums[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            nums[k] = L[i];
            i++;
        } else {
            nums[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy any remaining elements of L[] and R[] (if any)
    while (i < n1) {
        nums[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        nums[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort function
void mergeSort(std::vector<int>& nums, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;  // Calculate the middle point

        // Recursively sort the two halves
        mergeSort(nums, left, mid);
        mergeSort(nums, mid + 1, right);

        // Merge the sorted halves
        merge(nums, left, mid, right);
    }
}

int main() {
    std::vector<int> nums = {12, 11, 13, 5, 6, 7};
    mergeSort(nums, 0, nums.size() - 1);

    // Print the sorted array
    for (const int& num : nums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}

