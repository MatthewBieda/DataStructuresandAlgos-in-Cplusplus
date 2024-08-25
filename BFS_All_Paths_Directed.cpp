#include <vector>
#include <queue>
#include <iostream>

class Solution {
public:
	std::vector<std::vector<int>> allPathsSourceTarget(std::vector<std::vector<int>>& graph) {
        std::vector<std::vector<int>> paths;
        if (graph.size() == 0) {
            return paths;
        }

        std::vector<int> path;
        std::queue<std::vector<int>> q;
        path.push_back(0);
        q.push(path);

        while (!q.empty()) {
            std::vector<int> currentPath = q.front();
            q.pop();

            int node = currentPath.back();
            
            for (int neighbor: graph[node]) {
                std::vector<int> tmpPath(currentPath.begin(), currentPath.end());
                tmpPath.push_back(neighbor);
                if (neighbor == graph.size() -1 ) {
                    paths.push_back(tmpPath);
                } else {
                    q.push(tmpPath);
                }
            }
        }
        return paths;
    }
};

int main() {
    Solution solution;

    std::vector<std::vector<int>> graph = {{4,3,1}, {3,2,4}, {3}, {4}, {}};
  
    std::vector<std::vector<int>> output_vector = solution.allPathsSourceTarget(graph);
    
    for (const std::vector<int>& output: output_vector) {
	std::cout << "[ ";
	for (const int& node: output) {
	    std::cout << node << " ";
	}
	std::cout << "]" << std::endl;
    }

    return 0;
}
