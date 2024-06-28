/*
 *  因為importance的定義是兩個city的和 所以road越多的city給越高的weight
    inportance = n0 + n1 +
                 n1 + n2 +
                 n2 + n3 +
                 n0 + n2 +
                 n1 + n3 +
                 n2 + n4

               = 2*n0 + 3*n1 + 3*n2+ 2*n3 + 1*n4;
 *
 *  time  : O(R + NlogN + N) = O(R + NlogN)
 *  space : O(N + N + logN)  = O(N)
 */
class Solution {
public:
    long long maximumImportance(int n, vector<vector<int>>& roads) {
        vector<int> cnt(n), idx(n);
        for(auto& r : roads)
            cnt[r[0]]++, cnt[r[1]]++;
        iota(begin(idx), end(idx), 0);
        sort(begin(idx), end(idx), [&](int a, int b){
            return cnt[a] < cnt[b];
        });
        long long ans{};
        for(int i = 0; i < n; ++i)
            ans += (long long)(i + 1) * cnt[idx[i]];
        return ans;
    }
};
