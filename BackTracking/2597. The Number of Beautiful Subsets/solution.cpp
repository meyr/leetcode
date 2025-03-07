/*  看到這題constraints就意識到這是Backtracking的問題 因為 1 <= nums.length <= 18
 *  使用一個unordered_map每次要取此nums[idx]就檢查是否有 nums[idx] + k, 或是 nums[idx] - k在裡面
 *
 *  time  : O(2^N) , N : size of nums
 *  space : O(N)
 */
class Solution {
    int rtn{}, k;
    void helper(vector<int>& nums, unordered_map<int, int>& ans, int idx) {
        if(idx == nums.size()) {
            rtn++;
        } else {
            helper(nums, ans, idx + 1);
            if(ans[nums[idx] - k] == 0 && ans[nums[idx] + k] == 0) {
                ans[nums[idx]]++;
                helper(nums, ans, idx + 1);
                ans[nums[idx]]--;
            }
        }
    }
public:
    int beautifulSubsets(vector<int>& nums, int k) {
        this->k = k;
        for(int i = 0; i < nums.size(); ++i) {
            unordered_map<int, int> ans;
            ans[nums[i]]++;
            helper(nums, ans, i + 1);
        }
        return rtn;
    }
};
