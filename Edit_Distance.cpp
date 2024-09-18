#include <vector>
#include <iostream>
#include <string>

// 2D dp
// Similar to LCS problem

class Solution {
public:
    int minDistance(std::string word1, std::string word2) {
        int n = word1.length();
        int m = word2.length();

        dp = std::vector<std::vector<int>> (n + 1, std::vector<int>(m + 1, -1));

        return minDist(0, 0, word1, word2, n, m);
    }

private:
    std::vector<std::vector<int>> dp;

    int minDist(int i, int j, const std::string& word1, const std::string& word2, int n, int m) {
        // base case, string exhaustion
        if (i == n) {
            return m - j;
        } else if (j == m) {
            return n - i;
        }

        // If already recorded in DP matrix just return this value
        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        // already matching character, just skip to next indexes
        if (word1[i] == word2[j]) {
            dp[i][j] = minDist(i + 1, j + 1, word1, word2, n, m);
        } else {
        // Find optimal choice between insertion, deletion and replacement
            int replace = 1 + minDist(i + 1, j + 1, word1, word2, n, m);
            int insertion = 1 + minDist(i, j + 1, word1, word2, n, m);
            int deletion = 1 + minDist(i + 1, j, word1, word2, n, m);
            
            int min1 = std::min(replace, insertion);
            dp[i][j] = std::min(min1, deletion);
        }

        return dp[i][j];
    }
};

int main() {
    Solution solution;

    std::string word1("horse");
    std::string word2("ros");

    int res = solution.minDistance(word1, word2);

    std::cout << res << std::endl;

    return 0;
}
