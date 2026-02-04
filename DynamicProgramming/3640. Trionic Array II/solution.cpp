/* ref : https://leetcode.com/problems/trionic-array-ii/solutions/7038543/modified-kadane-short-clean-code-c-by-ru-gcja/
 * 還有AI的解說 這是state machine DP問題
 *              定義狀態 0 : start point  <-- 所有數值都可以當起始點
 *                       1 : increasing
 *                       2 : decreasing
 *                       3 : increasing   <-- 到達這一階段才是題目要的 inc-dec-inc trionic array
 *
 *
 *              dp[1][i] = max(dp[0][i - 1], dp[1][i - 1]) + nums[i];   state1 是從起始點 或是 上升中的數值而來
 *              dp[2][i] = max(dp[1][i - 1], dp[2][i - 1]) + nums[i];   state2 是從上升中 或是 下降中的數值而來
 *              dp[3][i] = max(dp[2][i - 1], dp[3][i - 1]) + nums[i];   state3 是從下降中 或是 上升中的數值而來
 *
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
public:
    long long maxSumTrionic(vector<int>& a) {
        int n = a.size();
        /*
                        dp[1]       /dp[3]
                       /  \        /
                      /    \      /
        ---dp[0]---- /     dp[2]


        dp[0] = start phase
        dp[1] = 1st increaseing phase
        dp[2] = 1st decreaseing phase
        dp[3] = 2nd increasing
        */

        vector<vector<long long>> dp(4, vector<long long>(n, -1e18));   //__important__ 如果沒達成條件就是-1e18

        long long ans = -1e18;
        for(int i = 0; i < n; i++) {
            dp[0][i] = a[i];    // 每一個element都可以是起始點
            if(i) {             // 跳過i == 0 因為 沒有前一個element
                if(a[i] > a[i - 1]) dp[1][i] = max(dp[0][i - 1] + a[i], dp[1][i - 1] + a[i]);
                if(a[i] < a[i - 1]) dp[2][i] = max(dp[1][i - 1] + a[i], dp[2][i - 1] + a[i]);
                if(a[i] > a[i - 1]) dp[3][i] = max(dp[2][i - 1] + a[i], dp[3][i - 1] + a[i]);
            }
            ans = max(ans, dp[3][i]); // 每個點都可能是結束點
        }

        return ans;
    }
};
