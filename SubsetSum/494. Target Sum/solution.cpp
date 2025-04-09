/*  參考chatgpt solution
 *
 *  P + N = sum
 *  P - N = target
 * 
 *  2P = sum + target
 *   P = (sum + target) / 2    --> sum - target必為偶數
 *
 *  有多少組和可以達到P? --> subset sum counting
 *  和416想法類似 每個組合都是從nums[i] shift過來
 *
 *  dp[p] += dp[i - n] 從第i個移動n個到p的位置
 *
 *  time  : O(N + N * P) = O(NP)
 *  space : O(P)
 */
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = accumulate(begin(nums), end(nums), 0);
        if((sum - target) % 2 != 0 || abs(target) > sum) return 0;
        int p = (sum - target) / 2;
        vector<int> dp(p + 1);
        dp[0] = 1;
        for(auto& n : nums) {
            for(int i = p; i >= n; --i) 
                dp[i] += dp[i - n];
        }
        return dp.back();
    }
};
