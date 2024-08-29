// In an undirected graph, a cycle exists if during DFS traversal, we visit an already visited node
// that is not the parent of the current node (this is a "trivial cycle" and must be ignored
// as opposed to a legitimate back edge)

#include <iostream>
#include <vector>

class Graph {
private:
    std::vector<std::vector<int>> adjList;
    std::vector<bool> visited;

    bool dfs(int node, int parent) {
        visited[node] = true;

        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                // Visit the neighbor recursively
                if (dfs(neighbor, node)) {
                    return true;
                }
            } else if (neighbor != parent) {
                // If the neighbor is visited and is not the parent, we found a cycle
                return true;
            }
        }
        return false;
    }

public:
    Graph(int vertices) : adjList(vertices), visited(vertices, false) {}

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Since the graph is undirected
    }

    bool hasCycle() {
        // Check for each component
        for (int i = 0; i < adjList.size(); ++i) {
            if (!visited[i]) {
                if (dfs(i, -1)) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    Graph g(5); // Create a graph with 5 vertices

    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0); // Adding a cycle here (0-1-2-0)
    g.addEdge(1, 3);
    g.addEdge(3, 4);

    if (g.hasCycle()) {
        std::cout << "Graph contains a cycle" << std::endl;
    } else {
        std::cout << "Graph does not contain a cycle" << std::endl;
    }

    return 0;
}


