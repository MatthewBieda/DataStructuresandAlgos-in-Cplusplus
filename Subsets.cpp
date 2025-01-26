#include <iostream>
#include <vector>

void backtrack(int start, const std::vector<int>& nums, std::vector<int>& currentSubset, std::vector<std::vector<int>>& allSubsets) {
    // Add the current subset to the result
    allSubsets.push_back(currentSubset);
    
    // Explore further subsets
    for (int i = start; i < nums.size(); ++i) {
        // Include nums[i] in the current subset
        currentSubset.push_back(nums[i]);
        
        // Move to the next element
        backtrack(i + 1, nums, currentSubset, allSubsets);
        
        // Exclude nums[i] from the current subset (backtrack)
        currentSubset.pop_back();
    }
}

int main() {
    std::vector<int> nums = {1, 2, 8, 0, 4, 3, 5};
    std::vector<std::vector<int>> allSubsets;
    std::vector<int> currentSubset;
    
    // Generate all subsets starting from index 0
    backtrack(0, nums, currentSubset, allSubsets);
    
    std::cout << "Subsets:\n";
    for (const auto& subset : allSubsets) {
        std::cout << "[ ";
        for (int num : subset) {
            std::cout << num << " ";
        }
        std::cout << "]\n";
    }
    
    return 0;
}

