/*
 *   從top-down memorization的解法
 *   變成
 *   bottom-up tabulation的解法
 *   
 */
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<vector<int>> dp(coins.size() + 1, vector<int>(amount + 1));
        for(int y = 0; y < coins.size(); ++y)
            dp[y][0] = 1;
        for(int y = coins.size() - 1; y >= 0; --y) {
            for(int x = 1; x <= amount; ++x) { // x = 0 is initial condition
                if(coins[y] > x) // no take
                    dp[y][x] = dp[y + 1][x];
                else // notake + take
                    dp[y][x] = dp[y + 1][x] + dp[y][x - coins[y]];
            }
        }
        return dp[0][amount];
        // time : O(NM)
        // space : O(NM)
    }
};
