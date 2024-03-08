class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        if(target == 1) return 1;
        int left = 0, sum{}, ans = nums.size() + 1;
        for(int right = 0; right < nums.size(); ++right) {
            sum += nums[right];
            while(sum >= target && left <= right) {
                ans = min(ans, right - left + 1);
                sum -= nums[left++];
            }
        }
        return ans == nums.size() + 1 ? 0 : ans;
    }
};
