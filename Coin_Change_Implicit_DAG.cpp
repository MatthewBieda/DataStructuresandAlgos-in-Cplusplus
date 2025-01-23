#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

struct Solution {
    // Function to solve the Coin Change problem using topological sorting
    int coinChange(const std::vector<int>& coins, int amount) {
        int V = amount + 1;  // Vertices represent amounts from 0 to amount
        std::vector<std::vector<int>> adjList(V);

        // Build the adjacency list for the DAG
        for (int i = 0; i < V; ++i) {
            for (int coin : coins) {
                if (i + coin <= amount) {
                    adjList[i].push_back(i + coin);
                }
            }
        }

        // Perform topological sorting using Kahn's algorithm
        std::vector<int> topoOrder = kahnTopologicalSort(V, adjList);

        // DP array to store the minimum number of coins for each amount
        std::vector<int> dp(V, std::numeric_limits<int>::max());
        dp[0] = 0;  // Base case: 0 coins needed to make amount 0

        // Process each vertex (amount) in topological order
        for (int u : topoOrder) {
            if (dp[u] != std::numeric_limits<int>::max()) {
                for (int v : adjList[u]) {
                    dp[v] = std::min(dp[v], dp[u] + 1);
                }
            }
        }

        return dp[amount] == std::numeric_limits<int>::max() ? -1 : dp[amount];
    }

    // Function to perform Kahn's algorithm for topological sorting
    std::vector<int> kahnTopologicalSort(int V, const std::vector<std::vector<int>>& adjList) {
        std::vector<int> inDegree(V, 0);
        std::queue<int> topoQueue;
        std::vector<int> topoOrder;

        // Compute in-degree for each vertex
        for (int u = 0; u < V; ++u) {
            for (int v : adjList[u]) {
                inDegree[v]++;
            }
        }

        // Push all vertices with 0 in-degree to the queue
        for (int i = 0; i < V; ++i) {
            if (inDegree[i] == 0) {
                topoQueue.push(i);
            }
        }

        // Process the vertices in topological order
        while (!topoQueue.empty()) {
            int u = topoQueue.front();
            topoQueue.pop();
            topoOrder.push_back(u);

            for (int v : adjList[u]) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    topoQueue.push(v);
                }
            }
        }

        return topoOrder;
    }
};

int main() {
    Solution sol;
    std::vector<int> coins = {1, 2, 5};  // Coin denominations
    int amount = 11;  // Total amount to make

    int result = sol.coinChange(coins, amount);
    std::cout << "Minimum coins required: " << result << std::endl;

    return 0;
}
