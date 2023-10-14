#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <cassert>

// We will construct an N-ary tree and make it a Trie, since we have 26 English letters, we need 26 children per node
#define N 26

struct TrieNode {
    // The Trie Node structure
    // Each node has N children, starting from the root and a flag to check if it's a leaf node
    char data; // Storing for printing purposes only
    TrieNode* children[N];
    int is_leaf;
};

TrieNode* make_trienode(const char data) {
    // Allocate memory for a TrieNode
    TrieNode* node = (TrieNode*)calloc(1, sizeof(TrieNode));
    assert(node != nullptr);
    for (int i = 0; i < N; i++) {
        node->children[i] = nullptr;
    }
    node->is_leaf = 0;
    node->data = data;
    return node;
}

void free_trienode(TrieNode* node) {
    // Free the trienode sequence 
    for (int i = 0; i < N; i++) {
        if (node->children[i] != nullptr) {
            free_trienode(node->children[i]);
        }
        else {
            continue;
        }
    }
    free(node);
}

TrieNode* insert_trie(TrieNode* root, const char* word) {
    // Inserts the word onto the Trie
    // ASSUMPTION: THe word only contains lowercase characters
    TrieNode* temp = root;

    for (int i = 0; word[i] != '\0'; i++) {
        // Get the relative position in the alphabet list
        int index = (int)word[i] - 'a';
        if (temp->children[index] == nullptr) {
            // If the corresponding child doesn't exist, we will create it
            temp->children[index] = make_trienode(word[i]);
        }
        else {
            // Do nothing, the node already exists
        }
        // Go down a level, to the child referenced by index since we have a prefix match
        temp = temp->children[index];
    }
    // At the end of the work, mark this node as the leaf node
    temp->is_leaf = 1;
    return root;
}

int is_leaf_node(TrieNode* root, const char* word) {
    // Checks if the prefix match of word and root is a leaf node
    TrieNode* temp = root;
    for (int i = 0; word[i]; i++) {
        int position = (int) word[i] - 'a';
        if (temp->children[position]) {
            temp = temp->children[position];
        }
    }
    return temp->is_leaf;
}


int check_divergence(TrieNode* root, char* word) {
    // Checks if there is branching at the last character of word and return the largest position in the word where branching occurs
    TrieNode* temp = root;
    int len = strlen(word);
    if (len == 0)
        return 0;
    // We will return the largest index where branching occurs
    int last_index = 0;
    for (int i = 0; i < len; i++) {
        int position = word[i] - 'a';
        if (temp->children[position]) {
            // If a child exists a that position we will check if there exists any other child so that branching occurs
            for (int j = 0; j < N; j++) {
                if (j != position && temp->children[j]) {
                    // We've found another child! This is a branch. Update the branch position
                    last_index = i + 1;
                    break;
                }
            }
            // Go to the next child in the sequence
            temp = temp->children[position];
        }
    }
    return last_index;
}

char* find_longest_prefix(TrieNode* root, const char* word) {
    // Finds the longest common prefix substring of a word in the Trie
    if (!word || word[0] == '\0')
        return nullptr;
    // Length of the longest prefix
    int len = strlen(word);

    // We initially set the longest prefix as the word itself, and try to back-track from the deepest position to a point of divergence, if it exists
    char* longest_prefix = (char*)calloc(len + 1, sizeof(char));
    for (int i = 0; word[i] != '\0'; i++) {
        longest_prefix[i] = word[i];
    }
    longest_prefix[len] = '\0';

    // If there is no branching from the root, this means we're matching the original string. Not what we want
    int branch_index = check_divergence(root, longest_prefix) - 1;
    if (branch_index >= 0) {
        // There is branching, we must update the position to the longest match and update the longest prefix by the branch index length
        longest_prefix[branch_index] = '\0';
        longest_prefix = (char*)realloc(longest_prefix, (branch_index + 1) * sizeof(char));
    }

    return longest_prefix;
}

TrieNode* delete_trie(TrieNode* root, const char* word) {
    // Will try to delete the word sequence from the Trie only if it terminates in a leaf node
    if (!root)
        return nullptr;
    if (!word || word[0] == '\0')
        return root;
    // If the node corresponding to the match is not a leaf node we will stop
    if (!is_leaf_node(root, word)) {
        return root;
    }
    TrieNode* temp = root;
    // Find the longest prefix string that is not the current word
    char* longest_prefix = find_longest_prefix(root, word);
    printf("Longest Prefix = %s\n", longest_prefix);
    if (longest_prefix[0] == '\0') {
        free(longest_prefix);
        return root;
    }
    // Keep track of position in the Trie
    for (int i = 0; longest_prefix[i] != '\0'; i++) {
        int position = (int)longest_prefix[i] - 'a';
        if (temp->children[position] != nullptr) {
            // Keep moving to the deepest node in the common prefix
            temp = temp->children[position];
        }
        else {
            // There is no such node, simply return.
            free(longest_prefix);
            return root;
        }
    }
    // Now, we have reached the deepest common node between the two strings. We need to delete the sequence corresponding to the word.
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        int position = (int)word[i] - 'a';
        if (temp->children[position]) {
            // Delete the remaining sequence
            TrieNode* rm_node = temp->children[position];
            temp->children[position] = nullptr;
            free_trienode(rm_node);
        }
    }
    free(longest_prefix);
    return root;
}

int search_trie(TrieNode* root, const char* word) {
    // Searches for a word in the Trie
    TrieNode* temp = root;

    for (int i = 0; word[i] != '\0'; i++) {
        int position = word[i] - 'a';
        if (temp->children[position] == nullptr) {
            return 0;
        }
        temp = temp->children[position];
    }
    if (temp != nullptr && temp->is_leaf == 1) {
        return 1;
    }
    return 0;
}

void print_trie(TrieNode* root) {
    // Prints the nodes of the trie
    if (!root) {
        return;
    }
    TrieNode* temp = root;
    printf("%c -> ", temp->data);
    for (int i = 0; i < N; i++) {
        print_trie(temp->children[i]);
    }
}

void print_search(TrieNode* root, const char* word) {
    printf("Seaching for %s: ", word);
    if (search_trie(root, word) == 0) {
        printf("Not Found\n");
    }
    else {
        printf("Found\n");
    }

}

int main() {
    // Drive program to test the operations of our Trie implementation
    TrieNode* root = make_trienode('\0');
    root = insert_trie(root, "hello");
    root = insert_trie(root, "hi");
    root = insert_trie(root, "teabag");
    root = insert_trie(root, "teacan");
    print_search(root, "tea");
    print_search(root, "teabag");
    print_search(root, "teacan");
    print_search(root, "hi");
    print_search(root, "hey");
    print_search(root, "hello");
    print_trie(root);
    printf("\n");
    root = delete_trie(root, "hello");
    printf("After deleting 'hello'...\n");
    print_trie(root);
    printf("\n");
    root = delete_trie(root, "teacan");
    printf("After deleting 'teacan'...\n");
    print_trie(root);
    printf("\n");
    free_trienode(root);
    return 0;
}
