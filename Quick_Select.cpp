#include <vector>
#include <iostream>

class Solution {
public:
    int findKthSmallest(std::vector<int>& nums, int k) {
        return quickSelect(nums, k);   
    }

    int quickSelect(std::vector<int>& nums, int k) {
        int pivot = nums[rand() % nums.size()];

        std::vector<int> left;
        std::vector<int> mid;
        std::vector<int> right;

        for (const int& num: nums) {
            if (num < pivot) {  
                left.push_back(num);
            } else if (num > pivot) {  
                right.push_back(num);
            } else {
                mid.push_back(num);
            }
        }

        if (k <= left.size()) {
            return quickSelect(left, k);
        }

        if (left.size() + mid.size() < k) {
            return quickSelect(right, k - left.size() - mid.size());
        }

        return pivot;
    }
};

int main() {
    Solution solution;

    std::vector<int> nums{1, 7, 18, 44, 2, 0, 32, 47, 5};
    int k = 3;

    int top_k_element = solution.findKthSmallest(nums, k);
    std::cout << top_k_element << std::endl;

    return 0;
}

