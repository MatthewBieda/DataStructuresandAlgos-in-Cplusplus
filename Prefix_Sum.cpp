#include <vector>
#include <iostream>

int main() {
    // 1-Dimensional

    std::vector<int> nums{1,2,3,4,5,6};
    std::vector<int> prefix_sum(nums.size(), 0);

    // Initalize the first element of the prefix sum
    prefix_sum[0] = nums[0];

    for (int i = 1; i < nums.size(); ++i) {
        prefix_sum[i] = prefix_sum[i - 1] + nums[i];
    }

    std::cout << "1D Prefix Sum: ";
    for (const int& psum: prefix_sum) {
	std::cout << psum << " ";
    }
    std::cout << std::endl;

    return 0;	
}
