#include <vector>
#include <iostream>
#include <algorithm>

void binary_search(int n, std::vector<int>& numbers) {
    int left = 0;
    int right = numbers.size() - 1;

    int midpoint;

    while (left <= right) {
        midpoint = left + (right - left) / 2; // Avoid potential overflow

        if (numbers[midpoint] == n) {
            std::cout << "Integer " << n << " " << "is located at: " << midpoint << " " << "index of the sorted array" << std::endl;
	    return;
        } else if (numbers[midpoint] < n) {
            left = midpoint + 1;
        } else {
            right = midpoint - 1;
        }
    }

    // If we exit the loop, the number was not found;
    std::cout << "Integer " << n << " not found in the array" << std::endl;
    return;
}

int main() {
    int n = 7; 
    std::vector<int> numbers{2,56,3,58,7,1,89,-8,3};

    std::sort(numbers.begin(), numbers.end());
    for (const int& number: numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;

    // Valid test case
    binary_search(n, numbers);

    n = 44;
    // Invalid test case
    binary_search(n, numbers);

    return 0;
}
