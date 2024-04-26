/*
 *  每個區間都有兩個選項 買或不買
 *  買的話 下一個區間可以用binary search找到
 *
 *  time  : O(NlogN + NlogN) = O(NlogN)
 *  space : O(N)
 *
 */
class Solution {
    int helper(vector<vector<int>>& offers, int idx) {
        if(~mem[idx]) return mem[idx];
        int notbuy = helper(offers, idx + 1);
        vector<int> target{offers[idx][1] + 1, 0, 0};
        int nxt = lower_bound(begin(offers) + idx + 1, end(offers), target) - begin(offers);
        int buy = helper(offers, nxt) + offers[idx][2];
        return mem[idx] = max(notbuy, buy);
    }
    vector<int> mem;
public:
    int maximizeTheProfit(int n, vector<vector<int>>& offers) {
        sort(begin(offers), end(offers));
        mem.resize(offers.size() + 1, -1);
        mem.back() = 0;
        return helper(offers, 0);
    }
};
