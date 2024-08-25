// The Edmonds-Karp algorithm is an implementation of the Floyd-Fulkerson method that uses BFS to find the shortest augmenting path in terms of the number of edges. 
// This implementation guarantees an O(V + E^2) time complexity, whwre V is the number of vertices and E is the number of edges.

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

class MaxFlow {
public:
    MaxFlow(int n) : n(n), capacity(n, vector<int>(n, 0)) {}

    void addEdge(int u, int v, int cap) {
        capacity[u][v] = cap;
    }

    int fordFulkerson(int source, int sink) {
        int maxFlow = 0;
        vector<int> parent(n, -1);

        while (bfs(source, sink, parent)) {
            int pathFlow = numeric_limits<int>::max();
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                pathFlow = min(pathFlow, capacity[u][v]);
            }

            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                capacity[u][v] -= pathFlow;
                capacity[v][u] += pathFlow;
            }

            maxFlow += pathFlow;
        }

        return maxFlow;
    }

private:
    int n;
    vector<vector<int>> capacity;

    bool bfs(int source, int sink, vector<int>& parent) {
        fill(parent.begin(), parent.end(), -1);
        queue<int> q;
        q.push(source);
        parent[source] = -2;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v = 0; v < n; ++v) {
                if (parent[v] == -1 && capacity[u][v] > 0) {
                    parent[v] = u;
                    if (v == sink) return true;
                    q.push(v);
                }
            }
        }
        return false;
    }
};

int main() {
    MaxFlow maxFlow(6);

    maxFlow.addEdge(0, 1, 16);
    maxFlow.addEdge(0, 2, 13);
    maxFlow.addEdge(1, 2, 10);
    maxFlow.addEdge(1, 3, 12);
    maxFlow.addEdge(2, 1, 4);
    maxFlow.addEdge(2, 4, 14);
    maxFlow.addEdge(3, 2, 9);
    maxFlow.addEdge(3, 5, 20);
    maxFlow.addEdge(4, 3, 7);
    maxFlow.addEdge(4, 5, 4);

    cout << "Maximum Flow: " << maxFlow.fordFulkerson(0, 5) << endl;

    return 0;
}

