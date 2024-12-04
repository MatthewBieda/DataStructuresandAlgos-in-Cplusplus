#include <iostream>
#include <vector>
#include <numeric> // For std::iota

class UnionFind {
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    // Initialize Union-Find with `size` elements
    UnionFind(int size) : parent(size), rank(size, 0) {
        std::iota(parent.begin(), parent.end(), 0); // Initialize parent to itself
    }

    // Find the representative of the set containing `x` with path compression
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    // Union two sets containing `x` and `y` using rank optimization
    void unionSets(int x, int y) {
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

    // Check if two elements are in the same set
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

// Detect cycles in an undirected graph using Union-Find
bool hasCycle(int vertices, const std::vector<std::pair<int, int>>& edges) {
    UnionFind uf(vertices);

    for (const auto& [u, v] : edges) { // Structured bindings to unpack edges
        // If u and v are already connected, we found a cycle
        if (uf.connected(u, v)) {
            return true;
        }

        // Union the sets containing u and v
        uf.unionSets(u, v);
    }

    return false; // No cycle detected
}

int main() {
    // Example graph
    int vertices = 5;
    std::vector<std::pair<int, int>> edges = {
        {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 1}
    }; // Undirected graph edges

    if (hasCycle(vertices, edges)) {
        std::cout << "The graph contains a cycle.\n";
    } else {
        std::cout << "The graph does not contain a cycle.\n";
    }

    return 0;
}
