#include <vector>
#include <queue>
#include <iostream>

class Solution {
public:
    // Function to determine if a valid path exists between `start` and `end` in an undirected graph
    bool validPath(int n, const std::vector<std::vector<int>>& edges, int start, int end) {
        // Edge case: If the graph has no edges, the path is valid only if start == end
        if (edges.empty()) {
            return start == end;
        }

        // Step 1: Build the adjacency list for the graph
        std::vector<std::vector<int>> adjacencyList(n);
        for (const auto& edge : edges) {
            adjacencyList[edge[0]].push_back(edge[1]);
            adjacencyList[edge[1]].push_back(edge[0]);
        }

        // Step 2: Perform BFS to check for a path from `start` to `end`
        std::queue<int> q;
        std::vector<bool> visited(n, false);

        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int currentNode = q.front();
            q.pop();

            // Check if we reached the target node
            if (currentNode == end) {
                return true;
            }

            // Visit all unvisited neighbors
            for (int neighbor : adjacencyList[currentNode]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        // If we exhaust the BFS without finding `end`, no path exists
        return false;
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
