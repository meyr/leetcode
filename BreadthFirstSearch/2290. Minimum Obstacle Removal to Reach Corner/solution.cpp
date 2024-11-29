/* 直覺使用BFS來解
 *
 * time  : O(4MN) = O(MN) 每個position都有可能從四個方向進來
 * space : O(MN)
 */
class Solution {
    vector<vector<int>> dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> ans(m, vector<int>(n, INT_MAX)); // 從{0, 0}到{y, x}需要移除最少obstacle數量
        ans[0][0] = 0;
        queue<pair<int, int>> q;
        q.push(make_pair(0, 0));
        while(!q.empty()) {
            auto [y, x] = q.front(); q.pop();
            for(auto& d : dirs) {
                int ny = y + d[0];
                int nx = x + d[1];
                if(ny < 0 || nx < 0 || ny == m || nx == n) continue;
                if(ans[ny][nx] > ans[y][x] + grid[y][x]) {
                    ans[ny][nx] = ans[y][x] + grid[y][x];
                    q.push(make_pair(ny, nx));
                }
            }
        }
        return ans.back().back();
    }
};
/*  參考解答: https://leetcode.com/problems/minimum-obstacle-removal-to-reach-corner/solutions/2111406/minesweeper/
 *
 *  這邊分成empty 和 obstacle兩個 vector
 *  1. 當empty有東西 我們就會一直取 empty的東西 --> 表示一直往empty前進直到遇到obstacle
 *  2. 當empty沒東西了且還沒到終點 --> 表示我們必須移除一個obstacle(res++) 
 *                                    一次移除全部的obstacle 所以obstacle都變成empty(swap(obs, emp))
 *
 *  因為會一直往empty的方向走 所以效率比BFS好
 *
 *  time  : O(MN)
 *  space : O(MN)
 */
class Solution {
    pair<int, int> dirs[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
public:
    int minimumObstacles(vector<vector<int>>& g) {
        int m = g.size(), n = g[0].size(), res = 0;
        deque<array<int, 2>> emp{{0, 0}}, obs;
        while (!emp.empty() || !obs.empty()) {
            if (emp.empty()) {
                ++res;
                swap(emp, obs);
            }
            const auto [i, j] = emp.front(); emp.pop_front();
            if (i == m - 1 && j == n - 1)
                break;
            for (const auto [dx, dy] : dirs) {
                int x = i + dx, y = j + dy;
                if (min(x, y) >= 0 && x < m && y < n && g[x][y] >= 0) {
                    if (g[x][y])
                        obs.push_back({x, y});
                    else
                        emp.push_back({x, y});
                    g[x][y] = -1; // 已經拜訪過了
                }
            }
        }
        return res;
    }
};
/* 使用pair相加讓程式更具可讀性
 *
 */
template <typename T,typename U>
pair<T,U> operator+(const pair<T,U>& l,const pair<T,U>& r) {
    return {l.first + r.first, l.second + r.second};
}

class Solution {
    pair<int, int> dirs[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), res{};
        deque<pair<int, int>> obs, emp{{0, 0}};
        while(!emp.empty() || !obs.empty()) {
            if(emp.empty()) {
                res++;
                swap(emp, obs);
            }
            auto cur = emp.front(); emp.pop_front();
            if(cur.first == m - 1 && cur.second == n - 1)  break;
            for(auto& d : dirs) {
                auto [ny, nx] = cur + d;
                if(ny < 0 || nx < 0 || ny == m || nx == n || grid[ny][nx] == -1) continue;
                if(grid[ny][nx]) // obstacle
                    obs.push_back({ny, nx});
                else
                    emp.push_back({ny, nx});
                grid[ny][nx] = -1;
            }
        }
        return res;
    }
};
