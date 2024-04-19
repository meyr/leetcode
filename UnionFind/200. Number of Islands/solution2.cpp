/*
 *   使用DFS走訪island
 */
class Solution {
    int m, n;
    void dfs(vector<vector<char>>& grid, int y, int x) {
        if(y < 0 || x < 0 || y == m || x == n || grid[y][x] == '0') return;
        grid[y][x] = '0';
        dfs(grid, y + 1, x);
        dfs(grid, y, x + 1);
        dfs(grid, y - 1, x);
        dfs(grid, y, x - 1);
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int ans{};
        m = grid.size(), n = grid[0].size();
        for(int y = 0; y < m; ++y) {
            for(int x = 0; x < n; ++x) {
                if(grid[y][x] == '1') {
                    ans++;
                    dfs(grid, y, x);
                }
            }
        }
        return ans;
    }
};
