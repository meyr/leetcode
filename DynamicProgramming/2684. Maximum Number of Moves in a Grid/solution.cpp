class Solution {
    int m, n, ans{};
    vector<vector<int>> dirs{{-1, 1}, {0, 1}, {1, 1}};
    vector<vector<int>> dp;
    int helper(vector<vector<int>>& grid, int y, int x) {
        if(~dp[y][x]) return dp[y][x];
        int rtn{};
        for(auto& d : dirs) {
            int ny = y + d[0];
            int nx = x + d[1];
            if(ny >= 0 && ny < m && nx < n && grid[y][x] < grid[ny][nx])
                rtn = max(rtn, 1 + helper(grid, ny, nx));
        }
        return dp[y][x] = rtn;
    }
public:
    int maxMoves(vector<vector<int>>& grid) {
        m = grid.size(), n = grid[0].size();
        dp.resize(m, vector<int>(n, -1));
        for(int y = 0; y < m; ++y)
            ans = max(ans, helper(grid, y, 0));
        return ans;
    }
};
