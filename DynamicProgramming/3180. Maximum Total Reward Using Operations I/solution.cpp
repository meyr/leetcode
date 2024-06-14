/*
 * 恩為1 <= rewardValues[i] <= 2000
 * 所以mem的大小只需要mem[sz + 1][2001] , sz = rewardValue.size();
 *
 */

class Solution {
    int helper(vector<int>& rwv, int idx, int cur) {
        if(idx == rwv.size()) return cur;
        if(~mem[idx][cur]) return mem[idx][cur];
        int notake = helper(rwv, idx + 1, cur);
        int nxt = upper_bound(begin(rwv) + idx + 1, end(rwv), cur + rwv[idx]) - rwv.begin();
        int take = helper(rwv, nxt, cur + rwv[idx]);
        return mem[idx][cur] = max(notake, take);
    }
    vector<vector<int>> mem;
public:
    int maxTotalReward(vector<int>& rewardValues) {
        sort(begin(rewardValues), end(rewardValues));
        mem.resize(rewardValues.size() + 1, vector<int>(2001, -1));
        return helper(rewardValues, 0, 0);
    }
};
