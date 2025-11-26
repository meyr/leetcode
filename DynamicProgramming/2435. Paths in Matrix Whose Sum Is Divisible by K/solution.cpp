/*
 *  time  : O(MNK)
 *  space : O(MNK)
 */
class Solution {
    int m, n, k;
    int mod = 1e9 + 7;
    int helper(vector<vector<int>>& grid, int y, int x, int m) {
        if(y < 0 || x < 0) return 0;
        else if(~mem[y][x][m]) return mem[y][x][m];
        else {
            int val = grid[y][x] % k;
            int need = ((m - val) + k) % k; // __important__ 我要達到m 我需要多少的數值
            return mem[y][x][m] = ((long)helper(grid, y - 1, x, need) + helper(grid, y, x - 1, need)) % mod;
        }
    }
    /*
        f(y, x, m) = f(y - 1, x, need) + f(y, x - 1, need)
                                            --->
                           |
                          \|/
    */
    vector<vector<vector<int>>> mem;
public:
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        m = grid.size(), n = grid[0].size();
        this->k = k;
        mem.resize(m, vector<vector<int>>(n, vector<int>(k, -1)));
        for(int i = 0; i < k; ++i)
            mem[0][0][i] = 0;
        mem[0][0][grid[0][0] % k] = 1;
        return helper(grid, m - 1, n - 1, 0);
    }
};
/*  bottom-up tabulation
 *  
 *  time  : O(MNK)
 *  space : O(MNK)
 */
class Solution {
    int m, n, k;
    int mod = 1e9 + 7;
public:
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        m = grid.size(), n = grid[0].size();
        this->k = k;
        vector<int> zero(k);
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(k)));
        dp[0][0][grid[0][0] % k] = 1;
        for(int y = 0; y < m; ++y) {
            for(int x = 0; x < n; ++x) {
                if(y == 0 && x == 0) continue;
                int cur = grid[y][x] % k;
                const vector<int>& left  = x - 1 >= 0 ? dp[y][x - 1] : zero;
                const vector<int>& above = y - 1 >= 0 ? dp[y - 1][x] : zero;
                for(int i = 0; i < k; ++i) {
                    dp[y][x][(i + cur) % k] = ((long long)dp[y][x][(i + cur) % k] + left[i] + above[i]) % mod;
                }
            }
        }
        return dp.back().back()[0];
    }
};
