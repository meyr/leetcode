/*
    題目是問最長的subarray 所以使用slinding window
    使用map來記錄目前最大和最小值

    time  : O(NlogN)
    space : O(N)
*/
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        map<int, int> m;
        int ans{1};
        for(int left = 0, right = 0; right < nums.size(); ++right) {
            m[nums[right]]++;
            while(m.size() > 1 && m.rbegin()->first - m.begin()->first > limit) {
                if(--m[nums[left]] == 0) m.erase(nums[left]);
                left++;
            }
            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};
