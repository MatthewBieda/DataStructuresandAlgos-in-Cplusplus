#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

// Simple structure for a node in the grid
struct Node {
    int x, y;   // Coordinates
    int g;      // Cost from start node
    int h;      // Heuristic cost to goal
    int f;      // Total cost (g + h)
    Node* parent;

    Node(int x, int y, int g, int h, Node* parent = nullptr)
        : x(x), y(y), g(g), h(h), f(g + h), parent(parent) {}

    // Comparator for priority queue (min-heap)
    bool operator>(const Node& other) const {
        return f > other.f;
    }
};

class AStarSearch {
public:
    AStarSearch(int rows, int cols, const vector<vector<int>>& grid)
        : rows(rows), cols(cols), grid(grid) {}

    vector<Node> search(const Node& start, const Node& goal) {
        priority_queue<Node, vector<Node>, greater<>> openSet;
        vector<vector<bool>> closedSet(rows, vector<bool>(cols, false));

        openSet.push(start);

        while (!openSet.empty()) {
            Node current = openSet.top();
            openSet.pop();

            if (current.x == goal.x && current.y == goal.y) {
                return reconstructPath(current);
            }

            closedSet[current.x][current.y] = true;

            for (const auto& dir : directions) {
                int newX = current.x + dir.first;
                int newY = current.y + dir.second;

                if (isValid(newX, newY) && !closedSet[newX][newY]) {
                    int g = current.g + grid[newX][newY];
                    int h = heuristic(newX, newY, goal.x, goal.y);
                    Node neighbor(newX, newY, g, h, new Node(current));

                    if (!isInOpenSet(neighbor, openSet)) {
                        openSet.push(neighbor);
                    }
                }
            }
        }

        return {}; // Return an empty path if no path is found
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

    bool isInOpenSet(const Node& node, priority_queue<Node, vector<Node>, greater<>>& openSet) {
        // Use a simple linear search to check if the node is already in the open set
        priority_queue<Node, vector<Node>, greater<>> temp = openSet;
        while (!temp.empty()) {
            Node n = temp.top();
            temp.pop();
            if (n.x == node.x && n.y == node.y && n.f <= node.f) {
                return true;
            }
        }
        return false;
    }

    vector<Node> reconstructPath(const Node& node) {
        vector<Node> path;
        const Node* current = &node;
        while (current) {
            path.push_back(*current);
            current = current->parent;
        }
        reverse(path.begin(), path.end());
        return path;
    }
};

int main() {
    int rows = 5;
    int cols = 5;
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
        cout << "Path found:" << endl;
        for (const Node& node : path) {
            cout << "(" << node.x << ", " << node.y << ") ";
        }
        cout << endl;
    } else {
        cout << "No path found." << endl;
    }

    return 0;
}

