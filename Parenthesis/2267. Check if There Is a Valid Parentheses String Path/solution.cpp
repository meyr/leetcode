/*  參考: https://leetcode.com/problems/check-if-there-is-a-valid-parentheses-string-path/solutions/2017937/simple-dfs-dp-by-jainam_sogani-ijab/ 
 *  
 *  因為y == m - 1 && x == n - 1也就是終點 只要一條路徑成立就可以 所以mem[m - 1][n - 1] 所紀錄的之前結果不需要參考 只在乎是否為true
 *
 *  time  : O(MN(M+N))
 *  space : O(MN(M+N))
 */
class Solution {
    int m, n;
    bool helper(vector<vector<char>>& grid, int y, int x, int bal) {
        if(y == m || x == n) return false;
        bal += (grid[y][x] == '(') ? 1 : -1;
        if(bal < 0) return false;
        if(y == m - 1 && x == n - 1) return bal == 0;  // __important__ 以前都是先檢查mem但是這邊直接檢查bal == 0 表示不受之前結果的影響
        if(~mem[y][x][bal]) return mem[y][x][bal];
        return mem[y][x][bal] = helper(grid, y + 1, x, bal) || helper(grid, y, x + 1, bal);
    }
    vector<vector<vector<int>>> mem;
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        m = grid.size(), n = grid[0].size();
        mem.resize(m, vector<vector<int>>(n, vector<int>(205, -1)));
        return helper(grid, 0, 0, 0);
    }
};
