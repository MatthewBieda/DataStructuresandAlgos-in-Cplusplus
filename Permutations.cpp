#include <iostream>
#include <vector>

void backtrack(int start, std::vector<int>& nums, std::vector<std::vector<int>>& allPermutations) {
    // If we've reached the end of the list, add the current permutation to the result
    if (start == nums.size()) {
        allPermutations.push_back(nums);
        return;
    }

    // Explore all possible swaps for the current position
    for (int i = start; i < nums.size(); ++i) {
        // Swap to create a new permutation
		std::swap(nums[start], nums[i]);

        // Recursively permute the remaining elements
        backtrack(start + 1, nums, allPermutations);

        // Backtrack: swap back to restore the previous state
		std::swap(nums[start], nums[i]);
    }
}

int main() {
	std::vector<int> nums = {1, 2, 3, 4, 5};
	std::vector<std::vector<int>> allPermutations;

    // Generate all permutations starting from index 0
    backtrack(0, nums, allPermutations);

	std::cout << "Permutations:\n";
    for (const auto& perm : allPermutations) {
		std::cout << "[ ";
        for (int num : perm) {
			std::cout << num << " ";
        }
		std::cout << "]\n";
    }

    return 0;
}
