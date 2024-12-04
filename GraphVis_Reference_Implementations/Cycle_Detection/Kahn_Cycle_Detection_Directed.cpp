#include <vector>
#include <queue>
#include <iostream>

class Solution {
public:
    // Function to detect cycles in a directed graph using Kahn's Algorithm
    bool hasCycle(int numCourses, const std::vector<std::vector<int>>& prerequisites) {
        // Step 1: Initialize adjacency list and in-degree array
        std::vector<std::vector<int>> adj(numCourses); // Adjacency list
        std::vector<int> inDegree(numCourses, 0);      // In-degree array

        // Step 2: Build the graph
        for (const auto& prereq : prerequisites) {
            int course = prereq[0];
            int dependency = prereq[1];
            adj[dependency].push_back(course); // Edge from dependency -> course
            inDegree[course]++;
        }

        // Step 3: Initialize the queue with nodes having in-degree 0
        std::queue<int> zeroInDegreeQueue;
        for (int i = 0; i < numCourses; ++i) {
            if (inDegree[i] == 0) {
                zeroInDegreeQueue.push(i);
            }
        }

        // Step 4: Process nodes with in-degree 0
        int processedNodes = 0; // Count of processed nodes
        while (!zeroInDegreeQueue.empty()) {
            int node = zeroInDegreeQueue.front();
            zeroInDegreeQueue.pop();
            ++processedNodes;

            // Reduce the in-degree of all neighbors
            for (const auto& neighbor : adj[node]) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    zeroInDegreeQueue.push(neighbor);
                }
            }
        }

        // Step 5: Check if all nodes were processed
        return processedNodes != numCourses; // True if a cycle exists
    }
};

int main() {
    Solution solution;
    int numCourses = 4;
    std::vector<std::vector<int>> prerequisites = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};

    if (solution.hasCycle(numCourses, prerequisites)) {
        std::cout << "The graph contains a cycle.\n";
    } else {
        std::cout << "The graph does not contain a cycle.\n";
    }

    return 0;
}
