#include <iostream>
#include <unordered_map>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Compute prefix sum for each node
void computePrefixSum(TreeNode* node, int current_sum, std::unordered_map<TreeNode*, int>& prefix_sum) {
    if (!node) return;

    // Update the prefix sum for the current node
    current_sum += node->val;
    prefix_sum[node] = current_sum;

    // Recursively compute prefix sums for left and right children
    computePrefixSum(node->left, current_sum, prefix_sum);
    computePrefixSum(node->right, current_sum, prefix_sum);
}

// Print prefix sums
void printPrefixSums(const std::unordered_map<TreeNode*, int>& prefix_sum) {
    for (const auto& pair : prefix_sum) {
        std::cout << "Node value: " << pair.first->val << ", Prefix Sum: " << pair.second << std::endl;
    }
}

// Delete binary tree nodes
void deleteTree(TreeNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main() {
    // Construct the binary tree
    //      5
    //     / \
    //    3   8
    //   / \   \
    //  2   4   9

    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(9);

    std::unordered_map<TreeNode*, int> prefix_sum;

    // Compute prefix sums for each node
    computePrefixSum(root, 0, prefix_sum);

    // Print the prefix sums
    printPrefixSums(prefix_sum);

    // Cleanup memory
    deleteTree(root);

    return 0;
}

