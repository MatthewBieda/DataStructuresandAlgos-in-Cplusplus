#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// Class to represent the graph and implement Kosaraju's Algorithm
class Kosaraju {
public:
    Kosaraju(int vertices) : vertices(vertices) {
        adjList.resize(vertices);          // Adjacency list for the graph
        transposedAdjList.resize(vertices); // Adjacency list for the transposed graph
    }

    // Add a directed edge from u to v
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        transposedAdjList[v].push_back(u);
    }

    // Function to find and print all Strongly Connected Components (SCCs)
    void findSCCs() {
        vector<bool> visited(vertices, false); // Track visited nodes
        stack<int> finishStack;               // Stack to store finishing order

        // Step 1: Perform DFS on the original graph to get the finishing order
        for (int i = 0; i < vertices; i++) {
            if (!visited[i]) {
                dfs1(i, visited, finishStack);
            }
        }

        // Step 2: Reset the visited array for processing the transposed graph
        fill(visited.begin(), visited.end(), false);

        // Step 3: Process nodes in the order of their finishing times
        while (!finishStack.empty()) {
            int v = finishStack.top();
            finishStack.pop();
            if (!visited[v]) {
                // Each DFS in the transposed graph identifies one SCC
                cout << "SCC: ";
                dfs2(v, visited); // Explore the SCC
                cout << endl;
            }
        }
    }

private:
    int vertices;                            // Number of vertices in the graph
    vector<vector<int>> adjList;             // Adjacency list for the original graph
    vector<vector<int>> transposedAdjList;   // Adjacency list for the transposed graph

    // DFS to populate the finish stack based on finishing times
    void dfs1(int v, vector<bool>& visited, stack<int>& finishStack) {
        visited[v] = true; // Mark the current node as visited
        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                dfs1(neighbor, visited, finishStack);
            }
        }
        // Push the node to the stack after processing all its neighbors
        finishStack.push(v);
    }

    // DFS on the transposed graph to explore an SCC
    void dfs2(int v, vector<bool>& visited) {
        visited[v] = true; // Mark the current node as visited
        cout << v << " ";  // Print the node as part of the SCC
        for (int neighbor : transposedAdjList[v]) {
            if (!visited[neighbor]) {
                dfs2(neighbor, visited);
            }
        }
    }
};

int main() {
    // Create a graph with 5 vertices
    Kosaraju kosaraju(5);

    // Add directed edges to the graph
    kosaraju.addEdge(0, 1);
    kosaraju.addEdge(1, 2);
    kosaraju.addEdge(2, 0);
    kosaraju.addEdge(1, 3);
    kosaraju.addEdge(3, 4);

    cout << "Strongly Connected Components (Kosaraju's Algorithm):" << endl;
    kosaraju.findSCCs(); // Find and print SCCs

    return 0;
}
