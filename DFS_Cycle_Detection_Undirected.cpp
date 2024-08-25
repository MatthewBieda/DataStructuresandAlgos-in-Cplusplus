// In an undirected graph, a cycle exists if during DFS traversal, we visit an already visited node
// that is not the parent of the current node (this is a "trivial cycle" and must be ignored
// as opposed to a legitimate back edge)

#include <iostream>
#include <vector>

using namespace std;

class Graph {
    int V; // Number of vertices
    vector<vector<int>> adjList; // Adjacency list

    bool dfs(int v, int parent, vector<bool> &visited);

public:
    Graph(int V);
    void addEdge(int v, int w);
    bool hasCycle();
};

Graph::Graph(int V) {
    this->V = V;
    adjList.resize(V);
}

void Graph::addEdge(int v, int w) {
    adjList[v].push_back(w);
    adjList[w].push_back(v); // Since the graph is undirected
}

bool Graph::dfs(int v, int parent, vector<bool> &visited) {
    visited[v] = true;

    for (int u : adjList[v]) {
        if (!visited[u]) {
            if (dfs(u, v, visited)) {
                return true;
            }
        } else if (u != parent) {
            return true; // A cycle is detected
        }
    }
    return false;
}

bool Graph::hasCycle() {
    vector<bool> visited(V, false);

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (dfs(i, -1, visited)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(3, 4);

    if (g.hasCycle()) {
        cout << "Cycle detected in the undirected graph" << endl;
    } else {
        cout << "No cycle detected in the undirected graph" << endl;
    }

    return 0;
}

