/*
 *  每一個node和前面組合起來會有k個可能 所以用vector<vector<int>> len(sz, vector<int>(k)); 來表示
 *
 *  time  : O(N^2)
 *  space : O(NK)
 */

class Solution {
public:
    int maximumLength(vector<int>& nums, int k) {
        int sz = nums.size(), ans{};
        vector<vector<int>> len(sz, vector<int>(k));
        for(int i = 0; i < sz; ++i) {
            len[i][nums[i] % k] = 1;
            for(int j = 0; j < i; ++j) {
                int t = (nums[i] + nums[j]) % k;
                if(len[j][t] == 0) len[i][t] = 2; // num[i], nums[j]成為新的subsequence
                else len[i][t] = max(len[i][t], len[j][t] + 1); // 和之前的合併
                ans = max(ans, len[i][t]);
            }
        }
        return ans;
    }
};
