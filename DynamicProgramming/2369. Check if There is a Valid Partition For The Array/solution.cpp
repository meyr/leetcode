/*
 *   標準的DP問題 因為切兩個或是三個還要根據後面的結果
 *
 */

class Solution {
    bool helper(vector<int>& nums, int idx) {
        if(~mem[idx]) return mem[idx];
        bool rtn{false};
        if(idx + 1 < nums.size())
            rtn |= nums[idx] == nums[idx + 1] && helper(nums, idx + 2);
        if(idx + 2 < nums.size())
            rtn |= ((nums[idx] == nums[idx + 1] && nums[idx + 1] == nums[idx + 2]) || 
                     (nums[idx] + 1 == nums[idx + 1] && nums[idx + 1] + 1== nums[idx + 2])) &&
                     helper(nums, idx + 3);
        return mem[idx] = rtn;
    }
    vector<int> mem;
public:
    bool validPartition(vector<int>& nums) {
        mem.resize(nums.size() + 1, -1);
        mem.back() = 1;
        return helper(nums, 0);
    }
};
