// Return subsets that satisfy the constraint (i.e. backtracking)

#include <vector>
#include <iostream>

class Solution {
public:
    std::vector<std::vector<int>> combine(int n, int k) {
        std::vector<std::vector<int>> answer;
        std::vector<int> current;

        backtrack(current, 1, answer, k, n);

        return answer;
    }

private:
    void backtrack(std::vector<int>& curr, int firstNum, std::vector<std::vector<int>>& answer, int k, int n) {

        // constraint that prunes the search space
        if (curr.size() == k) {
            answer.push_back(curr);
            return;
        }

        for (int num = firstNum; num <= n; ++num) {
            curr.push_back(num);
            backtrack(curr, num + 1, answer, k, n);
            curr.pop_back();
        }

        return;
    }
};

int main() {
    Solution solution;

    int n = 4;
    int k = 2;

    std::vector<std::vector<int>> all_combinations = solution.combine(n, k);
    
    for (const std::vector<int>& combination: all_combinations) {
	for (const int& value: combination) {
	    std::cout << value << std::endl;
    	}
    }
}
