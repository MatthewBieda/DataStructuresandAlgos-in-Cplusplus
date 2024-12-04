#include <vector>
#include <iostream>
#include <algorithm>

class Solution {
public:
    int findTheCity(int n, std::vector<std::vector<int>>& edges, int distanceThreshold) {
        const int INF = 1e9 + 7;  // Large value to represent "infinity"

        // Distance matrix to store shortest paths between all pairs of cities
        std::vector<std::vector<int>> distanceMatrix(n, std::vector<int>(n, INF));

        // Initialize self-distances to zero
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

        // Compute shortest paths between all pairs of cities
        floydWarshall(n, distanceMatrix);

        // Find the city with the fewest number of reachable cities within the threshold
        return findCityWithFewestReachable(n, distanceMatrix, distanceThreshold);
    }

private:
    // Floyd-Warshall algorithm to compute shortest paths
    void floydWarshall(int n, std::vector<std::vector<int>>& distanceMatrix) {
        for (int k = 0; k < n; k++) {  // Intermediate nodes
            for (int i = 0; i < n; i++) {  // Source nodes
                for (int j = 0; j < n; j++) {  // Destination nodes
                    // Update shortest path from i to j via k
                    distanceMatrix[i][j] = std::min(distanceMatrix[i][j],
                                                   distanceMatrix[i][k] + distanceMatrix[k][j]);
                }
            }
        }
    }

    // Find the city with the fewest reachable neighbors within the distance threshold
    int findCityWithFewestReachable(int n, const std::vector<std::vector<int>>& distanceMatrix, int distanceThreshold) {
        int cityWithFewestReachable = -1;
        int fewestReachableCount = n;

        // Iterate over each city to count reachable neighbors
        for (int i = 0; i < n; i++) {
            int reachableCount = 0;
            for (int j = 0; j < n; j++) {
                if (i != j && distanceMatrix[i][j] <= distanceThreshold) {
                    reachableCount++;
                }
            }

            // Update city with fewer reachable neighbors (prefer higher-index cities in ties)
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

    // Define the input: number of cities, edges, and the distance threshold
    int cities = 4;
    std::vector<std::vector<int>> edges = {{0, 1, 3}, {1, 2, 1}, {1, 3, 4}, {2, 3, 1}};
    int distanceThreshold = 4;

    // Compute the result
    int result = solution.findTheCity(cities, edges, distanceThreshold);

    // Output the city with the fewest reachable neighbors
    std::cout << "City with the fewest reachable cities within distance " << distanceThreshold << ": " << result << std::endl;

    return 0;
}
