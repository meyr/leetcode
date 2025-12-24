/*  
 *  從lake開始往外擴展 --> bfs
 *
 */
class Solution {
public:
    vector<vector<int>> highestPeak(vector<vector<int>>& isWater) {
        int m = isWater.size(), n = isWater[0].size();
        vector<vector<int>> rtn(m, vector<int>(n));
        unordered_set<int> visited;
        queue<vector<int>> q;
        for(int y = 0; y < m; ++y)
            for(int x = 0; x < n; ++x)
                if(isWater[y][x]) {
                    q.push({y, x});
                    visited.insert(y * n + x);
                }

            
        vector<vector<int>> dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        while(!q.empty()) {
            vector<int> cur = q.front(); q.pop();
            int y = cur[0], x = cur[1];
            for(auto& d : dirs) {
                int ny = y + d[0];
                int nx = x + d[1];
                if(ny < 0 || nx < 0 || ny == m || nx == n || visited.count(ny * n + nx)) continue;
                rtn[ny][nx] = rtn[y][x] + 1;
                q.push({ny, nx});
                visited.insert(ny * n + nx);
            }
        }
        return rtn;
    }
};
