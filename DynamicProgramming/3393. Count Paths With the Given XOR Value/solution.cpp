/*
 *
 * time  : O(16MN) = O(MN)
 * space : O(16MN) = O(MN)
 */
class Solution {
    int m, n, k;
    int helper(vector<vector<int>>& grid, int val, int y, int x) {
        if(y < 0 || x < 0) return 0;
        val ^= grid[y][x];
        if(~mem[val][y][x]) 
            return mem[val][y][x];
        else 
            return mem[val][y][x] = (helper(grid, val, y - 1, x) + helper(grid, val, y, x - 1)) % (int)(1e9 + 7);
        
    }
    vector<vector<vector<int>>> mem;
public:
    int countPathsWithXorValue(vector<vector<int>>& grid, int k) {
        m = grid.size(), n = grid[0].size();
        this->k = k;
        mem.resize(16, vector<vector<int>>(m, vector<int>(n, -1)));
        mem[k][0][0] = 1;
        return helper(grid, 0, m - 1, n - 1);
    }
};
