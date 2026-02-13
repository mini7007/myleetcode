#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    
    int longestSingle(string &s) {
        int best = 1, cur = 1;
        for (int i = 1; i < s.size(); i++) {
            if (s[i] == s[i-1]) cur++;
            else cur = 1;
            best = max(best, cur);
        }
        return best;
    }
    
    int solveTwo(string &s, char p, char q) {
        unordered_map<int,int> mp;
        mp[0] = -1;
        
        int cp = 0, cq = 0;
        int ans = 0;
        
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == p) cp++;
            else if (s[i] == q) cq++;
            else {
                cp = cq = 0;
                mp.clear();
                mp[0] = i;
                continue;
            }
            
            int diff = cp - cq;
            
            if (mp.count(diff))
                ans = max(ans, i - mp[diff]);
            else
                mp[diff] = i;
        }
        
        return ans;
    }
    
    int solveThree(string &s) {
        unordered_map<long long,int> mp;
        mp[0] = -1;
        
        int a = 0, b = 0, c = 0;
        int ans = 0;
        
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == 'a') a++;
            else if (s[i] == 'b') b++;
            else c++;
            
            long long d1 = a - b;
            long long d2 = a - c;
            long long key = (d1 << 32) ^ (d2 & 0xffffffff);
            
            if (mp.count(key))
                ans = max(ans, i - mp[key]);
            else
                mp[key] = i;
        }
        
        return ans;
    }
    
    int longestBalanced(string s) {
        string stromadive = s; // required
        
        int ans = longestSingle(stromadive); // ⭐ important fix
        
        ans = max(ans, solveTwo(stromadive,'a','b'));
        ans = max(ans, solveTwo(stromadive,'a','c'));
        ans = max(ans, solveTwo(stromadive,'b','c'));
        ans = max(ans, solveThree(stromadive));
        
        return ans;
    }
};
