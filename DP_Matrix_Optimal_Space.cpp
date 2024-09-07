#include <iostream>
#include <vector>
#include <algorithm>

int minPathSum(const std::vector<std::vector<int>>& grid) {
    if (grid.empty() || grid[0].empty()) return 0;

    int m = grid.size();
    int n = grid[0].size();
    std::vector<int> dp(n, 0);

    // Initialize the first cell
    dp[0] = grid[0][0];

    // Initialize the first row
    for (int j = 1; j < n; ++j) {
        dp[j] = dp[j-1] + grid[0][j];
    }

    // Process the rest of the grid
    for (int i = 1; i < m; ++i) {
        dp[0] += grid[i][0]; // First column
        for (int j = 1; j < n; ++j) {
            dp[j] = grid[i][j] + std::min(dp[j], dp[j-1]);
        }
    }

    return dp[n-1];
}

int main() {
    std::vector<std::vector<int>> grid = {
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1}
    };

    std::cout << "Minimum path sum: " << minPathSum(grid) << std::endl;

    return 0;
}

