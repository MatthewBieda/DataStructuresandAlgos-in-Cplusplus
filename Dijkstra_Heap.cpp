#include <vector>
#include <queue> 
#include <iostream>
#include <unordered_set>

class Solution {
public:
    int networkDelayTime(std::vector<std::vector<int>>& times, int n, int k) {
        std::vector<std::vector<std::pair<int,int>>> adj(n+1);

        for (const std::vector<int>& time: times) {
            adj[time[0]].push_back({time[1], time[2]});
        }

        std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> minHeap;
        minHeap.push({0, k});

        std::unordered_set<int> visited;

        int time = 0;

        while (!minHeap.empty()) {
            const auto [currWeight, currNode] = minHeap.top();
            minHeap.pop();

            if (visited.contains(currNode)) {
                continue;
            }

            visited.insert(currNode);

            time = currWeight;

            for (const auto& [nextNode, nextWeight]: adj[currNode]) {
                if (!visited.contains(nextNode)) {
                    minHeap.push({currWeight + nextWeight, nextNode});
                }
            }

        }   
        return visited.size() == n ? time : -1;
    }
};

int main() {
    Solution solution;


    int node_count = 4;
    int destination = 2;    
    std::vector<std::vector<int>> times{{2,1,1}, {2,3,1}, {3,4,1}};

    int result = solution.networkDelayTime(times, node_count, destination);

    std::cout << result << std::endl;

    return 0;
}
