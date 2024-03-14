/*
 *   重點是滿足條件後 計算subarray的方法
 *
 */

class Solution {
public:
    int countCompleteSubarrays(vector<int>& nums) {
        unordered_set<int> s(begin(nums), end(nums));
        unordered_map<int, int> m;//value, count
        int sz = s.size(), ans{};
        for(int r = 0, l = 0; r < nums.size(); ++r) {
            m[nums[r]]++;
            while(m.size() == sz) {
                ans += nums.size() - r; // 已經滿足 所以已right 到 nums.size() - 1 都會滿足
                if(--m[nums[l]] == 0)
                    m.erase(nums[l]);
                l++;
            }
        }
        return ans;
    }
};
