/*
 *  time  : O(NK), N : size of piles
 *  space : O(NK)
 */
class Solution {
    int helper(vector<vector<int>>& piles, int idx, int k) {
        if(k == 0 || idx == piles.size()) return 0;
        else if(~mem[idx][k]) return mem[idx][k];
        int rtn = helper(piles, idx + 1, k); // don't take
        int sum{};
        for(int i = 1; i - 1 < piles[idx].size() && i <= k ; ++i) {
            sum += piles[idx][i - 1];
            rtn = max(rtn, helper(piles, idx + 1, k - i) + sum);
        }
        return mem[idx][k] = rtn;
    }
    vector<vector<int>> mem;
public:
    int maxValueOfCoins(vector<vector<int>>& piles, int k) {
        mem.resize(piles.size(), vector<int>(k + 1, -1));
        return helper(piles, 0, k);
    }
};
