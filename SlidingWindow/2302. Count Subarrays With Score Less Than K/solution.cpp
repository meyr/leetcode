/*
 *   參考解答 : https://leetcode.com/problems/count-subarrays-with-score-less-than-k/solutions/2138778/sliding-window/
 *   想的太複雜了 其實很容易
 *
 */
class Solution {
public:
    long long countSubarrays(vector<int>& nums, long long k) {
        long long sum{}, ans{};
        for(int r = 0, l = 0; r < nums.size(); ++r) {
            sum += nums[r];
            while(sum * (r - l + 1) >= k)
                sum -= nums[l++];
            ans += r - l + 1; // 這裡面以right為結尾subarray都滿足
        }
        return ans;
    }
};
