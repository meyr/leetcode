/*
 *  使用prefix sum來判斷查詢的區域是否有 違反規則的element
 *
 *  time  : O(N + M), N: size of nums, M : size of queries
 *  space : O(N + M)
 */

class Solution {
public:
    vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries) {
        int sz = nums.size();
        vector<int> pfs(sz);
        for(int i = 1; i < sz; ++i) 
            pfs[i] = pfs[i - 1] + (nums[i - 1] % 2 == nums[i] % 2);
        vector<bool> rtn;
        for(auto& q : queries)
            rtn.push_back(pfs[q[1]] - pfs[q[0]] == 0);
        return rtn;
    }
};
/*
    3, 4, 1, 2, 6
    o, e, o, e, e

                x
    1, 0, 1, 0, 0

          x
    4, 3, 1, 6
    e, o, o, e
    0, 0, 1, 1
*/
