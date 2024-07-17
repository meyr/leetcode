/*  
 *  沒什麼想法 看一下資料沒很大 所以使用暴力破解 
 *  每個情況都去試 然後使用Floyd-warshall找出最短距離
 *  但是這個方法在某些testcase會過不了
 */
class Solution {
    int check(vector<vector<int>>& path, int n) {
        //print(path);
        for(int k = 0; k < n; ++k) {
            for(int i = 0; i < n; ++i) {
                for(int j = 0; j < n; ++j) {
                    path[i][j] = min(path[i][j], path[i][k] + path[k][j]);

                }
            }
        }
        //print(path);
        int maxPath = 0;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j)
                if(i != j && path[i][j] < 1e6) maxPath = max(maxPath, path[i][j]);
        }
        return maxPath == 0 ? 1e6 : maxPath;
    }
public:
    int numberOfSets(int n, int maxDistance, vector<vector<int>>& roads) {
        int ans{};
        for(int idx = 0; idx < pow(2, n); ++idx) {
            if(n - __builtin_popcount(idx) <= 1) {
                ans++;
            } else {
                vector<vector<int>> path(n, vector<int>(n, 1e6));
                bitset<11> bs(idx);
                for(int i = 0; i < n; ++i) {
                    if(!bs.test(i))
                        path[i][i] = 0;
                }
                for(auto& r : roads) {
                    if(!bs.test(r[0]) && !bs.test(r[1])) {
                        path[r[0]][r[1]] = min(path[r[0]][r[1]], r[2]);
                        path[r[1]][r[0]] = min(path[r[1]][r[0]], r[2]);
                    }
                }
                int rtn = check(path, n);
                if(rtn <= maxDistance) {
                    ans++;
                }
            }
        }
        return ans;
    }
};
/*
 * 參考解答 : https://leetcode.com/problems/number-of-possible-sets-of-closing-branches/solutions/4382557/mask-floyd-warshall/
 * 和我的想法類似 mask改成保留的node
 * 不特別去建立path 2Dvector而是在執行floyd-warshall跳過刪除的點
 */

class Solution {
public:
    int getMaxDistance(int mask, int n, vector<vector<int>> d /* copy */) {
        int res = 0;
        for (int k = 0; k < n; ++k) // Floyd-Warshall
            if (mask & (1 << k))    // 確保i, j, k都在mask裡面
                for (int i = 0; i < n; ++i)
                    if (i != k && mask & (1 << i))
                        for (int j = 0; j < n; ++j)
                            if (j != i && mask & (1 << j))
                                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        for (int i = 0; i < n; ++i)
            if (mask & (1 << i)) // 確保i, j都在mask
                for (int j = i + 1; j < n; ++j) // 因為d[i][j] == d[j][i] 所以往後找即可
                    if (mask & (1 << j))
                        res = max(res, d[i][j]);
        return res;
    }
    int numberOfSets(int n, int maxDistance, vector<vector<int>>& roads) {
        vector<vector<int>> d(n, vector<int>(n, 100000));
        for (auto &r : roads) {
            d[r[0]][r[1]] = min(d[r[0]][r[1]], r[2]);
            d[r[1]][r[0]] = min(d[r[1]][r[0]], r[2]);
        }
        int comb = 1 << n, res = 1;
        for (int mask = 1; mask < comb; ++mask) {
            if(__builtin_popcount(mask) <= 1) res++;
            else res += getMaxDistance(mask, n, d) <= maxDistance;
        }
        return res;
    }
};
