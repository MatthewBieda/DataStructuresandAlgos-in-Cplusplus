#include <vector>
#include <iostream>

class Solution {
public:
    // Function to determine if a valid path exists between `start` and `end` in an undirected graph
    bool validPath(int n, const std::vector<std::vector<int>>& edges, int start, int end) {
        // Edge case: If there are no edges, the path is valid only if `start == end`
        if (edges.empty()) {
            return start == end;
        }

        // Step 1: Build the adjacency list for the graph
        std::vector<std::vector<int>> adjacencyList(n);
        for (const auto& edge : edges) {
            adjacencyList[edge[0]].push_back(edge[1]);
            adjacencyList[edge[1]].push_back(edge[0]); // Undirected graph
        }

        // Step 2: Use a visited array to prevent revisiting nodes
        std::vector<bool> visited(n, false);

        // Step 3: Perform DFS
        return dfs(adjacencyList, start, end, visited);
    }

private:
    // Recursive DFS function
    bool dfs(const std::vector<std::vector<int>>& adj, int current, int target, std::vector<bool>& visited) {
        // If we reach the target node, a path exists
        if (current == target) {
            return true;
        }

        // Mark the current node as visited
        visited[current] = true;

        // Visit all unvisited neighbors
        for (int neighbor : adj[current]) {
            if (!visited[neighbor]) {
                if (dfs(adj, neighbor, target, visited)) {
                    return true; // Stop searching once a path is found
                }
            }
        }

        return false; // No path found
    }
};

int main() {
    Solution solution;

    int n = 3; // Number of nodes
    int start = 0; // Starting node
    int destination = 2; // Target node

    std::vector<std::vector<int>> edges = {
        {0, 1}, {1, 2}, {2, 0}
    }; // Edges in the graph

    bool isValid = solution.validPath(n, edges, start, destination);

    std::cout << (isValid ? "Path exists" : "No path exists") << std::endl;

    return 0;
}
