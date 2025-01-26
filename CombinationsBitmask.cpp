#include <iostream>
#include <vector>

void generateCombinations(const std::vector<int>& nums, int k) {
    int n = nums.size();
    int totalCombinations = 1 << n; // 2^n total subsets

    // Iterate through all bitmasks
    for (int mask = 0; mask < totalCombinations; ++mask) {
        std::vector<int> currentCombination;

        // Count how many bits are set in the mask (Hamming weight)
        int bitCount = 0;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                bitCount++;
                currentCombination.push_back(nums[i]);
            }
        }

        // Only consider combinations of size k
        if (bitCount == k) {
            // Print the current combination
            std::cout << "[ ";
            for (int num : currentCombination) {
                std::cout << num << " ";
            }
            std::cout << "]\n";
        }
    }
}

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    int k = 3; 
    generateCombinations(nums, k);
    return 0;
}
