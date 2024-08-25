#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

class Graph {
public:
    Graph(int n) : n(n), adj(n) {}

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
    }

    vector<vector<int>> johnson() {
        // Step 1: Add a new node with zero-weight edges to all other nodes
        int newNode = n;
        adj.emplace_back();
        vector<int> h(n + 1, INF);
        h[newNode] = 0;
        
        // Step 2: Run Bellman-Ford from the new node
        if (!bellmanFord(newNode, h)) {
            throw runtime_error("Negative weight cycle detected");
        }

        // Step 3: Reweight the graph
        vector<vector<pair<int, int>>> reweightedAdj(n);
        for (int u = 0; u < n; ++u) {
            for (const auto& [v, w] : adj[u]) {
                if (u < n) {
                    reweightedAdj[u].push_back({v, w + h[u] - h[v]});
                }
            }
        }

        // Step 4: Run Dijkstra's algorithm for each node
        vector<vector<int>> dist(n, vector<int>(n, INF));
        for (int u = 0; u < n; ++u) {
            dist[u] = dijkstra(u, reweightedAdj);
        }

        // Adjust distances back to original weights
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (dist[u][v] < INF) {
                    dist[u][v] += h[v] - h[u];
                }
            }
        }

        return dist;
    }

private:
    int n;
    vector<vector<pair<int, int>>> adj;

    bool bellmanFord(int start, vector<int>& h) {
        for (int i = 0; i < n + 1; ++i) {
            for (int u = 0; u <= n; ++u) {
                for (const auto& [v, w] : adj[u]) {
                    if (h[u] < INF && h[u] + w < h[v]) {
                        h[v] = h[u] + w;
                    }
                }
            }
        }

        // Check for negative weight cycles
        for (int u = 0; u < n; ++u) {
            for (const auto& [v, w] : adj[u]) {
                if (h[u] < INF && h[u] + w < h[v]) {
                    return false; // Negative weight cycle detected
                }
            }
        }

        return true;
    }

    vector<int> dijkstra(int src, const vector<vector<pair<int, int>>>& adjList) {
        vector<int> dist(n, INF);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, src});
        dist[src] = 0;

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) continue;

            for (const auto& [v, w] : adjList[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }

        return dist;
    }
};

int main() {
    int n = 5; // Number of vertices
    Graph g(n);
    
    g.addEdge(0, 1, -1);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 2);
    g.addEdge(1, 4, 2);
    g.addEdge(3, 2, 5);
    g.addEdge(3, 1, 1);
    g.addEdge(4, 3, -3);

    try {
        vector<vector<int>> dist = g.johnson();

        cout << "Shortest path distances:" << endl;
        cout << "     ";
        for (int i = 0; i < n; ++i) {
            cout << i << "   ";
        }
        cout << endl;

        for (int i = 0; i < n; ++i) {
            cout << i << ": ";
            for (int j = 0; j < n; ++j) {
                if (dist[i][j] == INF) {
                    cout << "INF ";
                } else {
                    cout << dist[i][j] << "   ";
                }
            }
            cout << endl;
        }
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }

    return 0;
}

