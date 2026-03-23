/* ref : https://leetcode.com/problems/maximum-non-negative-product-in-a-matrix/solutions/855142/c-on-dp-by-votrubac-scy7/
 *
 * grid.back().back()的最大值 會根據grid.back().back()改變 如果是負值我就希望過來的是負最大值
 *                                                               正值我就希望過來的是正最大值
 *
 * 不只最後的grid中間的grid也是一樣 所以每個grid都要記錄最大最小值
 *
 * time  : O(MN)
 * space : O(MN)
 *
 */
class Solution {
public:
    int maxProductPath(vector<vector<int>>& g) {
        auto r = g.size(), c = g[0].size();
        vector<vector<pair<long, long>>> dp(r, vector<pair<long, long>>(c));    // 每個grid都記錄最大最小值 {最大值, 最小值}
        for (auto i = 0; i < r; ++i) {
            for (auto j = 0; j < c; ++j) {
                if (i == 0 && j == 0)                                           // 起始點最大最小值都一樣
                    dp[0][0].first = dp[0][0].second = g[0][0];
                else {
                    auto &up = i > 0 ? dp[i - 1][j] : dp[i][j - 1];             // i == 0 的上面故意選左邊
                    auto &left = j > 0 ? dp[i][j - 1] : dp[i - 1][j];           // j == 0 的左邊故意選上面
                    auto first = max(up.first, left.first), second = min(up.second, left.second);
                    if (g[i][j] < 0)                                            // 如果grid[i][j] < 0 最大值和最小值會互換
                        swap(first, second);
                    dp[i][j].first = first * g[i][j];
                    dp[i][j].second = second * g[i][j];
                }
            }
        }
        return dp[r - 1][c - 1].first < 0 ? -1 : dp[r - 1][c - 1].first % 1000000007;
    }
};
