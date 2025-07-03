/* 使用DP跑過所有可能的分類
 *
 *  time  : O(NK)
 *  space : O(NK)
 *
 */
class Solution {
    int helper(vector<int>& nums, int k, int i) {
        int ans{INT_MAX}, cur{};
        if(~mem[k][i]) return mem[k][i];
        if(k == 0 || i == nums.size()) ans = 0;
        else if(k == 1) {
            int rtn{};
            for(int j = i; j < nums.size(); ++j)
                rtn ^= nums[j];
            ans = rtn;
        } else {
            for(int j = i, remain = nums.size() - i - 1; remain >= k - 1; ++j, --remain) {
                cur ^= nums[j];
                ans = min(ans, max(cur, helper(nums, k - 1, j + 1))); //__important__ 每次選擇的cur, 就會選出那次的最大值，
            }                                                         //              只輸出每次選擇cur之後的最小值
        }
        return mem[k][i] = ans;
    }
    vector<vector<int>> mem;
public:
    int minXor(vector<int>& nums, int k) {
        mem.resize(k + 1, vector<int>(nums.size() + 1, -1));
        return helper(nums, k, 0);
    }
};
