/*
 *  每個element只有兩種情況 1. 加入前面的subarray 2. 成立新的subarray
 *
 *  time  : O(N)
 *  space : O(N)
 */

class Solution {
    using LL = long long;
    LL helper(vector<int>& nums, int idx, int w) {
        if(idx == nums.size()) return 0;
        if(~mem[idx][w + 1]) return mem[idx][w + 1];
        LL take_to_prev = helper(nums, idx + 1, w * -1) + nums[idx] * w;
        LL new_subarray = helper(nums, idx + 1, 1) + nums[idx];
        return mem[idx][w + 1] = max(take_to_prev, new_subarray);
    }
    vector<vector<LL>> mem;
public:
    long long maximumTotalCost(vector<int>& nums) {
        mem.resize(nums.size(), vector<LL>(3, -1));
        return helper(nums, 0, 1);
    }
};
