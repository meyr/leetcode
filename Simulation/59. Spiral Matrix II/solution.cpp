/*
 *  time  : O(N^2)
 *  space : O(N^2)
 */
class Solution {
    vector<vector<int>> dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
public:
    vector<vector<int>> generateMatrix(int n) {
        int d{}, y{}, x{}, cnt{}, val{1};
        vector<vector<int>> rtn(n, vector<int>(n));
        while(cnt < n * n) {
            cnt++;
            rtn[y][x] = val++;
            int ny = y + dirs[d][0];
            int nx = x + dirs[d][1];
            while(cnt < n * n && (ny < 0 || nx < 0 || ny == n || nx == n || rtn[ny][nx])) {
                d = (d + 1) % dirs.size();
                ny = y + dirs[d][0];
                nx = x + dirs[d][1];
            }
            y = ny;
            x = nx;
        }
        return rtn;
    }
};
