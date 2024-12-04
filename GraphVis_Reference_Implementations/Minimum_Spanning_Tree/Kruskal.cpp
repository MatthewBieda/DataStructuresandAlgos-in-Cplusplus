#include <vector>
#include <tuple>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <cmath>

// Union-Find (Disjoint Set Union) Data Structure
class UnionFind {
private:
    std::vector<int> parent;  // Parent of each node
    std::vector<int> rank;    // Rank (depth) of each node's tree

public:
    // Initialize Union-Find for 'size' nodes
    UnionFind(int size) : parent(size), rank(size, 0) {
        std::iota(parent.begin(), parent.end(), 0); // Set each node as its own parent
    }

    // Find the root of a set containing 'x', with path compression
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    // Union two sets containing 'x' and 'y', using union by rank
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    // Check if 'x' and 'y' are in the same set
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

class Solution {
public:
    // Function to compute the minimum cost to connect all points
    int minCostConnectPoints(const std::vector<std::vector<int>>& points) {
        int n = points.size();
        std::vector<std::tuple<int, int, int>> edges;

        // Step 1: Generate all edges with their weights (Manhattan distance)
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int weight = std::abs(points[i][0] - points[j][0]) + std::abs(points[i][1] - points[j][1]);
                edges.emplace_back(weight, i, j);
            }
        }

        // Step 2: Sort edges by weight (non-decreasing order)
        std::sort(edges.begin(), edges.end());

        // Step 3: Initialize Union-Find and process edges
        UnionFind uf(n);
        int mstCost = 0;
        int edgesUsed = 0;

        for (const auto& [weight, u, v] : edges) {
            if (edgesUsed == n - 1) break; // MST complete with (n-1) edges

            if (!uf.connected(u, v)) {
                uf.unite(u, v);
                mstCost += weight;
                ++edgesUsed;
            }
        }

        return mstCost; // Total cost of the MST
    }
};

int main() {
    Solution solution;
    std::vector<std::vector<int>> points = {{3, 12}, {-2, 5}, {-4, 1}};

    int mstCost = solution.minCostConnectPoints(points);

    std::cout << "Minimum cost to connect all points: " << mstCost << std::endl;

    return 0;
}
