#include <iostream>
#include <vector>
#include <climits>

// Floyd-Warshall algorithm for All Pairs Shortest Path (APSP)
void floydWarshallDistance(int n, std::vector<std::vector<int>>& distanceMatrix) {
    for (int k = 0; k < n; ++k) { // Intermediate node
        for (int i = 0; i < n; ++i) { // Source node
            for (int j = 0; j < n; ++j) { // Destination node
                if (distanceMatrix[i][k] != INT_MAX && distanceMatrix[k][j] != INT_MAX) {
                    distanceMatrix[i][j] = std::min(
                        distanceMatrix[i][j],
                        distanceMatrix[i][k] + distanceMatrix[k][j]
                    );
                }
            }
        }
    }
}

// Floyd-Warshall algorithm for Transitive Closure
void floydWarshallReachability(int n, std::vector<std::vector<bool>>& reachable) {
    for (int k = 0; k < n; ++k) { // Intermediate node
        for (int i = 0; i < n; ++i) { // Source node
            for (int j = 0; j < n; ++j) { // Destination node
                reachable[i][j] = reachable[i][j] || (reachable[i][k] && reachable[k][j]);
            }
        }
    }
}

int main() {
    // Example 1: All Pairs Shortest Path (APSP)
    std::cout << "All Pairs Shortest Path (APSP) Example:\n";
    int n1 = 4;
    std::vector<std::vector<int>> distanceMatrix = {
        {0, 3, INT_MAX, 5},
        {2, 0, INT_MAX, 4},
        {INT_MAX, 1, 0, INT_MAX},
        {INT_MAX, INT_MAX, 2, 0}
    };
    
    floydWarshallDistance(n1, distanceMatrix);

    std::cout << "Shortest distances between all pairs of nodes:\n";
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < n1; ++j) {
            if (distanceMatrix[i][j] == INT_MAX) {
                std::cout << "INF ";
            } else {
                std::cout << distanceMatrix[i][j] << " ";
            }
        }
        std::cout << "\n";
    }

    // Example 2: Transitive Closure
    std::cout << "\nTransitive Closure Example:\n";
    int n2 = 4;
    std::vector<std::vector<bool>> reachable = {
        {true, true, false, false},
        {false, true, false, true},
        {false, false, true, false},
        {false, false, true, true}
    };

    floydWarshallReachability(n2, reachable);

    std::cout << "Reachability matrix:\n";
    for (int i = 0; i < n2; ++i) {
        for (int j = 0; j < n2; ++j) {
            std::cout << reachable[i][j] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
