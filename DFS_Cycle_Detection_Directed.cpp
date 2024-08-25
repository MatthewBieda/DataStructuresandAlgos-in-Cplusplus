// We must keep track of the recursion stack to determine whether the node is revisited in the same DFS path
// which indicates the presence of a cycle

#include <iostream>
#include <vector>

using namespace std;

class Graph {
    int V; // Number of vertices
    vector<vector<int>> adjList; // Adjacency list

    bool dfs(int v, vector<bool> &visited, vector<bool> &recStack);

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
}

bool Graph::dfs(int v, vector<bool> &visited, vector<bool> &recStack) {
    visited[v] = true;
    recStack[v] = true;

    for (int u : adjList[v]) {
        if (!visited[u]) {
            if (dfs(u, visited, recStack)) {
                return true;
            }
        } else if (recStack[u]) {
            return true; // A cycle is detected
        }
    }

    recStack[v] = false; // Remove the vertex from recursion stack
    return false;
}

bool Graph::hasCycle() {
    vector<bool> visited(V, false);
    vector<bool> recStack(V, false);

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (dfs(i, visited, recStack)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);

    if (g.hasCycle()) {
        cout << "Cycle detected in the directed graph" << endl;
    } else {
        cout << "No cycle detected in the directed graph" << endl;
    }

    return 0;
}

