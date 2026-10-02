// Problem: 22. Generate Parentheses
// URL: https://leetcode.com/problems/generate-parentheses/
// Language: C++
// Solved: 2026-10-02

#include <vector>
#include <string>
#include <utility>

using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        dfs(n, n, "", ans);
        return ans;
    }

private:
    void dfs(int l, int r, string&& path, vector<string>& ans) {
        if (l == 0 && r == 0) {
            ans.push_back(path);
            return;
        }
        if (l > 0) {
            path.push_back('(');
            dfs(l - 1, r, std::move(path), ans);
            path.pop_back();
        }
        if (l < r) {
            path.push_back(')');
            dfs(l, r - 1, std::move(path), ans);
            path.pop_back();
        }
    }
};
