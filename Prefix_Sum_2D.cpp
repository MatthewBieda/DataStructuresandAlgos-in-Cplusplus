#include <vector>
#include <iostream>

int main() {
    std::vector<std::vector<int>> mat{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int m = mat.size();
    int n = mat[0].size();
    
    // Initialize the 2D prefix sum matrix with the same size as the input matrix
    std::vector<std::vector<int>> prefix_sum(m, std::vector<int>(n, 0));

    // Compute the 2D prefix sum
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            prefix_sum[i][j] = mat[i][j];

            if (i > 0) 
                prefix_sum[i][j] += prefix_sum[i-1][j]; // Add above element
            
            if (j > 0) 
                prefix_sum[i][j] += prefix_sum[i][j-1]; // Add left element
            
            if (i > 0 && j > 0) 
                prefix_sum[i][j] -= prefix_sum[i-1][j-1]; // Subtract overlap
        }
    }

    // Output the 2D prefix sum matrix
    for (const auto& row : prefix_sum) {
        for (const auto& psum : row) {
            std::cout << psum << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

