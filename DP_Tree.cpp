#include <iostream>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int maxIndependentSet(TreeNode* root) {
        auto res = dfs(root);
        return std::max(res.first, res.second);
    }

private:
    // Pair represents {size including current node, size excluding current node}
    std::pair<int, int> dfs(TreeNode* node) {
        if (!node) return {0, 0};
        
        auto left = dfs(node->left);
        auto right = dfs(node->right);
        
        // If we include this node, we cannot include its children
        int include = node->val + left.second + right.second;
        
        // If we exclude this node, we can take the best from its children
        int exclude = std::max(left.first, left.second) + std::max(right.first, right.second);
        
        return {include, exclude};
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    Solution sol;
    std::cout << "Maximum Independent Set Size: " << sol.maxIndependentSet(root) << std::endl;
    
    return 0;
}

