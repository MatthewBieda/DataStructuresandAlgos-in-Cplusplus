#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Structure representing a grid node
struct Node {
    int x, y;                     // Coordinates in the grid
    int costFromStart;            // Cost from the start node (g)
    int heuristicCost;            // Heuristic cost to the goal node (h)
    int totalCost;                // Total cost (f = g + h)
    Node* parent;                 // Pointer to the parent node for path reconstruction

    Node(int x, int y, int g, int h, Node* parent = nullptr)
        : x(x), y(y), costFromStart(g), heuristicCost(h),
          totalCost(g + h), parent(parent) {}

    // Comparator for priority queue (min-heap)
    bool operator>(const Node& other) const {
        return totalCost > other.totalCost;
    }
};

class AStarSearch {
public:
    AStarSearch(int rows, int cols, const vector<vector<int>>& grid)
        : rows(rows), cols(cols), grid(grid) {}

    // Perform the A* search algorithm
    vector<Node> search(const Node& start, const Node& goal) {
        // Priority queue for open set (min-heap sorted by total cost f = g + h)
        auto compare = [](Node* a, Node* b) { return *a > *b; };
        priority_queue<Node*, vector<Node*>, decltype(compare)> openSet(compare);

        // Track the best total cost for each node
        unordered_map<int, unordered_map<int, int>> bestCost;

        // Closed set to mark visited nodes
        vector<vector<bool>> closedSet(rows, vector<bool>(cols, false));

        // Add the start node to the open set
        openSet.push(new Node(start.x, start.y, 0, heuristic(start.x, start.y, goal.x, goal.y)));

        while (!openSet.empty()) {
            Node* current = openSet.top();
            openSet.pop();

            // Check if we've reached the goal
            if (current->x == goal.x && current->y == goal.y) {
                vector<Node> path = reconstructPath(current);
                cleanUp(openSet);
                return path;
            }

            // Mark the current node as visited
            closedSet[current->x][current->y] = true;

            // Explore neighbors
            for (const auto& direction : directions) {
                int newX = current->x + direction.first;
                int newY = current->y + direction.second;

                // Skip invalid or already visited nodes
                if (!isValid(newX, newY) || closedSet[newX][newY]) {
                    continue;
                }

                int newCost = current->costFromStart + grid[newX][newY];
                int heuristicCost = heuristic(newX, newY, goal.x, goal.y);

                // If a better cost is found, add the neighbor to the open set
                if (bestCost[newX][newY] == 0 || newCost + heuristicCost < bestCost[newX][newY]) {
                    bestCost[newX][newY] = newCost + heuristicCost;
                    openSet.push(new Node(newX, newY, newCost, heuristicCost, current));
                }
            }
        }

        cleanUp(openSet); // Clean up allocated memory
        return {}; // Return an empty path if no solution is found
    }

private:
    int rows, cols; // Dimensions of the grid
    vector<vector<int>> grid; // Grid representation with weights
    const vector<pair<int, int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; // 4 possible movements (NSEW)

    // Check if a cell is within bounds
    bool isValid(int x, int y) const {
        return x >= 0 && x < rows && y >= 0 && y < cols;
    }

    // Calculate Manhattan distance (heuristic for A*)
    int heuristic(int x1, int y1, int x2, int y2) const {
        return abs(x1 - x2) + abs(y1 - y2);
    }

    // Reconstruct the path from the goal node to the start node
    vector<Node> reconstructPath(Node* node) const {
        vector<Node> path;
        while (node) {
            path.emplace_back(*node);
            node = node->parent;
        }
        reverse(path.begin(), path.end()); // Reverse to get the path from start to goal
        return path;
    }

    // Clean up dynamically allocated memory in the open set
    template <typename T>
    void cleanUp(priority_queue<Node*, vector<Node*>, T>& openSet) {
        while (!openSet.empty()) {
            delete openSet.top();
            openSet.pop();
        }
    }
};

int main() {
    // Grid dimensions and weights
    int rows = 5, cols = 5;
    vector<vector<int>> grid = {
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1}
    };

    // Create A* search object
    AStarSearch aStar(rows, cols, grid);

    // Define start and goal nodes
    Node start(0, 0, 0, 0);
    Node goal(4, 4, 0, 0);

    // Perform the search
    vector<Node> path = aStar.search(start, goal);

    // Print the results
    if (!path.empty()) {
        cout << "Path found:\n";
        for (const Node& node : path) {
            cout << "(" << node.x << ", " << node.y << ") ";
        }
        cout << endl;
    } else {
        cout << "No path found." << endl;
    }

    return 0;
}
