#include <iostream>
#include <vector>

bool subsetSum(const std::vector<int>& nums, int target) {
    int n = nums.size();
    int numSubsets = 1 << n; // Total number of subsets
    std::vector<bool> dp(numSubsets, false);

    // Base case: subset with 0 elements has a sum of 0
    dp[0] = true;

    // Iterate through all subsets
    for (int mask = 0; mask < numSubsets; ++mask) {
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) { // If the ith element is included in the subset
                sum += nums[i];
            }
        }
        if (sum == target) return true;
    }

    return false;
}

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    int target = 8;

    if (subsetSum(nums, target)) {
        std::cout << "A subset with sum " << target << " exists." << std::endl;
    } else {
        std::cout << "No subset with sum " << target << " exists." << std::endl;
    }

    return 0;
}

