class Solution {
    int sz;
    vector<int> root, rank;
    int find(vector<vector<int>>& grid, int y, int x) {
        if(y < 0 || x < 0 || y == sz || x == sz || !grid[y][x]) return -1;
        else return find(y, x);
    }
    int find(int y, int x) {
        return find(y * sz + x);
    }
    int find(int x) {
        if(root[x] == x) return x;
        else return root[x] = find(root[x]);
    }
    int un(vector<vector<int>>& grid, int y, int x, int ny, int nx) {
        if(ny < 0 || nx < 0 || ny == sz || nx == sz || !grid[ny][nx]) return rank[find(y, x)];
        int r1 = find(y, x), r2 = find(ny, nx);
        if(r1 == r2) return rank[r1];
        if(rank[r2] > rank[r1]) swap(r1, r2); // rank[r1] > rank[r2]
        root[r2] = r1;
        return rank[r1] += rank[r2];
    }
public:
    int largestIsland(vector<vector<int>>& grid) {
        sz = grid.size();
        root.resize(sz * sz);
        iota(begin(root), end(root), 0);
        rank.resize(sz * sz, 1);
        int ans{};
        for(int y = 0; y < sz; ++y) {
            for(int x = 0; x < sz; ++x) {
                if(grid[y][x]) {
                    ans = max({ans, un(grid, y, x, y + 1, x),
                                    un(grid, y, x, y - 1, x),
                                    un(grid, y, x, y, x + 1)});
                }
            }
        }

        for(int y = 0; y < sz; ++y) {
            for(int x = 0; x < sz; ++x) {
                if(!grid[y][x]) {
                    unordered_set<int> rt;
                    rt.insert(find(grid, y + 1, x));
                    rt.insert(find(grid, y, x + 1));
                    rt.insert(find(grid, y - 1, x));
                    rt.insert(find(grid, y, x - 1));
                    int tmp{1};
                    for(auto& r : rt)
                        tmp += (r == -1) ? 0 : rank[r];
                    ans = max(ans, tmp);
                }
            }
        }
        return ans;
    }
};
