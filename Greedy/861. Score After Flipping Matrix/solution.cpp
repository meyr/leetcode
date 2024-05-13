/*
 *  因為題目要找出最大值 所以第一步就是讓MSB都是1
 *  第二步就是依序看每個x的位置 如果1的個數少於 n - x - 1就全部翻轉
 *
 *  time  : O(MN)
 *  space : O(1)
 */
class Solution {
public:
    int matrixScore(vector<vector<int>>& grid) {
        int ans{};
        int m = grid.size(), n = grid[0].size();
        for(int y = 0; y < m; ++y) { //O(MN)
            if(grid[y][0] == 0) {
                for(int x = 0; x < n ;++x)
                    grid[y][x] ^= 1;
            }
        }
        for(int x = 0; x < n; ++x) { //O(MN)
            int cnt{};
            for(int y = 0; y < m; ++y) cnt += grid[y][x];
            if(cnt < (m + 1) / 2) {
                cnt = 0;
                for(int y = 0; y < m; ++y) {
                    grid[y][x] ^= 1;
                    cnt += grid[y][x];
                }
            }
            ans += cnt * (1 << (n - x - 1));
        }
        return ans;
    }
};
