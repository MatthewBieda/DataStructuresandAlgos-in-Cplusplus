#ifndef DP_TEMPLATES_H
#define DP_TEMPLATES_H

#include <vector>
#include <algorithm>
#include <climits>

// 1D DP Example: Fibonacci or Staircase problem
int fibonacci(int n) {
    if (n < 0) return -1; // Error handling
    if (n <= 1) return n;
    std::vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

// 2D DP Example: Unique Paths in Grid
int uniquePaths(int rows, int cols) {
    std::vector<std::vector<int>> dp(rows, std::vector<int>(cols, 1)); // Initialize to 1
    
    for (int i = 1; i < rows; ++i) {
        for (int j = 1; j < cols; ++j) {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    return dp[rows - 1][cols - 1];
}

// Space-optimized 1D DP: Fibonacci (Optimized)
int fibonacciOptimized(int n) {
    if (n < 0) return -1; // Error handling
    if (n <= 1) return n;
    int prev1 = 0, prev2 = 1;
    for (int i = 2; i <= n; ++i) {
        int current = prev1 + prev2;
        prev1 = prev2;
        prev2 = current;
    }
    return prev2;
}

// 0/1 Knapsack Problem (Maximization)
int knapsack(int capacity, const std::vector<int>& weights, const std::vector<int>& values) {
    int n = weights.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));
    
    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            if (weights[i - 1] <= w) {
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[n][capacity];
}

// Space-optimized 0/1 Knapsack Problem (1D DP)
int knapsackOptimized(int capacity, const std::vector<int>& weights, const std::vector<int>& values) {
    std::vector<int> dp(capacity + 1, 0);
    
    for (int i = 0; i < weights.size(); ++i) {
        for (int w = capacity; w >= weights[i]; --w) {
            dp[w] = std::max(dp[w], dp[w - weights[i]] + values[i]);
        }
    }
    return dp[capacity];
}

// Unbounded Knapsack Problem (Maximization)
int unboundedKnapsack(int capacity, const std::vector<int>& weights, const std::vector<int>& values) {
    std::vector<int> dp(capacity + 1, 0);

    for (int i = 0; i < weights.size(); ++i) {
        for (int w = weights[i]; w <= capacity; ++w) {
            dp[w] = std::max(dp[w], dp[w - weights[i]] + values[i]);
        }
    }
    return dp[capacity];
}

// Coin Change Problem (Minimization)
int coinChange(const std::vector<int>& coins, int amount) {
    std::vector<int> dp(amount + 1, amount + 1); // Fill with a large value (amount+1 acts as infinity)
    dp[0] = 0;
    
    for (int coin : coins) {
        for (int i = coin; i <= amount; ++i) {
            dp[i] = std::min(dp[i], dp[i - coin] + 1);
        }
    }
    
    return dp[amount] > amount ? -1 : dp[amount]; // If dp[amount] still has the initial value, return -1 (not possible)
}

// Memoization DP (Top-down with recursion): Fibonacci
int fibonacciMemo(int n, std::vector<int>& memo) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    
    memo[n] = fibonacciMemo(n - 1, memo) + fibonacciMemo(n - 2, memo);
    return memo[n];
}

// Bitmask DP Example: Assigning tasks to minimize cost
int bitmaskDP(int n, const std::vector<std::vector<int>>& cost) {
    int all_mask = (1 << n) - 1;
    std::vector<int> dp(1 << n, INT_MAX);
    dp[0] = 0;
    
    for (int mask = 0; mask <= all_mask; ++mask) {
        int x = __builtin_popcount(mask); // Number of tasks assigned
        for (int j = 0; j < n; ++j) {
            if (!(mask & (1 << j))) { // If the j-th task is not yet assigned
                dp[mask | (1 << j)] = std::min(dp[mask | (1 << j)], dp[mask] + cost[x][j]);
            }
        }
    }
    return dp[all_mask];
}

#endif // DP_TEMPLATES_H

