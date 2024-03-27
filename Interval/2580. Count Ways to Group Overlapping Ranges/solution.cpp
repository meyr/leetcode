/*
 *   [[1, 3],[10, 20],[2, 5],[4, 8]]
 *   [[1,3][2,5],[4,8]],[[10,20]] --> 2^2
 *
 *   組合的個數就是找出non-overlap的個數(cnt) 再算pow(2, cnt)
 *
 *   time  : O(N + M) , N:size of ranges, M : log2 of num of non-overlap interval groups
 *   space : O(logN), sorting
 */
class Solution {
    int mod = 1e9 + 7;
    int modpow(int b, int e) {
        if(e == 0) return 1;
        else if(e == 1) return b;
        int rtn = modpow(b, e / 2);
        rtn = ((long)rtn * rtn) % mod;
        return e % 2 == 1 ? (b * rtn) % mod : rtn;
    }
public:
    int countWays(vector<vector<int>>& ranges) {
        int sz = ranges.size();
        sort(begin(ranges), end(ranges));
        int cnt{1}, idx{};
        for(int i = 1; i < sz; ++i) {
            if(min(ranges[i][1], ranges[idx][1]) >= max(ranges[i][0], ranges[idx][0])) {
                ranges[idx][1] = max(ranges[i][1], ranges[idx][1]);
            } else {
                cnt++;
                idx = i;
            }
        }
        return modpow(2, cnt);
    }
};

