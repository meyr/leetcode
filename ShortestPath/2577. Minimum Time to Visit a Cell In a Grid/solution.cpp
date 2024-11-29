/*  參考: https://leetcode.com/problems/minimum-time-to-visit-a-cell-in-a-grid/solutions/3231527/back-n-forth-dijkstra/
 *  
 *  想法和參考解答類似 但是寫出來卻是錯的
 *  
 */
class Solution {
    int dir[5] = {0, 1, 0, -1, 0};
public:
    int minimumTime(vector<vector<int>>& g) {
        int m = g.size(), n = g[0].size();
        if (min(g[0][1], g[1][0]) > 1) // 先確定{0, 1}, {1, 0} 可以走 因為每一秒都要移動
            return -1;
        vector<vector<int>> vis(m, vector<int>(n, INT_MAX)); // 使用此2d vector來記錄是否拜訪過和最少拜訪時間
        priority_queue<array<int, 3>> pq;  // shortest path method 使用priority_queue
        pq.push({0, 0, 0});
        while(!pq.empty()) {
            auto [neg_sec, i, j] = pq.top(); pq.pop(); // __important__ 使用array<int, 3>才可以這樣使用 使用vector不可以
            if (i == m - 1 && j == n - 1)
                break;
            for (int d = 0; d < 4; ++d) {
                int x = i + dir[d], y = j + dir[d + 1];
                if (min(x, y) >= 0 && x < m && y < n) {
                    int sec = -neg_sec + 1;
                    if (sec < g[x][y])
                        sec = g[x][y] + (g[x][y] - sec) % 2;  //__importatn__ 在附近的cell一直來回等到時間到
                    if (sec < vis[x][y]) {
                        vis[x][y] = sec;
                        pq.push({-sec, x, y});
                    }
                }
            }
        }
        return vis.back().back();
    }
};
