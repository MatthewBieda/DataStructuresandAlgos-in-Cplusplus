#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Tarjan {
public:
    // Constructor to initialize the graph with 'vertices' nodes
    Tarjan(int vertices) 
        : vertices(vertices), time(0), 
          adjList(vertices), indices(vertices, -1), 
          lowLink(vertices, -1), onStack(vertices, false) {}

    // Add a directed edge from node 'u' to node 'v'
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

    // Find and print all Strongly Connected Components (SCCs)
    void findSCCs() {
        for (int i = 0; i < vertices; i++) {
            if (indices[i] == -1) {
                strongconnect(i); // Start a DFS from unvisited node
            }
        }
    }

private:
    int vertices;                     // Number of nodes in the graph
    int time;                         // Global timestamp for DFS traversal
    vector<vector<int>> adjList;      // Adjacency list representing the graph
    vector<int> indices;              // Discovery times of nodes
    vector<int> lowLink;              // Lowest discovery time reachable from a node
    vector<bool> onStack;             // Tracks nodes currently in the recursion stack
    stack<int> myStack;               // Stack to manage current path in the DFS

    // Helper function to perform a DFS and identify SCCs
    void strongconnect(int v) {
        indices[v] = lowLink[v] = time++; // Assign discovery time and low-link value
        myStack.push(v);                 // Push node onto the stack
        onStack[v] = true;               // Mark it as on the stack

        // Explore all neighbors of the current node
        for (int neighbor : adjList[v]) {
            if (indices[neighbor] == -1) {
                // If the neighbor is unvisited, recursively explore it
                strongconnect(neighbor);
                // Update the low-link value after the recursive call
                lowLink[v] = min(lowLink[v], lowLink[neighbor]);
            } else if (onStack[neighbor]) {
                // If the neighbor is on the stack, update low-link (back edge)
                lowLink[v] = min(lowLink[v], indices[neighbor]);
            }
        }

        // If 'v' is a root node (low-link equals its index), pop all nodes
        // in the current SCC off the stack
        if (lowLink[v] == indices[v]) {
            cout << "SCC: ";
            while (true) {
                int w = myStack.top();
                myStack.pop();
                onStack[w] = false;
                cout << w << " ";
                if (w == v) break; // Stop when the root node is reached
            }
            cout << endl; // End of one SCC
        }
    }
};

int main() {
    Tarjan tarjan(5);

    // Define a graph with edges
    tarjan.addEdge(0, 1);
    tarjan.addEdge(1, 2);
    tarjan.addEdge(2, 0);
    tarjan.addEdge(1, 3);
    tarjan.addEdge(3, 4);

    // Output all Strongly Connected Components
    cout << "Strongly Connected Components (Tarjan's Algorithm):" << endl;
    tarjan.findSCCs();

    return 0;
}
