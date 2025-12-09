/*
 *  time  : O(N)
 *  sapce : O(N)
 */
class Solution {
public:
    int specialTriplets(vector<int>& nums) {
        int sz = nums.size();
        vector<int> fwd(sz);
        unordered_map<int, int> um;
        for(int i = 0; i < sz; ++i) {
            fwd[i] = um[nums[i] * 2];
            um[nums[i]]++;
        }
        int ans{};
        um.clear();
        for(int i = sz - 1; i >= 0; --i) {
            long long bwd = um[nums[i] * 2];
            um[nums[i]]++;
            ans = (ans + fwd[i] * bwd) % (int)(1e9 + 7);
        }
        return ans;
    }
};
