/*
 *  這種題目因為1 <= m, n <= 15 所以可以用backtracking
 *
 *  time  : O(K*3^K) , K = NM,  from each cell we can go in three directions
 *  space : O(K)
 */
class Solution {
    int m, n;
    int getGold(vector<vector<int>>& grid, vector<vector<int>>& v, int y, int x) {
        if(y < 0 || x < 0 || y == m || x == n || grid[y][x] == 0 || v[y][x] == 1) return 0;
        v[y][x] = 1;
        int rtn = grid[y][x] + max({getGold(grid, v, y + 1, x), 
                                 getGold(grid, v, y, x + 1), 
                                 getGold(grid, v, y - 1, x), 
                                 getGold(grid, v, y, x - 1)});
        v[y][x] = 0;
        return rtn;
    }
public:
    int getMaximumGold(vector<vector<int>>& grid) {
        m = grid.size(), n = grid[0].size();
        int ans{};
        for(int y = 0; y < m; ++y) {
            for(int x = 0; x < n; ++x) {
                vector<vector<int>> v(m, vector<int>(n));
                ans = max(ans, getGold(grid, v, y, x));
            }
        }
        return ans;
    }
};
