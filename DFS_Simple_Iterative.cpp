#include <vector>
#include <iostream>
#include <stack>

class Solution {
public:
    bool canVisitAllRooms(std::vector<std::vector<int>>& rooms) {
        std::vector<bool> visited(rooms.size(), false);
        std::stack<int> stack;

        stack.push(0);
        visited[0] = true;

        while (!stack.empty()) {
            int node = stack.top();
            stack.pop();

            for (const int& neighbor: rooms[node]) {
                if (!visited[neighbor]) {
                    stack.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }

        for (const bool& v: visited) {
            if (!v) {
                return false;
            }
        }

        return true;
    }
};

int main() {
    Solution solution;

    std::vector<std::vector<int>> rooms{{1,3}, {3,0,1}, {2}, {0}};
    std::vector<std::vector<int>> rooms2{{1}, {2}, {3}, {}};

    bool valid_case = solution.canVisitAllRooms(rooms);
    bool invalid_case = solution.canVisitAllRooms(rooms2);

    std::cout << valid_case << std::endl;
    std::cout << invalid_case << std::endl;
}
