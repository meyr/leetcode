/*  想法和參考的解答類似 只是我想得太複雜了
 *  參考解答 : https://leetcode.com/problems/maximum-number-of-points-from-grid-queries/solutions/6587849/sorting-priority-queue-python-by-otabek_-wn5u/
 *
 */
class Solution {
public:
    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
        int m = grid.size(), n = grid[0].size();
        vector<pair<int, int>> sq; // sorted queries, <value, index>
        for(int i = 0; i < queries.size(); ++i)
            sq.push_back({queries[i], i});
        sort(begin(sq), end(sq));

        vector<int> ans(queries.size());
        priority_queue<vector<int>, vector<vector<int>>, greater<>> pq; // minheap, <value, y, x>
        vector<vector<int>> v(m, vector<int>(n));
        pq.push({grid[0][0], 0, 0});
        v[0][0] = 1;
        int points{};
        vector<vector<int>> dirs{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for(auto [cur_max, idx] : sq) {
            while(!pq.empty() && cur_max > pq.top()[0]) {
                int y = pq.top()[1], x = pq.top()[2];
                pq.pop();
                points++;   // 只計算經過幾個cell
                for(auto& d : dirs) {
                    int ny = y + d[0];
                    int nx = x + d[1];
                    if(ny >= 0 && nx >= 0 && ny < m && nx < n && !v[ny][nx]) {
                        pq.push({grid[ny][nx], ny, nx});
                        v[ny][nx] = 1;
                    }
                }
            }
            ans[idx] = points;
        }
        return ans;
    }
};
