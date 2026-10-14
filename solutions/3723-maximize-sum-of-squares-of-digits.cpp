// Problem: 3723. Maximize Sum of Squares of Digits
// URL: https://leetcode.com/problems/maximize-sum-of-squares-of-digits/
// Language: C++

#include <string>
using namespace std;

class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        if (sum > 9 * num) return "";
        int k = sum / 9, r = sum % 9;
        string res(k, '9');
        if (r > 0) res += char('0' + r);
        res.append(num - res.size(), '0');
        return res;
    }
};
