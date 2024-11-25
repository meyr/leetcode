/*
 *  想了一陣子決定使用暴力破解 意外地通過了 應該是data還是很小
 *
 */
class Solution {
    int hash(const vector<vector<int>>& board) {
        int ans{};
        for(auto& r : board)
            for(auto& n : r)
                ans = ans << 3 | n;
        return ans;
    }
    vector<vector<int>> dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        unordered_set<int> v;
        queue<vector<vector<int>>> q;
        q.push(board);
        v.insert(hash(board));
        int target = hash({{1, 2, 3}, {4, 5, 0}});
        int ans{};
        while(!q.empty()) {
            for(int loop = q.size(); loop > 0; --loop) {
                vector<vector<int>> cur = q.front(); q.pop();
                if(hash(cur) == target) return ans;
                int y, x;
                for(int i = 0; i < 2; ++i) {
                    for(int j = 0; j < 3; ++j) {
                        if(!cur[i][j]) {
                            y = i, x = j;
                            break;
                        }
                    }
                }
                for(auto& d : dirs) {
                    int ny = y + d[0];
                    int nx = x + d[1];
                    if(ny < 0 || nx < 0 || ny == 2 || nx == 3) continue;
                    swap(cur[y][x], cur[ny][nx]);
                    if(!v.count(hash(cur))) {
                        v.insert(hash(cur));
                        q.push(cur);
                    }
                    swap(cur[y][x], cur[ny][nx]);
                }
            }
            ans++;
        }
        return -1;
    }
};
