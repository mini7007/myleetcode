class Solution {
 public:
  string shortestCommonSupersequence(string str1, string str2) {
    string ans;
    int i = 0, j = 0;

    for (const char c : getLCS(str1, str2)) {
      while (str1[i] != c)
        ans += str1[i++];
      while (str2[j] != c)
        ans += str2[j++];
      ans += c;
      ++i, ++j;
    }

    return ans + str1.substr(i) + str2.substr(j);
  }

 private:
  string getLCS(const string& a, const string& b) {
    int m = a.length(), n = b.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Compute LCS length
    for (int i = 1; i <= m; ++i)
      for (int j = 1; j <= n; ++j)
        if (a[i - 1] == b[j - 1])
          dp[i][j] = 1 + dp[i - 1][j - 1];
        else
          dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

    // Reconstruct LCS
    string lcs;
    int i = m, j = n;
    while (i > 0 && j > 0) {
      if (a[i - 1] == b[j - 1]) {
        lcs += a[i - 1];
        --i, --j;
      } else if (dp[i - 1][j] > dp[i][j - 1]) {
        --i;
      } else {
        --j;
      }
    }

    reverse(lcs.begin(), lcs.end());
    return lcs;
  }
};
