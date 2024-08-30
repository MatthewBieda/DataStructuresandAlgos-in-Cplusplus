#include <iostream>
#include <vector>

using namespace std;

// Function to generate all subsets
void backtrack(int start, const vector<int>& nums, vector<int>& currentSubset, vector<vector<int>>& allSubsets) {
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
    vector<int> nums = {1, 2, 8, 0, 4, 3, 5};  // Set of integers
    vector<vector<int>> allSubsets;
    vector<int> currentSubset;
    
    // Generate all subsets starting from index 0
    backtrack(0, nums, currentSubset, allSubsets);
    
    // Print all subsets
    cout << "Subsets:\n";
    for (const auto& subset : allSubsets) {
        cout << "[ ";
        for (int num : subset) {
            cout << num << " ";
        }
        cout << "]\n";
    }
    
    return 0;
}

