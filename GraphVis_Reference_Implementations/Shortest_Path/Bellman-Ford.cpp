#include <vector>
#include <iostream>
#include <limits>

class Solution {
public:
    int findCheapestPrice(int n, std::vector<std::vector<int>>& flights, int src, int dst, int k) {
        std::vector<int> previous (n, std::numeric_limits<int>::max());
        std::vector<int> current (n, std::numeric_limits<int>::max());

        previous[src] = 0;

        for (int i = 1; i < k + 2; ++i) {
            for (const std::vector<int>& flight: flights) {
                int prevFlight = flight[0];
                int currFlight = flight[1];
                int cost = flight[2];

                if (previous[prevFlight] != std::numeric_limits<int>::max() && current[currFlight] > previous[prevFlight] + cost) {
                    current[currFlight] = previous[prevFlight] + cost;
                }
            }
            previous = current;
        }
        return current[dst] == std::numeric_limits<int>::max() ? -1 : current[dst];
    }
};

int main() {
    Solution solution;

    int cities = 4;
    std::vector<std::vector<int>> flights {{0,1,100}, {1,2,100}, {2,0,100}, {1,3,600}, {2,3,200}};
    int source = 0;
    int destination = 3;
    int stops = 1;

    int result = solution.findCheapestPrice(cities, flights, source, destination, stops);

    if (result == -1) {
        std::cout << "No route available within " << stops << " stops." << std::endl;
    } else {
        std::cout << "Cheapest price from " << source << " to " << destination 
                  << " with at most " << stops << " stops: " << result << std::endl;
    }

    return 0;
}
