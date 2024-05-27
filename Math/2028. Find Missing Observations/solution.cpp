class Solution {
public:
    vector<int> missingRolls(vector<int>& rolls, int mean, int n) {
        int total = accumulate(begin(rolls), end(rolls), 0); // O(M)
        int diff = mean * (rolls.size() + n) - total;
        if(diff < n || diff > n * 6) return {};
        vector<int> ans(n, diff / n);
        if(diff % n != 0) {
            for(int i = 0, m = diff % n; i < n && m; ++i, --m) //O(N)
                ans[i]++;
        }
        return ans;
        // time  : O(M+N)
        // spcae : O(M)
    }
};
/*
    3+2+4+3 = 12, mean = 4, n = 2

    6*4 = 24
    24 - 12 = 12

*/

