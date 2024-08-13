class Solution {
    void helper(vector<int>& nums, int target, int idx, vector<int>& sol, vector<vector<int>>& rtn) {
        if(target == 0) rtn.push_back(sol); // 先判斷target==0 避免idx == nums.size()卻沒存到
        else if(idx == nums.size()) return;
        else {
            for(int i = idx; i < nums.size() && nums[i] <= target; ++i) {
                sol.push_back(nums[i]);
                helper(nums, target - nums[i], i + 1, sol, rtn);
                sol.pop_back();
                while(i + 1 < nums.size() && nums[i] == nums[i + 1]) i++; // 跳過相同的value避免重複的combination
            }
        }
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> rtn;
        vector<int> sol;
        sort(begin(candidates), end(candidates));
        helper(candidates, target, 0, sol, rtn);
        return rtn;
    }
};
/*
    10, 1, 2, 7, 6, 1, 5
    1, 1, 2, 5, 6, 7, 10

    1, 2, 2, 2, 5
*/
