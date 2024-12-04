#include <vector>
#include <deque>
#include <limits>
#include <iostream>
#include <stdexcept>

class Solution {
public:
    int findTheCity(int n, std::vector<std::vector<int>>& edges, int distanceThreshold) {
        // Initialize adjacency list and shortest path matrix
        std::vector<std::vector<std::pair<int, int>>> adjacencyList(n);
        std::vector<std::vector<int>> shortestPathMatrix(n, std::vector<int>(n, std::numeric_limits<int>::max()));

        // Self-loops have zero distance
        for (int i = 0; i < n; i++) {
            shortestPathMatrix[i][i] = 0;
        }

        // Build adjacency list from edge list
        for (const auto& edge : edges) {
            int start = edge[0];
            int end = edge[1];
            int weight = edge[2];
            adjacencyList[start].emplace_back(end, weight);
            adjacencyList[end].emplace_back(start, weight);
        }

        // Run SPFA for each city to calculate shortest paths
        for (int i = 0; i < n; i++) {
            try {
                spfa(n, adjacencyList, shortestPathMatrix[i], i);
            } catch (const std::runtime_error& e) {
                std::cerr << "Error: " << e.what() << " for source city " << i << std::endl;
                return -1;
            }
        }

        // Determine the city with the fewest reachable cities
        return getCityWithFewestReachable(n, shortestPathMatrix, distanceThreshold);
    }

private:
    // SPFA implementation to find shortest paths from a single source
    void spfa(int n, const std::vector<std::vector<std::pair<int, int>>>& adjacencyList,
              std::vector<int>& shortestPathDistances, int source) {
        std::deque<int> queue;                 // Deque for SPFA
        std::vector<bool> inQueue(n, false);   // Track whether a node is in the queue
        std::vector<int> updateCount(n, 0);    // Count updates to detect negative cycles

        shortestPathDistances[source] = 0;     // Distance to self is zero
        queue.push_back(source);               // Start with the source node
        inQueue[source] = true;

        while (!queue.empty()) {
            int currentCity = queue.front();
            queue.pop_front();
            inQueue[currentCity] = false;

            // Relax all neighbors of the current city
            for (const auto& [neighborCity, edgeWeight] : adjacencyList[currentCity]) {
                if (shortestPathDistances[neighborCity] > shortestPathDistances[currentCity] + edgeWeight) {
                    shortestPathDistances[neighborCity] = shortestPathDistances[currentCity] + edgeWeight;

                    // Add the neighbor to the queue if not already present
                    if (!inQueue[neighborCity]) {
                        queue.push_back(neighborCity);
                        inQueue[neighborCity] = true;

                        // Increment update count to check for negative weight cycles
                        updateCount[neighborCity]++;
                        if (updateCount[neighborCity] > n) {
                            throw std::runtime_error("Negative weight cycle detected");
                        }
                    }
                }
            }
        }
    }

    // Find the city with the fewest reachable cities within the distance threshold
    int getCityWithFewestReachable(int n, const std::vector<std::vector<int>>& shortestPathMatrix,
                                   int distanceThreshold) {
        int cityWithFewestReachable = -1;
        int fewestReachableCount = n; // Maximum possible count

        for (int city = 0; city < n; city++) {
            int reachableCount = 0;

            // Count reachable cities for the current city
            for (int neighbor = 0; neighbor < n; neighbor++) {
                if (city != neighbor && shortestPathMatrix[city][neighbor] <= distanceThreshold) {
                    reachableCount++;
                }
            }

            // Update result if this city has fewer reachable cities or is a tie (favor higher index)
            if (reachableCount <= fewestReachableCount) {
                fewestReachableCount = reachableCount;
                cityWithFewestReachable = city;
            }
        }

        return cityWithFewestReachable;
    }
};

int main() {
    Solution solution;

    // Input: Number of cities, edges, and distance threshold
    int cities = 4;
    std::vector<std::vector<int>> edges{{0, 1, 3}, {1, 2, 1}, {1, 3, 4}, {2, 3, 1}};
    int distanceThreshold = 4;

    try {
        int result = solution.findTheCity(cities, edges, distanceThreshold);
        std::cout << "City with the fewest reachable cities: " << result << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
