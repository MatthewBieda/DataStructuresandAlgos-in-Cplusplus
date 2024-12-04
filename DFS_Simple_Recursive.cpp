#include <vector>
#include <iostream>

class Solution {
public:
    bool canVisitAllRooms(const std::vector<std::vector<int>>& rooms) {
        int n = rooms.size();                    // Number of rooms
        std::vector<bool> visited(n, false);     // Tracks if a room has been visited

        dfs(0, visited, rooms);                  // Start DFS from room 0

        // Check if all rooms are visited
        for (const bool& v : visited) {
            if (!v) {
                return false;
            }
        }

        return true;
    }

private:
    void dfs(int room, std::vector<bool>& visited, const std::vector<std::vector<int>>& rooms) {
        visited[room] = true;                    // Mark current room as visited

        // Explore all keys (neighbors) in the current room
        for (const int& neighbor : rooms[room]) {
            if (!visited[neighbor]) {
                dfs(neighbor, visited, rooms);
            }
        }
    }
};

int main() {
    Solution solution;

    // Test cases
    std::vector<std::vector<int>> rooms1{{1, 3}, {3, 0, 1}, {2}, {0}};
    std::vector<std::vector<int>> rooms2{{1}, {2}, {3}, {}};

    // Check the results
    bool case1 = solution.canVisitAllRooms(rooms1); // Should return false
    bool case2 = solution.canVisitAllRooms(rooms2); // Should return true

    std::cout << "Case 1: " << (case1 ? "True" : "False") << std::endl;
    std::cout << "Case 2: " << (case2 ? "True" : "False") << std::endl;

    return 0;
}
