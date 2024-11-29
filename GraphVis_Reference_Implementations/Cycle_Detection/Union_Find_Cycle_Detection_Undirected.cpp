#include <iostream>
#include <vector>
#include <numeric>

class UnionFind {
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    UnionFind(int size) : parent(size), rank(size, 0) {
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

    bool set_connected(int x, int y) {
        return set_find(x) == set_find(y);
    }
};

bool hasCycle(int vertices, const std::vector<std::pair<int, int>>& edges) {
    UnionFind uf(vertices);

    for (const auto& [u, v] : edges) { // Structured bindings to unpack the edge
        // If u and v are already in the same set, we found a cycle
        if (uf.set_connected(u, v)) {
            return true;
        }

        // Otherwise, union the sets
        uf.set_union(u, v);
    }

    return false; // No cycle detected
}

int main() {
    int vertices = 5;
    std::vector<std::pair<int, int>> edges = {
        {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 1}
    }; // Edges in the graph

    if (hasCycle(vertices, edges)) {
        std::cout << "The graph contains a cycle.\n";
    } else {
        std::cout << "The graph does not contain a cycle.\n";
    }

    return 0;
}
