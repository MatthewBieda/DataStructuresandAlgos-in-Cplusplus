#include <iostream>
#include <unordered_map>

std::unordered_map<int, std::unordered_map<int, int>> memo;

int dp(int x, int y) {
    // Check if the result is already memoized
    if (memo.contains(x) && memo[x].contains(y)) {
        return memo[x][y];
    }

    // Base case (example: when x or y is 0)
    if (x == 0 || y == 0) {
        return 1;  // Just an example value
    }

    // Recursive computation
    int result = dp(x - 1, y) + dp(x, y - 1);

    // Memoize the result before returning it
    memo[x][y] = result;

    return result;
}

int main() {
    int x = 3, y = 3;
    std::cout << "dp(" << x << ", " << y << ") = " << dp(x, y) << std::endl;

    return 0;
}

