#include <iostream>
#include <vector>

class DirectedGraph {
private:
    std::vector<std::vector<int>> adjList; // Adjacency list representation
    std::vector<int> state;                // Node state: 0 = unvisited, 1 = visiting, 2 = visited

    // Depth-First Search (DFS) for cycle detection
    bool dfs(int node) {
        if (state[node] == 1) {
            return true; // Cycle detected via back edge
        }
        if (state[node] == 2) {
            return false; // Node already processed, no cycle in this path
        }

        // Mark node as visiting
        state[node] = 1;

        // Explore all neighbors
        for (int neighbor : adjList[node]) {
            if (dfs(neighbor)) {
                return true;
            }
        }

        // Mark node as visited after processing all neighbors
        state[node] = 2;
        return false;
    }

public:
    // Constructor to initialize graph with `vertices` nodes
    DirectedGraph(int vertices) : adjList(vertices), state(vertices, 0) {}

    // Add a directed edge from `u` to `v`
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

    // Check if the graph contains a cycle
    bool hasCycle() {
        for (int i = 0; i < adjList.size(); ++i) {
            if (state[i] == 0) { // Start DFS only on unvisited nodes
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

    // Add edges to form the graph
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0); // Adding a cycle here (0 → 1 → 2 → 0)
    g.addEdge(1, 3);
    g.addEdge(3, 4);

    // Check for cycles
    if (g.hasCycle()) {
        std::cout << "Graph contains a cycle" << std::endl;
    } else {
        std::cout << "Graph does not contain a cycle" << std::endl;
    }

    return 0;
}
