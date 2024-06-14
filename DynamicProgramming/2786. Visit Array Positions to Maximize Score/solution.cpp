/*  
 *  很直覺的使用DP 每個element有兩種狀態 取和不取
 *  取的話 必須考慮和前一次的parity有沒有一樣
 *
 *  time  : O(N)
 *  space : O(N)
 */

class Solution {
    long long helper(vector<int>& nums, int x, int idx, int p) {
        if(~mem[idx][p]) return mem[idx][p];
        else {
            long long notake = helper(nums, x, idx + 1, p);
            long long take = nums[idx] - ((nums[idx] & 1) == p ? 0 : x) + 
                        helper(nums, x, idx + 1, nums[idx] & 1);
            return mem[idx][p] = max(notake, take);
        }
    }
    vector<vector<long long>> mem;
public:
    long long maxScore(vector<int>& nums, int x) {
        mem.resize(nums.size() + 1, vector<long long>(2, -1));
        mem.back()[0] = mem.back()[1] = 0;
        return helper(nums, x, 0, nums[0] % 2);        
    }
};
