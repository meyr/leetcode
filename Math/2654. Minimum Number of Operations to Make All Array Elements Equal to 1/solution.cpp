/*  苦手的數學題目
 *  參考: https://leetcode.com/problems/minimum-number-of-operations-to-make-all-array-elements-equal-to-1/solutions/3445725/explained-easy-gcd-and-intuition-by-i_pr-rvpl/
 *
 *  1. 先找看看nums裡面有沒有1, 如果有只要擴散出去就好
 *  2. 找出哪個subarray 所有數的gcd為1
 *
 *  time  : O(N + N^2) = O(N^2)
 *  space : O(1)
 */
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int sz = nums.size();
        int cnt = count(begin(nums), end(nums), 1);
        if(cnt) return sz - cnt;
        int ans = 1e7;
        for(int left = 0; left < sz; ++left) {
            int g = nums[left];
            for(int right = left + 1; right < sz; ++right) {
                g = __gcd(g, nums[right]);
                if(g == 1) ans = min(ans, right - left + sz - 1); // 找到了subarray全部的數gcd == 1, 讓subarray變成1的次數為right - left
            }                                                     // 有了1之後還需要sz - 1次把剩下的都變為1
        }
        return ans == 1e7 ? -1 : ans;
    }
};
