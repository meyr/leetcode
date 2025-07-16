/* (nums[i - 1] + nums[i]) % 2 = even/odd 可以化簡為xor
 *
 *   odd  + odd  = even --> (1^1 = 0)
 *   odd  + even = odd  --> (1^0 = 1)
 *   even + odd  = even --> (0^1 = 1)
 *   even + even = even --> (0^0 = 0)
 *
 *  time  : O(4N) = O(N)
 *  space : O(N)
 */
class Solution {
    int helper(vector<int>& nums, int prev_p, int priority, int idx) {
        int shift = (prev_p << 1) | priority;
        if(~mem[shift][idx]) return mem[shift][idx];
        int cur = nums[idx] % 2;
        if(priority == (cur ^ prev_p))  // 如果cur ^ prev_p 等於目標priority 就選這個一個
            return mem[shift][idx] = helper(nums, cur, priority, idx + 1) + 1;
        else
            return mem[shift][idx] = helper(nums, prev_p, priority, idx + 1);   // 不選
    }
    vector<vector<int>> mem;
public:
    int maximumLength(vector<int>& nums) {
        int sz = nums.size();
        mem.resize(4, vector<int>(sz + 1, -1));
        mem[0][sz] = mem[1][sz] = mem[2][sz] = mem[3][sz] = 0;
        return max({helper(nums, 0, 0, 0), helper(nums, 0, 1, 0),       // 列舉四種可能
                    helper(nums, 1, 0, 0), helper(nums, 1, 1, 0)});
    }
};
