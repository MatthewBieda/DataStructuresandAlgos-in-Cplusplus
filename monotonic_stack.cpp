#include<vector>
#include<stack>
#include<iostream>

class Solution {
public:
    std::vector<int> dailyTemperatures(std::vector<int>& temperatures) {
        std::stack<int> mono_stack;
        std::vector<int> result(temperatures.size(), 0);

        for (int i = 0; i < temperatures.size(); ++i) {
            while (!mono_stack.empty() && temperatures[mono_stack.top()] < temperatures[i]) {
                int index = mono_stack.top();
                mono_stack.pop();

                result[index] = i - index; // Difference in days
            }

        mono_stack.push(i);
        }

        return result;
    }
};

int main() {
    Solution solution;

    std::vector<int> temperatures{73,74,75,71,69,72,76,73};

    std::vector<int> result = solution.dailyTemperatures(temperatures);

    for (const int& days_until_higher: result) {
	std::cout << days_until_higher << std::endl;
    }

    return 0;
}
