#include <vector>
#include <tuple> 
#include <iostream>
#include <numeric>
#include <algorithm>

class UnionFind {
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    UnionFind(int size): parent(size), rank(size, 0) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int set_find(int x) {
        if (parent[x] != x) {
            parent[x] = set_find(parent[x]);
        }

        return parent[x];
    }

    void set_union(int x, int y) {
        int rootX = set_find(x);
        int rootY = set_find(y);

        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }

    bool set_connected(int x, int y) {
        return set_find(x) == set_find(y);
    }
};


class Solution {
public:
    int minCostConnectPoints(std::vector<std::vector<int>>& points) {
        int n = points.size();

        std::vector<std::tuple<int,int,int>> adj;

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int weight = std::abs(points[i][0] - points[j][0]) + std::abs(points[i][1] - points[j][1]);

                adj.push_back({weight, i, j});
            }
        }

        std::sort(adj.begin(), adj.end());

        UnionFind dsu(n);

        int mstCost = 0;
        int edgesUsed = 0;

        for (const auto[weight, node1, node2]: adj) {
            if (edgesUsed == n - 1) {
                break;
            }

            if (!dsu.set_connected(node1, node2)) {
                dsu.set_union(node1, node2);
                mstCost += weight;
                ++edgesUsed;
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
