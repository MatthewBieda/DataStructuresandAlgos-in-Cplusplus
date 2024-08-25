#include <iostream>
#include <vector>

class Solution {
public:
    void dfs(std::vector<std::vector<int>>& graph, int node, std::vector<int>& path,
             std::vector<std::vector<int>>& paths) {
        path.push_back(node);
        if (node == graph.size() - 1) {
            paths.emplace_back(path);
            return;
        }
        std::vector<int> nextNodes = graph[node];
        for (int nextNode : nextNodes) {
            dfs(graph, nextNode, path, paths);
            path.pop_back();
        }
    }

    std::vector<std::vector<int>> allPathsSourceTarget(std::vector<std::vector<int>>& graph) {
        std::vector<std::vector<int>> paths;
        if (graph.size() == 0) {
            return paths;
        }
        std::vector<int> path;
        dfs(graph, 0, path, paths);
        return paths;
    }
};

int main() {
    Solution solution;
    std::vector<std::vector<int>> graph = {{4, 3, 1}, {3, 2, 4}, {3}, {4}, {}};
    std::vector<std::vector<int>> output_vector = solution.allPathsSourceTarget(graph);

    for (const std::vector<int>& path : output_vector) {
        std::cout << "[ ";
        for (int node : path) {
            std::cout << node << " ";
        }
        std::cout << "]" << std::endl;
    }

    return 0;
}

