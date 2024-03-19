/*
 *   參考 : https://leetcode.com/problems/maximum-score-of-a-good-subarray/solutions/1108333/java-c-python-two-pointers/
 *
 *   因為k為中心 所以使用two pointers來代表subarray的上下界
 *   subarry擴大是往下個數比較大的方向 因為一樣的長度往數字大的方向比較有利
 *
 */

class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
        int sz = nums.size(), left = k, right = k;
        int ans, currMin = ans = nums[k];
        while(left > 0 || right < sz - 1) {
            int l = left > 0 ? nums[left - 1] : 0;
            int r = right < sz - 1 ? nums[right + 1] : 0;
            if(l < r)
                currMin = min(currMin, nums[++right]);
            else
                currMin = min(currMin, nums[--left]);
            ans = max(ans, currMin * (right - left + 1));    
        }
        return ans;

    }
};
