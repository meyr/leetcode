/*  一開始以為是prefix sum的問題 想了一陣子沒解出來
 *  後來看hint是使用slinding window 其實subarray應該就要想到是slinding window
 *  重點是left往右移動 cnt要如何修正  
 *
 *  1, 1, 1, 1, 1
 *                      um[1] = 5 cnt = 1+2+3+4
 *  l           r
 *     l        r       um[1] = 4 cnt = 1+2+3
 *
 *  time  : O(N)
 *  space : O(N)
 */

class Solution {
public:
    long long countGood(vector<int>& nums, int k) {
        long long ans{}, cnt{};
        unordered_map<int, int> um;
        for(int left = 0, right = 0; right < nums.size(); ++right) {
            cnt += um[nums[right]]++;
            while(cnt >= k) {
                ans += nums.size() - right;
                cnt -= um[nums[left]]-- - 1;
                left++;
            }
        }
        return ans;
    }
};
