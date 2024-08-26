#include <vector>
#include <iostream>

class SegmentTree {
public:
    SegmentTree(const std::vector<int>& data) : n(data.size()) {
        tree.resize(2 * n);
        build(data);
    }

    // Build the segment tree
    void build(const std::vector<int>& data) {
        for (int i = 0; i < n; ++i) {
            tree[n + i] = data[i];
        }
        for (int i = n - 1; i > 0; --i) {
            tree[i] = tree[2 * i] + tree[2 * i + 1];
        }
    }

    // Update the value at index `pos`
    void update(int pos, int value) {
        pos += n;
        tree[pos] = value;
        for (; pos > 1; pos /= 2) {
            tree[pos / 2] = tree[pos] + tree[pos ^ 1];
        }
    }

    // Query the sum of the range [left, right)
    int query(int left, int right) {
        int sum = 0;
        left += n;
        right += n;
        while (left < right) {
            if (left & 1) sum += tree[left++];
            if (right & 1) sum += tree[--right];
            left /= 2;
            right /= 2;
        }
        return sum;
    }

private:
    std::vector<int> tree;
    int n;
};

int main() {
    std::vector<int> data = {3, 2, -1, 6, 5, 4, -3, 3, 7, 2, 3};

    SegmentTree st(data);

    // Query the sum of the range [0, 5)
    std::cout << "Sum of the range [0, 5): " << st.query(0, 5) << std::endl;

    // Update the value at index 2 to 1
    st.update(2, 1);
    std::cout << "After update, sum of the range [0, 5): " << st.query(0, 5) << std::endl;

    return 0;
}

