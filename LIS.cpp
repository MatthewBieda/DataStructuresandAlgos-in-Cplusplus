#include <vector>
#include <iostream>
#include <algorithm>

class Solution {
public:
    int lengthOfLIS(std::vector<int>& nums) {
        int n = nums.size();
        std::vector<int> dp(n, 1);

        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[i] > nums[j]) {
                    dp[i] = std::max(dp[i], dp[j] + 1);
                }
            }
        }
        
        return *std::max_element(dp.begin(), dp.end());
    }
};

int main() {
    Solution solution;

    std::vector<int> nums{10,9,2,5,3,7,101,18};

    int result = solution.lengthOfLIS(nums);
    std::cout << result << std::endl;

    return 0;
}
