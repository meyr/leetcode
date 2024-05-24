/*
 *   最有competitive subsequence就是從subsequence找出最小的值 --> monotonic stack
 *
 *  time  : O(N)
 *  space : O(K)
 */

class Solution {
public:
    vector<int> mostCompetitive(vector<int>& nums, int k) {
        if(k == nums.size()) return nums;
        vector<int> ans;
        int sz = nums.size();
        for(int i = 0; i < nums.size(); ++i) {
            while(!ans.empty() && ans.size() + sz - i > k  && ans.back() > nums[i])
                ans.pop_back();
            if(ans.size() < k)
                ans.push_back(nums[i]);
            else if(ans.size() == k)
                ans.back() = min(ans.back(), nums[i]);
        }
        return ans;
    }
};
