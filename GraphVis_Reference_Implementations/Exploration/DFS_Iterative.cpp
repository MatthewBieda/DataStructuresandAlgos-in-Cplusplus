#include <vector>
#include <iostream>
#include <stack>

class Solution {
public:
    bool canVisitAllRooms(const std::vector<std::vector<int>>& rooms) {
        int n = rooms.size();                     // Number of rooms
        std::vector<bool> visited(n, false);      // Tracks if a room has been visited
        std::stack<int> stack;                    // Stack for DFS traversal

        stack.push(0);                            // Start DFS from room 0
        visited[0] = true;                        // Mark room 0 as visited
        int visitedCount = 1;                     // Counter for visited rooms

        while (!stack.empty()) {
            int currentRoom = stack.top();
            stack.pop();

            // Explore all neighbors (keys to other rooms)
            for (const int& neighbor : rooms[currentRoom]) {
                if (!visited[neighbor]) {
                    stack.push(neighbor);
                    visited[neighbor] = true;     // Mark the room as visited
                    visitedCount++;

                    // Early exit: All rooms visited
                    if (visitedCount == n) {
                        return true;
                    }
                }
            }
        }

        // If all rooms are visited, visitedCount should equal n
        return visitedCount == n;
    }
};

int main() {
    Solution solution;

    // Test cases
    std::vector<std::vector<int>> rooms1{{1, 3}, {3, 0, 1}, {2}, {0}};
    std::vector<std::vector<int>> rooms2{{1}, {2}, {3}, {}};

    bool case1 = solution.canVisitAllRooms(rooms1); // Should return false
    bool case2 = solution.canVisitAllRooms(rooms2); // Should return true

    std::cout << "Case 1: " << (case1 ? "True" : "False") << std::endl;
    std::cout << "Case 2: " << (case2 ? "True" : "False") << std::endl;

    return 0;
}
