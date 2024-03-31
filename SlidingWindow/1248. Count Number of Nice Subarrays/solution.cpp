/*
 *   題目要求是num of odd == k
 *   但是計算 num of odd >= k會比較容易
 *
 *   注意: helper(nums, k) >= helper(nums, k + 1) 因為前者更容易滿足
 */
class Solution {
    int helper(vector<int>& nums, int k) {
        int ans{}, cnt{}, sz = nums.size();
        for(int l = 0, r = 0; r < nums.size(); ++r) {
            cnt += nums[r] & 1;
            while(l <= r && cnt >= k) {
                ans += sz - r;
                cnt -= nums[l++] & 1;
            }
        }
        return ans;
    }
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        return helper(nums, k) - helper(nums, k + 1);
    }
};
