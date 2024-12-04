#include <iostream>
#include <vector>

class Solution {
public:
    // Depth-First Search to explore all paths
    void dfs(const std::vector<std::vector<int>>& graph, int node, std::vector<int>& path,
             std::vector<std::vector<int>>& paths) {
        path.push_back(node); // Add the current node to the path

        if (node == graph.size() - 1) {
            // If the target node is reached, add the path to the result
            paths.push_back(path);
        } else {
            // Recursively explore neighbors of the current node
            for (int nextNode : graph[node]) {
                dfs(graph, nextNode, path, paths);
            }
        }

        path.pop_back(); // Backtrack to explore other paths
    }

    std::vector<std::vector<int>> allPathsSourceTarget(const std::vector<std::vector<int>>& graph) {
        std::vector<std::vector<int>> paths; // Store all valid paths
        if (graph.empty()) {
            return paths; // Return empty result if the graph is empty
        }

        std::vector<int> path; // Track the current path
        dfs(graph, 0, path, paths); // Start DFS from the source node (0)
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
