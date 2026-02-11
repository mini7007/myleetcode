#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
private:
    struct Node {
        int l, r;
        int mn, mx;
        int lazy;
    };

    vector<Node> tr;

    void build(int u, int l, int r) {
        tr[u] = {l, r, 0, 0, 0};
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
    }

    void apply(int u, int v) {
        tr[u].mn += v;
        tr[u].mx += v;
        tr[u].lazy += v;
    }

    void pushUp(int u) {
        tr[u].mn = min(tr[u << 1].mn, tr[u << 1 | 1].mn);
        tr[u].mx = max(tr[u << 1].mx, tr[u << 1 | 1].mx);
    }

    void pushDown(int u) {
        if (tr[u].lazy != 0) {
            apply(u << 1, tr[u].lazy);
            apply(u << 1 | 1, tr[u].lazy);
            tr[u].lazy = 0;
        }
    }

public:
    SegmentTree(int n) {
        tr.resize((n + 1) << 2);
        build(1, 0, n);
    }

    // Range add: add v to [l, r]
    void modify(int u, int l, int r, int v) {
        if (tr[u].l >= l && tr[u].r <= r) {
            apply(u, v);
            return;
        }
        pushDown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        if (l <= mid) modify(u << 1, l, r, v);
        if (r > mid) modify(u << 1 | 1, l, r, v);
        pushUp(u);
    }

    // Binary search on segment tree:
    // find smallest position where prefix sum == target
    int query(int u, int target) {
        if (tr[u].l == tr[u].r) return tr[u].l;
        pushDown(u);
        if (tr[u << 1].mn <= target && target <= tr[u << 1].mx)
            return query(u << 1, target);
        return query(u << 1 | 1, target);
    }
};

class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        int n = nums.size();
        SegmentTree st(n);

        unordered_map<int, int> last;
        int now = 0;      // current prefix difference
        int ans = 0;

        for (int i = 1; i <= n; ++i) {
            int x = nums[i - 1];
            int det = (x & 1) ? 1 : -1;

            // remove previous contribution if exists
            if (last.count(x)) {
                st.modify(1, last[x], n, -det);
                now -= det;
            }

            // add new contribution
            last[x] = i;
            st.modify(1, i, n, det);
            now += det;

            // find earliest position with same prefix sum
            int pos = st.query(1, now);
            ans = max(ans, i - pos);
        }

        return ans;
    }
};
