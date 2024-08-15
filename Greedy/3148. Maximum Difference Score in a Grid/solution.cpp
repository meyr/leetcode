/*  一開始以為是DP問題 所以使用以下方法
 *  time : O(MNN + NMM) 很僥倖的AC
 */
class Solution {
public:
    int maxScore(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> score(m, vector<int>(n, 0));
        int ans{-1}, onejump{INT_MIN};
        for(int y = 0; y < m; ++y) {
            for(int x = n - 1; x >= 0; --x) {
                for(int k = x + 1; k < n; ++k) {
                    onejump = max(onejump, grid[y][k] - grid[y][x]);
                    if(grid[y][k] >= grid[y][x]) {
                        score[y][x] = max(score[y][x], grid[y][k] - grid[y][x] + score[y][k]);
                        ans = max(ans, score[y][x]);
                    }
                }
            }
        }
        for(int x = 0; x < n; ++x) {
            for(int y = m - 1; y >= 0; --y) {
                for(int k = y + 1; k < m; ++k) {
                    onejump = max(onejump, grid[k][x] - grid[y][x]);
                    if(grid[k][x] >= grid[y][x]) {
                        score[y][x] = max(score[y][x], grid[k][x] - grid[y][x] + score[k][x]);
                        ans = max(ans, score[y][x]);
                    }
                }
            }
        }
        return ans == -1 ? onejump : ans;
    }
};

/*  參考 : https://leetcode.com/problems/maximum-difference-score-in-a-grid/solutions/5145704/java-c-python-dp-minimum-on-top-left/
 *
 *  因為 移動過程 (c1 - c2) + (c2 - c3) + (c3 - c4) = c1 - c4 
 *  也就是找出目前遇到的最小值
 *
 *  Greedy point : 從目前位置[y, x]往上往左看遇到的最小值
 *
 *  time  : O(MN)
 *  space : O(1)
 */
class Solution {
public:
    int maxScore(vector<vector<int>>& A) {
        int res = -1e6, m = A.size(), n = A[0].size();
        for (int y = 0; y < m; y++) {
            for (int x = 0; x < n; x++) {
                // 最小值有可能從上面或是左邊過來
                int pre = min(i > 0 ? A[y - 1][x] : 1e6, j > 0 ? A[y][x - 1] : 1e6);
                res = max(res, A[y][x] - pre);
                A[y][x] = min(A[y][x], pre); // 儲存目前遇到最小值
            }
        }
        return res;
    }
};
