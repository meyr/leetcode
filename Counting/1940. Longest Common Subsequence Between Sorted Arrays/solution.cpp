/*  
 *  找出共同的subsequence其實就是數數看每個數字是否出現n次
 *
 *  time  : O(N), N : the number of arrays
 *  space : O(1)
 */

class Solution {
public:
    vector<int> longestCommonSubsequence(vector<vector<int>>& arrays) {
        int n = arrays.size();
        vector<int> cnt(100 + 1);
        for(auto& r : arrays) {
            for(auto& n : r) cnt[n]++;
        }
        vector<int> ans;
        for(int i = 1; i <= 100; ++i)
            if(cnt[i] == n) ans.push_back(i);
        return ans;
    }
};
