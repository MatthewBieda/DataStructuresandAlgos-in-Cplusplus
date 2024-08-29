#include <iostream>
#include <vector>

class Graph {
private:
    std::vector<std::vector<int>> adjList;
    std::vector<bool> visited;
    std::vector<bool> inRecStack; // To keep track of nodes in the recursion stack

    bool dfs(int node) {
        // If the node is currently in the recursion stack, we found a cycle
        if (inRecStack[node]) {
            return true;
        }
        // If the node is already visited, no need to process it again
        if (visited[node]) {
            return false;
        }

        // Mark the node as visited and add it to the recursion stack
        visited[node] = true;
        inRecStack[node] = true;

        // Visit all adjacent nodes
        for (int neighbor : adjList[node]) {
            if (dfs(neighbor)) {
                return true;
            }
        }

        // Remove the node from the recursion stack and continue
        inRecStack[node] = false;
        return false;
    }

public:
    Graph(int vertices) : adjList(vertices), visited(vertices, false), inRecStack(vertices, false) {}

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

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
    Graph g(5); // Create a graph with 5 vertices

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

