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
