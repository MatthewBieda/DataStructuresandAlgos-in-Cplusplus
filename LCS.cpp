#include <string>
#include <vector>
#include <iostream>

class Solution {
public:
    int longestCommonSubsequence(std::string text1, std::string text2) {
        int n = text1.size();
        int m = text2.size();

        dp = std::vector<std::vector<int>> (n + 1, std::vector<int>(m + 1, -1));

        return lcs(0, 0, text1, text2);
    }

private:
    std::vector<std::vector<int>> dp;

    int lcs(int text1_index, int text2_index, const std::string& text1, const std::string& text2) {
        // If either string is exhausted, we can't make any more matches
        if (text1_index == text1.length() || text2_index == text2.length()) {
            return 0;
        }

        if (dp[text1_index][text2_index] != -1) {
            return dp[text1_index][text2_index];
        }

        // character match
        if (text1[text1_index] == text2[text2_index]) {
            int charMatch = 1 + lcs(text1_index + 1, text2_index + 1, text1, text2);
            dp[text1_index][text2_index] = charMatch;
        } else {
            int skipText1 = lcs(text1_index + 1, text2_index, text1, text2);
            int skipText2 = lcs(text1_index, text2_index + 1, text1, text2);
            dp[text1_index][text2_index] = std::max(skipText1, skipText2);
        }

        return dp[text1_index][text2_index];
    }
};

int main() {
    Solution solution;

    std::string text1 = "abcde";
    std::string text2 = "ace";

    int lcs = solution.longestCommonSubsequence(text1, text2);
    std::cout << lcs << std::endl;

    return 0;

}
