/*  
 *  直覺的使用2D UnionFind, 從最後開始連接土地
 *
 */
class UnionFind{
    int m, n, sz, top, bottom;
    vector<int> root, rank;
    int find(int x) {
        if(root[x] == x) return x;
        else return root[x] = find(root[x]);
    }
    int un(int x, int y) {
        x = find(x), y = find(y);
        if(x == y) return 0;
        if(rank[y] > rank[x]) swap(x, y);
        root[y] = x;
        return rank[x] += rank[y];        
    }
public:
    UnionFind(int m, int n) : m(m), n(n), sz(m * n + 2), root(sz), rank(sz) {
        iota(begin(root), end(root), 0);
        top = sz - 2;
        bottom = sz - 1;
        for(int i = 0; i < n; ++i) {
            un(i, top);
            un((m - 1) * n + i, bottom);
        }
    }
    int un(const vector<int>& x2d, const vector<int>& y2d) {
        return un(x2d[0] * n + x2d[1], y2d[0] * n + y2d[1]);
    }
    int isConnect(int x, int y) {
        return find(x) == find(y);
    }
    int isCrossable() {
        return isConnect(top, bottom);
    }
};
class Solution {
    enum state{
        land,
        water
    };
public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        UnionFind uf(row, col);
        vector<vector<int>> dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        vector<vector<int>> matrix(row, vector<int>(col, water)); // all water first
        int sz = cells.size();
        for(int day = sz - 1; day >= 0; --day) {
            int y = cells[day][0] - 1, x = cells[day][1] - 1;
            matrix[y][x] = land;
            for(auto& d : dirs) {
                int ny = y + d[0];
                int nx = x + d[1];
                if(ny < 0 || nx < 0 || ny == row || nx == col || matrix[ny][nx] == water) continue;
                uf.un({y, x}, {ny, nx});
            }
            if(uf.isCrossable())
                return day;
        }
        return 0;
    }
};
