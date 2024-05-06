class Solution {
    int m, n;
    int helper(vector<vector<int>>& grid, int y, int x1, int x2) {
        if(y == m || x1 < 0 || x2 < 0 || x1 == n || x2 == n) return 0;
        if(~mem[y][x1][x2]) return mem[y][x1][x2];
        int take = x1 == x2 ? grid[y][x1] : grid[y][x1] + grid[y][x2];
        int res{};
        for(int i = -1; i <= 1; ++i)
            for(int j = -1; j <= 1; ++j)
                res = max(res, helper(grid, y + 1, x1 + i, x2 + j));
        return mem[y][x1][x2] = res + take;
    }
    vector<vector<vector<int>>> mem;
public:
    int cherryPickup(vector<vector<int>>& grid) {
        m = grid.size(), n = grid[0].size();
        mem.resize(m, vector<vector<int>>(n, vector<int>(n, -1)));
        return helper(grid, 0, 0, n - 1);
    }
};
