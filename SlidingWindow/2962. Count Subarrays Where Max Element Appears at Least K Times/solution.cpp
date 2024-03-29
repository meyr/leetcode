/*
 *
 *   time  : O(N)
 *   space : O(1)
 */
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        int sz = nums.size();
        int maxv = *max_element(begin(nums), end(nums));
        long long ans{};
        for(int left = 0, right = 0; right < nums.size(); ++right) {
            k -= nums[right] == maxv;
            while(left <= right && k == 0) {
                ans += sz - right;
                k += nums[left++] == maxv;
            }
        }
        return ans;
    }
};
