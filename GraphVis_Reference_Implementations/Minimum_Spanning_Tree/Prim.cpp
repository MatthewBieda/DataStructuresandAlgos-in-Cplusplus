#include <vector>
#include <iostream>
#include <queue>
#include <cmath> // For abs()

class Solution {
public:
    int minCostConnectPoints(std::vector<std::vector<int>>& points) {
        int n = points.size();

        // Min-heap to store edges in the format {weight, nextNode}
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> minHeap;
        minHeap.push({0, 0}); // Start with an arbitrary node (0)

        std::vector<bool> visited(n, false); // Track visited nodes
        int mstCost = 0;                     // Total cost of the MST
        int edgesUsed = 0;                   // Count of edges added to the MST

        while (edgesUsed < n) {
            // Get the edge with the smallest weight
            const auto [weight, currentNode] = minHeap.top();
            minHeap.pop();

            // If the node is already visited, skip it
            if (visited[currentNode]) {
                continue;
            }

            // Mark the node as visited
            visited[currentNode] = true;
            mstCost += weight;  // Add edge weight to MST cost
            ++edgesUsed;        // Increment the edge count

            // Add all valid edges from the current node to the heap
            for (int nextNode = 0; nextNode < n; ++nextNode) {
                if (!visited[nextNode]) {
                    int nextWeight = calculateDistance(points[currentNode], points[nextNode]);
                    minHeap.push({nextWeight, nextNode});
                }
            }
        }

        return mstCost;
    }

private:
    // Calculate Manhattan distance between two points
    int calculateDistance(const std::vector<int>& point1, const std::vector<int>& point2) {
        return std::abs(point1[0] - point2[0]) + std::abs(point1[1] - point2[1]);
    }
};

int main() {
    Solution solution;

    std::vector<std::vector<int>> points = {{3, 12}, {-2, 5}, {-4, 1}};

    int mstCost = solution.minCostConnectPoints(points);

    std::cout << "Minimum Cost to Connect Points: " << mstCost << std::endl;

    return 0;
}
