#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <iostream>

using namespace std;

class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        // Adjacency list to store the graph
        vector<vector<pair<int, int>>> adjacencyList(n);
        // Matrix to store shortest path distances from each city
        vector<vector<int>> shortestPathMatrix(n, vector<int>(n, numeric_limits<int>::max()));

        // Initialize adjacency list and shortest path matrix
        for (int i = 0; i < n; i++) {
            shortestPathMatrix[i][i] = 0;  // Distance to itself is zero
        }

        // Populate the adjacency list with edges
        for (const auto& edge : edges) {
            int start = edge[0];
            int end = edge[1];
            int weight = edge[2];
            adjacencyList[start].emplace_back(end, weight);
            adjacencyList[end].emplace_back(start,
                                            weight);  // For undirected graph
        }

        // Compute shortest paths from each city using SPFA algorithm
        for (int i = 0; i < n; i++) {
            spfa(n, adjacencyList, shortestPathMatrix[i], i);
        }

        // Find the city with the fewest number of reachable cities within the
        // distance threshold
        return getCityWithFewestReachable(n, shortestPathMatrix,
                                          distanceThreshold);
    }

    // SPFA algorithm to find shortest paths from a source city
    void spfa(int n, const vector<vector<pair<int, int>>>& adjacencyList,
              vector<int>& shortestPathDistances, int source) {
        // Queue to process nodes with updated shortest path distances
        queue<int> queue;
        vector<int> updateCount(n, 0);
        queue.push(source);
        fill(shortestPathDistances.begin(), shortestPathDistances.end(), std::numeric_limits<int>::max());
        shortestPathDistances[source] = 0;  // Distance to source itself is zero

        // Process nodes in queue
        while (!queue.empty()) {
            int currentCity = queue.front();
            queue.pop();
            for (const auto& [neighborCity, edgeWeight] :
                 adjacencyList[currentCity]) {
                if (shortestPathDistances[neighborCity] >
                    shortestPathDistances[currentCity] + edgeWeight) {
                    shortestPathDistances[neighborCity] =
                        shortestPathDistances[currentCity] + edgeWeight;
                    updateCount[neighborCity]++;
                    queue.push(neighborCity);

                    // Detect negative weight cycles (not expected in this
                    // problem)
                    if (updateCount[neighborCity] > n) {
                        cerr << "Negative weight cycle detected" << endl;
                    }
                }
            }
        }
    }

    // Determine the city with the fewest number of reachable cities within the
    // distance threshold
    int getCityWithFewestReachable(
        int n, const vector<vector<int>>& shortestPathMatrix,
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
                if (shortestPathMatrix[i][j] <= distanceThreshold) {
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
