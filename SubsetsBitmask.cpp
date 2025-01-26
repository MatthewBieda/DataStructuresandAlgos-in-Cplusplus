#include <iostream>
#include <vector>

void generateSubsets(const std::vector<int>& nums) {
    int n = nums.size();
    int totalSubsets = 1 << n; // 2^n subsets
    
    for (int mask = 0; mask < totalSubsets; ++mask) {
        std::vector<int> currentSubset;
        
        // For each bit in mask, add corresponding element from nums
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {  // If the i-th bit is set, include nums[i]
                currentSubset.push_back(nums[i]);
            }
        }

        // Print the current subset
        std::cout << "[ ";
        for (int num : currentSubset) {
            std::cout << num << " ";
        }
        std::cout << "]\n";
    }
}

int main() {
    std::vector<int> nums = {1, 2, 3};
    generateSubsets(nums);
    return 0;
}
