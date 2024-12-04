#include <iostream>
#include <vector>

class Graph {
private:
    std::vector<std::vector<int>> adjList; // Adjacency list representation
    std::vector<bool> visited;            // Tracks visited nodes
    std::vector<bool> inRecStack;         // Tracks nodes in the current recursion stack

    // Depth-First Search (DFS) to detect a cycle
    bool dfs(int node) {
        // If the node is in the recursion stack, a cycle is detected
        if (inRecStack[node]) {
            return true;
        }

        // If the node is already visited and not in the recursion stack, skip processing
        if (visited[node]) {
            return false;
        }

        // Mark the node as visited and add it to the recursion stack
        visited[node] = true;
        inRecStack[node] = true;

        // Traverse all neighbors
        for (int neighbor : adjList[node]) {
            if (dfs(neighbor)) {
                return true;
            }
        }

        // Remove the node from the recursion stack before backtracking
        inRecStack[node] = false;
        return false;
    }

public:
    // Constructor to initialize the graph
    Graph(int vertices) : adjList(vertices), visited(vertices, false), inRecStack(vertices, false) {}

    // Add a directed edge from `u` to `v`
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

    // Check if the graph contains a cycle
    bool hasCycle() {
        for (int i = 0; i < adjList.size(); ++i) {
            if (!visited[i]) {
                if (dfs(i)) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    // Example: Create a graph with 5 vertices
    Graph g(5);

    // Add edges to the graph
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
