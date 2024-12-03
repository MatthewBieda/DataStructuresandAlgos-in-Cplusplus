#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Structure for a node in the grid
struct Node {
    int x, y;                     // Coordinates
    int costFromStart;            // Cost from the start node (g)
    int heuristicCost;            // Heuristic cost to the goal (h)
    int totalCost;                // Total cost (f = g + h)
    Node* parent;                 // Pointer to the parent node

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

    vector<Node> search(const Node& start, const Node& goal) {
        auto compare = [](Node* a, Node* b) { return *a > *b; };
        priority_queue<Node*, vector<Node*>, decltype(compare)> openSet(compare);
        unordered_map<int, unordered_map<int, int>> bestCost; // To track best f values
        vector<vector<bool>> closedSet(rows, vector<bool>(cols, false));

        openSet.push(new Node(start.x, start.y, 0, heuristic(start.x, start.y, goal.x, goal.y)));

        while (!openSet.empty()) {
            Node* current = openSet.top();
            openSet.pop();

            if (current->x == goal.x && current->y == goal.y) {
                vector<Node> path = reconstructPath(current);
                cleanUp(openSet);
                return path;
            }

            closedSet[current->x][current->y] = true;

            for (const auto& dir : directions) {
                int newX = current->x + dir.first;
                int newY = current->y + dir.second;

                if (isValid(newX, newY) && !closedSet[newX][newY]) {
                    int newCost = current->costFromStart + grid[newX][newY];
                    int heuristicCost = heuristic(newX, newY, goal.x, goal.y);

                    if (bestCost[newX][newY] == 0 || newCost + heuristicCost < bestCost[newX][newY]) {
                        bestCost[newX][newY] = newCost + heuristicCost;
                        openSet.push(new Node(newX, newY, newCost, heuristicCost, current));
                    }
                }
            }
        }

        cleanUp(openSet);
        return {}; // No path found
    }

private:
    int rows, cols;
    vector<vector<int>> grid;
    const vector<pair<int, int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    bool isValid(int x, int y) const {
        return x >= 0 && x < rows && y >= 0 && y < cols;
    }

    int heuristic(int x1, int y1, int x2, int y2) const {
        return abs(x1 - x2) + abs(y1 - y2); // Manhattan distance
    }

    vector<Node> reconstructPath(Node* node) const {
        vector<Node> path;
        while (node) {
            path.emplace_back(*node);
            node = node->parent;
        }
        reverse(path.begin(), path.end());
        return path;
    }

    template <typename T>
    void cleanUp(priority_queue<Node*, vector<Node*>, T>& openSet) {
        while (!openSet.empty()) {
            delete openSet.top();
            openSet.pop();
        }
    }
};

int main() {
    int rows = 5, cols = 5;
    vector<vector<int>> grid = {
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1}
    };

    AStarSearch aStar(rows, cols, grid);

    Node start(0, 0, 0, 0);
    Node goal(4, 4, 0, 0);

    vector<Node> path = aStar.search(start, goal);

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
