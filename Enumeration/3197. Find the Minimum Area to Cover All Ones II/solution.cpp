/*  f()  : 計算最小的一個rectangle
 *  f2() : 分別從水平和垂直切割，兩個block分別使用f() 
 *  f3() : 分別從水平和垂直切割，兩個block分別使用[f(), f2()]和[f2(), f()]
 */
class Solution {
    // one rectangle
    int m, n;
    int f(vector<vector<int>>& grid, int sy, int sx, int ey, int ex) {
        int lx{100}, ly{100}, mx{0}, my{0};
        for(int y = sy; y < ey; ++y)
            for(int x = sx; x < ex; ++x) {
                if(grid[y][x]) {
                    lx = min(lx, x);
                    ly = min(ly, y);
                    mx = max(mx, x);
                    my = max(my, y);
                }
            }
        return (my - ly + 1) * (mx - lx + 1);
    }
    int f2(vector<vector<int>>& grid, int sy, int sx, int ey, int ex) {
        int rtn = 1e4;
        for(int h = 1; sy + h < ey; ++h) // seperate horizontal
            rtn = min(rtn, f(grid, sy, sx, sy + h, ex) + f(grid, sy + h, sx, ey, ex));
        for(int w = 1; sx + w < ex; ++w) // seperate vertical
            rtn = min(rtn, f(grid, sy, sx, ey, sx + w) + f(grid, sy, sx + w, ey, ex));
        return rtn;
    }
    int f3(vector<vector<int>>& grid, int sy, int sx, int ey, int ex) {
        int rtn = 1e4;
        for(int h = 1; sy + h < ey; ++h) // seperate horizontal
            rtn = min({
                        rtn
                        ,f(grid, sy, sx, sy + h, ex) + f2(grid, sy + h, sx, ey, ex)
                        ,f2(grid, sy, sx, sy + h, ex) + f(grid, sy + h, sx, ey, ex)
                        });
        for(int w = 1; sx + w < ex; ++w) // seperate vertical
            rtn = min({
                        rtn
                        ,f(grid, sy, sx, ey, sx + w) + f2(grid, sy, sx + w, ey, ex)
                        ,f2(grid, sy, sx, ey, sx + w) + f(grid, sy, sx + w, ey, ex)
                        });
        return rtn;       
    }
public:
    int minimumSum(vector<vector<int>>& grid) {
        m = grid.size(), n = grid[0].size();
        return f3(grid, 0, 0, m, n); // 3 rectangles 
    }
};
