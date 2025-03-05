/*  看了hint使用DP求解
 *
 *  time  : O(N^2)
 *  space : O(N^2)
 */

class Solution {
    int helper(vector<int>& nums, int prev, int cur) {
        if(~mem[prev][cur]) return mem[prev][cur];
        if(cur >= nums.size()) return mem[prev][cur] = nums[prev];
        else if(cur == nums.size() - 1) return mem[prev][cur] = max(nums[prev], nums[cur]);
        else {
            return mem[prev][cur] = min({max(nums[cur], nums[cur + 1]) + helper(nums, prev, cur + 2),
                                    max(nums[prev], nums[cur + 1]) + helper(nums, cur, cur + 2),
                                    max(nums[prev], nums[cur]) + helper(nums, cur + 1, cur + 2)});            
        }
    }
    vector<vector<int>> mem;
public:
    int minCost(vector<int>& nums) {
        int sz = nums.size();
        mem.resize(sz + 1, vector<int>(sz + 1, -1));
        return helper(nums, 0, 1);
    }
};
