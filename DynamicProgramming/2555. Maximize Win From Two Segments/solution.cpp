/*
 *  使用DP因為有兩個線段 所以每次都有兩種選擇 取和不取
 *
 *  time  : O(NlogN)
 *  sapce : O(N)
 */
class Solution {
    int k;
    int helper(vector<int>& pp, int idx, int cnt) {
        if(idx == pp.size() || cnt == 0) return 0;
        else if(~mem[idx][cnt]) return mem[idx][cnt];
        int notake = helper(pp, idx + 1, cnt);
        int nxt = upper_bound(begin(pp) + idx, end(pp), pp[idx] + k) - pp.begin(); // 找出下一個值的位置
        int take = (nxt - idx) + helper(pp, nxt, cnt - 1);
        return mem[idx][cnt] = max(notake, take);
    }
    vector<vector<int>> mem;
public:
    int maximizeWin(vector<int>& prizePositions, int k) {
        if(prizePositions.back() - prizePositions.front() <= 2 * k) return prizePositions.size();
        this->k = k;
        int sz = prizePositions.size();
        mem.resize(sz, vector<int>(3, -1));
        return helper(prizePositions, 0, 2);
    }
};
