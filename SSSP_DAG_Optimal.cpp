// Optimal solution for solving SSSP on a DAG (V + E)
// Kahn's Algorithm + relaxation

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>

void shortestPathDag(int src, int V, const std::vector<std::vector<std::pair<int, int>>>& adjList) {
	constexpr int INF = std::numeric_limits<int>::max();

	// Step1: Compute in-degree of all vertices
	std::vector<int> inDegree(V, 0);
	for (int u = 0; u < V; ++u) {
		for (const auto& [v, weight]: adjList[u]) {
			inDegree[v]++;
		}
	}

	// Step2: Use Kahn's Algorithm to perform Topological Sort
	std::queue<int> topoQueue;
	for (int i = 0; i < V; ++i) {
		if (inDegree[i] == 0) {
			topoQueue.push(i);
		}
	}

	std::vector<int> topoOrder;
	while (!topoQueue.empty()) {
		int u = topoQueue.front();
		topoQueue.pop();
		topoOrder.push_back(u);

		for (const auto& [v, weight]: adjList[u]) {
			inDegree[v]--;
			if (inDegree[v] == 0) {
				topoQueue.push(v);
			}
		}
	}

	// Step3: Initilize distances to max
	std::vector<int> dist(V, INF);
	dist[src] = 0;

	// Step4: Process vertices in topological order
	for (const int& u: topoOrder) {
		if (dist[u] != std::numeric_limits<int>::max()) {
			for (const auto& [v, weight]: adjList[u]) {
				if (dist[u] + weight < dist[v]) {
					dist[v] = dist[u] + weight;	
				}
			}
		}
	}

	// Step5 Print shortest distance
	std::cout << "Vertex\tDistance from Source " << src << "\n";
	for (int i = 0; i < V; ++i) {
		if (dist[i] == INF) {
			std::cout << i << "\tUnreachable\n";
		} else {
			std::cout << i << "\t" << dist[i] << "\n";
		}
	}
}

int main() {
	int V = 6;
	std::vector<std::vector<std::pair<int, int>>> adjList(V);

	adjList[0].push_back({1, 5});
    adjList[0].push_back({2, 3});
    adjList[1].push_back({3, 6});
    adjList[1].push_back({2, 2});
    adjList[2].push_back({4, 4});
    adjList[2].push_back({5, 2});
    adjList[2].push_back({3, 7});
    adjList[3].push_back({5, 1});
    adjList[4].push_back({5, -1});

	int src = 0;
	shortestPathDag(src, V, adjList);

	return 0;
}
