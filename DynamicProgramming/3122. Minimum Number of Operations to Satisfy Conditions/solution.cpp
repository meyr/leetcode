/*
 *  1. 先計算每個column上0~9的個數
 *  2. 使用dynamic programming 假設每個index都會選擇0~9 找出最少改變的數值
 */
class Solution {
    vector<vector<int>> count;
    vector<vector<int>> mem;
    int m, n;
    int helper(int prev, int idx) {
        int rtn = 1e6;
        if(~mem[prev][idx]) return mem[prev][idx];
        else {
            for(int num = 0; num < 10; ++num) {
                if(num != prev)
                    rtn = min(rtn, m - count[idx][num] + helper(num, idx + 1));
            }
        }
        return mem[prev][idx] = rtn;
    }
public:
    int minimumOperations(vector<vector<int>>& grid) {
        m = grid.size(), n = grid[0].size();
        count.resize(n, vector<int>(10));
        for(int x = 0; x < n; ++x)
            for(int y = 0; y < m; ++y) 
                count[x][grid[y][x]]++;
        
        mem.resize(11, vector<int>(n + 1, -1));
        for(int i = 0; i < 10; ++i) mem[i][n] = 0;
        return helper(10, 0);
    }
};
