vector<int> Dijkstra(int source, int n, const vector<vector<pair<int, int>>>& adj) {
    vector<int> dist(n, numeric_limits<int>::max());  // Distance from source to each node
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;

    dist[source] = 0;
    minHeap.push({0, source});  // Push the source with distance 0

    while (!minHeap.empty()) {
        const auto [currWeight, currNode] = minHeap.top();
        minHeap.pop();

        if (currWeight > dist[currNode]) continue;  // Skip if this is not the shortest distance

        for (const auto& [nextNode, nextWeight] : adj[currNode]) {
            if (dist[currNode] + nextWeight < dist[nextNode]) {
                dist[nextNode] = dist[currNode] + nextWeight;
                minHeap.push({dist[nextNode], nextNode});
            }
        }
    }

    return dist;
}
