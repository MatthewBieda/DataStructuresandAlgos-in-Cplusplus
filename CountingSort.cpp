#include <iostream>
#include <vector>

void CountingSort(std::vector<int>& input_array, int range) {
    int size = input_array.size();
    
    // Create a count array with all elements initialized to 0
    std::vector<int> count_array(range, 0);
    
    // Count the occurrences of each element in the input_array
    for (int i = 0; i < size; i++) {
        ++count_array[input_array[i]];
    }

    // Update count_array to store the cumulative sum
    for (int i = 1; i < range; i++) {
        count_array[i] += count_array[i - 1];
    }

    // Create an output array to store the sorted elements
    std::vector<int> output_array(size);

    // Place elements into the output array in sorted order
    for (int i = size - 1; i >= 0; i--) {
        output_array[--count_array[input_array[i]]] = input_array[i];
    }

    // Copy the sorted elements back into the input_array
    for (int i = 0; i < size; i++) {
        input_array[i] = output_array[i];
    }
}

int main() {
    std::vector<int> myArray = {4, 2, 2, 8, 3, 3, 1, 5, 6, 7};
    int range = 10;

    std::cout << "Before Sorting:" << std::endl;
    for (int num : myArray) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    CountingSort(myArray, range);

    std::cout << "After Sorting:" << std::endl;
    for (int num : myArray) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
