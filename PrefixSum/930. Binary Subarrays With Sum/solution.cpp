class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        int ans{}, pfs{};
        unordered_map<int, int> m{{0, 1}};
        for(auto& n : nums) {
            pfs += n;
            ans += m[pfs - goal];
            m[pfs]++;
        }
        return ans;
    }
};
