/*  
 *  使用Union Find來連結2D grid
 *
 */
class Solution {
    vector<int> root, rank;
    int m, n, sz;
    vector<vector<int>> dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int find(int x) {
        if(root[x] == x) return x;
        else return root[x] = find(root[x]);
    }
    int find(int y, int x) {
        return find(y * n + x);
    }
    int un(int y, int x, int ny, int nx) {
        return un(y * n + x, ny * n + nx);
    }
    int un(int x, int y) {
        x = find(x), y = find(y);
        if(x == y) return 0;
        if(rank[y] > rank[x]) swap(x, y);
        root[y] = x;
        return rank[x] += rank[y];
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        m = grid.size(), n = grid[0].size();
        sz = m * n;
        root.resize(sz);
        iota(begin(root), end(root), 0);
        rank.resize(sz, 1);
        for(int y = 0; y < m; ++y) {
            for(int x = 0; x < n; ++x) {
                if(grid[y][x] == '0') continue;
                for(auto& d : dirs) {
                    int ny = y + d[0];
                    int nx = x + d[1];
                    if(ny < 0 || nx < 0 || ny == m || nx == n || grid[ny][nx] == '0') continue;
                    un(y, x, ny, nx);
                }
            }
        }
        unordered_set<int> groups;
        for(int y = 0; y < m; ++y) {
            for(int x = 0; x < n; ++x) {
                if(grid[y][x] == '1') groups.insert(find(y, x));
            }
        }
        return groups.size();
    }
};
