#include <iostream>
#include <vector>

class DirectedGraph {
private:
    std::vector<std::vector<int>> adjList;
    std::vector<int> state; // 0 = unvisited, 1 = visiting, 2 = visited

    bool dfs(int node) {
        if (state[node] == 1) {
            return true; // Found a cycle
        }
        if (state[node] == 2) {
            return false; // Already processed, no cycle in this path
        }

        state[node] = 1; // Mark as visiting

        for (int neighbor : adjList[node]) {
            if (dfs(neighbor)) {
                return true;
            }
        }

        state[node] = 2; // Mark as visited
        return false;
    }

public:
    DirectedGraph(int vertices) : adjList(vertices), state(vertices, 0) {}

    void addEdge(int u, int v) {
        adjList[u].push_back(v); // Directed edge from u to v
    }

    bool hasCycle() {
        for (int i = 0; i < adjList.size(); ++i) {
            if (state[i] == 0) { // Unvisited
                if (dfs(i)) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    DirectedGraph g(5); // Create a graph with 5 vertices

    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0); // Adding a cycle here (0->1->2->0)
    g.addEdge(1, 3);
    g.addEdge(3, 4);

    if (g.hasCycle()) {
        std::cout << "Graph contains a cycle" << std::endl;
    } else {
        std::cout << "Graph does not contain a cycle" << std::endl;
    }

    return 0;
}

