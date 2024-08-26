#include <vector>
#include <iostream>

class FenwickTree {
public:
    FenwickTree(int n) : bit(n + 1, 0) {}

    // Update the tree with value at index `i`
    void update(int i, int value) {
        while (i < bit.size()) {
            bit[i] += value;
            i += i & -i; // Move to the next element in the tree
        }
    }

    // Get the prefix sum up to index `i`
    int query(int i) const {
        int sum = 0;
        while (i > 0) {
            sum += bit[i];
            i -= i & -i; // Move to the parent node
        }
        return sum;
    }

    // Get the sum of the range [left, right]
    int range_query(int left, int right) const {
        return query(right) - query(left - 1);
    }

private:
    std::vector<int> bit; // Binary Indexed Tree (1-based indexing)
};

int main() {
    std::vector<int> data = {0, 3, 2, -1, 6, 5, 4, -3, 3, 7, 2, 3}; // 1-based index
    FenwickTree ft(data.size());

    // Building the Fenwick Tree
    for (int i = 1; i < data.size(); ++i) {
        ft.update(i, data[i]);
    }

    // Query the prefix sum up to index 5
    std::cout << "Prefix sum up to index 5: " << ft.query(5) << std::endl;

    // Update the value at index 3 by 2
    ft.update(3, 2);
    std::cout << "After update, prefix sum up to index 5: " << ft.query(5) << std::endl;

    // Query the sum of the range [3, 8]
    std::cout << "Sum of the range [3, 8]: " << ft.range_query(3, 8) << std::endl;

    return 0;
}

