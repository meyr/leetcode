/*
 *
 *
 *      time  : O(N)
 *      sapce : O(N)
 */
class Solution {
    int helper(int cur, const vector<int>& costs) {
        if(cur < 0) return 1e9;
        else if(~mem[cur]) return mem[cur];
        else {
            return mem[cur] = min({
                helper(cur - 1, costs) + costs[cur - 1] + 1,
                helper(cur - 2, costs) + costs[cur - 1] + 4,
                helper(cur - 3, costs) + costs[cur - 1] + 9
            });
        }
    }
    vector<int> mem;
public:
    int climbStairs(int n, vector<int>& costs) {
        //mem.resize(n + 1, -1);
        //mem[0] = 0;
        //return helper(n, costs);
        vector<int> dp(n + 1);
        for(int i = 1; i <= n; ++i) {
            dp[i] = min({
                i - 1 >= 0 ? dp[i - 1] + costs[i - 1] + 1 : 1e9,
                i - 2 >= 0 ? dp[i - 2] + costs[i - 1] + 4 : 1e9,
                i - 3 >= 0 ? dp[i - 3] + costs[i - 1] + 9 : 1e9,
            });
        }
        return dp.back();
    }
};
/*
    n = 4
                0, 1, 2, 3, 4
                   1, 2, 3, 4    costs

                --->
*/
