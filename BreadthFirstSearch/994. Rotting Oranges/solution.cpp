/*
 *  很直覺的BFS題目
 *
 *  time  : O(MN + MN) 統計cnt和把rotten oranges推入queue + while loop 每個element都會走訪一次 = O(MN)
 *  space : O(MN) 最worsest case全部塞滿MN個rotten oranges
 */
class Solution {
    vector<vector<int>> dirs{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int cnt{}, m = grid.size(), n = grid[0].size();
        queue<vector<int>> q;
        for(int y = 0; y < m; ++y) {
            for(int x = 0; x < n; ++x) {
                cnt += grid[y][x] == 1;
                if(grid[y][x] == 2) q.push({y, x});
            }
        }
        int ans{};
        while(!q.empty() && cnt > 0) {
            for(int loop = q.size(); loop > 0; --loop) {
                vector<int> cur = q.front(); q.pop();
                for(auto& d : dirs) {
                    int y = cur[0] + d[0];
                    int x = cur[1] + d[1];
                    if(y < 0 || x < 0 || y == m || x == n || grid[y][x] != 1) continue;
                    grid[y][x] = 2;
                    cnt--;
                    q.push({y, x});
                }
            }
            ans++;
        }
        return cnt != 0 ? -1 : ans;
    }
};
