#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

class Solution {
public:
    std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>>& prerequisites) {
        std::vector<int> answer;

        std::vector<std::vector<int>> adj(numCourses);
        std::vector<int> inDegree(numCourses, 0);

        for (const std::vector<int>& prereq: prerequisites) {
            adj[prereq[0]].push_back(prereq[1]);
            inDegree[prereq[1]]++;
        }

        std::queue<int> queue;
        for (int i = 0; i < numCourses; ++i)  {
            if (inDegree[i] == 0) {
                queue.push(i);
            }
        }

        while (!queue.empty()) {
            int elem = queue.front();
            queue.pop();

            answer.push_back(elem);

            for (const int& neighbor: adj[elem]) {
                inDegree[neighbor]--;
                
                if (inDegree[neighbor] == 0) {
                    queue.push(neighbor);
                }
            }
        }

        if (answer.size() == numCourses) {
            std::reverse(answer.begin(), answer.end());
            return answer;
        } else {
            return {};
        }
    }
};

int main() {
    Solution solution;
    int numCourses = 4;
    std::vector<std::vector<int>> prerequisites = {{1,0},{2,0},{3,1},{3,2}};

    std::vector<int> order = solution.findOrder(numCourses, prerequisites);

    for (int course: order) {
	std::cout << course << " ";
    }
    std::cout << std::endl;

    return 0;
}
