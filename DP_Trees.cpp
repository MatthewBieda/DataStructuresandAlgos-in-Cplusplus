#include <iostream>
#include <climits>
#include <algorithm>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int max_sum = INT_MIN;
        maxPathSumHelper(root, max_sum);
        return max_sum;
    }

private:
    int maxPathSumHelper(TreeNode* node, int& max_sum) {
        if (!node) return 0;

        // Compute the maximum path sum starting from left and right child
        int left = std::max(maxPathSumHelper(node->left, max_sum), 0);
        int right = std::max(maxPathSumHelper(node->right, max_sum), 0);

        // Update the maximum path sum with the current node's value
        max_sum = std::max(max_sum, node->val + left + right);

        // Return the maximum path sum starting from the current node
        return node->val + std::max(left, right);
    }
};

int main() {
    // Example tree:
    //        10
    //       /  \
    //      2    10
    //     / \     \
    //    20  1     -25
    //              /  \
    //            3    4
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(2);
    root->right = new TreeNode(10);
    root->left->left = new TreeNode(20);
    root->left->right = new TreeNode(1);
    root->right->right = new TreeNode(-25);
    root->right->right->left = new TreeNode(3);
    root->right->right->right = new TreeNode(4);

    Solution sol;
    std::cout << "Maximum Path Sum: " << sol.maxPathSum(root) << std::endl;

    return 0;
}

