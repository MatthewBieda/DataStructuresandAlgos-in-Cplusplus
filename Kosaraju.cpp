#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Kosaraju {
public:
    Kosaraju(int vertices) : vertices(vertices) {
        adjList.resize(vertices);
        transposedAdjList.resize(vertices);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        transposedAdjList[v].push_back(u);
    }

    void findSCCs() {
        vector<bool> visited(vertices, false);
        stack<int> finishStack;

        // 1st Pass: Order vertices by finishing times
        for (int i = 0; i < vertices; i++) {
            if (!visited[i]) {
                dfs1(i, visited, finishStack);
            }
        }

        // 2nd Pass: Process nodes in decreasing order of finishing times
        fill(visited.begin(), visited.end(), false);

        while (!finishStack.empty()) {
            int v = finishStack.top();
            finishStack.pop();
            if (!visited[v]) {
                cout << "SCC: ";
                dfs2(v, visited);
                cout << endl;
            }
        }
    }

private:
    int vertices;
    vector<vector<int>> adjList;
    vector<vector<int>> transposedAdjList;

    void dfs1(int v, vector<bool>& visited, stack<int>& finishStack) {
        visited[v] = true;
        for (int w : adjList[v]) {
            if (!visited[w]) {
                dfs1(w, visited, finishStack);
            }
        }
        finishStack.push(v);
    }

    void dfs2(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";
        for (int w : transposedAdjList[v]) {
            if (!visited[w]) {
                dfs2(w, visited);
            }
        }
    }
};

int main() {
    Kosaraju kosaraju(5);
    kosaraju.addEdge(0, 1);
    kosaraju.addEdge(1, 2);
    kosaraju.addEdge(2, 0);
    kosaraju.addEdge(1, 3);
    kosaraju.addEdge(3, 4);

    cout << "Strongly Connected Components (Kosaraju's Algorithm):" << endl;
    kosaraju.findSCCs();

    return 0;
}

