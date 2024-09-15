#include <iostream>
#include <stack>
#include <vector>

class MonotonicStack {
public:
    // Increasing stack: keeps elements in non-decreasing order
    void push(int value) {
        // Pop elements while the stack top is greater than the incoming value
        while (!st.empty() && st.top() > value) {
            st.pop();
        }
        st.push(value);
    }

    // Function to print the current stack
    void print_stack() const {
        std::stack<int> temp = st;
        std::vector<int> elements;
        while (!temp.empty()) {
            elements.push_back(temp.top());
            temp.pop();
        }
        std::cout << "Current Stack (from top to bottom): ";
        for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

private:
    std::stack<int> st;
};

int main() {
    MonotonicStack ms;

    std::vector<int> nums = {5, 2, 6, 3, 4};

    for (int num : nums) {
        ms.push(num);
        ms.print_stack();
    }

    return 0;
}

