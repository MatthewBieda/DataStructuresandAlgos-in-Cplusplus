#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> tree;
vector<int> dp, subtree_size, result;

void dfs(int u, int parent) {
    subtree_size[u] = 1;  // Size of subtree rooted at u
    dp[u] = 0;            // Sum of distances from u to its subtree

    for (int v : tree[u]) {
        if (v == parent) continue;
        dfs(v, u);
        subtree_size[u] += subtree_size[v];
        dp[u] += dp[v] + subtree_size[v];
    }
}

void reRoot(int u, int parent) {
    result[u] = dp[u];

    for (int v : tree[u]) {
        if (v == parent) continue;

        // Adjust dp values for re-rooting
        dp[u] -= dp[v] + subtree_size[v];
        subtree_size[u] -= subtree_size[v];

        dp[v] += dp[u] + subtree_size[u];
        subtree_size[v] += subtree_size[u];

        // Recurse with v as the new root
        reRoot(v, u);

        // Undo the changes to revert back to the original state
        subtree_size[v] -= subtree_size[u];
        dp[v] -= dp[u] + subtree_size[u];

        subtree_size[u] += subtree_size[v];
        dp[u] += dp[v] + subtree_size[v];
    }
}

int main() {
    int n = 10;  // Number of nodes in the tree

    tree.resize(n);
    dp.resize(n);
    subtree_size.resize(n);
    result.resize(n);

    // Hardcoding the example tree edges
    tree[0].push_back(1);
    tree[0].push_back(2);
    tree[1].push_back(0);
    tree[2].push_back(0);

    tree[1].push_back(3);
    tree[1].push_back(4);
    tree[3].push_back(1);
    tree[4].push_back(1);

    tree[4].push_back(6);
    tree[6].push_back(4);

    tree[2].push_back(5);
    tree[5].push_back(2);

    tree[5].push_back(7);
    tree[7].push_back(5);

    tree[7].push_back(8);
    tree[7].push_back(9);
    tree[8].push_back(7);
    tree[9].push_back(7);

    // Root the tree at node 0 and perform initial DFS
    dfs(0, -1);

    // Re-root the tree and calculate results for all nodes
    reRoot(0, -1);

    // Output the results
    for (int i = 0; i < n; ++i) {
        cout << "Sum of distances for node " << i << ": " << result[i] << endl;
    }

    return 0;
}

/*
        0
       / \
      1   2
     /|   |
    3 4   5
       |   \
       6    7
           / \
          8   9
*/

