// In an undirected graph, a cycle exists if during DFS traversal, we visit an already visited node
// that is not the parent of the current node (this is a "trivial cycle" and must be ignored
// as opposed to a legitimate back edge)

#include <iostream>
#include <vector>

class UndirectedGraph {
private:
    std::vector<std::vector<int>> adjList; // Adjacency list representation
    std::vector<bool> visited;            // Visited nodes tracker

    // Depth-First Search (DFS) to detect cycles
    bool dfs(int node, int parent) {
        visited[node] = true; // Mark the node as visited

        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                // Recur for unvisited neighbors
                if (dfs(neighbor, node)) {
                    return true; // Cycle detected
                }
            } else if (neighbor != parent) {
                // If the neighbor is visited and not the parent, a cycle exists
                return true;
            }
        }
        return false; // No cycle found in this DFS path
    }

public:
    // Constructor to initialize the graph with `vertices` nodes
    UndirectedGraph(int vertices) : adjList(vertices), visited(vertices, false) {}

    // Add an undirected edge between `u` and `v`
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    // Check for cycles in the graph
    bool hasCycle() {
        // Iterate through all components of the graph
        for (int i = 0; i < adjList.size(); ++i) {
            if (!visited[i]) {
                if (dfs(i, -1)) { // Pass `-1` as the parent for the starting node
                    return true;
                }
            }
        }
        return false; // No cycles detected in any component
    }
};

int main() {
    UndirectedGraph g(5); // Create a graph with 5 vertices

    // Add edges to form the graph
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0); // Adding a cycle here (0-1-2-0)
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
