#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

class Solution {
public:
    std::string longestDupSubstring(std::string s) {
        int lo = 1, hi = s.size();
        int start = -1, length = 0;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            int pos = possible(s, mid);
            if (pos != -1) {
                start = pos;
                length = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        return start != -1 ? s.substr(start, length) : "";
    }

private:
    int possible(const std::string& s, int len) {
        long long hash = 0, mod = 1'000'000'007, R = 26;
        int n = s.size();

        for (int i = 0; i < len; ++i)
            hash = (hash * R + (s[i] - 'a')) % mod;

        std::unordered_map<long long, std::vector<int>> seen;
        seen[hash].push_back(0);

        long long RM = 1; // R^(len-1) % mod
        for (int i = 1; i < len; ++i)
            RM = (RM * R) % mod;

        for (int start = len; start < n; ++start) {
            hash = (hash + mod - (s[start - len] - 'a') * RM % mod) % mod;
            hash = (hash * R + (s[start] - 'a')) % mod;

            if (seen.contains(hash)) {
                std::string cur = s.substr(start - len + 1, len);
                for (const int& i: seen[hash]) {
                    if (s.substr(i, len) == cur)
                        return i;
                }
            }

            seen[hash].push_back(start - len + 1);
        }
        return -1;
    }
};

int main() {
    Solution solution;

    std::string testcase = "banana";
    std::cout << solution.longestDupSubstring(testcase) << std::endl;

    return 0;
}
