/*  根據題意一層一層旋轉
 *  每一層先讀出來成一維vector方便旋轉
 *  之後再寫回去
 *
 *  time  : O(MN)
 *  space : O(M + N)
 */
class Solution {
    void helper(vector<vector<int>>& grid, int y, int x, int leny, int lenx, int k) {
        int sz = (lenx + leny - 2) * 2;
        k %= sz;
        k = sz - k;
        vector<int> nums;
        for(int i = 0; i < lenx - 1; ++i)
            nums.push_back(grid[y][x + i]);
        for(int i = 0; i < leny - 1; ++i)
            nums.push_back(grid[y + i][x + lenx - 1]);
        for(int i = 0; i < lenx - 1; ++i)
            nums.push_back(grid[y + leny - 1][x + lenx - 1 - i]);
        for(int i = 0; i < leny - 1; ++i)
            nums.push_back(grid[y + leny - 1 - i][x]);
        reverse(begin(nums), end(nums));
        reverse(begin(nums), begin(nums) + k);
        reverse(begin(nums) + k, end(nums));
        int idx = 0;
        for(int i = 0; i < lenx - 1; ++i)
            grid[y][x + i] = nums[idx++];
        for(int i = 0; i < leny - 1; ++i)
            grid[y + i][x + lenx - 1] = nums[idx++];
        for(int i = 0; i < lenx - 1; ++i)
            grid[y + leny - 1][x + lenx - 1 - i] = nums[idx++];
        for(int i = 0; i < leny - 1; ++i)
            grid[y + leny - 1 - i][x] = nums[idx++];        
    }
public:
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        for(int y = 0, x = 0, leny = m, lenx = n; leny && lenx; ++y, ++x, leny -= 2, lenx -= 2)
            helper(grid, y, x, leny, lenx, k); 
        return grid;
    }
};
