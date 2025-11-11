/*  根據hint寫出的解答，但是TLE
 *
 *  time  : O(MNK)
 *  space : O(MNK)
 */
class Solution {
    int m, n, k;
    vector<vector<vector<int>>> mem;
    void helper(vector<vector<int>>& grid, int y, int x, int score, int cost) {
        if(y == m || x == n) return;
        cost += grid[y][x] > 0;
        score += grid[y][x];
        if(cost > k || mem[y][x][cost] >= score) return;
        mem[y][x][cost] = score;
        helper(grid, y + 1, x, score, cost);
        helper(grid, y, x + 1, score, cost);
    }        
public:
    int maxPathScore(vector<vector<int>>& grid, int k) {
        m = grid.size();
        n = grid[0].size();
        this->k = k;
        mem.resize(m, vector<vector<int>>(n, vector<int>(k + 1, -1)));
        helper(grid, 0, 0, 0, 0);
        int ans{-1};
        for(auto& n : mem.back().back())
            ans = max(ans, n);
        return ans;
    }
};
/* 根據gemini給出的bottom-up解答 time complexity 一樣是O(MNK)但是可以過
 *
 */
class Solution {
public:
    int maxPathScore(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        const int INF = -20001;
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(k + 1, INF)));
        dp[0][0][0] = 0;

        for (int y = 0; y < m; ++y) {
            for (int x = 0; x < n; ++x) {
                for (int prev_c = 0; prev_c <= k; ++prev_c) {
                    if (y > 0) {
                        if (dp[y - 1][x][prev_c] != INF) {
                            int new_cost = prev_c + (grid[y][x] > 0);
                            if (new_cost <= k) {
                                int new_score = dp[y - 1][x][prev_c] + grid[y][x];
                                dp[y][x][new_cost] = max(dp[y][x][new_cost], new_score);
                            }
                        }
                    }
                    
                    if (x > 0) {
                        if (dp[y][x - 1][prev_c] != INF) {
                            int new_cost = prev_c + (grid[y][x] > 0);
                            if (new_cost <= k) {
                                int new_score = dp[y][x - 1][prev_c] + grid[y][x];
                                dp[y][x][new_cost] = max(dp[y][x][new_cost], new_score);
                            }
                        }
                    }
                }
            }
        }

        int ans{INF};
        for (auto& n : dp.back().back())
            ans = max(ans, n);

        return (ans == INF) ? -1 : ans;
    }
};
