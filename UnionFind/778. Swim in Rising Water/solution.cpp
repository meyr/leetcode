class Solution {
    int n, sz;
    vector<int> t2num, root, rank;
    int toNum(int y, int x) {
        return y * n + x;
    }
    pair<int, int> toGrid(int num) {
        return {num / n, num % n};
    }
    int find(int x) {
        if(root[x] == x) return x;
        else return root[x] = find(root[x]);
    }
    int connect(int y, int x) {
        y = find(y), x = find(x);
        if(y == x) return 0;
        if(rank[y] > rank[x]) swap(y, x);
        root[y] = x;
        return rank[x] += rank[y];
    }
    bool isConnected(int x, int y) {
        return find(x) == find(y);
    }
    vector<vector<int>> dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
public:
    int swimInWater(vector<vector<int>>& grid) {
        n = grid.size(), sz = n * n;
        t2num.resize(sz), root.resize(sz), rank.resize(sz, 1);
        iota(begin(root), end(root), 0);
        for(int y = 0; y < n; ++y)
            for(int x = 0; x < n; ++x)
                t2num[grid[y][x]] = toNum(y, x);
        int ans{};
        for(; ans < sz; ++ans) {
            int num = t2num[ans];
            auto [y, x] = toGrid(num);
            for(const auto& d : dirs) {
                int ny = y + d[0];
                int nx = x + d[1];
                if(ny < 0 || nx < 0 || ny == n || nx == n || grid[ny][nx] > grid[y][x]) continue;
                connect(toNum(ny, nx), num);
            }
            if(isConnected(0, sz - 1)) break;
        }
        return ans;
    }
};
