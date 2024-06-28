/*
 *  每個task都有兩種可能 1. 使用paid painter 2. 使用free painter
 *  當使用paid painter剩下的就是 remain - time[idx] - 1 記得要減掉自己
 *
 *  time  : O(N^2)
 *  space : O(N^2)
 */

class Solution {
    int helper(vector<int>& cost, vector<int>& time, int remain, int idx) {
        int ans{};
        if(remain <= 0) return 0;
        else if(~mem[remain][idx]) return mem[remain][idx];
        else {
            int paid = helper(cost, time, remain - time[idx] - 1, idx + 1) + cost[idx];
            int pass = helper(cost, time, remain, idx + 1);
            ans = min(paid, pass);
        }
        return mem[remain][idx] = ans;
    }
    vector<vector<int>> mem;
public:
    int paintWalls(vector<int>& cost, vector<int>& time) {
        int sz = cost.size();
        mem.resize(sz + 1, vector<int>(sz + 1, -1));
        for(int i = 0; i <= sz; ++i) mem[i][sz] = 1e9;
        return helper(cost, time, cost.size(), 0);
    }
};
