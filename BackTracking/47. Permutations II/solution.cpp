class Solution {
    vector<vector<int>> rtn;
    int all_taken{};
    void helper(vector<int>& nums, vector<int>& ans, int taken) {
        if(taken == all_taken) rtn.push_back(ans);
        else {
            for(int i = 0; i < nums.size(); ++i) {
                if(!(taken >> i & 1)) {
                    taken |= 1 << i;
                    ans.push_back(nums[i]);
                    helper(nums, ans, taken);
                    ans.pop_back();
                    taken ^= 1 << i;
                    while(i + 1 < nums.size() && nums[i + 1] == nums[i]) ++i;   // __important__ 取得數字如果一樣就會有重複的情況
                }
            }
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(begin(nums), end(nums));
        vector<int> ans;
        int taken{};
        all_taken = (1 << nums.size()) - 1;
        helper(nums, ans, taken);
        return rtn;
    }
};
