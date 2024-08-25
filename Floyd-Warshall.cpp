#include <vector>
#include <iostream>
#include <algorithm>


class Solution {
public:
    int findTheCity(int n, std::vector<std::vector<int>>& edges, int distanceThreshold) {
        // Large value to represent infinity
        const int INF = 1e9 + 7;
        // Distance matrix to store shortest paths between all pairs of cities
        std::vector<std::vector<int>> distanceMatrix(n, std::vector<int>(n, INF));

        // Initialize distance matrix
        for (int i = 0; i < n; i++) {
            distanceMatrix[i][i] = 0;  // Distance to itself is zero
        }

        // Populate the distance matrix with initial edge weights
        for (const auto& edge : edges) {
            int start = edge[0];
            int end = edge[1];
            int weight = edge[2];
            distanceMatrix[start][end] = weight;
            distanceMatrix[end][start] = weight;  // For undirected graph
        }

        // Compute shortest paths using Floyd-Warshall algorithm
        floyd(n, distanceMatrix);

        // Find the city with the fewest number of reachable cities within the
        // distance threshold
        return getCityWithFewestReachable(n, distanceMatrix, distanceThreshold);
    }

private:
    // Floyd-Warshall algorithm to compute shortest paths between all pairs of
    // cities
    void floyd(int n, std::vector<std::vector<int>>& distanceMatrix) {
        // Update distances for each intermediate city
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    // Update shortest path from i to j through k
                    distanceMatrix[i][j] =
                        std::min(distanceMatrix[i][j],
                            distanceMatrix[i][k] + distanceMatrix[k][j]);
                }
            }
        }
    }

    // Determine the city with the fewest number of reachable cities within the
    // distance threshold
    int getCityWithFewestReachable(int n,
                                   const std::vector<std::vector<int>>& distanceMatrix,
                                   int distanceThreshold) {
        int cityWithFewestReachable = -1;
        int fewestReachableCount = n;

        // Count number of cities reachable within the distance threshold for
        // each city
        for (int i = 0; i < n; i++) {
            int reachableCount = 0;
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    continue;
                }  // Skip self
                if (distanceMatrix[i][j] <= distanceThreshold) {
                    reachableCount++;
                }
            }
            // Update the city with the fewest reachable cities
            if (reachableCount <= fewestReachableCount) {
                fewestReachableCount = reachableCount;
                cityWithFewestReachable = i;
            }
        }
        return cityWithFewestReachable;
    }
};

int main() {
    Solution solution;

    int cities = 4;
    std::vector<std::vector<int>> edges{{0,1,3}, {1,2,1}, {1,3,4}, {2,3,1}};
    int distance_threshold = 4;

    int result = solution.findTheCity(cities, edges, distance_threshold);

    std::cout << result << std::endl;
    
    return 0;
}
