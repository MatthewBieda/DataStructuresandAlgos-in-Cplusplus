#include <vector>
#include <iostream>
#include <queue>

class Solution {
public:
	std::vector<std::vector<int>> updateMatrix(std::vector<std::vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();

        std::vector<std::vector<int>> directions{{0,1}, {0,-1}, {1,0}, {-1,0}};

        std::vector<std::vector<int>> output = mat;
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        std::queue<std::pair<int, int>> queue;

        for (int row = 0; row < m; ++row) {
            for (int col = 0; col < n; ++col) {
                if (mat[row][col] == 0) {
                    queue.push({row, col});
                    visited[row][col] = true;
                }
            }
        }

        while (!queue.empty()) {
            int level_size = queue.size();

            for (int i = 0; i < level_size; ++i) {
                const auto [row, col] = queue.front();
                queue.pop();

                for (const std::vector<int>& direction: directions) {
                    int newRow = row + direction[0];
                    int newCol = col + direction[1];

                    if (newRow >= 0 && newCol >= 0 && newRow < m && newCol < n && !visited[newRow][newCol]) {
                        queue.push({newRow, newCol});
                        visited[newRow][newCol] = true;

                        output[newRow][newCol] = output[row][col] + 1;
                    }
                }
            }
        }

        return output;
    }
};

int main() {
    Solution solution;

    std::vector<std::vector<int>> mat{{0,0,0}, {0,1,0}, {1,1,1}};

    std::vector<std::vector<int>> result = solution.updateMatrix(mat);

    for (const std::vector<int>& row: result) {
	std::cout << row[0] << row[1] << row[2] << std::endl;
    }
}
