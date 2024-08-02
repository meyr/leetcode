/*
 *  一開始對right triangle定義 思考方向有錯誤 以為是指在右邊
 *  其實是相同row 和相同column的兩個element就可以組成 right triangle
 *
 *  使用prefix sum的解法
 *
 *  time  : O(MN)
 *  space : O(MN)
 */
class Solution {
public:
    long long numberOfRightTriangles(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> pfs_t2d(m, vector<int>(n)), pfs_l2r(m, vector<int>(n));
        for(int x = 0; x < n; ++x) {
            pfs_t2d[0][x] = grid[0][x];
            for(int y = 1; y < m; ++y)
                pfs_t2d[y][x] = pfs_t2d[y - 1][x] + grid[y][x];
        }
        for(int y = 0; y < m; ++y) {
            pfs_l2r[y][0] = grid[y][0];
            for(int x = 1; x < n; ++x)
                pfs_l2r[y][x] = pfs_l2r[y][x - 1] + grid[y][x];
        }
        long long ans{};
        for(int y = 0; y < m; ++y) {
            for(int x = 0; x < n; ++x) {
                if(grid[y][x])
                    ans += (pfs_l2r[y].back() - 1) * (pfs_t2d[m - 1][x] - 1);
                    // 因為這邊都只使用到最後一個element所以只需要統計每個row和column 1的數量即可
            }
        }
        return ans;
    }
};

/*  
 *   只需計算每個row和column的1個數
 *   time  : O(MN)
 *   space : O(M + N)
 */
class Solution {
public:
    long long numberOfRightTriangles(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<int> rcnt(m), ccnt(n);
        for(int y = 0; y < m; ++y)
            for(int x = 0; x < n; ++x)
                rcnt[y] += grid[y][x];

        for(int x = 0; x < n; ++x)
            for(int y = 0; y < m; ++y)
                ccnt[x] += grid[y][x];

        long long ans{};
        for(int y = 0; y < m; ++y)
            for(int x = 0; x < n; ++x)
                ans += grid[y][x] ? (rcnt[y] - 1) * (ccnt[x] - 1) : 0;

        return ans;
    }
};
