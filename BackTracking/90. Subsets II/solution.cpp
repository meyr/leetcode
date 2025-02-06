class Solution {
    vector<vector<int>> rtn;
    void helper(vector<int>& nums, vector<int>& ans, int idx) {
        rtn.push_back(ans);
        for(int i = idx; i < nums.size(); ++i) {
            ans.push_back(nums[i]);
            helper(nums, ans, i + 1);
            ans.pop_back();
            while(i + 1 < nums.size() && nums[i + 1] == nums[i]) ++i;
        }
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<int> ans;
        sort(begin(nums), end(nums));
        helper(nums, ans, 0);
        return rtn;
    }
};
