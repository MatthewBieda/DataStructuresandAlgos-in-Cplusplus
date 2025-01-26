#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	std::vector<int> nums = {1, 2, 3};
	std::vector<std::vector<int>> allPermutations;

    // Sort the input to ensure we start with the lexicographically smallest permutation
	std::sort(nums.begin(), nums.end());

    do {
        // Save the current permutation
        allPermutations.push_back(nums);
    } while (std::next_permutation(nums.begin(), nums.end()));  // Generate next permutation

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
