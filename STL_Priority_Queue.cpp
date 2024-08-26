#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::priority_queue<int> maxHeap;   // Max-heap
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;  // Min-heap

    maxHeap.push(10);
    maxHeap.push(20);
    maxHeap.push(5);

    minHeap.push(10);
    minHeap.push(20);
    minHeap.push(5);

    std::cout << "Max-Heap top: " << maxHeap.top() << std::endl;
    std::cout << "Min-Heap top: " << minHeap.top() << std::endl;

    return 0;
}

