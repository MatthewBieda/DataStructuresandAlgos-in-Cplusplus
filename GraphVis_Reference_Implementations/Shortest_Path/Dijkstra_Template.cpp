#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <iostream>

using namespace std;

vector<int> Dijkstra(int source, int n, const vector<vector<pair<int, int>>>& adj) {
    // Distance from the source to each node, initially set to "infinity"
    vector<int> dist(n, numeric_limits<int>::max());
    // Min-heap to process nodes in increasing order of their distance
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;

    dist[source] = 0;  // Distance to the source is 0
    minHeap.push({0, source});  // Push the source node with distance 0

    while (!minHeap.empty()) {
        // Extract the node with the smallest distance
        const auto [currWeight, currNode] = minHeap.top();
        minHeap.pop();

        // Skip if this distance is not up-to-date (a better path was found earlier)
        if (currWeight > dist[currNode]) continue;

        // Explore all neighbors of the current node
        for (const auto& [nextNode, nextWeight] : adj[currNode]) {
            // Relaxation: If the new distance is shorter, update and push to the heap
            if (dist[currNode] + nextWeight < dist[nextNode]) {
                dist[nextNode] = dist[currNode] + nextWeight;
                minHeap.push({dist[nextNode], nextNode});
            }
        }
    }

    return dist;  // Return the shortest distances from the source to all nodes
}

int main() {
    int n = 5; // Number of nodes
    vector<vector<pair<int, int>>> adj = {
        {{1, 2}, {2, 4}},         // Neighbors of node 0: (1 with weight 2), (2 with weight 4)
        {{2, 1}, {3, 7}},         // Neighbors of node 1
        {{3, 3}},                 // Neighbors of node 2
        {{4, 1}},                 // Neighbors of node 3
        {}                        // Node 4 has no neighbors
    };

    int source = 0; // Starting node
    vector<int> distances = Dijkstra(source, n, adj);

    cout << "Shortest distances from node " << source << ":\n";
    for (int i = 0; i < n; ++i) {
        cout << "Node " << i << ": " 
             << (distances[i] == numeric_limits<int>::max() ? "Unreachable" : to_string(distances[i])) 
             << endl;
    }

    return 0;
}
