#include <vector>
#include <iostream>

class Solution {
public:
    bool canVisitAllRooms(std::vector<std::vector<int>>& rooms) {
        std::vector<bool> visited(rooms.size(), false);
        visited[0] = true;

        dfs(0, visited, rooms);

        for (const bool& v: visited) {
            if (!v) {
                return false;
            }
        } 

        return true;
    }

private:
    void dfs(int node, std::vector<bool>& visited, const std::vector<std::vector<int>>& rooms) {
        visited[node] = true;

        for (const int& neighbor: rooms[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, visited, rooms);
            }
        }
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
