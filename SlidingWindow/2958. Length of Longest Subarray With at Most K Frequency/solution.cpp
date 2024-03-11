class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        int left = 0, ans = 1;
        for(int right = 0; right < nums.size(); ++right) {
            m[nums[right]]++;
            while(left < right && m[nums[right]] > k)
                m[nums[left++]]--;
            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};
