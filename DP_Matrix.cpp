#include <iostream>
#include <vector>
#include <algorithm>

int minPathSum(const std::vector<std::vector<int>>& grid) {
    if (grid.empty() || grid[0].empty()) return 0;

    int m = grid.size();
    int n = grid[0].size();
    std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));

    // Initialize the starting point
    dp[0][0] = grid[0][0];

    // Fill the first row
    for (int j = 1; j < n; ++j) {
        dp[0][j] = dp[0][j-1] + grid[0][j];
    }

    // Fill the first column
    for (int i = 1; i < m; ++i) {
        dp[i][0] = dp[i-1][0] + grid[i][0];
    }

    // Fill the rest of the DP table
    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            dp[i][j] = grid[i][j] + std::min(dp[i-1][j], dp[i][j-1]);
        }
    }

    return dp[m-1][n-1];
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

