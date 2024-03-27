/*
 *   找出subarray product >= k 會簡單一點
 *   當找到product >= k的subarray之後 right->last都會是product >= k
 *   所以 cut += sz - right;
 *
 *   time complexity  : O(N)
 *   space complexity : O(1)
 */

class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if(k == 0) return 0;
        int sz = nums.size();
        int total = (1 + sz) * sz / 2;
        int cnt{}, cur{1};
        for(int left = 0, right = 0; right < sz; ++right) { // O(N)
            cur *= nums[right];
            while(left <= right && cur >= k) {
                cnt += sz - right;
                cur /= nums[left++];
            }
        }
        return total - cnt;
    }
};
