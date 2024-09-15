#include <iostream>
#include <vector>
#include <stack>

std::vector<int> nextGreaterElement(const std::vector<int>& nums) {
    int n = nums.size();
    std::vector<int> result(n, -1);  // Initialize the result array with -1
    std::stack<int> st;  // This will store indexes of the elements

    for (int i = 0; i < n; ++i) {
        // While stack is not empty and the current element is greater than the element at the top of the stack
        while (!st.empty() && nums[i] > nums[st.top()]) {
            result[st.top()] = nums[i];  // The next greater element for the element at st.top() is nums[i]
            st.pop();
        }
        st.push(i);  // Push current index to the stack
    }

    return result;  // Elements with no greater element to the right will have -1
}

int main() {
    std::vector<int> nums = {5, 2, 6, 3, 4};
    std::vector<int> result = nextGreaterElement(nums);

    std::cout << "Next Greater Elements: ";
    for (int res : result) {
        std::cout << res << " ";
    }
    std::cout << std::endl;

    return 0;
}

