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
