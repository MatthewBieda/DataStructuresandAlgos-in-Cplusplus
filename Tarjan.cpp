#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Tarjan {
public:
    Tarjan(int vertices) : vertices(vertices), time(0) {
        adjList.resize(vertices);
        indices.resize(vertices, -1);
        lowLink.resize(vertices, -1);
        onStack.resize(vertices, false);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

    void findSCCs() {
        for (int i = 0; i < vertices; i++) {
            if (indices[i] == -1) {
                strongconnect(i);
            }
        }
    }

private:
    int vertices;
    int time;
    vector<vector<int>> adjList;
    vector<int> indices;
    vector<int> lowLink;
    vector<bool> onStack;
    stack<int> myStack;

    void strongconnect(int v) {
        indices[v] = lowLink[v] = time++;
        myStack.push(v);
        onStack[v] = true;

        for (int w : adjList[v]) {
            if (indices[w] == -1) {
                strongconnect(w);
                lowLink[v] = min(lowLink[v], lowLink[w]);
            } else if (onStack[w]) {
                lowLink[v] = min(lowLink[v], indices[w]);
            }
        }

        if (lowLink[v] == indices[v]) {
            cout << "SCC: ";
            while (true) {
                int w = myStack.top();
                myStack.pop();
                onStack[w] = false;
                cout << w << " ";
                if (w == v) break;
            }
            cout << endl;
        }
    }
};

int main() {
    Tarjan tarjan(5);
    tarjan.addEdge(0, 1);
    tarjan.addEdge(1, 2);
    tarjan.addEdge(2, 0);
    tarjan.addEdge(1, 3);
    tarjan.addEdge(3, 4);

    cout << "Strongly Connected Components (Tarjan's Algorithm):" << endl;
    tarjan.findSCCs();

    return 0;
}

