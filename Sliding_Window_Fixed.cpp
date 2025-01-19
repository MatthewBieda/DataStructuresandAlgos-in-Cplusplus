#include <vector>
#include <iostream>

int slidingWindowFixedSize(std::vector<int>& nums, int k) {
    int left = 0, sum = 0, maxSum = 0;

    // Initialize the sum of the first window
    for (int i = 0; i < k; ++i) {
        sum += nums[i];
    }

    maxSum = sum;

    // Slide the window
    for (int right = k; right < nums.size(); ++right, ++left) {
        sum += nums[right];    // Add the new element
        sum -= nums[left];     // Remove the old element
        maxSum = std::max(maxSum, sum);
    }

    return maxSum;
}

int main() {
	std::vector<int> nums{1, 6, 10, 9, 3, 5, 4, 7, 2};
	int windowSize = 3;

	std::cout << slidingWindowFixedSize(nums, windowSize) << std::endl;
}
