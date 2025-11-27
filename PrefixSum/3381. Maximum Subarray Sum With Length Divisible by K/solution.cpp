/*  因為要取subarray長度為k的倍數
 *  例如 k = 4, 則取長度4, 8, 12, ...
 *  所以在每個index只需要看 此 (index + 1) % k 所紀錄的最小值
 *
 *  time  : O(N)
 *  space : O(K)
 */
class Solution {
public:
    long long maxSubarraySum(vector<int>& nums, int k) {
        vector<long long> minval(k, 1e16);
        minval[0] = 0;
        long long ans{LLONG_MIN}, cur{};
        for(int i = 0; i < nums.size(); ++i) {
            cur += nums[i];
            ans = max(ans, cur - minval[(i + 1) % k]);
            minval[(i + 1) % k] = min(minval[(i + 1) % k], cur);
        }
        return ans;
    }
};
