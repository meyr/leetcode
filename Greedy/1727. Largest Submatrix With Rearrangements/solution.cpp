/*
 * ref : https://leetcode.com/problems/largest-submatrix-with-rearrangements/solutions/1020710/c-clean-and-clear-with-intuitive-picture-pcwo/
 * 暴力破解的話 就是每一個(y, x)視為submatrix的右下角, 可以組成最大的submatrix就是把相同的y row, 連續1由大到小排列
 * 例如:
 *
 *          3, 1, 0, 2  -->  x          --> 根據連續1的數有小到大排序  -->         x        --> 這樣就可以輕易知道面積
 *                           x      x                                           x  x
 *                           x x    x                                        x  x  x
 *                                                                                 3x1
 *                                                                              2x2
 *                                                                           1x3
 *  time  : O(M(N + N + NlogN + N)) = O(MNlogN)
 *  space : O(N + N + logN) = O(N)
 */
class Solution {
public:
    int largestSubmatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size(), ans{};
        vector<int> height(n);
        for(int y = 0; y < m; ++y) {
            for(int x = 0; x < n; ++x) {
                if(matrix[y][x] && y > 0)
                    matrix[y][x] += matrix[y - 1][x];
                height[x] = matrix[y][x];
            }
            vector<int> order_height(begin(height), end(height));
            sort(begin(order_height), end(order_height));
            for(int x = n - 1; x >= 0; --x) {
                if(order_height[x])
                    ans = max(ans, order_height[x] * (n - x));
            }
        }
        return ans;
    }
};
