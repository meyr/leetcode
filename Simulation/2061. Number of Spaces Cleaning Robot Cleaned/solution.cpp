/*
 *  模擬robot走一次 同時也記錄走過的(y, x, d) 
 *  
 *  time  : O(NM)
 *  space : O(NM)
 */
class Solution {
    int m, n;
    vector<vector<int>> dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    unordered_set<int> visited;
    int toNum(int y, int x, int d) {
        return d * 1e6 + (y * n + x);
    }
public:
    int numberOfCleanRooms(vector<vector<int>>& room) {
        m = room.size(), n = room[0].size();
        int y = 0, x = 0, d = 0, ans = 0;
        while(!visited.count(toNum(y, x, d))) {
            visited.insert(toNum(y, x, d));
            ans += room[y][x] == 0;
            room[y][x] = 2; // has already cleaned
            for(int i = 0; i < 4; ++i) {
                int ny = y + dirs[d][0];
                int nx = x + dirs[d][1];
                if(ny < 0 || nx < 0 || ny == m || nx == n || room[ny][nx] == 1) d = (d + 1) % 4;
                else {
                    y = ny;
                    x = nx;
                    break;
                }
            }
        }
        return ans;
    }
};
