/*
    標準的DP問題 每個job有取和不取兩種狀態
    取的話，下一個job就是根據endtime使用binary search來尋找

    time  : O(NlogN + N) = O(NlogN)
    space : O(N + logN) = O(N)

*/
class Solution {
    int sz;
    vector<int> mem;
    vector<vector<int>> t;
    int helper(int idx) {
        if(~mem[idx]) return mem[idx];
        vector<int> target{t[idx][1], 0, 0};
        int nxtidx = lower_bound(begin(t) + idx, end(t), target) - t.begin();
        return mem[idx] = max(helper(idx + 1), helper(nxtidx) + t[idx][2]);       
    }
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        sz = startTime.size();
        for(int i = 0; i < sz; ++i) t.push_back({startTime[i], endTime[i], profit[i]});
        sort(begin(t), end(t)); // O(NlogN)
        mem.resize(sz + 1, -1);
        mem[sz] = 0;
        return helper(0);
    }
};
