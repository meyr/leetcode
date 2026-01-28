/*
 *  ref : https://leetcode.cn/problems/minimum-cost-path-with-teleportations/solutions/3755031/dp-by-tsreaper-a33e/
 *
 *  因為多了teleportation且次數不能多於k
 *  dp[k][y][x](位置y, x使用了k次teleportaton) 就會被 dp[k - 1][y'][x'] 其中grid[y'][x'] >= grid[y][x] 中的最小值所決定
 *  所以使用map<int, vector<pair<int, int>>> 紀錄 grid[y][x], <y, x>
 */
class Solution {
public:
    int minCost(vector<vector<int>>& grid, int K) {
        int n = grid.size(), m = grid[0].size();

        const long long INF = 1e18;
        long long f[K + 1][n][m];
        for (int k = 0; k <= K; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    f[k][i][j] = INF;
        // 第一層使用k = 0次teleportation
        // 所以都是normal move
        f[0][0][0] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
            if (i + 1 < n)
                f[0][i + 1][j] = min(f[0][i + 1][j], f[0][i][j] + grid[i + 1][j]);
            if (j + 1 < m)
                f[0][i][j + 1] = min(f[0][i][j + 1], f[0][i][j] + grid[i][j + 1]);
            }
        }

        typedef pair<int, int> pii;
        map<int, vector<pii>> mp;       // grid[y][x], <y, x>
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                mp[-grid[i][j]].push_back({i, j});

        for (int k = 1; k <= K; k++) {
            // teleportation move
            long long mn = INF;
            for (auto &p : mp) {    // __important__ 從大到小 所以前一層的較大grid可以跳到這一層較小的grid
                for (pii pos : p.second) mn = min(mn, f[k - 1][pos.first][pos.second]); // __important__ 找出k-1層 且cost <= grid[pos.first][pos.second]的最小值
                for (pii pos : p.second) f[k][pos.first][pos.second] = mn;
            }
            // normal move
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (i > 0) f[k][i][j] = min(f[k][i][j], f[k][i - 1][j] + grid[i][j]);
                    if (j > 0) f[k][i][j] = min(f[k][i][j], f[k][i][j - 1] + grid[i][j]);
                }
            }
        }

        // 取得每一層到達(m-1, n-1)的最小值
        long long ans = INF;
        for (int k = 0; k <= K; k++)
            ans = min(ans, f[k][n - 1][m - 1]);
        return ans;
    }
};
/*  根據上面的想法 自己重寫了一次
 *
 */
class Solution {
public:
    int minCost(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        const int INF = 2 * 80 * 1e4;
        vector<vector<vector<int>>> dp(k + 1, vector<vector<int>>(m, vector<int>(n, INF)));
        map<int, vector<pair<int, int>>> mp;
        dp[0][0][0] = 0;
        for (int y = 0; y < m; ++y) {
            for(int x = 0; x < n; ++x) {
                mp[-grid[y][x]].push_back({y, x});
                if(y + 1 < m) dp[0][y + 1][x] = min(dp[0][y + 1][x], dp[0][y][x] + grid[y + 1][x]);
                if(x + 1 < n) dp[0][y][x + 1] = min(dp[0][y][x + 1], dp[0][y][x] + grid[y][x + 1]);
            }
        }
        for(int i = 1; i <= k; ++i) {
            int mn{INT_MAX};
            for(auto& ref : mp) {
                for(auto& [y, x] : ref.second) mn = min(mn, dp[i - 1][y][x]);
                for(auto& [y, x] : ref.second) dp[i][y][x] = mn;
            }
            // normal move
            for(int y = 0; y < m; ++y) {
                for(int x = 0; x < n; ++x) {
                    if(y + 1 < m) dp[i][y + 1][x] = min(dp[i][y + 1][x], dp[i][y][x] + grid[y + 1][x]);
                    if(x + 1 < n) dp[i][y][x + 1] = min(dp[i][y][x + 1], dp[i][y][x] + grid[y][x + 1]);
                }
            }
        }
        int ans{INT_MAX};
        for(int i = 0; i <= k; ++i)
            ans = min(ans, dp[i][m - 1][n - 1]);
        return ans;
    }
};
