/*
 *  使用2D prefix sum計算面積
 *  不要忘了side length = 1的時候也需要檢查
 *
 *  time  : O(NMW) , W = min(N, M)
 *  space : O(NM)
 *
 */
class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> pfs(m + 1, vector<int>(n + 1));
        pfs[1][1] = mat[0][0];
        int ans = mat[0][0] <= threshold;
        for(int y = 1; y < m; ++y) {
            ans = max(ans, (int)(mat[y][0] <= threshold));
            pfs[y + 1][1] = pfs[y][1] + mat[y][0];
        }
        for(int x = 1; x < n; ++x) {
            ans = max(ans, (int)(mat[0][x] <= threshold));
            pfs[1][x + 1] = pfs[1][x] + mat[0][x];
        }
        for(int y = 1; y < m; ++y) {
            for(int x = 1; x < n; ++x) {
                ans = max(ans, (int)(mat[y][x] <= threshold));
                pfs[y + 1][x + 1] = pfs[y + 1][x] + pfs[y][x + 1] - pfs[y][x] + mat[y][x];
                for(int w = min(y + 1, x + 1); w > 0; --w) {
                    int sum = pfs[y + 1][x + 1] - pfs[y + 1 - w][x + 1] - pfs[y + 1][x + 1 - w] + pfs[y + 1 - w][x + 1 - w];
                    if(sum <= threshold) {
                        ans = max(ans, w);
                        break;
                    }
                }
            }
        }
        return ans;
    }
};
