#include <vector>
#include <queue>
#include <iostream>

class Solution {
public:
    // Find all paths from source to target in a directed graph
    std::vector<std::vector<int>> allPathsSourceTarget(const std::vector<std::vector<int>>& graph) {
        std::vector<std::vector<int>> paths; // Store all valid paths
        if (graph.empty()) {
            return paths;
        }

        std::queue<std::vector<int>> queue; // BFS queue to store paths
        queue.push({0}); // Start from the source node

        int target = graph.size() - 1;

        // BFS traversal
        while (!queue.empty()) {
            std::vector<int> currentPath = queue.front();
            queue.pop();

            int currentNode = currentPath.back(); // Get the last node in the current path

            // Explore neighbors of the current node
            for (int neighbor : graph[currentNode]) {
                std::vector<int> newPath = currentPath; // Create a new path
                newPath.push_back(neighbor); // Add the neighbor to the path

                if (neighbor == target) {
                    // If the neighbor is the target, store the path
                    paths.push_back(newPath);
                } else {
                    // Otherwise, continue exploring
                    queue.push(newPath);
                }
            }
        }

        return paths;
    }
};

int main() {
    Solution solution;

    // Define the directed graph as an adjacency list
    std::vector<std::vector<int>> graph = {
        {4, 3, 1}, // Node 0 has edges to nodes 4, 3, 1
        {3, 2, 4}, // Node 1 has edges to nodes 3, 2, 4
        {3},       // Node 2 has an edge to node 3
        {4},       // Node 3 has an edge to node 4
        {}         // Node 4 has no outgoing edges
    };

    // Find all paths from source (node 0) to target (last node)
    std::vector<std::vector<int>> paths = solution.allPathsSourceTarget(graph);

    // Print the paths
    std::cout << "All paths from source to target:" << std::endl;
    for (const auto& path : paths) {
        std::cout << "[ ";
        for (int node : path) {
            std::cout << node << " ";
        }
        std::cout << "]" << std::endl;
    }

    return 0;
}
