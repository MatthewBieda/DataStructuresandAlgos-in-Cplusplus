#include <iostream>

struct Node {
    int key;
    Node *left, *right;

    Node(int key) : key(key), left(nullptr), right(nullptr) {}
};

class SplayTree {
private:
    Node* root;

    // Right rotate
    Node* rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    // Left rotate
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    // Splay operation
    Node* splay(Node* root, int key) {
        if (!root || root->key == key)
            return root;

        // Key lies in left subtree
        if (root->key > key) {
            if (!root->left) return root;

            // Zig-Zig (Left Left)
            if (root->left->key > key) {
                root->left->left = splay(root->left->left, key);
                root = rightRotate(root);
            } 
            // Zig-Zag (Left Right)
            else if (root->left->key < key) {
                root->left->right = splay(root->left->right, key);
                if (root->left->right)
                    root->left = leftRotate(root->left);
            }

            // Perform one more rotation to bring key to root
            return root->left ? rightRotate(root) : root;
        } else { // Key lies in right subtree
            if (!root->right) return root;

            // Zig-Zig (Right Right)
            if (root->right->key < key) {
                root->right->right = splay(root->right->right, key);
                root = leftRotate(root);
            } 
            // Zig-Zag (Right Left)
            else if (root->right->key > key) {
                root->right->left = splay(root->right->left, key);
                if (root->right->left)
                    root->right = rightRotate(root->right);
            }

            // Perform one more rotation to bring key to root
            return root->right ? leftRotate(root) : root;
        }
    }

    // Utility function to insert a new node with given key
    Node* insert(Node* root, int key) {
        if (!root)
            return new Node(key);

        root = splay(root, key);

        if (root->key == key) return root;

        Node* newNode = new Node(key);

        if (root->key > key) {
            newNode->right = root;
            newNode->left = root->left;
            root->left = nullptr;
        } else {
            newNode->left = root;
            newNode->right = root->right;
            root->right = nullptr;
        }

        return newNode;
    }

    // Utility function to perform in-order traversal
    void inOrder(Node* root) const {
        if (!root) return;
        inOrder(root->left);
        std::cout << root->key << " ";
        inOrder(root->right);
    }

public:
    SplayTree() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

    void search(int key) {
        root = splay(root, key);
    }

    void inOrder() const {
        inOrder(root);
        std::cout << std::endl;
    }
};

int main() {
    SplayTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);

    std::cout << "In-order traversal of the tree: ";
    tree.inOrder();

    std::cout << "Search for key 30 and splay it to the root." << std::endl;
    tree.search(30);
    std::cout << "In-order traversal after splaying: ";
    tree.inOrder();

    return 0;
}

