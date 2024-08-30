// Return subsets that satisfy the constraint (i.e. backtracking)

#include <vector>
#include <iostream>

class Solution {
public:
    std::vector<std::vector<int>> combine(int n, int k) {
        std::vector<std::vector<int>> all_combinations; // To store all possible combinations
        std::vector<int> current_combination; // To store the current combination being built

        // Start backtracking from number 1
        backtrack(1, current_combination, all_combinations, n, k);
        
        return all_combinations;
    }

private:
    void backtrack(int next_start, std::vector<int>& current_combination, std::vector<std::vector<int>>& all_combinations, const int n, const int k) {
        // If the current combination has reached the desired size k, add it to the results
        if (current_combination.size() == k) {
            all_combinations.push_back(current_combination);
            return;
        }

        // Explore further combinations starting from next_start to n
        for (int i = next_start; i <= n; ++i) {
            current_combination.push_back(i); // Add i to the current combination
            // Recursively build the rest of the combination
            backtrack(i + 1, current_combination, all_combinations, n, k);
            // Backtrack: remove the last element to explore other possibilities
            current_combination.pop_back();
        }
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
