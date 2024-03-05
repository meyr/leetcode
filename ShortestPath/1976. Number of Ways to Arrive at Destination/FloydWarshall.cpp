/*
 *  參考解答 https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/solutions/1417752/c-solution-o-n-3-floyd-warshall-dp/
 *  使用任何一種shortest path演算法
 *  每次跟新distance的時候 順便更新count
 *  count的算法是 cnt[i][m] * cnt[m][j]	
 */

class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        int mod = 1e9 + 7;
        vector<vector<long long>> path(n, vector<long long>(n, 1e13));
        vector<vector<int>> cnt(n, vector<int>(n));
        for(int i = 0; i < n; ++i) { // i, j 為同一個node
            path[i][i] = 0;
            cnt[i][i] = 1;
        }
        for(auto& r : roads) {       // 增加 road
            path[r[0]][r[1]] = r[2];
            path[r[1]][r[0]] = r[2];
            cnt[r[0]][r[1]] = 1;
            cnt[r[1]][r[0]] = 1;
        }
        for(int m = 0; m < n; ++m) {
            for(int i = 0; i < n; ++i) {
                for(int j = 0; j < n; ++j) {
                    if(i == m || j == m) continue; // i, j不為中間點
                    if(path[i][j] > path[i][m] + path[m][j]) { // 找到更小的path
                        path[i][j] = path[i][m] + path[m][j];
                        cnt[i][j] = (cnt[i][m] * cnt[m][j]) % mod;
                    } else if(path[i][j] == path[i][m] + path[m][j]) // 找到和目前最小的path一樣的路徑
                        cnt[i][j] = (cnt[i][j] + cnt[i][m] * cnt[m][j]) % mod;
                }
            }
        }
        return cnt[0][n - 1];
        // time : O(N + R + N^3) = O(N^3)
		// space : O(N^2 + N^2) = O(N^2)
    }
};
