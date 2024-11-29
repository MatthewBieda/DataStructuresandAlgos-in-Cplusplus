#include <vector>
#include <queue>
#include <iostream>

class Solution {
public:
    bool hasCycle(int numCourses, const std::vector<std::pair<int, int>>& prerequisites) {
        std::vector<std::vector<int>> adj(numCourses);
        std::vector<int> inDegree(numCourses, 0);

        // Build the adjacency list and compute in-degrees
        for (const auto& [course, prereq] : prerequisites) {
            adj[prereq].push_back(course); // Edge from prereq -> course
            inDegree[course]++;
        }

        // Initialize the queue with nodes having in-degree 0
        std::queue<int> queue;
        for (int i = 0; i < numCourses; ++i) {
            if (inDegree[i] == 0) {
                queue.push(i);
            }
        }

        int processedNodes = 0;

        // Process the nodes
        while (!queue.empty()) {
            int node = queue.front();
            queue.pop();
            ++processedNodes;

            for (const auto& neighbor : adj[node]) {
                inDegree[neighbor]--;

                if (inDegree[neighbor] == 0) {
                    queue.push(neighbor);
                }
            }
        }

        // If we processed all nodes, there's no cycle
        return processedNodes != numCourses;
    }
};

int main() {
    Solution solution;
    int numCourses = 4;
    std::vector<std::pair<int, int>> prerequisites = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};

    if (solution.hasCycle(numCourses, prerequisites)) {
        std::cout << "The graph contains a cycle.\n";
    } else {
        std::cout << "The graph does not contain a cycle.\n";
    }

    return 0;
}
