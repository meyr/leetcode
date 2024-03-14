/*
 *  我只寫出prefix sum的解答 這題也可以用sliding window來解
 *  參考解答 : https://leetcode.com/problems/binary-subarrays-with-sum/solutions/186683/c-java-python-sliding-window-o-1-space/
 *  這邊的重點是 subarray sum == goal 等於 ((subarray sum 最多 goal) - (subarray sum 最多 goal - 1))
 *  因為slinding window只能處理 >= 或 <= 的題目
 */
class Solution {
    int helper(vector<int>& nums, int goal) {
        if(goal < 0) return 0;
        int ans{}, sum{};
        for(int r = 0, l = 0; r < nums.size(); ++r) {
            sum += nums[r];
            while(sum > goal)
                sum -= nums[l++];
            ans += r - l + 1;
        }
        return ans;
    }
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        return helper(nums, goal) - helper(nums, goal - 1);
    }
};
