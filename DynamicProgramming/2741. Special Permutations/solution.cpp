/*
 *  一開始以為是數學題
 *  後來看到長度只有14所以使用了Backtracking但是TLE
 *  再來從BT解修改成DP 並加入memorization的功能
 *
 *  time  : O(N*2^N)
 *  space : O(N*2^N)
 */
class Solution {
    int mask{}, mod = 1e9 + 7;
    int helper(vector<int>& nums, int prev, int used) {
        if(~mem[prev][used]) return mem[prev][used];
        int rtn{0};
        for(int i = 0; i < nums.size(); ++i) {
            if(((used >> i) & 1) == 0 && 
                (nums[prev] % nums[i] == 0 || 
                nums[i] % nums[prev] == 0)) {
                used |= 1 << i;
                rtn = (rtn + helper(nums, i, used)) % mod;
                used &= ~(1 << i);
            }
        }
        return mem[prev][used] = rtn;
    }
    vector<vector<int>> mem;
public:
    int specialPerm(vector<int>& nums) {
        int used{}, sz = nums.size();
        mask = pow(2, sz) - 1;
        mem.resize(sz, vector<int>(pow(2, sz), -1));
        for(int i = 0; i < sz; ++i)
            mem[i][mask] = 1;
        int ans{};
        for(int i = 0; i < nums.size(); ++i)
            ans = (ans + helper(nums, i, 1 << i)) % mod;
        
        return ans;
    }
};
