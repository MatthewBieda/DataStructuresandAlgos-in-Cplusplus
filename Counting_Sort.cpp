#include <vector>
#include <algorithm> // For std::min and std::max
#include <iostream>

void countingSort(std::vector<int>& nums) {
    if (nums.empty()) return;

    // Step 1: Find the minimum and maximum values
    int minVal = *std::min_element(nums.begin(), nums.end());
    int maxVal = *std::max_element(nums.begin(), nums.end());
    
    // Step 2: Create a count array to store frequency of each value in the range [minVal, maxVal]
    int range = maxVal - minVal + 1;
    std::vector<int> count(range, 0);
    
    // Step 3: Count occurrences of each number
    for (int num : nums) {
        count[num - minVal]++;
    }
    
    // Step 4: Use the count array to reconstruct the sorted array in-place
    int index = 0;
    for (int i = 0; i < range; ++i) {
	while (count[i] > 0) {
	    nums[index] = i + minVal; // Place value in sorted array
	    count[i]--; // Decrease count of that value
	    index++; // Move to next position in nums array
	}
    }    
}

int main() {
    std::vector<int> nums{1,7,4,9,0,3,3,8};

    countingSort(nums);

    for (const int& num: nums) {
	std::cout << num;
    }
}
