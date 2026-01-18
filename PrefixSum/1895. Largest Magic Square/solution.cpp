class Solution {
    int row_val, col_val, dia_val;
    bool check_dia(vector<vector<int>>& grid, int y, int x, int w) {
        int target{};
        for(int i = 0; i < w; ++i)
            target += grid[y + i][x + i];
        dia_val = target;
        for(int i = 0; i < w; ++i)
            target -= grid[y + i][x + (w - i - 1)];
        return target == 0;
    }
    bool check_col(vector<vector<int>>& pfs, int y, int x, int w) {
        for(int i = x + 1; i < x + w; ++i) {
            int curr = pfs[y + w][i] - pfs[y][i];
            int prev = pfs[y + w][i - 1] - pfs[y][i - 1];
            if(curr != prev)
                return false;
            col_val = curr;
        }
        return true;
    }
    bool check_row(vector<vector<int>>& pfs, int y, int x, int w) {
        for(int i = y + 1; i < y + w; ++i) {
            int curr = pfs[i][x + w] - pfs[i][x];
            int prev = pfs[i - 1][x + w] - pfs[i - 1][x];
            if(curr != prev) return false;
            row_val = curr;
        }
        return true;
    }
    bool check(vector<vector<int>>& row_pfs, vector<vector<int>>& col_pfs, int y, int x, int w) {
        //cout << "check (" << y << ", " << x << ", " << w << ")\n";
        if(!check_row(row_pfs, y, x, w)) return false;
        if(!check_col(col_pfs, y, x, w)) return false;
        return true;
    }
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> row_pfs(m, vector<int>(n + 1));
        vector<vector<int>> col_pfs(m + 1, vector<int>(n));
        for(int y = 0; y < m; ++y)
            for(int x = 0; x < n; ++x)
                row_pfs[y][x + 1] = row_pfs[y][x] + grid[y][x];
        for(int x = 0; x < n; ++x)
            for(int y = 0; y < m; ++y)
                col_pfs[y + 1][x] = col_pfs[y][x] + grid[y][x];
        int ans{1};
        for(int y = 0; y < m; ++y) {
            for(int x = 0; x < n; ++x) {
                for(int w = min(n - x, m - y); w > 1; --w) {
                   if(check(row_pfs, col_pfs, y, x, w) && check_dia(grid, y, x, w)) {
                        if(row_val == col_val && col_val == dia_val) {
                            ans = max(ans, w);
                            break;
                        }
                   }
                }
            }
        }
        return ans;
    }
};
