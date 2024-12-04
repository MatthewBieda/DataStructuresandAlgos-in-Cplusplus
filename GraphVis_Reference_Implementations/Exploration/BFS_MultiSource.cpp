#include <vector>
#include <iostream>
#include <queue>

class Solution {
public:
    // Function to compute the minimum distance of each cell from the nearest 0
    std::vector<std::vector<int>> updateMatrix(const std::vector<std::vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();

        // Directions for moving up, down, left, and right
        const std::vector<std::pair<int, int>> directions{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        // Output matrix to store the result
        std::vector<std::vector<int>> output(m, std::vector<int>(n, -1));

        // Queue for BFS, stores the coordinates of cells
        std::queue<std::pair<int, int>> queue;

        // Step 1: Initialize the queue with all 0-cells and mark them as visited
        for (int row = 0; row < m; ++row) {
            for (int col = 0; col < n; ++col) {
                if (mat[row][col] == 0) {
                    queue.push({row, col});
                    output[row][col] = 0; // Distance to itself is 0
                }
            }
        }

        // Step 2: BFS to update distances
        while (!queue.empty()) {
            auto [row, col] = queue.front();
            queue.pop();

            for (const auto& [dr, dc] : directions) {
                int newRow = row + dr;
                int newCol = col + dc;

                // Check bounds and unvisited status
                if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n && output[newRow][newCol] == -1) {
                    queue.push({newRow, newCol});
                    output[newRow][newCol] = output[row][col] + 1; // Update distance
                }
            }
        }

        return output;
    }
};

int main() {
    Solution solution;

    std::vector<std::vector<int>> mat = {
        {0, 0, 0},
        {0, 1, 0},
        {1, 1, 1}
    };

    // Compute the output matrix
    std::vector<std::vector<int>> result = solution.updateMatrix(mat);

    // Print the result matrix
    for (const std::vector<int>& row : result) {
        for (int cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
