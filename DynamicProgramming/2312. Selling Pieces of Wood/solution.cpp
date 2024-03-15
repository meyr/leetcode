/*
 *   參考解答 : https://leetcode.com/problems/selling-pieces-of-wood/solutions/2170082/partition-dp-recursion-memoization-tabulation-space-optimization/
 *
 */

class Solution {
    map<pair<int, int>, int> rect; //<h, w>, price
    vector<vector<long long>> mem;
    long long helper(int m, int n) {
        if(~mem[m][n]) return mem[m][n];
        long long  ans = rect[make_pair(m, n)];  // 剛好m, n切到有方塊的地方
        for(int i = 1; i <= m / 2; ++i) // 因為上下會一樣所以不需要做超過m/2
            ans = max(ans, helper(i, n) + helper(m - i, n));
        for(int i = 1; i <= n / 2; ++i) // 因為左右會一樣所以不需要做超過n/2
            ans = max(ans, helper(m, i) + helper(m, n - i));
        return mem[m][n] = ans;
    }
public:
    long long sellingWood(int m, int n, vector<vector<int>>& prices) {
        for(auto& p : prices)
            rect[make_pair(p[0], p[1])] = p[2];
        mem.resize(m + 1, vector<long long>(n + 1, -1));
        for(int i = 0; i < m; ++i) mem[i][0] = 0;
        for(int i = 0; i < n; ++i) mem[0][i] = 0;
        return helper(m, n);
    }
};
