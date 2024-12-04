#include <vector>
#include <iostream>
#include <limits>

class Solution {
public:
    int findCheapestPrice(int n, const std::vector<std::vector<int>>& flights, int src, int dst, int k) {
        // Initialize distance vectors with "infinity" for unreachable nodes
        std::vector<int> previousCost(n, std::numeric_limits<int>::max());
        std::vector<int> currentCost(n, std::numeric_limits<int>::max());
        
        // The cost to reach the source is 0
        previousCost[src] = 0;

        // Relax edges up to k+1 times (at most k stops means k+1 edges)
        for (int iteration = 0; iteration <= k; ++iteration) {
            bool updated = false;

            // Process each flight
            for (const auto& flight : flights) {
                int from = flight[0];
                int to = flight[1];
                int cost = flight[2];

                // Relax the edge if the "from" node has been reached
                if (previousCost[from] != std::numeric_limits<int>::max() &&
                    currentCost[to] > previousCost[from] + cost) {
                    currentCost[to] = previousCost[from] + cost;
                    updated = true;
                }
            }

            // Early termination: If no updates occurred, the solution is found
            if (!updated) break;

            // Prepare for the next iteration
            previousCost = currentCost;
        }

        // If the destination remains unreachable, return -1
        return currentCost[dst] == std::numeric_limits<int>::max() ? -1 : currentCost[dst];
    }
};

int main() {
    Solution solution;

    // Number of cities and flight information
    int cities = 4;
    std::vector<std::vector<int>> flights {
        {0, 1, 100},
        {1, 2, 100},
        {2, 0, 100},
        {1, 3, 600},
        {2, 3, 200}
    };

    int source = 0;       // Starting city
    int destination = 3;  // Destination city
    int stops = 1;        // Maximum number of stops allowed

    int result = solution.findCheapestPrice(cities, flights, source, destination, stops);

    if (result == -1) {
        std::cout << "No route available within " << stops << " stops." << std::endl;
    } else {
        std::cout << "Cheapest price from " << source << " to " << destination
                  << " with at most " << stops << " stops: " << result << std::endl;
    }

    return 0;
}
