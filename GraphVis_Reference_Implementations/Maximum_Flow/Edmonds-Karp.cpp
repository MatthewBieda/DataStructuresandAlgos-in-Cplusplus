// The Edmonds-Karp algorithm is an implementation of the Ford-Fulkerson method that uses BFS to find the shortest augmenting path in terms of the number of edges. 
// This implementation guarantees an O(V × E²) time complexity, whwre V is the number of vertices and E is the number of edges.

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Class to compute maximum flow using the Edmonds-Karp algorithm
class MaxFlow {
public:
    MaxFlow(int numVertices)
        : numVertices(numVertices), 
          residualCapacity(numVertices, vector<int>(numVertices, 0)) {}

    // Add an edge with capacity to the graph
    void addEdge(int u, int v, int capacity) {
        residualCapacity[u][v] = capacity; // Set initial capacity in the residual graph
    }

    // Compute the maximum flow from source to sink
    int edmondsKarp(int source, int sink) {
        int maxFlow = 0;              // Total flow
        vector<int> parent(numVertices, -1); // Store the augmenting path

        // Repeat while there exists an augmenting path
        while (bfs(source, sink, parent)) {
            // Find the bottleneck capacity along the path
            int pathFlow = numeric_limits<int>::max();
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                pathFlow = min(pathFlow, residualCapacity[u][v]);
            }

            // Update residual capacities along the path
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                residualCapacity[u][v] -= pathFlow;
                residualCapacity[v][u] += pathFlow; // Reverse flow in residual graph
            }

            maxFlow += pathFlow; // Add bottleneck capacity to total flow
        }

        return maxFlow;
    }

private:
    int numVertices;
    vector<vector<int>> residualCapacity;

    // Perform BFS to find an augmenting path
    bool bfs(int source, int sink, vector<int>& parent) {
        fill(parent.begin(), parent.end(), -1); // Reset parent vector
        queue<int> q;                           // Queue for BFS
        q.push(source);
        parent[source] = -2;                    // Mark source as visited

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            // Explore neighbors
            for (int v = 0; v < numVertices; ++v) {
                if (parent[v] == -1 && residualCapacity[u][v] > 0) {
                    parent[v] = u; // Mark the path
                    if (v == sink) {
                        return true; // Found a path to the sink
                    }
                    q.push(v); // Add neighbor to the queue
                }
            }
        }
        return false; // No augmenting path found
    }
};

int main() {
    // Create a graph with 6 vertices
    MaxFlow maxFlow(6);

    // Add edges and capacities
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

    // Compute maximum flow from node 0 (source) to node 5 (sink)
    cout << "Maximum Flow: " << maxFlow.edmondsKarp(0, 5) << endl;

    return 0;
}
