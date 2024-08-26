#include <iostream>

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;

    Node(int data) : data(data) {
        left = right = parent = nullptr;
        color = RED;
    }
};

class RedBlackTree {
private:
    Node *root;

    // Utility function to perform left rotation
    void leftRotate(Node *&x) {
        Node *y = x->right;
        x->right = y->left;

        if (y->left != nullptr) {
            y->left->parent = x;
        }

        y->parent = x->parent;

        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;
    }

    // Utility function to perform right rotation
    void rightRotate(Node *&x) {
        Node *y = x->left;
        x->left = y->right;

        if (y->right != nullptr) {
            y->right->parent = x;
        }

        y->parent = x->parent;

        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }

        y->right = x;
        x->parent = y;
    }

    // Utility function to fix violations after insertion
    void fixViolation(Node *&z) {
        while (z != root && z->parent->color == RED) {
            Node *parent = z->parent;
            Node *grandparent = parent->parent;

            // Parent is left child of grandparent
            if (parent == grandparent->left) {
                Node *uncle = grandparent->right;

                // Case 1: Uncle is RED
                if (uncle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    z = grandparent;
                } else {
                    // Case 2: z is right child
                    if (z == parent->right) {
                        leftRotate(parent);
                        z = parent;
                        parent = z->parent;
                    }

                    // Case 3: z is left child
                    rightRotate(grandparent);
                    std::swap(parent->color, grandparent->color);
                    z = parent;
                }
            } else { // Parent is right child of grandparent
                Node *uncle = grandparent->left;

                // Case 1: Uncle is RED
                if (uncle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    z = grandparent;
                } else {
                    // Case 2: z is left child
                    if (z == parent->left) {
                        rightRotate(parent);
                        z = parent;
                        parent = z->parent;
                    }

                    // Case 3: z is right child
                    leftRotate(grandparent);
                    std::swap(parent->color, grandparent->color);
                    z = parent;
                }
            }
        }

        root->color = BLACK;
    }

public:
    RedBlackTree() : root(nullptr) {}

    // Insert a new node with given data
    void insert(int data) {
        Node *z = new Node(data);
        Node *y = nullptr;
        Node *x = root;

        while (x != nullptr) {
            y = x;
            if (z->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        z->parent = y;
        if (y == nullptr) {
            root = z;
        } else if (z->data < y->data) {
            y->left = z;
        } else {
            y->right = z;
        }

        if (z->parent == nullptr) {
            z->color = BLACK;
            return;
        }

        if (z->parent->parent == nullptr) {
            return;
        }

        fixViolation(z);
    }

    // In-order traversal of the tree
    void inOrder(Node *node) const {
        if (node == nullptr) {
            return;
        }
        inOrder(node->left);
        std::cout << node->data << " ";
        inOrder(node->right);
    }

    // Utility function to get the root node
    Node* getRoot() const {
        return root;
    }
};

int main() {
    RedBlackTree tree;

    tree.insert(7);
    tree.insert(3);
    tree.insert(18);
    tree.insert(10);
    tree.insert(22);
    tree.insert(8);
    tree.insert(11);
    tree.insert(26);

    std::cout << "In-order traversal of the tree: ";
    tree.inOrder(tree.getRoot());
    std::cout << std::endl;

    return 0;
}

