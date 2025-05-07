/*  參考3341的解答 修正往前進是1秒或是2秒
 *
 */
class Solution {
    vector<vector<int>> dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        int m = moveTime.size(), n = moveTime[0].size();
        vector<vector<int>> minTime(m, vector<int>(n, INT_MAX));
        priority_queue<vector<int>, vector<vector<int>>, greater<>> pq; // minheap : time, y, x
        minTime[0][0] = 0;
        pq.push({0, 0, 0, 1});  // 多一個資料表示目前前進到下一格需要幾秒
        while(!pq.empty()) {
            vector<int> cur = pq.top(); pq.pop();
            int t = cur[0], y = cur[1], x = cur[2], st = cur[3];
            if(y == m - 1 && x == n - 1) return t;
            if(t > minTime[y][x]) continue;
            for(auto& d : dirs) {
                int ny = y + d[0], nx = x + d[1];
                if(ny < 0 || nx < 0 || ny == m || nx == n) continue;
                int nt = (t >= moveTime[ny][nx]) ? (t + st) : (moveTime[ny][nx] + st);
                if(minTime[ny][nx] > nt) {
                    minTime[ny][nx] = nt;
                    pq.push({nt, ny, nx, st + 1 > 2 ? 1 : st + 1}); // 大於2秒就變成1秒
                }
            }
        }
        return -1;

    }
};
