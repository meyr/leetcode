/*  參考:https://leetcode.cn/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/solutions/123916/shi-wang-ge-tu-zhi-shao-you-yi-tiao-you-xiao-lu-2/
 *
 *  因為題目要最小的cost達到目的地 ==> shortest algorithm
 *  四個方向中，當方向和grid[y][x]一樣 ==> 不需要cost
 *                                否則 ==> cost + 1
 *  time  : O(MNlogNM)
 *  space : O(MN)
 */
using PII = pair<int, int>;
class Solution {
private:
    static constexpr int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> dist(m * n, INT_MAX);
        vector<int> seen(m * n, 0);
        dist[0] = 0;
        priority_queue<PII, vector<PII>, greater<PII>> q;
        q.emplace(0, 0);

        while (!q.empty()) {
            auto [cur_dis, cur_pos] = q.top(); q.pop();
            if (seen[cur_pos]) continue;

            seen[cur_pos] = 1;
            int x = cur_pos / n;
            int y = cur_pos % n;
            for (int i = 0; i < 4; ++i) {
                int nx = x + dirs[i][0];
                int ny = y + dirs[i][1];
                int new_pos = nx * n + ny;
                int new_dis = cur_dis + (grid[x][y] != i + 1); // __important__ dist和grid[y][x]有關

                if (nx >= 0 && nx < m && ny >= 0 && ny < n && new_dis < dist[new_pos]) {
                    dist[new_pos] = new_dis;
                    q.emplace(new_dis, new_pos);
                }
            }
        }

        return dist[m * n - 1];
    }
};
/*  一樣使用shortest path algorithm 自己寫一次
 *  發現根本不需要用到vector<vector<int>> seen
 */
 class Solution {
    vector<vector<int>> dir{{0, 0},
                            {0, 1},
                            {0, -1},
                            {1, 0},
                            {-1, 0}};
    template<typename T>
    using minhp = priority_queue<T, vector<T>, greater<>>;
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        minhp<pair<int, int>> pq; //minheap <dist, position>
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
        dist[0][0] = 0;
        pq.push({0, 0});
        while(!pq.empty()) {
            auto [d, p] = pq.top(); pq.pop();
            int y = p / n, x = p % n;
            if(dist[y][x] < d) continue;
            for(int i = 1; i < dir.size(); ++i) {
                int ny = y + dir[i][0];
                int nx = x + dir[i][1];
                int nd = d + (grid[y][x] != i);
                if(ny < 0 || nx < 0 || ny == m || nx == n || dist[ny][nx] <= nd) continue;
                dist[ny][nx] = nd;
                pq.push({nd, ny * n + nx});
            }
        }
        return dist.back().back();
    }
};
