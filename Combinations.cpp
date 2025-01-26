#include <iostream>
#include <vector>

void backtrack(int next_start, int n, int k, std::vector<int>& current_combination, std::vector<std::vector<int>>& all_combinations) {
    // If the current combination has reached the desired size k, add it to the result
    if (current_combination.size() == k) {
        all_combinations.push_back(current_combination);
        return;
    }

    // Explore further combinations starting from next_start to n
    for (int i = next_start; i <= n; ++i) {
        current_combination.push_back(i); // Add i to the current combination
        
        // Recursively build the rest of the combination
        backtrack(i + 1, n, k, current_combination, all_combinations);
        
        // Backtrack: remove the last element to explore other possibilities
        current_combination.pop_back();
    }
}

int main() {
    int n = 5; // Upper bound for combination elements
    int k = 3; // Desired combination size

    std::vector<std::vector<int>> all_combinations;
    std::vector<int> current_combination;

    // Generate all combinations starting from number 1
    backtrack(1, n, k, current_combination, all_combinations);
    
    std::cout << "Combinations:\n";
    for (const auto& combination : all_combinations) {
        std::cout << "[ ";
        for (int num : combination) {
            std::cout << num << " ";
        }
        std::cout << "]\n";
    }
    
    return 0;
}
