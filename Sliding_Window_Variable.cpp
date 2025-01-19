#include <vector>
#include <iostream>
#include <limits>

int minimumSizeSubarray(std::vector<int>& nums, int target) {
    int left = 0, sum = 0, minLength = std::numeric_limits<int>::max();

    for (int right = 0; right < nums.size(); ++right) {
        sum += nums[right]; // Expand the window

        // Shrink the window while the condition is met
        while (sum >= target) {
            minLength = std::min(minLength, right - left + 1);
            sum -= nums[left]; // Shrink from the left
            ++left;
        }
    }

    return (minLength == std::numeric_limits<int>::max() ? 0 : minLength);
}

int main() {
	std::vector<int> nums{5,3,7,14,9,1,0,8,3,3,1};
	int target = 18;
	
	std::cout << minimumSizeSubarray(nums, target);
}
