#include <vector>
#include <queue>
#include <iostream>

class Solution {
public:
    std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>>& prerequisites) {
        std::vector<int> result;

        // Adjacency list to represent the graph
        std::vector<std::vector<int>> adj(numCourses);
        // In-degree array to track the number of incoming edges
        std::vector<int> inDegree(numCourses, 0);

        // Build the graph and populate in-degree array
        for (const auto& prereq : prerequisites) {
            adj[prereq[1]].push_back(prereq[0]);
            inDegree[prereq[0]]++;
        }

        // Queue for nodes with no incoming edges (in-degree == 0)
        std::queue<int> queue;
        for (int i = 0; i < numCourses; ++i) {
            if (inDegree[i] == 0) {
                queue.push(i);
            }
        }

        // Process nodes in topological order
        while (!queue.empty()) {
            int node = queue.front();
            queue.pop();
            result.push_back(node);

            // Reduce the in-degree of neighbors
            for (int neighbor : adj[node]) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    queue.push(neighbor);
                }
            }
        }

        // If we processed all nodes, return the result; otherwise, return empty (cycle detected)
        return result.size() == numCourses ? result : std::vector<int>{};
    }
};

int main() {
    Solution solution;
    int numCourses = 4;
    std::vector<std::vector<int>> prerequisites = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};

    std::vector<int> order = solution.findOrder(numCourses, prerequisites);

    if (!order.empty()) {
        std::cout << "Topological order: ";
        for (int course : order) {
            std::cout << course << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "No valid topological order exists (cycle detected)." << std::endl;
    }

    return 0;
}
