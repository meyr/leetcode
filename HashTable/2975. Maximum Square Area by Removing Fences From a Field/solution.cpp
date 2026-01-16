/*
 * 1. 先把1, m, n推入hFences和vFences再進行排序
 * 2. 因為1 <= hFences.length, vFences.length <= 600 大膽的使用暴力破解 列舉所有可能的width 和 height
 * 3. 可能的 width
 *
 * vFences  [1,  2, 5,  6] 可能的width
 *    diff     1  3   1
 *            --               1
 *               --            3
 *            -----            4
 *                    --       1
 *               -------       4
 *            ----------       5
 *
 *  time  : O(logH + logV + V^2 + H^2) = O(V^2 + H^2)
 *  space : O(logH + logV + H + V)     = O(V   + H)
 */

class Solution {
public:
    int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) {
        hFences.push_back(1);
        hFences.push_back(m);
        sort(begin(hFences), end(hFences));
        vFences.push_back(1);
        vFences.push_back(n);
        sort(begin(vFences), end(vFences));
        int ans{-1}, mod = 1e9 + 7;
        unordered_set<int> width;
        vector<int> vpfs(vFences.size() + 1);
        for(int i = 1, pfs = 0; i < vFences.size(); ++i) {
            pfs += vFences[i] - vFences[i - 1];
            for(int j = 0; j < vpfs.size(); ++j)
                width.insert(pfs - vpfs[j]);
            vpfs.push_back(pfs);
        }
        vector<int> hpfs(hFences.size() + 1);
        for(int i = 1, pfs = 0; i < hFences.size(); ++i) {
            pfs += hFences[i] - hFences[i - 1];
            for(int j = 0; j < hpfs.size(); ++j) {
                int height = pfs - hpfs[j];
                if(width.count(height))
                    ans = max(ans, height);
            }
            hpfs.push_back(pfs);
        }

        return ans == -1 ? -1 : ((long long)ans * ans) % mod;
    }
};
