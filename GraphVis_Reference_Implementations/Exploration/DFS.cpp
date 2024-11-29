#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int start, int end) {
        vector<vector<int>> adjacency_list(n);
        for (vector<int> edge : edges) {
            adjacency_list[edge[0]].push_back(edge[1]);
            adjacency_list[edge[1]].push_back(edge[0]);
        }
        
        vector<bool> seen(n, false);
        return dfs(adjacency_list, start, end, seen);
    }
    
private:
    bool dfs(vector<vector<int>>& adj, int node, int end, vector<bool>& seen) {
        if (node == end) return true;
        if (seen[node]) return false;
        
        seen[node] = true;
        
        for (int neighbor : adj[node]) {
            if (!seen[neighbor] && dfs(adj, neighbor, end, seen)) {
                return true;
            }
        }
        
        return false;
    }
};


int main() {
    Solution solution;
    int n = 3;
    int start = 0;
    int destination = 2;

    vector<vector<int>> edges = {{0,1}, {1,2}, {2,0}};
  
    bool isValid = solution.validPath(n, edges, start, destination);
    cout << isValid << endl;

    return 0;
}
