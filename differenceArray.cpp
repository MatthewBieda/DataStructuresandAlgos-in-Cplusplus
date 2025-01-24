#include <iostream>
#include <vector>
using namespace std;

class DifferenceArray {
private:
    vector<int> diff;
    vector<int> original;

public:
    // Constructor initializes difference array from input array
    DifferenceArray(const vector<int>& arr) : original(arr), diff(arr.size(), 0) {
        diff[0] = arr[0];
        for (int i = 1; i < arr.size(); ++i) {
            diff[i] = arr[i] - arr[i-1];
        }
    }

    // Range update: Add 'value' to all elements from index l to r (inclusive)
    void rangeUpdate(int l, int r, int value) {
        diff[l] += value;
        if (r + 1 < diff.size()) {
            diff[r + 1] -= value;
        }
    }

    // Get final array after all updates
    vector<int> getArray() {
        vector<int> result = original;
        for (int i = 1; i < result.size(); ++i) {
            result[i] = result[i-1] + diff[i];
        }
        return result;
    }

    // Get value at a specific index
    int getValue(int index) {
        int value = original[index];
        for (int i = 0; i <= index; ++i) {
            value += diff[i];
        }
        return value;
    }
};

int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    DifferenceArray da(arr);
    
    da.rangeUpdate(1, 3, 10);  // Add 10 to indices 1-3
    da.rangeUpdate(2, 4, 5);   // Add 5 to indices 2-4
    
    vector<int> result = da.getArray();
    for (int num : result) {
        cout << num << " ";
    }
    return 0;
}
