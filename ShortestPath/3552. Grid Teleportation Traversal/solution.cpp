/*  我寫的最後TLE 但是我覺得想法和解答是一樣的
 *
 */
class Solution {
    vector<vector<int>> dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
public:
    Solution() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
    }
    int minMoves(vector<string>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        unordered_map<char, vector<pair<int, int>>> tps;
        for(int y = 0; y < m; ++y)
            for(int x = 0; x < n; ++x)
                if(isupper(matrix[y][x]))
                    tps[matrix[y][x]].push_back({y, x});
        vector<vector<int>> dp(m, vector<int>(n, m * n + 1));
        dp[0][0] = 0;
        priority_queue<vector<int>, vector<vector<int>>, greater<>> q; //minheap <dist, y, x, used>
        q.push({0, 0, 0, 0});
        while(!q.empty()) {
            vector<int> cur = q.top(); q.pop();
            int dist = cur[0], y = cur[1], x = cur[2], used = cur[3];
            if(dist > dp[y][x]) continue;
            if(y == m - 1 && x == n - 1) return dist;
            for(auto& d : dirs) {
                int ny = d[0] + y, nx = d[1] + x;
                if(ny < 0 || nx < 0 || ny == m || nx == n || matrix[ny][nx] == '#') continue;
                if(dist + 1 < dp[ny][nx]) {
                    dp[ny][nx] = dist + 1;
                    q.push({dp[ny][nx], ny, nx, used});
                }
            }
            if(isupper(matrix[y][x])) {
                int offset = matrix[y][x] - 'A';
                int mask = 1 << offset;
                if(((used & mask) >> offset) == 0) {
                    used |= mask;
                    for(auto& [ny, nx] : tps[matrix[y][x]]) {
                        if(dist < dp[ny][nx]) {
                            dp[ny][nx] = dist;
                            q.push({dist, ny, nx, used});
                        }
                    }
                }
            }
        }
        return -1;
    }
};
