#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <stdexcept>
#include <iomanip> // For formatted output

using namespace std;

const int INF = numeric_limits<int>::max();

class Graph {
public:
    Graph(int n) : numVertices(n), adjacencyList(n) {}

    void addEdge(int u, int v, int weight) {
        adjacencyList[u].push_back({v, weight});
    }

    vector<vector<int>> johnson() {
        // Step 1: Add a new node connected to all nodes with zero-weight edges
        int newNode = numVertices;
        adjacencyList.emplace_back();
        vector<int> potential(numVertices + 1, INF);
        potential[newNode] = 0;

        // Step 2: Run Bellman-Ford from the new node to compute potentials
        if (!bellmanFord(newNode, potential)) {
            throw runtime_error("Negative weight cycle detected");
        }

        // Step 3: Reweight the graph using the potentials
        vector<vector<pair<int, int>>> reweightedAdjacencyList(numVertices);
        for (int u = 0; u < numVertices; ++u) {
            for (const auto& [v, weight] : adjacencyList[u]) {
                reweightedAdjacencyList[u].emplace_back(v, weight + potential[u] - potential[v]);
            }
        }

        // Step 4: Use Dijkstra's algorithm to find shortest paths for each vertex
        vector<vector<int>> distances(numVertices, vector<int>(numVertices, INF));
        for (int u = 0; u < numVertices; ++u) {
            distances[u] = dijkstra(u, reweightedAdjacencyList);
        }

        // Step 5: Adjust distances back to original weights
        for (int u = 0; u < numVertices; ++u) {
            for (int v = 0; v < numVertices; ++v) {
                if (distances[u][v] < INF) {
                    distances[u][v] += potential[v] - potential[u];
                }
            }
        }

        return distances;
    }

private:
    int numVertices;
    vector<vector<pair<int, int>>> adjacencyList;

    bool bellmanFord(int start, vector<int>& potential) {
        for (int i = 0; i <= numVertices; ++i) {
            for (int u = 0; u <= numVertices; ++u) {
                for (const auto& [v, weight] : adjacencyList[u]) {
                    if (potential[u] < INF && potential[u] + weight < potential[v]) {
                        potential[v] = potential[u] + weight;
                    }
                }
            }
        }

        // Check for negative weight cycles
        for (int u = 0; u < numVertices; ++u) {
            for (const auto& [v, weight] : adjacencyList[u]) {
                if (potential[u] < INF && potential[u] + weight < potential[v]) {
                    return false;
                }
            }
        }
        return true;
    }

    vector<int> dijkstra(int src, const vector<vector<pair<int, int>>>& adjList) {
        vector<int> dist(numVertices, INF);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [currentDistance, u] = pq.top();
            pq.pop();

            if (currentDistance > dist[u]) continue;

            for (const auto& [v, weight] : adjList[u]) {
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        return dist;
    }
};

int main() {
    int n = 5; // Number of vertices
    Graph graph(n);

    graph.addEdge(0, 1, -1);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 2);
    graph.addEdge(1, 4, 2);
    graph.addEdge(3, 2, 5);
    graph.addEdge(3, 1, 1);
    graph.addEdge(4, 3, -3);

    try {
        vector<vector<int>> distances = graph.johnson();

        // Output the shortest path distances
        cout << "Shortest path distances:\n\n";
        cout << setw(5) << " ";
        for (int i = 0; i < n; ++i) {
            cout << setw(5) << i;
        }
        cout << "\n";

        for (int i = 0; i < n; ++i) {
            cout << setw(5) << i;
            for (int j = 0; j < n; ++j) {
                if (distances[i][j] == INF) {
                    cout << setw(5) << "INF";
                } else {
                    cout << setw(5) << distances[i][j];
                }
            }
            cout << "\n";
        }
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
