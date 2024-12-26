/*
 *
 * time  : O(KN), K : target + sum(nums) * 2, N : size of nums
 * space : O(KN)
 */
class Solution {
    int helper(vector<int>& nums, int target, int idx) {
        if(idx == nums.size()) return mem[target][idx] = (target == 0);
        if(mem.count(target) && mem[target].count(idx)) return mem[target][idx];
        return mem[target][idx] = helper(nums, target - nums[idx], idx + 1) + helper(nums, target + nums[idx], idx + 1);
    }
    unordered_map<int, unordered_map<int, int>> mem;
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sz = nums.size();
        return helper(nums, target, 0);
    }
};
/*  使用vector<vector<int>> mem來記錄不使用unordered<int, unordered<int, int>>
 *
 *  -1000 <= target <= 1000
    0 <= sum(nums[i]) <= 1000  --> -1000 ~ 1000  (nums)
                                +  -1000 ~ 1000  (target)
                                ----------------
                                    -2000 ~ 2000  (total)
                                      0   2000   4000
 */
class Solution {
    int helper(vector<int>& nums, int target, int idx) {
        if(idx == nums.size()) return mem[target + 2000][idx] = (target == 0);
        if(~mem[target + 2000][idx]) return mem[target + 2000][idx];
        return mem[target + 2000][idx] = helper(nums, target - nums[idx], idx + 1) + helper(nums, target + nums[idx], idx + 1);
    }
    vector<vector<int>> mem;
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sz = nums.size();
        mem.resize(4001, vector<int>(sz + 1, -1));
        return helper(nums, target, 0);
    }
};
