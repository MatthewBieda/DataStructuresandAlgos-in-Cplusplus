#include <vector>
#include <iostream>
#include <queue>


class Solution {
public:
    int minCostConnectPoints(std::vector<std::vector<int>>& points) {
        int n = points.size();

        std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> heap;
        heap.push({0,0});

        std::vector<bool> visited(n);
        int mstCost = 0;
        int edgesUsed = 0;

        while (edgesUsed < n) {
            const auto [weight, currentNode] = heap.top();
            heap.pop();

            if (visited[currentNode]) {
                continue;
            }

            visited[currentNode] = true;
            mstCost += weight;
            ++edgesUsed;

            for (int nextNode = 0; nextNode < n; ++nextNode) {
                if (!visited[nextNode]) {
                    int nextWeight = std::abs(points[currentNode][0] - points[nextNode][0]) + std::abs(points[currentNode][1] - points[nextNode][1]);

                    heap.push({nextWeight, nextNode});
                }
            }
        }

        return mstCost;
    }
};

int main() {
    Solution solution;

    std::vector<std::vector<int>> points = {{3, 12}, {-2, 5}, {-4, 1}};

    int mstCost = solution.minCostConnectPoints(points);

    std::cout << mstCost << std::endl;

    return 0;
}
