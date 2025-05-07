/*  重點在於moveTime[i][j], 是一個絕對時間，必須先在adjacent cell等到此時間，才可以移動過去
 *                         所以到達此room的時間是 moveTime[i][j] + 1
 *  time  : O(MNlogMN)
 *  space : O(MN)
 */
class Solution {
    vector<vector<int>> dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        int m = moveTime.size(), n = moveTime[0].size();
        vector<vector<int>> minTime(m, vector<int>(n, INT_MAX));
        priority_queue<vector<int>, vector<vector<int>>, greater<>> pq; // minheap : time, y, x
        minTime[0][0] = 0;
        pq.push({0, 0, 0});
        while(!pq.empty()) {
            vector<int> cur = pq.top(); pq.pop();
            int t = cur[0], y = cur[1], x = cur[2];
            if(y == m - 1 && x == n - 1) return t;
            if(t > minTime[y][x]) continue;
            for(auto& d : dirs) {
                int ny = y + d[0], nx = x + d[1];
                if(ny < 0 || nx < 0 || ny == m || nx == n) continue;
                int nt = (t >= moveTime[ny][nx]) ? (t + 1) : (moveTime[ny][nx] + 1);    // __important__ 判斷是否可以移動到下一個cell t >= moveTime[ny][nx] 表示可以直接移動過去
                if(minTime[ny][nx] > nt) {                                              //                                            否則在前一格等到moveTime[ny][nx]再移動過去
                    minTime[ny][nx] = nt;
                    pq.push({nt, ny, nx});
                }
            }
        }
        return -1;
    }
};
