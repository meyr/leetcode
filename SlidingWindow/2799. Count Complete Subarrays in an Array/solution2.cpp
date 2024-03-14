/*
 *   不刪除unordered_map element的解法
 */

class Solution {
public:
    int countCompleteSubarrays(vector<int>& nums) {
        int sz = unordered_set<int>(begin(nums), end(nums)).size(), cnt{};
        unordered_map<int, int> m;
        int ans{};
        for(int r = 0, l = 0; r < nums.size(); ++r) {
            cnt += m[nums[r]]++ == 0;
            while(sz == cnt) {
                ans += nums.size() - r;
                if(m[nums[l]]-- == 1) cnt--;
                l++;
            }
        }
        return ans;
    }
};
