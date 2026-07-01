/*
 *   從thief往外擴張 把每一個element離thief多遠都標示出來
 *
 *   例如:
 *
 *   0, 0, 1         3, 2, 1
 *   0, 0, 0   -->   4, 3, 2
 *   0, 0, 0         5, 4, 3
 *
 *   並且建立 map<int, vector<vector<int>> m; 儲存每個value的座標
 *   m[5] = {{2, 0}};
 *   m[4] = {{1, 0}, {2, 1}};
 *   m[3] = {{0, 0}, {1, 1}, {2, 2}};
 *   m[2] = {{0, 1}, {1, 2}};
 *   m[1] = {{0, 2}};
 *
 *   使用Union Find從最大值開始連線 >= 自己數值的點
 *
 *   step1 :
 *              3, 2, 1
 *              4, 3, 2
 *            [5], 4, 3
 *
 *   step2 :
 *               3, 2, 1
 *              [4],3, 2
 *               |
 *               5-[4],3
 *
 *   step3 :
 *              [3],2, 1    在value = 3的時候(0, 0), (m - 1, n - 1)可以連接起來
 *               |          所以return 3 - 1
 *               4-[3],2
 *               |
 *               5-4-[3]
 *
 */
class Solution {
    vector<vector<int>> dirs{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int n, sz;
    vector<int> root, rank;
    int find(int x)  {
        if(root[x] == x) return x;
        else return root[x] = find(root[x]);
    }
    int un(int y, int x, int ny, int nx) {
        int a = find(y * n + x);
        int b = find(ny * n + nx);
        if(a == b) return 0;
        if(rank[b] < rank[a]) swap(a, b);
        root[b] = a;
        return rank[a] += rank[b];
    }
    bool isConnected() {
        return find(0) == find(sz - 1);
    }
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        n = grid.size();
        sz = n * n;
        // special case
        if(grid[0][0] || grid[n - 1][n - 1]) return 0;

        // search the thief
        queue<vector<int>> q;
        for(int y = 0; y < n; ++y) { // O(N) , N : total element in grid
            for(int x = 0; x < n; ++x) {
                if(grid[y][x] == 1) q.push({y, x});
            }
        }
        // add value
        map<int, vector<vector<int>>> m; // value, {y, x}
        while(!q.empty()) { // O(N)
            for(int loop = q.size(); loop > 0; --loop) {
                auto p = q.front(); q.pop();
                int y = p[0], x = p[1];
                for(auto& d : dirs) {
                    int ny = y + d[0];
                    int nx = x + d[1];
                    if(ny < 0 || nx < 0 || ny == n || nx == n || grid[ny][nx] != 0) continue;
                    grid[ny][nx] = grid[y][x] + 1;
                    q.push({ny, nx});
                    m[grid[ny][nx]].push_back({ny, nx});
                }
            }
        }

        // check connectivity
        root.resize(sz);
        iota(begin(root), end(root), 0);
        rank.resize(sz, 1);
        for(auto it = m.rbegin(); it != m.rend(); ++it) {
            for(auto& p : it->second) {
                for(auto& d : dirs) {
                    int ny = p[0] + d[0];
                    int nx = p[1] + d[1];
                    if(ny < 0 || nx < 0 || ny == n || nx == n || grid[ny][nx] < it->first) continue;
                    un(p[0], p[1], ny, nx);
                    if(isConnected()) return it->first - 1;
                }
            }
        }
        return 0;
    }
};
/*  2026/07/01 daily challenge
 *  想法類似 改使用bfs和dfs來找答案
 *
 */
class Solution {
    using vvi = vector<vector<int>>;
    int sz, maxw{};
    const vvi dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    map<int, vvi> mp;
    inline bool inRange(int y, int x) {
        if(y < 0 || x < 0 || y == sz || x == sz) return false;
        else return true;
    }
    void bfs(vvi& grid) {
        queue<vector<int>> q;
        for(int y = 0; y < sz; ++y) for(int x = 0; x < sz; ++x) {
            if(grid[y][x] == 1) {
                q.push({y, x, 0});
                grid[y][x] = -1;
            } else grid[y][x] = 1e3;
        }
        while(!q.empty()) {
            auto cur = q.front(); q.pop();
            int y = cur[0], x = cur[1], w = cur[2];
            mp[w].push_back({y, x});
            if((y == 0 && x == 0) || (y == sz - 1 && x == sz - 1)) maxw = max(maxw, w);
            for(const auto& d : dirs) {
                int ny = y + d[0], nx = x + d[1];
                if(!inRange(ny, nx) || grid[ny][nx] <= w + 1) continue;
                grid[ny][nx] = w + 1;
                q.push({ny, nx, grid[ny][nx]});
            }
        }
    }
    void fill(vvi& grid, const vvi& vecs) {
        for(const auto& v : vecs) {
            int y = v[0], x = v[1];
            grid[y][x] = 0;
        }
    }
    bool dfs(const vvi& grid, int y, int x, unordered_set<int>& seen) {
        if(grid[y][x] != 0) return false;
        else if(y == sz - 1 && x == sz - 1) return true;
        else {
            bool rtn{false};
            for(const auto& d : dirs) {
                int ny = y + d[0], nx = x + d[1];
                if(!inRange(ny, nx) || seen.count(ny * sz + nx)) continue;
                seen.insert(ny * sz + nx);
                rtn |= dfs(grid, ny, nx, seen);
            }
            return rtn;
        }
    }
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        sz = grid.size();
        // special case
        if(grid.front().front() || grid.back().back()) return 0;
        bfs(grid);
        for(auto it = mp.rbegin(); it != mp.rend(); ++it) {
            fill(grid, it->second);
            if(it->first > maxw) continue;
            unordered_set<int> seen;
            seen.insert({0, 0});
            if(dfs(grid, 0, 0, seen))
                return it->first;
        }
        return 0;
    }
};
